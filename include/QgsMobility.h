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

#if !defined (_QGS_MOBILITY_H)
#define _QGS_MOBILITY_H

#include <QtCore/QObject>
#include <QtCore/QPointF>
#include <QtGui/QImage>

class QgsMobility : public QObject
{
  Q_OBJECT
  
private:
  QgsMobility (void);

public:
  QString load_project (QString);
  int rotate (int);
  bool panByPixels (int start_x, int start_y, int end_x, int end_y);
  void scale (int);
  QPointF center (void);
  
  // Public but not visible to the python layer, as it is internal
  
  void mapClickAndHoldByPixels (int x, int y);
  void mapClickedByPixels (int x, int y);
    
  static QgsMobility * instance (void);

signals:
  
  void clickAndHold (double x, double y);
  void clicked (double x, double y);
  void ready (const QImage &);

  // Public but not visible to the python layer, as it is internal

  void rotateView (int rotation);
  void panMapByPixels (int start_x, int start_y, int end_x, int end_y);
  void scaleMap (int);
};

#endif // _QGS_MOBILITY_H
