
/*
*  wirelesswidget.cpp
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

#include "wirelesswidget.h"

//KDE
#include <KDebug>

//QT
#include <QHBoxLayout>

WirelessWidget::WirelessWidget(const Solid::Control::WirelessNetworkInterface *net) : 
   NetworkInterfaceBase(),
   wireless(net)
{
  connect(wireless,SIGNAL(connectionStateChanged(int,int,int)),this,SLOT(connectionStateChangedSlot(int,int,int)));
  createInterface();
}

Solid::Control::NetworkInterface::Type WirelessWidget::type() const
{
  return Solid::Control::NetworkInterface::Ieee80211;
}

void WirelessWidget::createInterface()
{
  QHBoxLayout *mainLayout = new QHBoxLayout(this);
  mainLayout->addWidget(createGroupBox("network-wireless",this,wireless));
  
  createArrow();
  mainLayout->addWidget(m_arrow);
  
  m_wirelessDestination = new WirelessDestination(getAccessPoint());
  mainLayout->addWidget(m_wirelessDestination);
}

void WirelessWidget::createArrow()
{
  m_arrow = new ArrowWidget(this);
  m_arrow->setConnectionStatus(wireless->isActive());
  m_arrow->setText(connectionStateToQString(wireless->connectionState()));
}

Solid::Control::AccessPoint* WirelessWidget::getAccessPoint()
{
  m_accessPointUDI = wireless->activeAccessPoint();
  Solid::Control::AccessPoint *tmpAp = wireless->findAccessPoint(m_accessPointUDI);
  return tmpAp;
}

void WirelessWidget::connectionStateChangedSlot(int newstate,int oldstate, int reason) 
{
  Q_UNUSED(oldstate);
  Q_UNUSED(reason);
  
  m_arrow->setText(connectionStateToQString(static_cast<Solid::Control::NetworkInterface::ConnectionState>(newstate)));
  if(newstate == Solid::Control::NetworkInterface::Activated)
  {
    m_wirelessDestination->changeAccessPoint(getAccessPoint());
    m_wirelessDestination->setAll();
    setAll(wireless);
  }
  else 
  {
    if(!wireless->isActive()) m_wirelessDestination->changeAccessPoint(0);
    m_wirelessDestination->setAll();
    setAll(wireless);
  }
  m_arrow->setConnectionStatus(wireless->isActive());
}

