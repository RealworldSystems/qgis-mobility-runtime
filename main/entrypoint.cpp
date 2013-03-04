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

#include "config.h"

#define QGISDEBUG

#include <string.h>

#include <Python.h>
#include <QDebug>
#include <QtGui/QMessageBox>
#include <QtCore/QThread>

#include <QtCore/QStringList>
#include <QtCore/QLibrary>
#include <QtCore/QString>
#include <QtCore/QStringBuilder>

#include <qgsapplication.h>
#include <qgsproject.h>
#include <qgsproviderregistry.h>
#include <qgsmaplayerregistry.h>
#include <qgsvectordataprovider.h>

#include <QgsMobilityConfigure.h>
#include <QgsMobilityWorker.h>


PyMODINIT_FUNC initqgismobility (void);


static inline void 
QgsMobilityInitialization (const QString & prefix_path,
			   const QString & plugin_path);

static inline void checkedImportModule (const char *name);
static inline void configure (void);
static inline void preConfigure (int argc, char *argv[]);

/*
 * The initialization routine is responsible for delegating the necessary
 * initialization options to QGis Core. It is a replacement routine of the
 * original initialization routine.
 */
static inline void 
QgsMobilityInitialization (const QString & prefix_path,
			   const QString & plugin_path)
{
  // The prefix path is responsible for recognizing where libraries are
  // put. In normal circumstances, the configure script will set this on
  // our config.h, however, if for some reason this isn't the proper
  // location, it can be overriden using the --prefix-path option.
  
  // Besides the prefix path, it is feasible to require the need of the
  // plugin path to be specified. Normally, the plugin path is determined
  // using the configure script, however, this might need to be overridden.
  
  // Due to the dependent layout of initialization, the first thing set is the
  // QgsProviderRegistry.

  qDebug() << "Plugin Path: " << plugin_path << "\n";
  qDebug() << "Prefix Path: " << prefix_path << "\n";

  QgsProviderRegistry::instance (plugin_path);
  QgsApplication::setPrefixPath (prefix_path);
  QgsApplication::setPluginPath (plugin_path);
  QgsMapLayerRegistry::instance ();

  QgsMobilityWorker::instance ();
}

static inline QString QgmPyRepr (PyObject *object)
{
  PyObject *repr = PyObject_Repr (object);
  QString s = PyString_AsString (repr);
  Py_XDECREF (repr);
  return s;
}

static inline void QgmPyDebug (PyObject *object)
{
  if (object == 0)
    {
      qDebug() << "Object is NULL" << "\n";
    }
  else
    {
      if (PyCallable_Check (object))
	{
	  qDebug() << "Next object is callable"  << "\n";
	}
      
      qDebug() << QgmPyRepr (object) << "\n";
    }
}


static inline void checkedImportModule (const char *name)
{
  qDebug () << "Attempting import of " << name << "\n";
  PyObject *config_module = PyImport_ImportModule (name);
  PyObject *etype, *evalue, *etraceback;
  PyErr_Fetch (&etype, &evalue, &etraceback);
  if (evalue != NULL)
    { /* Should not reach */
      QgmPyDebug (evalue);
      QgmPyDebug (etraceback);
    }

  Py_XDECREF (config_module);
}

static inline void configure (void)
{
  checkedImportModule ("config.target");
}

static inline void preConfigure (void)
{
  initqgismobility ();
  checkedImportModule ("preconfig");
}

#if defined (ANDROID)

class AndroidTCPConsoleThread : public QThread
{
public:
  AndroidTCPConsoleThread (void)
  {
    this->setTerminationEnabled (true);
  }
  
  void run (void)
  {
    checkedImportModule ("interactivenetconsole.boot");
  }
};

static AndroidTCPConsoleThread *a_thread;

static inline void run_interactivenetconsole (void)
{
  
  a_thread = new AndroidTCPConsoleThread ();
  a_thread->start ();

  /*  QObject::connect(QApplication::instance(), SIGNAL (aboutToQuit ()),
      a_thread, SLOT (terminate ()));*/
}

static inline void quit_interactivenetconsole (void)
{
  a_thread->quit ();
  a_thread->wait ();
  delete a_thread;
}

#endif


int runtime (int argc, char * argv[])
{
  QApplication app(argc, argv);
  
  setenv ("AUTOCONF_PROJECT_CODE_PATH", PROJECT_CODE_PATH, 1);

  //Py_SetProgramName(argv[0]);
  Py_Initialize();
#if defined (ANDROID)
  char *android_argv[3];
  android_argv[0] = argv[0];
  QString prefix_path = "--prefix-path=" % QString(getenv("PREFIX_PATH"));
  QString plugin_path = "--plugin-path=" % QString(getenv("PLUGIN_PATH"));

  qDebug() << "Prefix Path: " << prefix_path;
  qDebug() << "Plugin Path: " << plugin_path;

  char *alloca_prefix = new char[prefix_path.size () + 1];
  char *alloca_plugin = new char[plugin_path.size () + 1];

  memset (alloca_prefix, 0, prefix_path.size () + 1);
  memset (alloca_plugin, 0, plugin_path.size () + 1);

  QByteArray prefix_ba = prefix_path.toUtf8();
  QByteArray plugin_ba = plugin_path.toUtf8();

  memcpy(alloca_prefix, prefix_ba.constData (), prefix_path.size ());
  memcpy(alloca_plugin, plugin_ba.constData (), plugin_path.size ());

  qDebug() << "Allocated Prefix" << QString(alloca_prefix);
  qDebug() << "Allocated Plugin" << QString(alloca_plugin);

  android_argv[1] = alloca_prefix;
  android_argv[2] = alloca_plugin;
  
  PySys_SetArgv(3, android_argv);
#else
  PySys_SetArgv(argc, argv);
  
#endif
  qDebug() << "Estimated python path: " << QString(getenv("PYTHONPATH"));
  PySys_SetPath(getenv("PYTHONPATH"));
  PyEval_InitThreads();

  preConfigure ();

  QgsMobilityConfigure config;
  
  QgsMobilityInitialization (config.prefix_path (), config.plugin_path ());

  configure ();

#if defined (ANDROID)
  run_interactivenetconsole ();
#endif
  app.exec ();
  
#if defined (ANDROID)
  quit_interactivenetconsole ();
#endif
  Py_Finalize();

#if defined (ANDROID)
  delete alloca_prefix;
  delete alloca_plugin;
#endif

  return 0;

}
