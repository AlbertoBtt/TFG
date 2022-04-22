// Example of a plugin action

#include "Download.h"
#include "ccMainAppInterface.h"
#include "lasreader_las.hpp"
#include <QDir>
#include <QProgressDialog>
#include "ccPointCloud.h"
#include "spslidardownloaddlg.h"

namespace Download
{
	void performDownload( ccMainAppInterface *appInterface )
	{
		if ( appInterface == nullptr )
		{
			Q_ASSERT( false );
			
			return;
		}
		spslidarDownloadDlg interfaz((QWidget*)appInterface->getMainWindow());
		int result=interfaz.exec();
		if (result==interfaz.Accepted)
		{
			loadCloud(appInterface, &interfaz);
		}
	}

	/**
	 * @brief Auxiliar function which is used for load a cloud from a .laz which has been download with a spslidarDonwloadDlg
	 * 
	 * @param appInterface The main appInteface from CloudCompare
	 * @param dlg The spslidarDownloadDLg which has been used for download the data
	 */
	void loadCloud(ccMainAppInterface* appInterface, spslidarDownloadDlg* dlg) {
		std::list<glm::vec3> pointsPosition;
		std::list<glm::vec3> pointsColor;
		LASreaderLAS reader;
		QString ruta(dlg->getRuta());
		reader.open(ruta.toStdString().c_str());
		long numberOfPoints = reader.header.number_of_point_records;
		appInterface->dispToConsole(QString::fromStdString(to_string(numberOfPoints)));
		QString name = dlg->getDataset();
		ccPointCloud* cloud = new ccPointCloud();
		cloud->setName(name);
		cloud->reserve(numberOfPoints);
		cloud->reserveTheRGBTable();
		cloud->toggleColors();

		LASpoint& point = reader.point;
		unsigned int count = 0;

		QProgressDialog progressDialog(name, NULL, 0, numberOfPoints);
		progressDialog.setWindowTitle("Loading point cloud ...");
		progressDialog.setMinimumWidth(500);
		progressDialog.setMinimumHeight(200);


		while (reader.read_point()) {
			LASpoint& point = reader.point;
			float coordX = point.get_x();
			float coordY = point.get_y();
			float coordZ = point.get_z();
			CCVector3 vector(coordX, coordY, coordZ);

			int colorR = point.get_R() / 256;
			int colorG = point.get_G() / 256;
			int colorB = point.get_B() / 256;
			ccColor::Rgb color(colorR, colorG, colorB);

			cloud->addPoint(vector);
			cloud->addColor(color);

			pointsPosition.push_back(glm::vec3(coordX, coordY, coordZ));
			pointsColor.push_back(glm::vec3(colorR, colorG, colorB));

			++count;
			if (count % 100000 == 0) {
				progressDialog.setValue(count);
				QApplication::processEvents();
			}
		}

		progressDialog.close();

		appInterface->addToDB(cloud);
	}
}
