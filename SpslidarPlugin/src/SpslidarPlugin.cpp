//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: ExamplePlugin                      #
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
//#                             COPYRIGHT: XXX                             #
//#                                                                        #
//##########################################################################

// First:
//	Replace all occurrences of 'ExamplePlugin' by your own plugin class name in this file.
//	This includes the resource path to info.json in the constructor.

// Second:
//	Open ExamplePlugin.qrc, change the "prefix" and the icon filename for your plugin.
//	Change the name of the file to <yourPluginName>.qrc

// Third:
//	Open the info.json file and fill in the information about the plugin.
//	 "type" should be one of: "Standard", "GL", or "I/O" (required)
//	 "name" is the name of the plugin (required)
//	 "icon" is the Qt resource path to the plugin's icon (from the .qrc file)
//	 "description" is used as a tootip if the plugin has actions and is displayed in the plugin dialog
//	 "authors", "maintainers", and "references" show up in the plugin dialog as well

#include "SpslidarPlugin.h"
#include "ActionA.h"


// Default constructor:
//	- pass the Qt resource path to the info.json file (from <yourPluginName>.qrc file) 
//  - constructor should mainly be used to initialize actions and other members
SpslidarPlugin::SpslidarPlugin( QObject* parent/*=nullptr*/)
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/SpslidarPlugin/info.json" )
	, m_actionDownload( nullptr )
	, m_actionUpload( nullptr )
{
}

// This method should enable or disable your plugin actions
// depending on the currently selected entities ('selectedEntities').
void SpslidarPlugin::onNewSelection( const ccHObject::Container &selectedEntities )
{
	m_actionUpload->setEnabled( !selectedEntities.empty() );
	m_actionDownload->setEnabled( true );
}

// This method returns all the 'actions' your plugin can perform.
// getActions() will be called only once, when plugin is loaded.
QList<QAction *> SpslidarPlugin::getActions()
{
	QList<QAction*> group;
	if ( !m_actionDownload )
	{
		// Here we use the default plugin name, description, and icon,
		// but each action should have its own.
		m_actionDownload = new QAction( "Spslidar Download", this );
		m_actionDownload->setToolTip( "Spslidar Download Tool" );
		m_actionDownload->setIcon(QIcon(QString::fromUtf8(":/CC/plugin/SpslidarPlugin/images/download.png")));
		
		// Connect appropriate signal
		connect(m_actionDownload, &QAction::triggered, this, [this]()
			{
				Spslidar::performActionDownload(m_app);
			});
	}
	group.push_back(m_actionDownload);
	if (!m_actionUpload)
	{
		// Here we use the default plugin name, description, and icon,
		// but each action should have its own.
		m_actionUpload = new QAction("Spslidar Upload", this);
		m_actionUpload->setToolTip("Spslidar Upload Tool");
		m_actionUpload->setIcon(QIcon(QString::fromUtf8(":/CC/plugin/SpslidarPlugin/images/upload.png")));

		// Connect appropriate signal
		connect(m_actionUpload, &QAction::triggered, this, [this]()
			{
				Spslidar::performActionUpload(m_app);
			});
	}
	group.push_back(m_actionUpload);
	return group;
}

