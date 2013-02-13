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

#include <QgsMobilityConfigure.h>

QgsMobilityConfigure::QgsMobilityConfigure (void)
{
}


static QMap<QString, QString> _systemDictionary;

static QString system_dictionary_entry (QString);

bool
QgsMobilityConfigure::set_preconfiguration_dictionary
(QMap<QString, QString> dict)
{
  if (_systemDictionary.empty ())
    {
      _systemDictionary = dict;
      return true;
    }
  else
    {
      return false;
    }
}

QString QgsMobilityConfigure::default_plugin_path (void)
{
  return PLUGIN_PATH;
}

QString QgsMobilityConfigure::default_prefix_path (void)
{
  return PREFIX_PATH;
}

static QString system_dictionary_entry (QString key)
{
  if (_systemDictionary.empty ())
    {
      return "";
    }
  else
    {
      return _systemDictionary[key];
    }
}

QString QgsMobilityConfigure::plugin_path (void)
{
  return system_dictionary_entry("plugin_path");
}

QString QgsMobilityConfigure::prefix_path (void)
{
  return system_dictionary_entry("prefix_path");
}

QString QgsMobilityConfigure::load_path (void)
{
  return system_dictionary_entry("load_path");
}

QMap<QString, QString> QgsMobilityConfigure::preconfiguration (void)
{
  return _systemDictionary;
}
