#include <Python.h>
#include <QtGui/QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{

  // Given a mobile application, we need to get the following things sorted:
  // - The Python home path [PYTHONHOME] (where do the normal python things live)
  // - The Python path [PYTHONPATH] (where do the Qt, QGis, Python and other 
  //   libraries live)
  // - The LD_LIBRARY_PATH (where are all necessary plugin libraries)
  // - The PATH (where can we use certain executables)


  QApplication app(argc, argv);
  Py_SetProgramName(argv[0]);
  Py_Initialize();
  PySys_SetArgv(argc, argv);
  //PySys_SetPath(PYTHON_PATH);
  //FILE *fp = fopen(PYQT_MAIN, "r");
  //PyRun_SimpleFile(fp, PYQT_MAIN);
  
  PyRun_SimpleString("print 'Hello World'\n");
  
  Py_Finalize();
  //app.exec();
  
  //exit(0);
  return 0;
}
