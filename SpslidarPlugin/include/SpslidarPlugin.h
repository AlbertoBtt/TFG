/**
 * @file SpslidarPlugin.h
 * @brief header file for main plugin class
 *
 */

 //##########################################################################
 //#                                                                        #
 //#                CLOUDCOMPARE PLUGIN: SpslidarPlugin                     #
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
 //#						     COPYRIGHT:									#
 //#					 Alberto Beteta Fernandez							#                     
 //#				   Rafael Jesús Segura Sánchez							#
 //#				    Antonio Jesús Rueda Ruíz							#
 //#                  Carlos Javier Ogayar Anguita                          #
 //#                                                                        #
 //##########################################################################

#ifndef SPSLIDAR_PLUGIN_HEADER
#define SPSLIDAR_PLUGIN_HEADER

#include "ccStdPluginInterface.h"
/**
 * @brief SpslidarPLugin class, which represents the main class of the plugin
 */
class SpslidarPlugin : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccPluginInterface ccStdPluginInterface )
	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.Spslidar" FILE "../info.json" )

public:
	explicit SpslidarPlugin( QObject *parent = nullptr );
	~SpslidarPlugin() override = default;

	void onNewSelection( const ccHObject::Container &selectedEntities ) override;
	QList<QAction *> getActions() override;
private:
	QAction* m_actionDownload; ///< The Download Cloud Action
	QAction* m_actionUpload; ///< The Upload Cloud Action
};

#endif