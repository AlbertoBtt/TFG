/*****************************************************************//**
 * @file   SpslidarServerPlugin.h
 * @brief  Definition of the class SpslidarServerPlugin
 * 
 * @author Alberto Beteta Fernández
 * @date   March 2022
 *********************************************************************/

//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: SpslidarDownloadPlugin             #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                       COPYRIGHT: Universidad de Jaén                   #
//#                                                                        #
//##########################################################################

#pragma once

#include "ccStdPluginInterface.h"
#include <QMainWindow>

/**
 * @brief class SpslidarServerPlugin which is the main class from the plugin to download clouds from a Spslidar Server
 */
class SpslidarServerPlugin : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccPluginInterface ccStdPluginInterface )
	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.SpslidarDownloadPlugin" FILE "../info.json" )

public:
	explicit SpslidarServerPlugin( QObject *parent = nullptr );
	~SpslidarServerPlugin() override = default;

	void onNewSelection( const ccHObject::Container &selectedEntities ) override;
	QList<QAction *> getActions() override;

private:
	QAction* m_action; ///< The action of the plugin
};
