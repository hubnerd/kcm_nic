
/*
*  arrowwidget.cpp
*
*  Copyright (C) 2010 David Hubner <hubnerd@ntlworld.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*
*/

#include "arrowwidget.h"

#include <KLocale>

//QT
#include <QPaintEvent>
#include <QPainter>

ArrowWidget::ArrowWidget(QWidget *parent) :
  QWidget(parent), 
  m_arrowColor(Qt::red), 
  m_text(i18nc("Displayed when arrow widget does not know connection state", "UNKNOWN"))
{
  setWhatsThis(i18n("Shows if the network interface is connected; red for disconnected and green for connected"));
  setMinimumSize(150,50);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void ArrowWidget::paintEvent(QPaintEvent *event)
{
  int arrowHeight = 15;
  int rectHeight = this->height();
  
  int arrowY = (rectHeight / 2) - (arrowHeight / 2); 
  int arrowX = 10;
  int pointFrontPeak = 30;
  int arrowWidth = (this->width() - pointFrontPeak) - arrowX;
  
  //Set Painter
  
  QPainter painter;
  if(!painter.begin(this)) return;
  painter.setBrush(QBrush(m_arrowColor,Qt::SolidPattern));
  painter.setPen(m_arrowColor);
  painter.setRenderHint(QPainter::Antialiasing);
  
  // Arrow rect
  
  QRect box(arrowX,arrowY,arrowWidth,arrowHeight);
  painter.drawRect(box);
  
  // Arrow End
  
  int rectEndX = (arrowWidth + arrowX);
  int pointTopPeak = 20;
  int pointBottomPeak = 20;
  
  const QPointF points[5] = {
    QPointF(rectEndX, arrowY),
    QPointF(rectEndX, arrowY - pointTopPeak),
    QPointF(rectEndX + pointFrontPeak, (rectHeight / 2)),
    QPointF(rectEndX, (arrowY + arrowHeight) + pointBottomPeak), 
    QPointF(rectEndX, (arrowY + arrowHeight)),
  };
  
  painter.drawPolygon(points,5);
  
  // Arrow Text
  
  painter.setPen(Qt::black);
  
  QFont penFont;
  penFont.setBold(true);
  
  painter.setFont(penFont);
  painter.drawText(box,Qt::AlignCenter,m_text);
  
  painter.end();
  QWidget::paintEvent(event);
}
  
void ArrowWidget::setColor(Qt::GlobalColor color)
{
  m_arrowColor = color;
  update();
}

void ArrowWidget::setConnectionStatus(bool isActive)
{
  if(isActive)
  {
    setColor(Qt::green);
  }
  else
  {
    setColor(Qt::red);
  }
}

void ArrowWidget::setText(const QString& text)
{
  m_text = text;
  update();
}
