
/*
*  wiredwidget.h
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

#ifndef WIREDWIDGET
#define WIREDWIDGET

//Local
#include "networkinterfacebase.h"
#include "wireddestination.h"
#include "arrowwidget.h"

//QT

//Solid::Control
#include <solid/control/wirednetworkinterface.h>

class WiredWidget : public NetworkInterfaceBase
{
  Q_OBJECT
  
  public:
    WiredWidget(const Solid::Control::WiredNetworkInterface *);
    virtual ~WiredWidget() {};
    
    Solid::Control::NetworkInterface::Type type() const;
    
  Q_SIGNALS:
    void changeInconnectionState();
    
  public Q_SLOTS:
    void connectionStateChangedSlot(int, int,int);
    
  private:
    void createInterface();
    void createArrow();
    
    const Solid::Control::WiredNetworkInterface *wired;
    QGroupBox *m_wiredGroupBox;
    ArrowWidget *m_arrow;
    WiredDestination *m_wiredDestination;
};

#endif //WIREDWIDGET
