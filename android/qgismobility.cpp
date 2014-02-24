/*
 *  This file is part of QGis Mobility
 *
 *  QGis Mobility is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  QGis Mobility is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with QGis Mobility. If not, see 
 *  <http://www.gnu.org/licenses/>.
 */


#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QStringBuilder>
#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>
#include <QtCore/QDebug>

#include <sys/types.h>
#include <unistd.h>

extern int runtime (int argc, char *argv[]);

static void setenv_from_qstring (const char *name, QString value)
{
  QByteArray byteArray = value.toUtf8();
  setenv (name, byteArray.constData(), 1);
}

static bool base_path_from_cwd (QStringList &base_path)
{
  
  /* Attempt to get the base path from the current working directory. If sensible,
     store the base path into the given list and return true, else return false and
     leave the given list as is */
  char buf[2048];
  memset (buf, 0, 2048);
  getcwd (buf, 2048);
  
  QString transformed (buf);
  int transformed_size = transformed.size ();
  bool proper = false;

  if (transformed_size > 6)
    {
      /* Reduce the string using the "/files" as character array */
      char the_files[] = "/files";
      proper = true;
      int offset = transformed_size - 6;
      for (int i = 0; i < 6; i++)
	{
	  if (the_files[i] != transformed[offset + i])
	    {
	      proper = false;
	    }
	}
    }

  if (proper) {
    base_path << transformed.left (transformed_size - 6);
  }

  return proper;
}

static QString acquire_base_path (void)
{

  /* It appears Android 4.3 (and higher) use a different, easier way to calculate
     the base path, as this is simply the current working directory minus the /files
     portion, So this procedure has a different approach for Android 4.3, by using
     getcwd with a large enough buffer.
     
     However, it is rather uneasy to discover if the proper folder is used, so this
     routine checks whether the last portion is actually /files. */

  QStringList lst;
  if (base_path_from_cwd (lst)) {
    return lst[0];
  }

  QString proc_path = "/proc/";
  QString maps_file = "/maps";

  QString pid_as_string = QString::number (getpid ());
  
  QString the_maps = proc_path % pid_as_string % maps_file;
  
  QFile file (the_maps);

  if (!file.open (QIODevice::ReadOnly | QIODevice::Text))
    {
      qDebug () << "FATAL: Don't know how to open: " << the_maps;
      exit (1);
    }

  QString base_path;

  QTextStream in (&file);
  
  QRegExp splitter ("^[^\\s]+\\s+[^\\s]+\\s+[^\\s]+\\s+[^\\s]+\\s+[^\\s]+\\s+");
  QString line;

  do
    {
      line = in.readLine ();
      
      if (line.isNull ())
	{
	  qDebug () << "FATAL: Can't determine base path";
	  exit (1);
	}

      // Find if line contains our library name (libqgismobility_android_wrap.so)
      
      QString end = line.split (splitter).last ();

      QStringList path_elements = end.split ("/");

      if (path_elements.last () == "libqgismobility.so")
	{
	  qDebug() << "Found ourselves: " << end;
	  int max_elements = path_elements.size () - 2;
	  for (int i = 0; i < max_elements; i++)
	    {
	      if (i + 1 == max_elements)
		{
		  base_path = base_path % path_elements [i];
		}
	      else
		{
		  base_path = base_path % path_elements [i] % "/";
		}
	    }
	  break;
	}
    }
  while (!line.isNull ());

  return base_path;
}

static void i18n_cpp_phase (const QString &files_path)
{
  /* Given that Java should write a language file in the files path,
     called '__language__', read it and set the LANGUAGE environment
     properly */

  QFile file (files_path % "/__language__");
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  QTextStream in (&file);
  QString line = in.readLine ();
  setenv_from_qstring ("LANGUAGE", line);
}

static void initialize_environ (const QString &base_path)
{
  QString files_path = base_path % "/files";
  QString python_home_path = files_path % "/python";
  QString library_path = base_path % "/lib";

  /* Initialize the LANGUAGE environment variable, So C++ and Python have it */
  i18n_cpp_phase (files_path);

  setenv_from_qstring ("PYTHONHOME", python_home_path);
  
  QString ld_library_path = 
    python_home_path % "/lib" % ":" %
    "/system/lib" % ":" %
    "/data/data/org.kde.necessitas.ministro/qt/lib";

  setenv_from_qstring ("LD_LIBRARY_PATH", ld_library_path);

  setenv_from_qstring ("PYTHONPATH", 
		       ld_library_path % ":" %
		       files_path % "/qgsmsystem" % ":" %
		       python_home_path % "/lib/python2.7/lib-dynload" % ":" %
		       python_home_path % "/lib/python2.7" % ":" %
		       python_home_path % "/lib/python2.7/site-packages");
  
  char *path = getenv ("PATH");
  
  setenv_from_qstring ("PATH",
		       QString(path) % ":" %
		       python_home_path % "/bin");

  setenv_from_qstring ("PREFIX_PATH", base_path);
  setenv_from_qstring ("PLUGIN_PATH", library_path);
  
}

int main (int argc, char *argv[])
{
  
  /* The idea here is to read a specific configuration file from a known
     location. It should be possible to know where we (this library) is
     located on the target device.
  */
  
  QString base_path = acquire_base_path ();
  initialize_environ (base_path);
  
  return runtime (argc, argv);
}
