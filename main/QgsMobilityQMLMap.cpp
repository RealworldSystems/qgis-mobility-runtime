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

#include <QgsMobilityQMLMap.h>
#include <QgsMobilityPainter.h>
#include <QgsMobilityWorker.h>
#include <QgsMobility.h>

#include <QtCore/QString>
#include <QtCore/qmath.h>
#include <QtCore/QMutexLocker>
#include <QtGui/QTransform>
#include <QtGui/QPainter>

#include <QtCore/QDebug>


QgsMobilityQMLMap::QgsMobilityQMLMap (void) : 
  QDeclarativeItem (),
  mRotate (0),
  mMutex (QMutex::Recursive)
{
  //setCacheMode (QGraphicsItem::DeviceCoordinateCache);
  setFlag (QGraphicsItem::ItemHasNoContents, false);
  
  connect (&(QgsMobilityWorker::instance ()), SIGNAL (ready (const QImage &)),
	   this, SLOT (retrieveImage (const QImage &)));

  connect (QgsMobility::instance (), SIGNAL (rotateView (int)),
	   this, SLOT (rotate (int)));
}

QImage QgsMobilityQMLMap::copyImage (void)
{
  QMutexLocker locker (&this->mMutex);
  return this->mImage;
}

void QgsMobilityQMLMap::retrieveImage (const QImage &image)
{
  QMutexLocker locker (&this->mMutex);
  this->mImage = image;
  qDebug() << "Call Update";
  this->update (this->boundingRect ());
  
}

void QgsMobilityQMLMap::rotate (int rotation)
{
  QMutexLocker locker (&this->mMutex);
  mRotate = rotation;
  this->update (this->boundingRect ());
}

void QgsMobilityQMLMap::geometryChanged (const QRectF & n, const QRectF &)
{
  int diagonal = this->diagonal ();
  QgsMobilityWorker::instance().setSize(QSize(diagonal, diagonal));
}

int QgsMobilityQMLMap::diagonal (void)
{
  QMutexLocker locker (&this->mMutex);

  QRectF bounds = this->boundingRect ();
  int screen_width = bounds.width ();
  int screen_height = bounds.height ();

  return (int) qCeil (qSqrt ((screen_width * screen_width) +
			     (screen_height * screen_height)));
  
}

void QgsMobilityQMLMap::paint (QPainter *paint, const QStyleOptionGraphicsItem *, QWidget *)
{
  
  QImage image = this->copyImage ();
  QRectF bounds = this->boundingRect ();
  int diagonal = this->diagonal ();
  qDebug() << "diagonal: " << QString::number (diagonal);
  
  QgsMobilityPainter::setMobilityRenderHints (paint);
 
  QTransform transform;

  int height_of_window = bounds.height ();
  int height_delta = diagonal - height_of_window;
  int shift_up = height_delta / 2;

  int width_of_window = bounds.width ();
  int width_delta = diagonal - width_of_window;
  int shift_left = width_delta / 2;

  transform.translate(- shift_left, - shift_up);
  transform.translate(diagonal / 2, diagonal / 2);
  transform.rotate(mRotate);
  transform.translate(- (diagonal / 2), - (diagonal / 2));
  
  paint->setTransform(transform);
  paint->drawImage (0, 0, image);
  
}
