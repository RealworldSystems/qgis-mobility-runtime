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

#include <Python.h>
#include <QDebug>
#include <QtGui/QMessageBox>
#include <QtCore/QThread>

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
      qDebug() << "Object is NULL";
    }
  else
    {
      if (PyCallable_Check (object))
	{
	  qDebug() << "Next object is callable";
	}
      
      qDebug() << QgmPyRepr (object);
    }
}


static inline void checkedImportModule (const char *name)
{
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

static inline void preConfigure (int argc, char *argv[])
{
  PySys_SetArgv(argc, argv);
  initqgismobility ();
  checkedImportModule ("preconfig");
}



int runtime (int argc, char * argv[])
{
  // Given a mobile application, we need to get the following things sorted:
  // - The Python home path [PYTHONHOME] (where do the normal python things live)
  // - The Python path [PYTHONPATH] (where do the Qt, QGis, Python and other 
  //   libraries live)
  // - The LD_LIBRARY_PATH (where are all necessary plugin libraries)
  // - The PATH (where can we use certain executables)

  QApplication app(argc, argv);
  
  setenv ("PYTHONPATH", PRECONFIG_PATH, 1);
  setenv ("AUTOCONF_PROJECT_CODE_PATH", PROJECT_CODE_PATH, 1);

  Py_SetProgramName(argv[0]);
  Py_Initialize();
  preConfigure (argc, argv);

  QgsMobilityConfigure config;
  
  QgsMobilityInitialization (config.prefix_path (), config.plugin_path ());

  configure ();

  PyRun_InteractiveLoop (stdin, "<stdin>");
  
  Py_Finalize();
  return 0;
}
