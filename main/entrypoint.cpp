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
#include <QFileInfo>
#include <QMap>
#include <QList>

#include <qgsapplication.h>
#include <qgsproject.h>
#include <qgsmaplayerregistry.h>
#include <qgsmaprenderer.h>
#include <qgsproviderregistry.h>
#include <qgsvectordataprovider.h>

#include <QgsMobilityApplicationFrame.h>

/*
 * TODO: probably best is to not use QgsApplication, but need to figure out
 *       what init() does and doesn't. It's a static method, so no subclassing
 *       available.
 */

class QgsMobilityApplication : public QgsApplication
{
  
public:
  QgsMobilityApplication (int & argc, char ** argv, bool GUIenabled) :
    QgsApplication (argc, argv, GUIenabled, "")
  {
    setPrefixPath("/usr");
    setPluginPath("/usr/lib/qgis/plugins");
  }

};

int runtime(int argc, char *argv[])
{

  // Given a mobile application, we need to get the following things sorted:
  // - The Python home path [PYTHONHOME] (where do the normal python things live)
  // - The Python path [PYTHONPATH] (where do the Qt, QGis, Python and other 
  //   libraries live)
  // - The LD_LIBRARY_PATH (where are all necessary plugin libraries)
  // - The PATH (where can we use certain executables)

  QgsProviderRegistry::instance("/usr/lib/qgis/plugins");

  QgsMobilityApplication app(argc, argv, true);
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  PySys_SetArgv(argc, argv);

  QgsMobilityApplicationFrame frame;
  frame.showFullScreen();
  //frame.show();

  // Should invoke reset of map canvas, map registry and legend
  QgsProject *project = QgsProject::instance();
  
  QStringList providerList =  QgsProviderRegistry::instance()->providerList();
  for(QStringList::iterator iter = providerList.begin(); iter != providerList.end(); iter++)
    {
      qDebug() << *iter;
    }

  // TODO: Need to get this done from an interface (and obviously not hardcoded like this!
  QDir dir("samples/centercontrol");
  QFileInfo fileInfo = QFileInfo(dir.absoluteFilePath ("centercontrol.qgs"));
  qDebug() << project->read(fileInfo);
  qDebug() << project->error();
  

  //PySys_SetPath(PYTHON_PATH);
  //FILE *fp = fopen(PYQT_MAIN, "r");
  //PyRun_SimpleFile(fp, PYQT_MAIN);
  
  PyRun_SimpleString("print 'Hello World'\n");
  
  Py_Finalize();
  app.exec();

  //exit(0);
  return 0;
}
