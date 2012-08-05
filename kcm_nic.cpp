
/*
*  kcm_nic.cpp
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

#include "kcm_nic.h"

//QT
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStatusBar>

//KDE
#include <KPluginFactory>
#include <KPluginLoader>
#include <KDebug>
#include <KLocale>

K_PLUGIN_FACTORY(KcmNicModuleFactory, registerPlugin<KcmNic>();)
K_EXPORT_PLUGIN(KcmNicModuleFactory("kcm_nic"))

KcmNic::KcmNic(QWidget *parent, const QVariantList &)  : 
  KCModule(KcmNicModuleFactory::componentData(), parent), 
  m_parentWidget(parent),
  m_statusLabel(NULL)
{
  setContentsMargins(0,0,0,0);
  setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  
  m_backend = new NicBackend();
  if(m_backend->networkInterfacesCount() > 0)
  {
    createInterface();
    updateStatusBarStatus(m_backend->isNetConnected());
    connect(m_backend,SIGNAL(statusChanged(Solid::Networking::Status)),this,SLOT(networkingStatusChangedSlot(Solid::Networking::Status)));
  }
  else
  {
    createOppsMessage();
  }
}

KcmNic::~KcmNic()
{
  delete m_backend;
}

void KcmNic::createInterface() 
{
  QVBoxLayout *mainLay = new QVBoxLayout(this);
  mainLay->setContentsMargins(0,0,0,0);
  mainLay->setSpacing(5);
  
  m_tabs = new KTabWidget(this);
  m_tabs->setContentsMargins(0,0,0,0);
  m_tabs->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  
  //All 
  QScrollArea *allTabScroll = new QScrollArea(m_tabs);
  allTabScroll->setWidgetResizable(true);
  allTab = new QWidget(allTabScroll);

  createWidgetDisplay(allTab,NicBackend::ALL);
  allTabScroll->setWidget(allTab);
  
  allTabScroll->setWhatsThis(i18n("This tab shows all network interfaces"));
  m_tabs->addTab(allTabScroll,i18nc("Show all interfaces tab label","All Interfaces"));
  
  // Wired
  QScrollArea *wiredTabScroll = new QScrollArea(m_tabs);
  wiredTabScroll->setWidgetResizable(true);
  wiredTab = new QWidget();
  
  createWidgetDisplay(wiredTab,NicBackend::WIRED);
  wiredTabScroll->setWidget(wiredTab);
  
  wiredTabScroll->setWhatsThis(i18n("This tab shows only wired network interfaces"));
  m_tabs->addTab(wiredTabScroll,i18nc("Show all wired interfaces tab label", "Wired Interfaces"));
  
  //Wireless
  QScrollArea *wirelessTabScroll = new QScrollArea(m_tabs);
  wirelessTabScroll->setWidgetResizable(true);
  wirelessTab = new QWidget(wirelessTabScroll);
  
  createWidgetDisplay(wirelessTab,NicBackend::WIRELESS);
  wirelessTabScroll->setWidget(wirelessTab);
  
  wirelessTabScroll->setWhatsThis(i18n("This tab shows only wireless network interfaces"));
  m_tabs->addTab(wirelessTabScroll,i18nc("Show all wireless interfaces tab label", "Wireless Interfaces"));
  
  //StatusBar
  QStatusBar *status = new QStatusBar();
  status->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  status->setContentsMargins(0,0,0,0);
  status->setSizeGripEnabled(false); 
  
  m_statusLabel = new QLabel();
  
  //Adding
  status->addPermanentWidget(m_statusLabel); 
  mainLay->addWidget(m_tabs);
  mainLay->addWidget(status);
}

void KcmNic::createOppsMessage()
{
  QVBoxLayout *mainLay = new QVBoxLayout(this);
  mainLay->setContentsMargins(0,0,0,0);
  mainLay->setSpacing(5);
  
  QLabel *message = new QLabel(i18n("No Network Cards where detected.) ") 
			       + i18n("\nThis could be due to no network cards being found or that a Solid backend is not being used."));
  message->setWordWrap(true);
  message->setAlignment(Qt::AlignCenter);
  
  mainLay->addWidget(message);
}

void KcmNic::createWidgetDisplay(QWidget *parent, enum NicBackend::InterfaceType type) 
{
  QVBoxLayout *widgetLayout = new QVBoxLayout(parent);
  foreach (const NetworkInterfaceBase *device, m_backend->interfaces(type)) 
  {
    widgetLayout->addWidget(const_cast<NetworkInterfaceBase *>(device)); 
  }
}

void KcmNic::updateStatusBarStatus(bool isConnected)
{
  if(m_statusLabel == NULL) return;
  QString message = (isConnected == 0 ? i18n("Not Connected") : i18n("Connected"));
  m_statusLabel->setText(i18nc("%1 is connection status of connected or not connected","Connection Status: %1", message));
}

void KcmNic::networkingStatusChangedSlot(Solid::Networking::Status status)
{
  if(status == Solid::Networking::Unconnected) 
  {
    updateStatusBarStatus(false);
  }
  else if(status == Solid::Networking::Connected)
  {
    updateStatusBarStatus(true);
  }
}
