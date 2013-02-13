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

#include <QtCore/QFileInfo>

#include <QgsMobility.h>
#include <QgsMobilityApplicationFrame.h>
#include <QgsMobilityWorker.h>

#include <qgsproject.h>

static QgsMobilityApplicationFrame *frame = 0;

static void removeApplicationFrame (void)
{
  if (::frame != 0) delete ::frame;
}

QgsMobility::QgsMobility (void)
{
  if (::frame == 0)
    {
      ::frame = new QgsMobilityApplicationFrame;
      ::frame->setWindowFlags(Qt::FramelessWindowHint);
      atexit (removeApplicationFrame);
    }
}

bool QgsMobility::show_main_window_stack (void)
{
  if (::frame == 0) return false;
  ::frame->showFullScreen ();
  return true;
}

bool QgsMobility::hide_main_window_stack (void)
{ 
  if (::frame == 0) return false;
  ::frame->hide ();
  return true;
}

QString QgsMobility::load_project (QString projectfile)
{
  QgsProject *project = QgsProject::instance ();
  QFileInfo fileInfo = QFileInfo (projectfile);
  project->read (fileInfo);
  QString error = project->error ();
  return error;
}


bool QgsMobility::rotate (int rotation)
{
  if (::frame == 0) return false;
  ::frame->rotate (rotation);
  return true;
}

int QgsMobility::rotation (void)
{
  return ::frame->rotation ();
}
