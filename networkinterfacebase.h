
/*
*  networkinterfacebase.h
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

#ifndef NETWORKINTERFACEBASE
#define NETWORKINTERFACEBASE

//QT
#include <QGroupBox>
#include <QLabel>

//KDE
#include <KIcon>

//Solid::Control
#include <solid/control/networkinterface.h>

class NetworkInterfaceBase : public QWidget
{
  public:
    NetworkInterfaceBase();
    virtual ~NetworkInterfaceBase() {};
    
    virtual Solid::Control::NetworkInterface::Type type() const = 0;
    
  protected:
    virtual void createInterface() = 0;
    
    QString getNetworkHWAddy(const Solid::Control::NetworkInterface *);
    QString convertToTypeString(Solid::Control::NetworkInterface::Type);
    QString convertBoolToFriendly(bool);
    QString addressToQString(quint32);
    Solid::Control::IPv4Address iP4Address(Solid::Control::IPv4Config);
    void setIcon(const KIcon *) const;
    QString connectionStateToQString(Solid::Control::NetworkInterface::ConnectionState);
    
    void setGateway(const Solid::Control::NetworkInterface *);
    void setIpAddress(const Solid::Control::NetworkInterface *);
    void setHardwareAddress(const Solid::Control::NetworkInterface *);
    void setAll(const Solid::Control::NetworkInterface *);
    
    QGroupBox *createGroupBox(QString, QWidget *, const Solid::Control::NetworkInterface *);

  private:
    QLabel *m_icon;
    Solid::Control::NetworkInterface::Type interfaceType;
    
    QLabel *m_hardware;
    QLabel *m_ipAddress;
    QLabel *m_gateway;
    
};

#endif // NETWORKINTERFACEBASE

