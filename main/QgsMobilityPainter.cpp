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

#include <QgsMobilityPainter.h>

bool QgsMobilityPainter::begin (QPaintDevice *device)
{
  if (QPainter::begin (device))
    { 
      this->setRenderHint(QPainter::Antialiasing, true);
      this->setRenderHint(QPainter::HighQualityAntialiasing, true);
      this->setRenderHint(QPainter::SmoothPixmapTransform, true);
      return true;
    }
  else
    { return false; }
}