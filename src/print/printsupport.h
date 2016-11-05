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

#ifndef LITTLENAVMAP_PRINTSUPPORT_H
#define LITTLENAVMAP_PRINTSUPPORT_H

#include <QCoreApplication>

class MainWindow;
class QPrinter;
class QPixmap;
class QPainter;
class QPrintPreviewDialog;
class QTextDocument;

class PrintSupport
  : public QObject
{
  Q_DECLARE_TR_FUNCTIONS(PrintSupport)

public:
  PrintSupport(MainWindow *parent);
  virtual ~PrintSupport();

  void printMap();
  void printFlightplan();

  static void drawWatermark(const QPoint& pos, QPainter *painter);
  static void drawWatermark(const QPoint& pos, QPixmap *pixmap);

private:
  void paintRequestedMap(QPrinter *printer);
  void paintRequestedFlightplan(QPrinter *printer);
  static void drawWatermarkInternal(const QPoint& pos, QPainter *painter);
  QPrintPreviewDialog *buildPreviewDialog(const QString& printFileName);
  void deletePreviewDialog(QPrintPreviewDialog *print);

  QTextDocument *flightPlanDocument = nullptr;

  QPixmap *mapScreen = nullptr;
  MainWindow *mainWindow;

};

#endif // LITTLENAVMAP_PRINTSUPPORT_H