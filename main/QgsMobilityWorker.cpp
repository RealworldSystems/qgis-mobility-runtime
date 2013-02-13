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

#include <qgsmaplayerregistry.h>

#include <QgsMobilityWorker.h>
#include <QgsMobilityPainter.h>

#include <QtCore/QMutexLocker>
#include <QtCore/QStringList>
#include <QtXml/QDomNodeList>

static QgsMobilityProjectWorker *projectWorker_p = 0;
static QgsMobilityWorker *worker_p = 0;

QgsMobilityWorker::QgsMobilityWorker (void) :
  mSemaphore (0),
  mHalt (false),
  mMutex (QMutex::Recursive) { }

QgsMobilityWorker::~QgsMobilityWorker (void)
{
  this->halt();
}

QgsMobilityProjectWorker::QgsMobilityProjectWorker
(QgsMobilityWorker *worker_p) :
  mWorker_p (worker_p) {}

QgsMobilityWorker::Data::Data (void) :
  size (0, 0) { }



QgsMobilityWorker &QgsMobilityWorker::instance (void)
{
  if (::worker_p == 0)
    {
      ::worker_p = new QgsMobilityWorker ();
      atexit (QgsMobilityWorker::destroy);
      ::projectWorker_p = new QgsMobilityProjectWorker(::worker_p);
      ::worker_p->init ();
    }
  
  return *(::worker_p);
}

void QgsMobilityWorker::destroy (void)
{
  delete ::projectWorker_p;
  delete ::worker_p;
}

void QgsMobilityWorker::init (void)
{
  connect (QgsProject::instance(), SIGNAL (readProject (const QDomDocument &)),
	   ::projectWorker_p,      SLOT (readProject (const QDomDocument &)));

  connect (&(this->mThread), SIGNAL (started ()), 
	   this,             SLOT (doWork ()));
  
  this->moveToThread (&(this->mThread));
  this->mThread.start ();
}

void QgsMobilityProjectWorker::readProject (const QDomDocument &doc)
{
  QMutexLocker locker (&(this->mWorker_p->mMutex));

  QgsMapRenderer &renderer = this->mWorker_p->mRenderer;
  QDomNodeList nodes = doc.elementsByTagName( "mapcanvas" );
  if ( nodes.count() )
    {
      QDomNode node = nodes.item( 0 );
      renderer.readXML( node );
    }

  QStringList list = QgsMapLayerRegistry::instance()->mapLayers().keys();
  renderer.setLayerSet (list);
  this->mWorker_p->reset ();
}


void QgsMobilityWorker::setSize (const QSize &size)
{
  QMutexLocker locker (&(this->mMutex));
  this->mData.size = size;
  this->reset ();
}

void QgsMobilityWorker::reset (void)
{
  QMutexLocker locker (&(this->mMutex));
  if (!mSemaphore.available ())
    {
      mSemaphore.release ();
    }
}

void QgsMobilityWorker::halt (void)
{
  this->mHalt = true; /* Boolean assignment is atomic */
  this->mSemaphore.release ();
  this->mThread.exit ();
}

QgsMobilityWorker::Data QgsMobilityWorker::getDataCopy (void)
{
  QMutexLocker locker (&(this->mMutex));
  return this->mData;
}

void QgsMobilityWorker::doWork (void)
{
  do
    {
      mSemaphore.acquire ();
      
      /* If halt is set, work is done */
      if (! this->mHalt)
	{
	  Data data = this->getDataCopy ();
	  QImage image (data.size, QImage::Format_ARGB32);
	  
	  if (data.size.width () && data.size.height ())
	    {
	      image.fill (QColor (255, 255, 255).rgb ());
	      this->mRenderer.setOutputSize (data.size, 96);
	      QgsMobilityPainter paint;
	      paint.begin (&image);
	      paint.setClipRect (image.rect ());
	      this->mRenderer.render (&paint);
	      paint.end ();
	    }
  	  emit ready (image);
	}
    }
  while (! this->mHalt);
}
