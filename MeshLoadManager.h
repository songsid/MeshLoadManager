#ifndef MeshLoadManeger_H
#define MeshLoadManager_H
#define _USE_MATH_DEFINES

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
		std::string name;
		std::string meshTextureName;
		std::string meshCoordName;
		double  delta;

		UV uv;
	};
	TextureInfo textureInfo;

	public:
	
	std::vector<TextureInfo> textureInfoVector;

	void saveFaceDataToTxt(std::string);
	void openFileAndLoadData(std::string);
	char * loadPathTxt(std::string);
	void loadFaceDataFromTxt(char*, int);


	void loadDemoDataFromTxt(char * );

	void printLoadData();
	//
	char * stringToken(char* , char* ,char ** );
	char * stringPopBreak(char* , char* );
};

#endif