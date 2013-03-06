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

#include <QObject>

class QgsMobility : public QObject
{
  Q_OBJECT
  
private:
  QgsMobility (void);

public:
  QString load_project (QString);
  int rotate (int);
  bool panByPixels (int start_x, int start_y, int end_x, int end_y);
    
  static QgsMobility * instance (void);

signals:
  void rotateView (int rotation);
  void panMapByPixels (int start_x, int start_y, int end_x, int end_y);

};

#endif // _QGS_MOBILITY_H
