
/*
 *  wirelessdestination.h
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

#ifndef WIRELESSDESTINATION
#define WIRELESSDESTINATION

//KDE
#include <KDebug>

//QT
#include <QGroupBox>
#include <QLabel>

//Solid::Control
#include <solid/control/wirelessaccesspoint.h>

class WirelessDestination : public QGroupBox
{
  Q_OBJECT
  
  public:
    WirelessDestination(Solid::Control::AccessPoint *);
    ~WirelessDestination();
  
    void setSSID();
    void setFreqString();
    void setHardwareAddy();
    void setAll();
    
    void changeAccessPoint(Solid::Control::AccessPoint *);
    
  private Q_SLOTS:
    void changeSignalIcon(int);
    
  private:
    void createInterface();
    void connectSignals();
    void disconnectSignals();
    
    QLabel *m_ssidLabel;
    QLabel *m_freqLabel;
    QLabel *m_hAddyLabel;
    QLabel *m_icon;
    
    Solid::Control::AccessPoint *m_ap;
};

#endif //WIRELESSDESTINATION

