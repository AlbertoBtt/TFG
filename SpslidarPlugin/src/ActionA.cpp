/*****************************************************************//**
 * @file   ActionA.cpp
 * @brief  Implementation of the plugin's actions
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
 //#						     COPYRIGHT:									#
 //#					 Alberto Beteta Fernandez							#                     
 //#				   Rafael Jesús Segura Sánchez							#
 //#				    Antonio Jesús Rueda Ruíz							#
 //#                  Carlos Javier Ogayar Anguita                          #
 //#                                                                        #
 //##########################################################################

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
	QMap<QString, int> utm; ///<Map where the UTM zones are saved

	/**
	 * @brief Action to download a cloud from a server
	 * 
	 * @param [in] appInterface The main interface of CloudCompare
	 */
	void performActionDownload(ccMainAppInterface* appInterface)
	{
		if (appInterface == nullptr)
		{
			// The application interface should have already been initialized when the plugin is loaded
			Q_ASSERT(false);

			return;
		}
		spslidarDownloadDlg interfaz((QWidget*)appInterface->getMainWindow());
		//Execute the Dialog to obtain the dataset where the cloud will be downloaded
		int result=interfaz.exec();
		//Only continue if the Dialog finished correctly
		if (result == QDialog::Accepted)
		{
			//Create a new cloud from CloudCompare
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
			//Read all points from the .laz download and add it to the Cloud
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
			//Finally add the new cloud to the Database of CloudCompare
			appInterface->addToDB(cloud);
		}
	}

	/**
	 * @brief Action to upload a new cloud to a Server
	 * 
	 * @param [in] appInterface The main interface of CloudCompare
	 */
	void performActionUpload(ccMainAppInterface* appInterface)
	{
		if (appInterface == nullptr)
		{
			// The application interface should have already been initialized when the plugin is loaded
			Q_ASSERT(false);

			return;
		}
		
		//Assert that the dir %TempLocation%/spslidar/LAZ exists
		QDir dir(QString(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + "/spslidar/LAZ");
		if (!dir.exists()) dir.mkpath(".");
		//Create a new empty up.laz, if it exists will be deleted
		QString rute = QString(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + "/spslidar/LAZ/up.laz";
		if (QFile::exists(rute)) {
			QFile::remove(rute);
		}
		//Obtain the selected entities in CloudCompare
		const ccHObject::Container& selectedEntities = appInterface->getSelectedEntities();
		//Assert that the selected entities are correct
		bool typesCorrect = true;
		int c = 0;
		while (typesCorrect && c<selectedEntities.size()) {
			typesCorrect=selectedEntities[c]->isA(CC_TYPES::POINT_CLOUD);
			++c;
		}
		if (typesCorrect) {
			//Calculate the Bounding Box of all selected clouds
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
			//Create a default dataset with the Bounding box because the upload Dialog will use it to recommend the Bounding Box of the new dataset
			coord southWest(QString::number(minRel.x), QString::number(minRel.y), "30N", QString::number(minRel.z));
			coord northEast(QString::number(maxRel.x), QString::number(maxRel.y), "30N", QString::number(maxRel.z));
			boundingBoxDTO box(southWest, northEast);
			datasetDTO uploadDataset;
			uploadDataset.setBoundingBox(box);
			spslidarUploadDlg upload(uploadDataset, (QWidget*)appInterface->getMainWindow());
			//Execute the spslidarUploadDlg to obtain the path where the new cloud will be saved and to obtain the basic information to create the new .laz
			int result = upload.exec();
			if (result == QDialog::Accepted) {
				if (utm.isEmpty()) initialiceMap();

				//Obtain the final dataset
				datasetDTO dataset = upload.getDataset();
				//Set the default information of the .laz
				LASheader header;
				header.x_scale_factor = 0.01;
				header.y_scale_factor = 0.01;
				header.z_scale_factor = 0.01;
				header.point_data_format = 3;
				header.point_data_record_length = 36;

				header.number_of_point_records = npoints;
				header.set_bounding_box(minRel.x, minRel.y, minRel.z, maxRel.x, maxRel.y, maxRel.z, 1, 1);

				//Insert the GeoLocalization keys in the .laz
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

				//Go through all clouds saving their points in the .laz
				for (auto entity : selectedEntities)
				{
					ccPointCloud* cloud = ccHObjectCaster::ToPointCloud(entity);
					CCVector3d center = cloud->getGlobalBB_recursive().getCenter();
					//Get the Shift applied to the Cloud
					CCVector3d shift = cloud->getGlobalShift();
					double scale = cloud->getGlobalScale();
					for (int i = 0; i < cloud->size(); ++i) {
						//Calculate the coordinates of the point without the shift
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
				UploadDlg uploadCloud((QWidget*)appInterface->getMainWindow(), webRute, rute);
				//Execute the UploadDlg to upload the cloud to the server
				int uploadResult = uploadCloud.exec();
				if (uploadResult == QDialog::Accepted) QMessageBox::information((QWidget*)appInterface->getMainWindow(), "Success", "The cloud was uploaded successfully");
			}
		} else {
			QMessageBox::warning((QWidget*)appInterface->getMainWindow(), "Entities Error", "You just can select clouds\nThe clouds have the suffix - Cloud");
		}
	}

	/**
	 * @brief Initialize the Map with all the UTM Zones and their offsets
	 * 
	 */
	void initialiceMap()
	{
		QString letter = "N";
		int offset = 32601;
		for (int i = 1; i <= 60; i++) {
			utm.insert(QString::number(i) + letter, offset);
			offset++;
		}
		letter = "S";
		offset = 32701;
		for (int i = 1; i <= 60; i++) {
			utm.insert(QString::number(i) + letter, offset);
			offset++;
		}
	}
}