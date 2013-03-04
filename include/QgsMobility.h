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
  
public:
  QgsMobility (void);
  bool show_main_window_stack (void);
  bool hide_main_window_stack (void);
  QString load_project (QString);
  bool rotate (int);
  int rotation (void);
  qreal azimuth (void) const;
};

#endif // _QGS_MOBILITY_H
