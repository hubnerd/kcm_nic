
/*
 *  wireddestination.h
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

#ifndef WIREDDESTINATION
#define WIREDDESTINATION

//KDE
#include <KDebug>

//QT
#include <QGroupBox>
#include <QLabel>

class WiredDestination : public QGroupBox
{
  Q_OBJECT
  
  public:
    WiredDestination(quint32, quint32);

    void setSubnetString();
    void setNetmaskString();
    void setAll();
    
    void changeAddresses(quint32, quint32);

  private:
    void createInterface();
    void calculateAddresses();
    
    QLabel *m_subnetLabel;
    QLabel *m_netmaskLabel;
    quint32 m_netmaskAddress;
    quint32 m_ipAddress;
    
    quint32 m_netmask;
    quint32 m_subnet;
};

#endif //WIREDDESTINATION

