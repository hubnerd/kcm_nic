
/*
*  nicbackend.h
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

#ifndef NICBACKEND
#define NICBACKEND

//Local
#include "wiredwidget.h"
#include "wirelesswidget.h"
#include "networkinterfacebase.h"

//QT
#include <QList>
#include <QObject>

//Solid::Control
#include <solid/control/networkmanager.h> 
#include <solid/control/networkinterface.h>

class NicBackend : public QObject
{
  Q_OBJECT
  
  public:
    NicBackend();
    ~NicBackend();
    
    enum InterfaceType { WIRED=0, WIRELESS, ALL };
    
    QList<const NetworkInterfaceBase *> interfaces(InterfaceType);
    bool isNetConnected() const;
    int networkInterfacesCount() const;
    
  Q_SIGNALS:
    void statusChanged(Solid::Networking::Status);
    
  public Q_SLOTS:
    void networkingStatusChangedSlot(Solid::Networking::Status);
    
  private:
    QList<const NetworkInterfaceBase *> cachedInterfaces;
    Solid::Control::NetworkManager::Notifier *nm;
};

#endif //NICBACKEND

