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
#include <QgsMobilityWorker.h>
#include <qgsproject.h>
#include <qgspoint.h>


static QgsMobility * instance = 0;

QgsMobility * QgsMobility::instance (void)
{
  if (::instance == 0)
    {
      ::instance = new QgsMobility ();
    }
  return ::instance;
}

QgsMobility::QgsMobility (void)
{
}


QString QgsMobility::load_project (QString projectfile)
{
  QgsProject *project = QgsProject::instance ();
  QFileInfo fileInfo = QFileInfo (projectfile);
  project->read (fileInfo);
  QString error = project->error ();
  return error;
}


int QgsMobility::rotate (int rotation)
{
  rotation = rotation % 360;
  if (rotation > 180) { rotation -= 360; }
  if (rotation <= -180) { rotation += 360; }

  emit rotateView (rotation);
  return rotation;
}

bool QgsMobility::panByPixels (int start_x, int start_y, int end_x, int end_y)
{
  if (start_x != end_x || start_y != end_y)
    {
      emit panMapByPixels (start_x, start_y, end_x, end_y);
      return true;
    }
  else
    {
      return false;
    }
}

void QgsMobility::mapClickAndHoldByPixels (int x, int y)
{
  QgsPoint point = QgsMobilityWorker::instance().pixelToCoordinate(x, y);
  emit clickAndHold (point.x (), point.y ());
}

void QgsMobility::mapClickedByPixels (int x, int y)
{
  QgsPoint point = QgsMobilityWorker::instance().pixelToCoordinate(x, y);
  emit clicked (point.x (), point.y ());
}

void QgsMobility::scale (int scale)
{
  emit scaleMap (scale);
}
