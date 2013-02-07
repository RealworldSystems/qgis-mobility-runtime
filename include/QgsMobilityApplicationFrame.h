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


#if !defined (MY_TEST_WINDOW_H)
#define MY_TEST_WINDOW_H

#include <QList>

#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <QtXml/QDomDocument>
#include <QTimer>

#include <qgsmaprenderer.h>
#include <qgsmaplayer.h>

class QgsMobilityApplicationFrame : public QMainWindow
{
Q_OBJECT

public slots:
  void readProject (const QDomDocument & doc);
  void updateRotate ();

public:
  QgsMobilityApplicationFrame (void);
  ~QgsMobilityApplicationFrame (void);
  void paintEvent (QPaintEvent *event);
  void setLayerSet (QStringList layer_set);
  const QSize & renderSize (void);

protected:
  void resizeEvent (QResizeEvent *);
  void updatePixmap (void);
  int diagonal (void);

private:
  QgsMapRenderer mMapRenderer;
  QTimer mTimer;
  int mRotate;
  QSize mSize;
  QPixmap *mPixmap_p;
};
  
#endif
