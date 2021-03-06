#include "MeshLoadManager.h"

char delimiterChars[] = { ',' };

MeshLoadManager::MeshLoadManager()
{
	textureInfoVector.clear();
	textureInfoVector.resize(100);
	textureInfoVectorSize = 0;
	
	faceIteratorIdxVector.clear();
	faceIteratorIdxVector.resize(1000);
}

void MeshLoadManager::addSingleTextureInfo(TextureInfo singleTexture)
{
	if (textureInfoVectorSize == 0)
	{
		textureInfoVector[0] = singleTexture;
	}
	else
	{
		textureInfoVector.push_back(singleTexture);
	}
	textureInfoVectorSizeCount();
}

void MeshLoadManager::textureInfoVectorSizeCount()
{
	int sizeTexture = textureInfoVector.size();
	textureInfoVectorSize = 0;
	for (int k = 0; k < sizeTexture; k++)
	{
		if ((textureInfoVector[k].meshTextureName.length() > 0) || (textureInfoVector[k].meshCoordName.length() > 0))
			textureInfoVectorSize++;
	}
}

void MeshLoadManager::printLoadData()
{

	printf("realSize = %d", textureInfoVectorSize);
	for (int s = 0; s < textureInfoVectorSize; s++){
		std::cout << "TexrureName :" << textureInfoVector[s].meshTextureName << " " << textureInfoVector[s].meshTexturePath;
		printf("\n");
		std::cout << "CoordName :" << textureInfoVector[s].meshCoordName << " " << textureInfoVector[s].meshCoordPath;
		printf("\n");
		std::cout << "RotateDelta :" << textureInfoVector[s].delta;
		printf("\n");
		int sizeofVector = textureInfoVector[s].uv.vertexHandleIndex.size();

		for (int i = 0; i < sizeofVector; i++)
		{
			qDebug() << "i = " << i << "vertexindex=" << textureInfoVector[s].uv.vertexHandleIndex[i] << textureInfoVector[s].uv.u[i] << textureInfoVector[s].uv.v[i];
		}
	}
}
void MeshLoadManager::openFileAndLoadData(std::string fileName)
{
	std::fstream file;
	char * temp = (char*)malloc(sizeof(char) * 200000);

	file.open(fileName, std::fstream::in);
	if (file.is_open()){
		file >> temp;
		loadDemoDataFromTxt(temp);

	}
	textureInfoVectorSizeCount();
	free(temp);
	file.close();
}

char* MeshLoadManager::loadPathTxt(std::string fileName)
{
	std::fstream file;
	char* temp = (char*)malloc(sizeof(char) * 100000);
	file.open(fileName, std::fstream::in);

	if (file.is_open()) {
		file >> temp;
		file.close();
		return temp;
	}
}
void MeshLoadManager::loadFaceDataFromTxt(char *dataString, int textureIndex)
{
	int faceNum = 0;
	int faceIndex = 0;
	int vectorIndex = 0;
	double textureCoord = 0;
	char delimiterChars[] = { ',' };
	char * lastToken = NULL;

	if (textureInfoVector[textureIndex].uv.vertexHandleIndex.size() || textureInfoVector[textureIndex].faceHandleIndex.size())
	{
		textureInfoVector[textureIndex].uv.vertexHandleIndex.clear();
		textureInfoVector[textureIndex].uv.u.clear();
		textureInfoVector[textureIndex].uv.v.clear();
		textureInfoVector[textureIndex].faceHandleIndex.clear();
	}


	faceNum = atoi(stringToken(dataString, delimiterChars, &lastToken));//存有幾個面

	textureInfoVector[textureIndex].faceHandleIndex.resize(faceNum);

	textureInfoVector[textureIndex].delta = atof(stringToken(NULL, delimiterChars, &lastToken));

	faceIndex = atoi(stringToken(NULL, delimiterChars, &lastToken));

	textureInfoVector[textureIndex].faceHandleIndex.push_back(faceIndex);//save faceIndex

	while (faceIndex){
		for (int i = 0; i < 3; i++)
		{
			vectorIndex = atoi(stringToken(NULL, delimiterChars, &lastToken));
			textureInfoVector[textureIndex].uv.vertexHandleIndex.push_back(vectorIndex);


			textureCoord = atof(stringToken(NULL, delimiterChars, &lastToken));//存點的cx
			textureInfoVector[textureIndex].uv.u.push_back(textureCoord);

			textureCoord = atof(stringToken(NULL, delimiterChars, &lastToken));//存點的cy
			textureInfoVector[textureIndex].uv.v.push_back(textureCoord);
		}
		faceIndex = atoi(stringToken(NULL, delimiterChars, &lastToken));
		if (faceIndex) textureInfoVector[textureIndex].faceHandleIndex.push_back(faceIndex); //
	}
	textureInfoVectorSizeCount();

}

