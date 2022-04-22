// Example of a plugin action

#pragma once
#include <list>
#include <glm.hpp>
#include "spslidardownloaddlg.h"

class ccMainAppInterface;

namespace Spslidar
{
	void performActionDownload( ccMainAppInterface *appInterface );
	void performActionUpload( ccMainAppInterface* appInterface );
	void initialiceMap();
}
