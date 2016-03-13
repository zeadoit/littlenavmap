/*****************************************************************************
* Copyright 2015-2016 Alexander Barthel albar965@mailbox.org
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#ifndef NAVMAPWIDGET_H
#define NAVMAPWIDGET_H

#include "common/maptypes.h"

#include <marble/GeoDataLatLonAltBox.h>
#include <marble/MarbleWidget.h>

#include <QWidget>

namespace atools {
namespace geo {
class Pos;
class Rect;
}
namespace sql {
class SqlDatabase;
}
}

class QContextMenuEvent;
class MainWindow;
class MapPaintLayer;
class MapQuery;

class NavMapWidget :
  public Marble::MarbleWidget
{
  Q_OBJECT

public:
  NavMapWidget(MainWindow *parent, atools::sql::SqlDatabase *sqlDb);
  virtual ~NavMapWidget();

  void mapContextMenu(const QPoint& pos);

  void saveState();
  void restoreState();

  void showPoint(const atools::geo::Pos& pos, int zoom);
  void showRect(const atools::geo::Rect& rect);

  void changeMark(const atools::geo::Pos& pos);

  bool eventFilter(QObject *obj, QEvent *e) override;

  Marble::GeoDataCoordinates getMark() const
  {
    return mark;
  }

  void preDatabaseLoad();
  void postDatabaseLoad();

  void setTheme(const QString& theme, int index);
signals:
  void markChanged(const atools::geo::Pos& mark);
  void objectSelected(maptypes::ObjectType type, const QString& ident, const QString& region);

private:
  MainWindow *parentWindow;
  MapPaintLayer *paintLayer;
  MapQuery *mapQuery;
  atools::sql::SqlDatabase *db;
  Marble::GeoDataCoordinates mark;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual bool event(QEvent *event) override;

  void zoomHasChanged(int zoom);

  int curZoom = -1;
  Marble::GeoDataLatLonAltBox curBox;
};

#endif // NAVMAPWIDGET_H
