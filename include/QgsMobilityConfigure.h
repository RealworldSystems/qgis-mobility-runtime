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

#if !defined (_QGS_MOBILITY_CONFIGURE_H)
#define _QGS_MOBILITY_CONFIGURE_H

#include <QObject>
#include <QMap>
#include <QString>

class QgsMobilityRouter;

class QgsMobilityConfigure : public QObject
{
  Q_OBJECT

public:
  QgsMobilityConfigure (void);
  bool set_preconfiguration_dictionary (QMap<QString, QString>);
  QString default_plugin_path (void);
  QString default_prefix_path (void);
  QString plugin_path (void);
  QString prefix_path (void);
  QString load_path (void);
  QMap<QString, QString> preconfiguration (void);
  bool route (QgsMobilityRouter);
};


#endif // _QGS_MOBILITY_CONFIGURE_H
