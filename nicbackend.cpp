
/*
*  nicbackend.cpp
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

#include "nicbackend.h"

//QT
#include <KDebug>

//Solid::Control
#include <solid/control/networkinterface.h> 

NicBackend::NicBackend()
{
  // Created for adding and removing interfaces in realtime. 
  // Problem being i have no way to test this so if anyone wants 
  // to involve themselves on this, please do
  nm = new Solid::Control::NetworkManager::Notifier();
  connect(nm,SIGNAL(statusChanged(Solid::Networking::Status)),this,SLOT(networkingStatusChangedSlot(Solid::Networking::Status)));
}

NicBackend::~NicBackend()
{
  delete nm;
  qDeleteAll(cachedInterfaces);
  cachedInterfaces.clear();
}

QList<const NetworkInterfaceBase *> NicBackend::interfaces(InterfaceType interface)
{
  const Solid::Control::NetworkInterfaceList all = Solid::Control::NetworkManager::networkInterfaces();
  
  cachedInterfaces.clear();
  foreach (const Solid::Control::NetworkInterface *device, all) 
  {
    switch(interface)
    {
      case ALL:
      case WIRED:
	if(device->type() == Solid::Control::NetworkInterface::Ieee8023)
	{
	  cachedInterfaces.append(new WiredWidget(static_cast<const Solid::Control::WiredNetworkInterface *>(device)));
	}
	if(interface != ALL) continue;
      case WIRELESS:
	if(device->type() == Solid::Control::NetworkInterface::Ieee80211) 
	{
	  cachedInterfaces.append(new WirelessWidget(static_cast<const Solid::Control::WirelessNetworkInterface *>(device)));
	}
	continue;
    }
  }
  return cachedInterfaces;
}

bool NicBackend::isNetConnected() const 
{
  return Solid::Control::NetworkManager::isNetworkingEnabled();
}

void NicBackend::networkingStatusChangedSlot(Solid::Networking::Status status)
{
  emit statusChanged(status);
}

int NicBackend::networkInterfacesCount() const
{
  const Solid::Control::NetworkInterfaceList all = Solid::Control::NetworkManager::networkInterfaces();
  return all.count();
}
