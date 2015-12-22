#ifndef MeshLoadManeger_H
#define MeshLoadManager_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Tools/Utils/getopt.h>
#include <QDebug>
#include <QVector2D.h>
#include <QVector3D.h>
#include <QString>
//#include "Mesh/Pnt3d.h"



class MeshLoadManager
{
public:
	MeshLoadManager();

	struct TextureInfo
	{
		struct UV
		{
			std::vector<int>  vertexHandleIndex;
			std::vector<double> u;
			std::vector<double> v;
		};
		std::string meshTextureName;
		std::string meshTexturePath;
		std::string meshCoordName;
<<<<<<< HEAD
		std::string meshCoordPath;

=======
>>>>>>> origin/master

		std::vector<int> faceHandleIndex;

		double  delta;

		UV uv;
	};
	TextureInfo textureInfo;


<<<<<<< HEAD
public:

=======
	public:
	
>>>>>>> origin/master
	std::vector<TextureInfo> textureInfoVector;

	std::string modelName;
	int textureInfoVectorSize;
<<<<<<< HEAD
	void textureInfoVectorSizeCount();

	void addSingleTextureInfo(TextureInfo);

	
=======


	void addSingleTextureInfo(TextureInfo);

	void textureInfoVectorSizeCount();
>>>>>>> origin/master
	void saveFaceDataToTxt(std::string);
	void openFileAndLoadData(std::string);
	char * loadPathTxt(std::string);

	void loadFaceDataFromTxt(char*, int);//load coord txt

	void loadDemoDataFromTxt(char *);//load big txt

	void exportDataToDemoTxt(std::string);

	void printLoadData();
	//
	char * stringToken(char*, char*, char **);
	char * stringPopBreak(char*, char*);
};

#endif