
/*
*  wiredwidget.cpp
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

#include "wiredwidget.h"

//KDE
#include <KDebug>

//QT
#include <QHBoxLayout>

WiredWidget::WiredWidget(const Solid::Control::WiredNetworkInterface *net) : 
  NetworkInterfaceBase(),
  wired(net)
{
  connect(wired,SIGNAL(connectionStateChanged(int,int,int)),this,SLOT(connectionStateChangedSlot(int,int,int)));
  createInterface();
}    

Solid::Control::NetworkInterface::Type WiredWidget::type() const
{
  return Solid::Control::NetworkInterface::Ieee8023;
}

void WiredWidget::createInterface()
{
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(createGroupBox("network-wired",this,wired));
  
  createArrow();
  mainLayout->addWidget(m_arrow);
  
  m_wiredDestination = new WiredDestination(iP4Address(wired->ipV4Config()).netMask(),iP4Address(wired->ipV4Config()).address());
  mainLayout->addWidget(m_wiredDestination);
}

void WiredWidget::createArrow()
{
  m_arrow = new ArrowWidget(this);
  m_arrow->setConnectionStatus(wired->isActive());
  m_arrow->setText(connectionStateToQString(wired->connectionState()));
}

void WiredWidget::connectionStateChangedSlot(int newstate,int oldstate, int reason) 
{
  Q_UNUSED(oldstate);
  Q_UNUSED(reason);
  
  if(newstate == Solid::Control::NetworkInterface::Activated)
  {
    m_wiredDestination->changeAddresses(iP4Address(wired->ipV4Config()).netMask(),iP4Address(wired->ipV4Config()).address());
    m_wiredDestination->setAll();
    setAll(wired);
  }
  else
  {
    if(!wired->isActive()) m_wiredDestination->changeAddresses(0,0);
    m_wiredDestination->setAll();
    setAll(wired);
  }
  m_arrow->setText(connectionStateToQString(static_cast<Solid::Control::NetworkInterface::ConnectionState>(newstate)));
}