void MeshLoadManager::loadDemoDataFromTxt(char* dataString)
{
	int textureNum = 0;
	char * name = (char*)malloc(sizeof(char) * 200000);
	char * c = (char*)malloc(sizeof(char) * 200000);
	char * lastToken = NULL;
	std::fstream file;
	std::string tempString;

	FILE * fp;
	textureNum = atoi(stringToken(dataString, delimiterChars, &lastToken));//存有幾張貼圖

	for (int i = 0; i < textureNum; i++){
		name = stringToken(NULL, delimiterChars, &lastToken);//fine txt
		//printf("%s", name);
		textureInfoVector[i].meshCoordName = tempString.assign(name);

		char* buf = (char*)malloc(sizeof(char) * 256);
		printf("nwri");
		int nWritten = qsnprintf(buf, 256, "./textureInfo/%s", name);
		std::cout << "buf = " << buf;

		textureInfoVector[i].meshCoordPath = buf;

		file.open(buf, std::fstream::in);
		//去資料夾找名字一樣的文件
		if (file.is_open()){ //有此檔名並開啟成功
			file >> c;
			loadFaceDataFromTxt(c, i);

		}
		file.close();
		name = stringToken(NULL, delimiterChars, &lastToken);//bind png
		textureInfoVector[i].meshTextureName = tempString.assign(name);

		QString fileName = QString::fromStdString(textureInfoVector[i].meshTextureName);
		QString base = "./textureInfo/";
		base += fileName;
		textureInfoVector[i].meshTexturePath = base.toStdString();
	}
}

void MeshLoadManager::exportDataToDemoTxt(std::string fileName)
{
	/* in mainwindow you need to call below func and exportDataToDemoTxt
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Text"), "", tr("*.txt"));
	QFile fileq(filename);
	std::string a = fileq.fileName().toStdString();
*/

	std::fstream file;
	file.open(fileName, std::fstream::out);
	if (file.is_open()) {
		file << textureInfoVectorSize << ',';
		for (int i = 0; i < textureInfoVectorSize; i++)
		{
			file << textureInfoVector[i].meshCoordName << ',' << textureInfoVector[i].meshTextureName << ',';	
		}
		file.close();
	}


}

void loadFaceIterIdxFromTxt(char * dataString)
{
	// 初始化
	int faceIndex = 0;
	char delimiterChars[] = { ',' };
	char * lastToken = NULL;

	faceIndex = atoi(stringToken(dataString, delimiterChars, &lastToken));//存faceIteratorIndex
	if(faceIndex) faceIteratorIdxVector.push_back(faceIndex);
	
	while (faceIndex){
		faceIndex = atoi(stringToken(dataString, delimiterChars, &lastToken));//存faceIteratorIndex
		if(faceIndex) faceIteratorIdxVector.push_back(faceIndex);
	}
}

// string 
char *  MeshLoadManager::stringToken(char* inputString, char* delimiterChars, char ** lastToken){

	char *tmp;
	if (inputString == NULL){
		inputString = *lastToken;
		if (inputString == NULL)//字串沒有剩餘的token了
			return NULL;
	}

	tmp = stringPopBreak(inputString, delimiterChars);
	if (tmp) {
		*tmp = '\0';
		*lastToken = tmp + 1;
	}
	else
		*lastToken = NULL;
	return inputString;
}
char *  MeshLoadManager::stringPopBreak(char* inputString, char* delimiterChars){
	for (char *start = inputString; *start != '\0'; start++)
	{
		for (char *start1 = delimiterChars; *start1 != '\0'; start1++)
		{
			if (*start == *start1)
			{
				return start;
			}
		}
	}
	return NULL;
}
