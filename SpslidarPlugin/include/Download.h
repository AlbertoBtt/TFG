#pragma once
#include <list>
#include <glm.hpp>
#include "spslidardownloaddlg.h"

class ccMainAppInterface;

namespace Download
{
	void performDownload( ccMainAppInterface *appInterface );
	void loadCloud(ccMainAppInterface* appInterface, spslidarDownloadDlg* dlg);
}
