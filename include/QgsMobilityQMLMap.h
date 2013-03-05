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


#if !defined (_QGS_MOBILITY_QML_MAP)
#define _QGS_MOBILITY_QML_MAP

#include <QtCore/QMutex>
#include <QtDeclarative/QDeclarativeItem>

class QgsMobilityQMLMap : public QDeclarativeItem
{
Q_OBJECT

public slots:
  void retrieveImage (const QImage &);
  void rotate (int);
  
public:
  QgsMobilityQMLMap (void);
  void paint (QPainter *, const QStyleOptionGraphicsItem *, QWidget *);
  const QSize & renderSize (void);


protected:
  void geometryChanged (const QRectF &, const QRectF &);
  //void resizeEvent (QResizeEvent *);
  int diagonal (void);

private:
  int mRotate;
  QSize mSize;
  QImage mImage;
  QMutex mMutex;
  
  QImage copyImage (void);
};
  
#endif
