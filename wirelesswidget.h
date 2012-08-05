
/*
*  wirelesswidget.h
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

#ifndef WIRELESSWIDGET
#define WIRELESSWIDGET

//Local
#include "networkinterfacebase.h"
#include "arrowwidget.h"
#include "wirelessdestination.h"
#include "wireddestination.h"

//QT
#include <QString>

//Solid::Control
#include <solid/control/wirelessnetworkinterface.h>
#include <solid/control/wirelessaccesspoint.h>

class WirelessWidget : public NetworkInterfaceBase
{
  Q_OBJECT
  
  public:
    WirelessWidget(const Solid::Control::WirelessNetworkInterface *);
    virtual ~WirelessWidget() {};
    
    Solid::Control::NetworkInterface::Type type() const;
    
  Q_SIGNALS:
    void changeInconnectionState();
  
  public Q_SLOTS:
    void connectionStateChangedSlot(int, int,int);

  private:
    void createInterface();
    void createArrow();
    Solid::Control::AccessPoint* getAccessPoint();
    
    const Solid::Control::WirelessNetworkInterface *wireless;
    QString m_accessPointUDI;
    QGroupBox *m_wirelessGroupBox;
    ArrowWidget *m_arrow;
    WirelessDestination *m_wirelessDestination;
};

#endif //WIRELESSWIDGET

