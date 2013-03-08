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

#if !defined (_QGS_MOBILITY_WORKER_H)
#define _QGS_MOBILITY_WORKER_H

#include <QtCore/QSize>
#include <QtCore/QSemaphore>
#include <QtCore/QMutex>
#include <QtCore/QThread>

#include <QtXml/QDomDocument>

#include <qgsmaprenderer.h>
#include <qgsproject.h>


class QgsMobilityWorker;

class QgsMobilityProjectWorker : public QObject
{
  Q_OBJECT
  
  friend class QgsMobilityWorker;

public slots:
  void readProject (const QDomDocument &);
  void panMapByPixels (int start_x, int start_y, int end_x, int end_y);
  void scaleMap (int);
  
private:
  QgsMobilityProjectWorker (QgsMobilityWorker *);
  QgsMobilityWorker *mWorker_p;
  QgsMapRenderer &renderer (void);
  void reset (void);
  void moveExtent (double offset_x, double offset_y);
  void setExtent (const QgsRectangle &);
};

class QgsMobilityWorker : public QObject
{
  Q_OBJECT

  friend class QgsMobilityProjectWorker;

public slots:
  void doWork (void);

signals:
  void ready (const QImage &);

public:
  void setSize (const QSize &);
  void reset (void);
  void halt (void);
  QgsPoint pixelToCoordinate (int, int);
  QgsPoint centerCoordinate (void);
  
  static QgsMobilityWorker &instance (void);
  static void destroy (void);

private:
  QgsMobilityWorker (void);
  ~QgsMobilityWorker (void);
  struct Data
  {
    QSize size;
    
    Data (void);
  };

  QSemaphore mSemaphore;
  QMutex mMutex;
  Data mData;
  QgsMapRenderer mRenderer;
  QThread mThread;
  bool mHalt;

  void init (void);
  Data getDataCopy (void);
};

#endif // _QGS_MOBILITY_WORKER_H
