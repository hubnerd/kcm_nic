
/*
 *  wireddestination.cpp
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

#include "wireddestination.h"

//QT
#include <QGridLayout>
#include <QHostAddress>

//KDE
#include <KIcon>
#include <KLocale>

WiredDestination::WiredDestination(quint32 netmaskAddress, quint32 ipAddress) :
  QGroupBox(),
  m_subnetLabel(NULL),
  m_netmaskLabel(NULL),
  m_netmaskAddress(netmaskAddress),
  m_ipAddress(ipAddress),
  m_netmask(0),
  m_subnet(0)
 
{
  setMinimumWidth(180);
  setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  setWhatsThis(i18n("Shows where the wired network interface is connected to, if connected"));
  calculateAddresses();
  createInterface();
}

void WiredDestination::createInterface()
{
  QGridLayout *lay = new QGridLayout(this);
  lay->setAlignment(Qt::AlignTop);
  lay->setColumnStretch(1,1);
  setContentsMargins(3,3,3,3);
  
  // Top
  QLabel *icon = new QLabel();
  icon->setPixmap(KIcon("network-workgroup").pixmap(32,32));
  QLabel *type = new QLabel(i18n("Subnet"));
  
  lay->addWidget(icon,0,0, Qt::AlignLeft);
  lay->addWidget(type,0,1,Qt::AlignCenter);
  
  // Line Sep
  QFrame *sepLine = new QFrame();
  sepLine->setFrameStyle( QFrame::HLine );
  lay->addWidget(sepLine,1,0,1,2);
  
  // Bottom
  m_netmaskLabel = new QLabel();
  m_netmaskLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  m_subnetLabel = new QLabel();
  m_subnetLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  setNetmaskString();
  setSubnetString();
  
  lay->addWidget(m_subnetLabel,2,0,1,2, Qt::AlignTop);
  lay->addWidget(m_netmaskLabel,3,0,1,2, Qt::AlignTop);
}

void WiredDestination::calculateAddresses()
{
  quint32 netmask = 0xffffffff;
  quint32 shift = (32-m_netmaskAddress);
  m_netmask = (netmask << shift);
  m_subnet = (m_ipAddress & m_netmask);
}

void WiredDestination::setNetmaskString()
{
  if(m_netmaskLabel == NULL) return;
  QString netmaskString = ((m_subnet + 1) ? i18n("None") : QHostAddress(m_netmask).toString());
  m_netmaskLabel->setText(i18nc("%1 is the netmask of the destination","Netmask: %1",netmaskString));
}

void WiredDestination::setSubnetString()
{
  if(m_subnetLabel == NULL) return;
  QString subnetString = (m_subnet ? QHostAddress(m_subnet).toString() : i18n("None"));
  m_subnetLabel->setText(i18nc("%1 is the destination subnet","Subnet: %1",subnetString));
}

void WiredDestination::setAll()
{
  setSubnetString();
  setNetmaskString();
}

void WiredDestination::changeAddresses(quint32 netmaskAddress, quint32 ipAddress)
{
  m_netmaskAddress = netmaskAddress;
  m_ipAddress = ipAddress;
  calculateAddresses();
}



