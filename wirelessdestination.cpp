
/*
 *  wirelessdestination.cpp
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

#include "wirelessdestination.h"

//QT
#include <QString>
#include <QGridLayout>

//KDE
#include <KIcon>
#include <KLocale>

WirelessDestination::WirelessDestination(Solid::Control::AccessPoint *ap) :
  QGroupBox(),
  m_ssidLabel(NULL),
  m_freqLabel(NULL),
  m_hAddyLabel(NULL),
  m_icon(NULL),
  m_ap(ap)
{
  setMinimumWidth(180);
  setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  setWhatsThis(i18n("Show the information of the access point which this wireless network interface is connected to"));
  createInterface();
  connectSignals();
}

WirelessDestination::~WirelessDestination()
{
  disconnectSignals();
}

void WirelessDestination::createInterface()
{
  QGridLayout *lay = new QGridLayout(this);
  lay->setAlignment(Qt::AlignTop);
  lay->setColumnStretch(1,1);
  setContentsMargins(3,3,3,3);
  
  //Top
  m_icon = new QLabel();
  m_icon->setPixmap(KIcon("network-wireless-100").pixmap(32,32));
  QLabel *type = new QLabel(i18n("Access Point"));
  
  lay->addWidget(m_icon,0,0, Qt::AlignLeft);
  lay->addWidget(type,0,1,Qt::AlignCenter);
  
  // Line Sep
  QFrame *sepLine = new QFrame();
  sepLine->setFrameStyle( QFrame::HLine );
  lay->addWidget(sepLine,1,0,1,2);
  
  // Bottom
  m_ssidLabel = new QLabel();
  m_ssidLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  m_freqLabel = new QLabel();
  m_freqLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  m_hAddyLabel = new QLabel();
  m_hAddyLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);
  
  setSSID();
  setFreqString();
  setHardwareAddy();
  
  lay->addWidget(m_ssidLabel,2,0,1,2, Qt::AlignTop);
  lay->addWidget(m_freqLabel,3,0,1,2, Qt::AlignTop);
  lay->addWidget(m_hAddyLabel,4,0,1,2, Qt::AlignTop);
}

void WirelessDestination::setFreqString() 
{
  if(m_freqLabel == NULL) return;
  QString freqString = (m_ap ? QString::number(m_ap->frequency()) : i18n("None"));
  m_freqLabel->setText(i18nc("%1 is the frequency of the wireless destination","Frequency: %1",freqString));
}

void WirelessDestination::setHardwareAddy()
{
  if(m_hAddyLabel == NULL) return;
  QString hAddyString = (m_ap ? m_ap->hardwareAddress() : i18n("None"));
  m_hAddyLabel->setText(i18nc("%1 is the hardware address of the wireless destination","HardWare Address: %1",hAddyString));
}

void WirelessDestination::setSSID()
{
  if(m_ssidLabel == NULL) return;
  QString ssidString = (m_ap ? m_ap->ssid() : i18n("None"));
  m_ssidLabel->setText(i18nc("%1 is the ssid of the wireless destination","SSID: %1",ssidString));
}

void WirelessDestination::setAll()
{
  setSSID();
  setHardwareAddy();
  setFreqString();
}

void WirelessDestination::changeAccessPoint(Solid::Control::AccessPoint *ap)
{
  disconnectSignals();
  m_ap = ap;
  connectSignals();
}

void WirelessDestination::changeSignalIcon(int str)
{
  if(m_icon == NULL) return;
  if(str < 25) 
  {
    m_icon->setPixmap(KIcon("network-wireless-00").pixmap(32,32));
  }
  else if(str >= 26 && str <= 49)
  {
    m_icon->setPixmap(KIcon("network-wireless-25").pixmap(32,32));
  }
  else if(str >=50 && str <= 74)
  {
    m_icon->setPixmap(KIcon("network-wireless-50").pixmap(32,32));
  }
  else if(str >= 75 && str <= 99)
  {
    m_icon->setPixmap(KIcon("network-wireless-75").pixmap(32,32));
  }
  else
  {
    m_icon->setPixmap(KIcon("network-wireless-100").pixmap(32,32));
  }
}

void WirelessDestination::connectSignals()
{
  connect(m_ap,SIGNAL(signalStrengthChanged(int)),this,SLOT(changeSignalIcon(int)));
}

void WirelessDestination::disconnectSignals()
{
  disconnect(m_ap,SIGNAL(signalStrengthChanged(int)),this,SLOT(changeSignalIcon(int)));
}

