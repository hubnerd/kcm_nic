
/*
*  networkinterfacebase.cpp
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

#include "networkinterfacebase.h"

//KDE
#include <KDebug>
#include <KLocale>

//QT
#include <QGridLayout>

//Solid::Control
#include <solid/control/wirednetworkinterface.h>
#include <solid/control/wirelessnetworkinterface.h>

NetworkInterfaceBase::NetworkInterfaceBase() : 
  QWidget(),
  m_icon(new QLabel()),
  m_hardware(NULL),
  m_ipAddress(NULL),
  m_gateway(NULL)
{
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

Solid::Control::NetworkInterface::Type NetworkInterfaceBase::type() const
{
  return Solid::Control::NetworkInterface::UnknownType;
}

void NetworkInterfaceBase::setIcon(const KIcon *icon) const 
{
  m_icon->setPixmap(icon->pixmap(64,64));
}

QString NetworkInterfaceBase::convertToTypeString(Solid::Control::NetworkInterface::Type type)
{
  switch(type)
  {
    case Solid::Control::NetworkInterface::Ieee8023:
      return i18n("Ethernet");
    case Solid::Control::NetworkInterface::Ieee80211:
      return i18n("Wireless");
    default:
      return i18n("Unknown");
  }
  return i18n("Unknown");
}

QString NetworkInterfaceBase::convertBoolToFriendly(bool b) 
{
  if(b)
  {
    return i18n("Yes");
  }
  else
  {
    return i18n("No");
  }
}

Solid::Control::IPv4Address NetworkInterfaceBase::iP4Address(Solid::Control::IPv4Config ipConfig)
{
  if(!ipConfig.isValid()) return Solid::Control::IPv4Address();
  
  Solid::Control::IPv4Address address = ipConfig.addresses()[0];
  if(!address.isValid()) return Solid::Control::IPv4Address();
  
  return address;
}

QString NetworkInterfaceBase::addressToQString(quint32 address)
{
  QString stringIpAddy;
  if(!address) return i18n("None");
  
  QHostAddress *ipAddy = new QHostAddress(address);
  QString ipString = ipAddy->toString();
  delete ipAddy;
  return ipString;
}

QGroupBox *NetworkInterfaceBase::createGroupBox(QString icon, QWidget *parent, const Solid::Control::NetworkInterface *iface)
{
  //Layout
  QGroupBox *interfaceGroupBox = new QGroupBox(parent);
  interfaceGroupBox->setWhatsThis(i18n("Shows the details of the network interface"));
  interfaceGroupBox->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  QGridLayout *baseLayout = new QGridLayout(interfaceGroupBox);
  
  baseLayout->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
  baseLayout->setHorizontalSpacing(20);
  
  //Icon
  KIcon *iconPix = new KIcon(icon);
  setIcon(iconPix);
  delete iconPix;
  
  baseLayout->addWidget(m_icon,0,0,3,1,Qt::AlignCenter);
  
  //Top Right
  QLabel *topicName = new QLabel(i18n("Interface Name: "));
  QLabel *topicType = new QLabel(i18n("Connection Type: "));
  QLabel *topicActive = new QLabel(i18n("Is Connected?: "));
  
  QLabel *resultName = new QLabel(iface->interfaceName());
  resultName->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  QLabel *resultType = new QLabel(convertToTypeString(iface->type()));
  resultType->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  QLabel *resultActive = new QLabel(convertBoolToFriendly(iface->isActive()));
  resultActive->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  baseLayout->addWidget(topicName,0,1,1,1);
  baseLayout->addWidget(topicType,1,1,1,1);
  baseLayout->addWidget(topicActive,2,1,1,1);
  
  baseLayout->addWidget(resultName,0,2,1,1);
  baseLayout->addWidget(resultType,1,2,1,1);
  baseLayout->addWidget(resultActive,2,2,1,1);
  
  // Sep Line
  QFrame *sepLine = new QFrame();
  sepLine->setFrameStyle( QFrame::HLine );
  baseLayout->addWidget(sepLine,3,0,1,3);
  
  // Bottom
  
  m_ipAddress = new QLabel();
  m_ipAddress->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  m_gateway = new QLabel();
  m_gateway->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  m_hardware = new QLabel();
  m_hardware->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  setHardwareAddress(iface);
  setIpAddress(iface);
  setGateway(iface);
  
  baseLayout->addWidget(m_ipAddress,4,0,1,3);
  baseLayout->addWidget(m_gateway,5,0,1,3);
  baseLayout->addWidget(m_hardware,6,0,1,3);

  return interfaceGroupBox;
}

QString NetworkInterfaceBase::getNetworkHWAddy(const Solid::Control::NetworkInterface *iface)
{
  if(iface->type() == Solid::Control::NetworkInterface::Ieee8023)
  {
    const Solid::Control::WiredNetworkInterface *tmpIface = static_cast<const Solid::Control::WiredNetworkInterface *>(iface);
    return tmpIface->hardwareAddress();
  } 
  else if(iface->type() == Solid::Control::NetworkInterface::Ieee80211)
  {
    const Solid::Control::WirelessNetworkInterface *tmpIface = static_cast<const Solid::Control::WirelessNetworkInterface *>(iface);
    return tmpIface->hardwareAddress();
  }
  return i18n("Unknown");
}
      
QString NetworkInterfaceBase::connectionStateToQString(
  Solid::Control::NetworkInterface::ConnectionState conState)
{
  switch(conState) 
  {
    case Solid::Control::NetworkInterface::UnknownState:
      return i18n("UnknownState");
    case Solid::Control::NetworkInterface::Unmanaged:
      return i18n("Unmanaged");
    case Solid::Control::NetworkInterface::Unavailable:
      return i18n("Unavailable");
    case Solid::Control::NetworkInterface::Disconnected:
      return i18n("Disconnected");
    case Solid::Control::NetworkInterface::Preparing:
      return i18n("Preparing");
    case Solid::Control::NetworkInterface::Configuring:
      return i18n("Configuring");
    case Solid::Control::NetworkInterface::NeedAuth:
      return i18n("NeedAuth");
    case Solid::Control::NetworkInterface::IPConfig:
      return i18n("IPConfig");
    case Solid::Control::NetworkInterface::Activated:
      return i18n("Activated");
    case Solid::Control::NetworkInterface::Failed:
      return i18n("Failed");
    default:
      return i18n("UnknownState");
  }
}

void NetworkInterfaceBase::setHardwareAddress(const Solid::Control::NetworkInterface *iface)
{
  if(m_hardware == NULL) return;
  m_hardware->setText(i18nc("%1 is the hardware address of the nic","Hardware Address: %1",getNetworkHWAddy(iface)));
}

void NetworkInterfaceBase::setIpAddress(const Solid::Control::NetworkInterface *iface)
{
  if(m_ipAddress == NULL) return;
  m_ipAddress->setText(i18nc("%1 is the IP address of the nic","IP Address: %1",addressToQString(iP4Address(iface->ipV4Config()).address())));
}

void NetworkInterfaceBase::setGateway(const Solid::Control::NetworkInterface *iface)
{
  if(m_gateway == NULL) return;
  m_gateway->setText(i18nc("%1 is the gateway address of the nic","Gateway Address: %1",addressToQString(iP4Address(iface->ipV4Config()).gateway())));
}

void NetworkInterfaceBase::setAll(const Solid::Control::NetworkInterface *iface)
{
  setHardwareAddress(iface);
  setIpAddress(iface);
  setGateway(iface);
}


