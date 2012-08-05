
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

#ifndef KCMNIC
#define KCMNIC 

//local 
#include "nicbackend.h"
#include "networkinterfacebase.h"

//QT
#include <QWidget>
#include <QVariantList>

//KDE
#include <KCModule>
#include <KTabWidget>

class KcmNic : public KCModule 
{
  Q_OBJECT
  
  public: 
    KcmNic(QWidget *parent, const QVariantList &);
    ~KcmNic();
 
  public Q_SLOTS:
    void networkingStatusChangedSlot(Solid::Networking::Status);
    
  private:
    void createInterface();
    void createWidgetDisplay(QWidget *, enum NicBackend::InterfaceType);
    void updateStatusBarStatus(bool);
    void createOppsMessage();
    
    QWidget *m_parentWidget;
    NicBackend *m_backend;
    KTabWidget *m_tabs;
    
    QLabel *m_statusLabel;
    
    QWidget *allTab;
    QWidget *wirelessTab;
    QWidget *wiredTab;
};

#endif // KCMNIC

