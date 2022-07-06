/*****************************************************************//**
 * @file   SpslidarPlugin.cpp
 * @brief  Implementation of the main class from the plugin
 * 
 * @author Alberto Beteta Fernández
 * @date   April 2022
 *********************************************************************/

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
//#							     COPYRIGHT:								   #
//#						 Alberto Beteta Fernandez						   #                     
//#					   Rafael Jesús Segura Sánchez						   #
//#					     Antonio Jesús Rueda Ruíz						   #
//#				       Carlos Javier Ogayar Anguita                        #
//#                                                                        #
//##########################################################################

#include "SpslidarPlugin.h"
#include "ActionA.h"

/**
 * @brief Default Constructor of SpslidarPlugin
 * 
 * @param [in] parent Parent interface
 */
SpslidarPlugin::SpslidarPlugin( QObject* parent/*=nullptr*/)
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/SpslidarPlugin/info.json" )
	, m_actionDownload( nullptr )
	, m_actionUpload( nullptr )
{
}

/**
 * @brief Slot to modify the activation/desactivation of the plugin's actions. It is executed every time the selection of entities in CloudCompare change.
 * 
 * @param selectedEntities
 */
void SpslidarPlugin::onNewSelection( const ccHObject::Container &selectedEntities )
{
	m_actionUpload->setEnabled( !selectedEntities.empty() );
	m_actionDownload->setEnabled( true );
}

/**
 * @brief Start function that intialice the actions of the plugin
 * 
 * @return 
 */
QList<QAction *> SpslidarPlugin::getActions()
{
	QList<QAction*> group;
	if ( !m_actionDownload )
	{
		m_actionDownload = new QAction( "SPSLiDAR Download", this );
		m_actionDownload->setToolTip( "SPSLiDAR Download Tool" );
		m_actionDownload->setIcon(QIcon(QString::fromUtf8(":/CC/plugin/SpslidarPlugin/images/download.png")));
		
		connect(m_actionDownload, &QAction::triggered, this, [this]()
			{
				Spslidar::performActionDownload(m_app);
			});
	}
	group.push_back(m_actionDownload);
	if (!m_actionUpload)
	{
		m_actionUpload = new QAction("SPSLiDAR Upload", this);
		m_actionUpload->setToolTip("SPSLiDAR Upload Tool");
		m_actionUpload->setIcon(QIcon(QString::fromUtf8(":/CC/plugin/SpslidarPlugin/images/upload.png")));

		connect(m_actionUpload, &QAction::triggered, this, [this]()
			{
				Spslidar::performActionUpload(m_app);
			});
	}
	group.push_back(m_actionUpload);
	return group;
}

