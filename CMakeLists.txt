
project( kcm_nic )

find_package(KDE4 REQUIRED)
include_directories( ${KDE4_INCLUDES} )

set( 
    kcm_nicSources 
    kcm_nic.cpp 
    networkinterfacebase.cpp
    nicbackend.cpp 
    wiredwidget.cpp
    wirelesswidget.cpp
    arrowwidget.cpp
    wireddestination.cpp
    wirelessdestination.cpp
   )

kde4_add_plugin( kcm_nic ${kcm_nicSources} )
target_link_libraries( kcm_nic ${KDE4_KIO_LIBS} ${KDE4_SOLID_LIBS} solidcontrol)

install( TARGETS kcm_nic DESTINATION ${PLUGIN_INSTALL_DIR} )
install( FILES kcm_nic.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
