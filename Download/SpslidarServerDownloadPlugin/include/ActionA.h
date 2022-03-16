/*****************************************************************//**
 * @file   ActionA.h
 * @brief  Definition of the functions of ActionsA
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

#pragma once
#include <list>
#include <glm.hpp>
#include "spslidardownloaddlg.h"

class ccMainAppInterface;

namespace SpslidarServer
{
	void performActionA( ccMainAppInterface *appInterface );
	void loadCloud(ccMainAppInterface* appInterface, spslidarDownloadDlg* dlg);
}
