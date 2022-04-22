// Example of a plugin action

#include "ccMainAppInterface.h"
#include "..\include\ActionA.h"
#include <spslidardownloaddlg.h>
#include "lasreader_las.hpp"
#include "laswriter_las.hpp"
#include <QDir>
#include <QProgressDialog>
#include "ccPointCloud.h"
#include <QtCore>
#include "spslidaruploaddlg.h"
#include "uploaddlg.h"
#include "datasetdto.h"
#include "boundingboxDTO.h"
#include "coord.h"
#include <QMessageBox>

namespace Spslidar
{
	QMap<QString, int> utm;
	QNetworkReply* netReply;

	void performActionDownload(ccMainAppInterface* appInterface)
	{
		if (appInterface == nullptr)
		{
			// The application interface should have already been initialized when the plugin is loaded
			Q_ASSERT(false);

			return;
		}
		spslidarDownloadDlg interfaz((QWidget*)appInterface->getMainWindow());
		int result=interfaz.exec();
		if (result == QDialog::Accepted)
		{
			QList<glm::vec3> pointsPosition;
			QList<glm::vec3> pointsColor;
			LASreaderLAS reader;
			QString ruta(interfaz.getRuta());
			reader.open(ruta.toStdString().c_str());
			long numberOfPoints = reader.header.number_of_point_records;
			QString name = interfaz.getDataset();
			ccPointCloud* cloud = new ccPointCloud();
			cloud->setName(name);
			cloud->reserve(numberOfPoints);
			cloud->reserveTheRGBTable();
			cloud->toggleColors();

			LASpoint& point = reader.point;
			unsigned int count = 0;

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
			}
			appInterface->addToDB(cloud);
		}
	}
	void performActionUpload(ccMainAppInterface* appInterface)
	{
		if (appInterface == nullptr)
		{
			// The application interface should have already been initialized when the plugin is loaded
			Q_ASSERT(false);

			return;
		}

		QDir dir(QString(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + "/spslidar/LAZ");
		if (!dir.exists()) dir.mkpath(".");
		QString rute = QString(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + "/spslidar/LAZ/up.laz";
		if (QFile::exists(rute)) {
			QFile::remove(rute);
		}
		const ccHObject::Container& selectedEntities = appInterface->getSelectedEntities();
		CCVector3d minRel, maxRel;
		minRel = ccHObjectCaster::ToPointCloud(selectedEntities[0])->getGlobalBB_recursive().minCorner();
		maxRel = ccHObjectCaster::ToPointCloud(selectedEntities[0])->getGlobalBB_recursive().maxCorner();
		int npoints = 0;
		for (auto entity : selectedEntities)
		{
			ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(entity);
			npoints = npoints + cloud->size();
			CCVector3d minCornerCloud = cloud->getGlobalBB_recursive().minCorner();
			CCVector3d maxCornerCloud = cloud->getGlobalBB_recursive().maxCorner();
			if (minCornerCloud.x < minRel.x) minRel.x = minCornerCloud.x;
			if (minCornerCloud.y < minRel.y) minRel.y = minCornerCloud.y;
			if (minCornerCloud.z < minRel.z) minRel.z = minCornerCloud.z;
			if (maxCornerCloud.x > maxRel.x) maxRel.x = maxCornerCloud.x;
			if (maxCornerCloud.y > maxRel.y) maxRel.y = maxCornerCloud.y;
			if (maxCornerCloud.z > maxRel.z) maxRel.z = maxCornerCloud.z;
		}
		coord southWest(QString::number(minRel.x), QString::number(minRel.y), "16N", QString::number(minRel.z));
		coord northEast(QString::number(maxRel.x), QString::number(maxRel.y), "16N", QString::number(maxRel.z));
		boundingBoxDTO box(southWest, northEast);
		datasetDTO uploadDataset;
		uploadDataset.setBoundingBox(box);
		spslidarUploadDlg upload(uploadDataset,(QWidget*)appInterface->getMainWindow());
		int result = upload.exec();
		if (result == QDialog::Accepted) {
			if (utm.isEmpty()) initialiceMap();
			
			//We create the header object with default information
			datasetDTO dataset = upload.getDataset();
			LASheader header;
			header.x_scale_factor = 0.01;
			header.y_scale_factor = 0.01;
			header.z_scale_factor = 0.01;
			header.point_data_format = 3;
			header.point_data_record_length = 36;
			
			header.number_of_point_records = npoints;
			header.set_bounding_box(minRel.x, minRel.y, minRel.z, maxRel.x, maxRel.y, maxRel.z, 1, 1);
			LASvlr_key_entry keys[4];
			keys[0].key_id = 1024;
			keys[0].count = 1;
			keys[0].tiff_tag_location = 0;
			keys[0].value_offset = 1;

			keys[1].key_id = 3072;
			keys[1].count = 1;
			keys[1].tiff_tag_location = 0;
			keys[1].value_offset = utm.find(upload.getZone()).value();

			keys[2].key_id = 3076;
			keys[2].count = 1;
			keys[2].tiff_tag_location = 0;
			keys[2].value_offset = 9001;

			keys[3].key_id = 4099;
			keys[3].count = 1;
			keys[3].tiff_tag_location = 0;
			keys[3].value_offset = 9001;
			header.set_geo_keys(4, keys);
			LASwriteOpener laswriteropener;
			LASwriter* writerPointer;

			laswriteropener.set_file_name(rute.toStdString().c_str());
			writerPointer = laswriteropener.open(&header);

			//We init the point
			LASpoint point;
			point.init(&header, header.point_data_format, header.point_data_record_length, 0);

			//Variables used to write in the correct file
			for (auto entity : selectedEntities)
			{
				ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(entity);
				CCVector3d center = cloud->getGlobalBB_recursive().getCenter();
				CCVector3d shift = cloud->getGlobalShift();
				double scale = cloud->getGlobalScale();
				for (int i = 0; i < cloud->size(); ++i) {
					point.set_x((cloud->getPoint(i)->x / scale) - shift.x);
					point.set_y((cloud->getPoint(i)->y / scale) - shift.y);
					point.set_z((cloud->getPoint(i)->z / scale) - shift.z);
					U16 rgbcolor[3] = { cloud->getPointColor(i).r * 256, cloud->getPointColor(i).g * 256, cloud->getPointColor(i).b * 256 };

					point.set_RGB(rgbcolor);

					writerPointer->write_point(&point);
					writerPointer->update_inventory(&point);

				}
			}

			//Closing and deleting laswriters
			writerPointer->close();
			delete writerPointer;
			QString webRute(upload.getRute());
			UploadDlg uploadCloud((QWidget*)appInterface->getMainWindow(),webRute, rute);
			int uploadResult = uploadCloud.exec();
			if(uploadResult==QDialog::Accepted) QMessageBox::information((QWidget*)appInterface->getMainWindow(), "Success", "The cloud could be uploaded succesfully");
		}
	}
	void initialiceMap()
	{
		QString letter = "N";
		int offset = 32601;
		for (int i = 1; i <= 60; i++) {
			utm.insert(QString::number(i) + letter, offset);
			offset++;
		}
		letter = "S";
		for (int i = 1; i <= 60; i++) {
			utm.insert(QString::number(i) + letter, offset);
			offset++;
		}
	}
}