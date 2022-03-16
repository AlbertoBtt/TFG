/*****************************************************************//**
 * @file   SpslidarServerPlugin.cpp
 * @brief  Implementation of the functions from spslidarSeverPlugin.h
 * 
 * @author Alberto Beteta Fernández
 * @date   March 2022
 *********************************************************************/

//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: SpslidarServerDownloadPlugin       #
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
//#                   COPYRIGHT: Universidad de Jaen                       #
//#                                                                        #
//##########################################################################

#include <QtGui>

#include "SpslidarServerPlugin.h"

#include "ActionA.h"

/**
 * @brief Constructor of the class
 * 
 * @param parent The windows parent from the class
 */
SpslidarServerPlugin::SpslidarServerPlugin( QObject *parent )
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/SpslidarServerDownloadPlugin/info.json" )
	, m_action( nullptr )
{
}

/**
 * @brief Adds the plugin to the list of plugins
 * 
 * @param selectedEntities The list of plugins
 */
void SpslidarServerPlugin::onNewSelection( const ccHObject::Container &selectedEntities )
{
	if ( m_action == nullptr )
	{
		return;
	}
	
	m_action->setEnabled( true );
	
}

/**
 * @brief Get the actions and adds it to the list
 * 
 * @return The action which has been created
 */
QList<QAction *> SpslidarServerPlugin::getActions()
{

	if ( !m_action )
	{
		// Here we use the default plugin name, description, and icon,
		// but each action should have its own.
		m_action = new QAction( getName(), this );
		m_action->setToolTip( getDescription() );
		m_action->setIcon( getIcon() );
		
		// Connect appropriate signal
		connect( m_action, &QAction::triggered, this, [this]()
		{
				SpslidarServer::performActionA( m_app );
		});
	}

	return { m_action };
}
