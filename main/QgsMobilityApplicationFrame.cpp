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

#include "QgsMobilityApplicationFrame.h"

#include <QMap>
#include <QList>
#include <QString>
#include <QDebug>
#include <QtCore/qmath.h>

#include <QPainter>
#include <QTransform>
#include <QDomDocument>

#include <qgsmaplayer.h>
#include <qgsmaplayerregistry.h>
#include <qgsmaprenderer.h>
#include <qgsproject.h>


namespace {
  class SmoothPainter : public QPainter
  {
  public:
    bool begin (QPaintDevice *device)
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
  };
}


QgsMobilityApplicationFrame::QgsMobilityApplicationFrame (void) : 
  QMainWindow (),
  mPixmap_p (0),
  mRotate (0)
{
  connect (QgsProject::instance(), SIGNAL (readProject (const QDomDocument &)),
	   this,                   SLOT (readProject (const QDomDocument &)));

  connect (&mTimer, SIGNAL (timeout ()),
	   this,    SLOT   (updateRotate ()));
}


QgsMobilityApplicationFrame::~QgsMobilityApplicationFrame (void)
{
  if (this->mPixmap_p) delete this->mPixmap_p;
}

void QgsMobilityApplicationFrame::readProject (const QDomDocument &doc)
{
  QDomNodeList nodes = doc.elementsByTagName( "mapcanvas" );
  if ( nodes.count() )
    {
      QDomNode node = nodes.item( 0 );
      mMapRenderer.readXML( node );
    }

  QMap<QString, QgsMapLayer*> &mapLayers = QgsMapLayerRegistry::instance()->mapLayers();
  this->setLayerSet (mapLayers.keys());
  mTimer.start(1000);
}

void QgsMobilityApplicationFrame::updateRotate (void)
{
  mRotate += 5;
  if (mRotate == 360) mRotate = 0;
  this->update();
}

void QgsMobilityApplicationFrame::resizeEvent (QResizeEvent *)
{
  int diagonal = this->diagonal ();
  this->mSize = QSize (diagonal, diagonal); 
  this->updatePixmap();
}

const QSize & QgsMobilityApplicationFrame::renderSize (void)
{
  return this->mSize;
}

int QgsMobilityApplicationFrame::diagonal (void)
{
  int screen_width = this->size().width();
  int screen_height = this->size().height();

  // 2 is added at the and for integer floor correction
  return (int) qSqrt((screen_width * screen_width) +
		     (screen_height * screen_height)) + 2;
  
}

void QgsMobilityApplicationFrame::updatePixmap (void)
{  
  // Remove the old pixmap, if it exists  
  if (this->mPixmap_p) delete this->mPixmap_p;

  // Create a pixmap and fill it with white
  this->mPixmap_p = new QPixmap (this->renderSize());
  this->mPixmap_p->fill ();

  // Set the map renderer output size
  mMapRenderer.setOutputSize(this->renderSize(), mPixmap_p->logicalDpiX ());
  
  
  SmoothPainter paint;
  paint.begin (this->mPixmap_p);
  paint.setClipRect (mPixmap_p->rect());
  mMapRenderer.render (&paint);

  paint.end ();
  this->update();
}

void QgsMobilityApplicationFrame::setLayerSet (QStringList layer_set)
{
  mMapRenderer.setLayerSet (layer_set);
}

void QgsMobilityApplicationFrame::paintEvent (QPaintEvent *event)
{
  
  if (this->mPixmap_p == NULL) { this->updatePixmap(); return; }
  
  int diagonal = this->diagonal();
  
  SmoothPainter paint;
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
  paint.drawPixmap (0, 0, *(this->mPixmap_p));
  
  paint.end ();
}
