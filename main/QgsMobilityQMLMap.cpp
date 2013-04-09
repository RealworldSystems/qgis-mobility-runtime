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


#include <Qt>

#include <QtCore/QTimer>
#include <QtCore/QString>
#include <QtCore/qmath.h>
#include <QtCore/QMutexLocker>
#include <QtCore/QPointF>
#include <QtCore/QDateTime>
#include <QtGui/QTransform>
#include <QtGui/QPainter>
#include <QtGui/QGraphicsSceneMouseEvent>

#include <QtCore/QDebug>

#include <complex>

static const qreal PI = 2 * qAcos(0.0);
static QgsMobilityQMLMap *defaultQMLMap = 0;

QgsMobilityQMLMap::QgsMobilityQMLMap (void) : 
  QDeclarativeItem (),
  mRotate (0),
  mMouseMovePoint (0, 0),
  mMutex (QMutex::Recursive)
{
  //setCacheMode (QGraphicsItem::DeviceCoordinateCache);
  setFlag (QGraphicsItem::ItemHasNoContents, false);
  setFlag (QGraphicsItem::ItemIsMovable, true);
  setSmooth (true);
  this->mMousePressAndHoldTimer.setSingleShot (true);
  this->mMousePressAndHoldTimer.setInterval (2000);
  
  connect (&(QgsMobilityWorker::instance ()), SIGNAL (ready (const QImage &)),
	   this, SLOT (retrieveImage (const QImage &)));

  connect (QgsMobility::instance (), SIGNAL (rotateView (int)),
	   this, SLOT (rotate (int)));

  connect (this, SIGNAL (mapRendered ()),
	   QgsMobility::instance (), SIGNAL (rendered ()));

  connect (&(this->mMousePressAndHoldTimer), SIGNAL (timeout ()),
	   this, SLOT (mousePressAndHold ()));

  setAcceptedMouseButtons (Qt::LeftButton | Qt::MidButton | Qt::RightButton);
  setAcceptTouchEvents (true);
  setAcceptHoverEvents (true);

  if (!::defaultQMLMap) { ::defaultQMLMap = this; }
}

QgsMobilityQMLMap::~QgsMobilityQMLMap (void)
{
  if (::defaultQMLMap == this) { ::defaultQMLMap = 0; }
}

QgsMobilityQMLMap *QgsMobilityQMLMap::getDefault (void)
{
  return ::defaultQMLMap;
}

qreal QgsMobilityQMLMap::counterCornerPolar (void)
{
  return 0.0 - this->cornerPolar ();
}

qreal QgsMobilityQMLMap::cornerPolar (void)
{
  return ((qreal) mRotate) / 180 * PI;
}

qreal QgsMobilityQMLMap::counterScreenOffset (int range)
{
  int diagonal = this->diagonal ();
  return ((qreal)diagonal - (qreal)range) / 2;
}

qreal QgsMobilityQMLMap::screenOffset (int range)
{
  int diagonal = this->diagonal ();
  return ((qreal)diagonal - (qreal)range) / 2;
}


QPointF QgsMobilityQMLMap::counterViewportOffset (const QPointF & viewport)
{
  QRectF bounds = this->boundingRect ();
  qDebug() << "Viewport x:" << viewport.x() << "y:" << viewport.y();
  return QPointF (this->counterScreenOffset (bounds.width ())  + viewport.x (),
		  this->counterScreenOffset (bounds.height ()) + viewport.y ());
}

QPointF QgsMobilityQMLMap::viewportOffset (const QPointF &viewport)
{
  QRectF bounds = this->boundingRect ();
  return QPointF (viewport.x () - this->screenOffset (bounds.width ()),
		  viewport.y () - this->screenOffset (bounds.height ()));
}

void QgsMobilityQMLMap::mousePressEvent (QGraphicsSceneMouseEvent *event)
{
  this->mMousePressAndHoldPoint = event->pos ();
  this->mMouseCanMoveMap = true;
  this->mMousePressAndHoldTimer.start ();
  qDebug () << "Pressing";
  QDeclarativeItem::mousePressEvent (event);
}

void QgsMobilityQMLMap::mousePressAndHold (void)
{
  this->mMouseCanMoveMap = false;
  QPointF current = calculateCounterPosition (this->mMousePressAndHoldPoint);
  QgsMobility::instance()->mapClickAndHoldByPixels (current.x (), current.y ());
  
  qDebug() << "Press And Hold";
}

void QgsMobilityQMLMap::mouseMoveEvent (QGraphicsSceneMouseEvent *event)
{
  if (this->mMouseCanMoveMap)
    {
      this->mMousePressAndHoldTimer.stop ();
      mMouseMovePoint = (event->pos () - event->buttonDownPos (Qt::LeftButton));
      this->update ();
    }
}

QPointF QgsMobilityQMLMap::calculateCounterPosition (const QPointF & position)
{
  qreal r = (qreal)(this->diagonal ()) / 2.0;
  QPointF countered = this->counterViewportOffset (position);  
  QPointF current(countered.x() - r, countered.y() - r);
  qreal corner = this->counterCornerPolar ();
  qDebug() << "Corner Polar:" << corner;
  std::complex<qreal> correction_factor (qCos (corner), qSin (corner));
  std::complex<qreal> current_complex = 
    std::complex<qreal> (current.x (), current.y ()) * correction_factor;
  
  qDebug() << "Current w/ offset x:" << current.x() << "y:" << current.y();
  qDebug() << "Current complex x:" << current_complex.real() << 
    "y:" << current_complex.imag();

  return QPointF(current_complex.real() + r, current_complex.imag() + r);
  
}

void QgsMobilityQMLMap::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  this->mMousePressAndHoldTimer.stop ();

  if (!this->mMouseCanMoveMap) { return; }
  
  QPointF current = this->calculateCounterPosition (event->pos ());

  qDebug() << "New Current w/ offset x:" << current.x() << "y:" << current.y();


  if (mMouseMovePoint.x () != 0 || mMouseMovePoint.y () != 0)
    {
      QPointF start = this->calculateCounterPosition (event->buttonDownPos (Qt::LeftButton));
      QgsMobility::instance()->panByPixels (start.x (), 
					    start.y (),
					    current.x (),
					    current.y ());
    }
  else
    {
      QgsMobility::instance()->mapClickedByPixels (current.x (), 
						   current.y ());
    }
}

QPointF QgsMobilityQMLMap::renderPixelToMapPixel (const QPointF &point)
{
  QPointF current = this->viewportOffset (point);
  qreal corner = this->cornerPolar ();
  std::complex<qreal> correction_factor (qCos (corner), qSin (corner));
  std::complex<qreal> current_complex = 
    std::complex<qreal> (current.x (), current.y ()) * correction_factor;
  return QPointF (current_complex.real (), current_complex.imag ());
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
  mMouseMovePoint.setX(0);
  mMouseMovePoint.setY(0);
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
  
  QTransform transform;

  int height_of_window = bounds.height ();
  int height_delta = diagonal - height_of_window;
  int shift_up = height_delta / 2;

  int width_of_window = bounds.width ();
  int width_delta = diagonal - width_of_window;
  int shift_left = width_delta / 2;

  transform.translate(- shift_left + mMouseMovePoint.x (), - shift_up + mMouseMovePoint.y ());
  transform.translate(diagonal / 2, diagonal / 2);
  transform.rotate(mRotate);
  transform.translate(- (diagonal / 2), - (diagonal / 2));
  
  paint->setTransform(transform);
  paint->drawImage (0, 0, image);
  
  emit mapRendered ();
}
