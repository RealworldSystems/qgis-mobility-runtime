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
#include <QgsMobilityApplicationFrame.h>
#include <QgsMobilityWorker.h>

#include <QString>
#include <QtCore/qmath.h>
#include <QtCore/QMutexLocker>
#include <QTransform>

QgsMobilityApplicationFrame::QgsMobilityApplicationFrame (void) : 
  QMainWindow (),
  mRotate (0)
{
  connect (&(QgsMobilityWorker::instance ()), SIGNAL (ready (const QImage &)),
	   this, SLOT (retrieveImage (const QImage &)));
}

QImage QgsMobilityApplicationFrame::copyImage (void)
{
  QMutexLocker locker (&this->mMutex);
  return this->mImage;
}

void QgsMobilityApplicationFrame::retrieveImage (const QImage &image)
{
  QMutexLocker locker (&this->mMutex);
  this->mImage = image;
  this->update ();
}

void QgsMobilityApplicationFrame::rotate (int rotation)
{
  mRotate = rotation;
  this->update();
}

int QgsMobilityApplicationFrame::rotation (void)
{
  return mRotate;
}

void QgsMobilityApplicationFrame::resizeEvent (QResizeEvent *)
{
  int diagonal = this->diagonal ();
  QSize size(diagonal, diagonal);
  QgsMobilityWorker::instance().setSize(size);
}

int QgsMobilityApplicationFrame::diagonal (void)
{
  int screen_width = this->size().width();
  int screen_height = this->size().height();

  return (int) qCeil (qSqrt ((screen_width * screen_width) +
			     (screen_height * screen_height)));
  
}

void QgsMobilityApplicationFrame::paintEvent (QPaintEvent *event)
{
  
  QImage image = this->copyImage ();
 
  int diagonal = this->diagonal();
  
  QgsMobilityPainter paint;
  paint.begin (this);
  
  QTransform transform;

  int height_of_window = this->size().height();
  int height_delta = diagonal - height_of_window;
  int shift_up = height_delta / 2;

  int width_of_window = this->size().width();
  int width_delta = diagonal - width_of_window;
  int shift_left = width_delta / 2;

  transform.translate(- shift_left, - shift_up);
  transform.translate(diagonal / 2, diagonal / 2);
  transform.rotate(mRotate);
  transform.translate(- (diagonal / 2), - (diagonal / 2));
  
  paint.setTransform(transform);
  paint.drawImage (0, 0, image);
  
  paint.end ();
}
