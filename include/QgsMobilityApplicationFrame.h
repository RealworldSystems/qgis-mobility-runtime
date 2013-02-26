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

#include <QtCore/QMutex>
#include <QtGui/QWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QGridLayout>

class QgsMobilityApplicationFrame : public QMainWindow
{
Q_OBJECT

public slots:
  void retrieveImage (const QImage &);

public:
  QgsMobilityApplicationFrame (void);
  void paintEvent (QPaintEvent *);
  const QSize & renderSize (void);
  void rotate (int);
  int rotation (void);

protected:
  void resizeEvent (QResizeEvent *);
  int diagonal (void);

private:
  int mRotate;
  QSize mSize;
  QImage mImage;
  QMutex mMutex;
  
  QImage copyImage (void);
};
  
#endif
