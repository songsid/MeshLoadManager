#include "MeshLoadManager.h"

char delimiterChars[] = { ',' };

MeshLoadManager::MeshLoadManager()
{
	textureInfoVector.clear();
	textureInfoVector.resize(20);
}


void MeshLoadManager::printLoadData()
{
	int sizeTexture = textureInfoVector.size();

	for (int s = 0; s < sizeTexture; s++){
		std::cout << "  name :" << textureInfoVector[s].name ;
		std::cout << "  tName :" << textureInfoVector[s].meshTextureName ;
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
	char * temp = (char*)malloc(sizeof(char)* 200000);


	file.open(fileName, std::fstream::in);
	if (file.is_open()){
		file >> temp;

		loadDemoDataFromTxt(temp);

	}
	free(temp);
	file.close();
}

char* MeshLoadManager::loadPathTxt(std::string fileName)
{
	std::fstream file;
	char* temp = (char*)malloc(sizeof(char)* 100000);
	file.open(fileName, std::fstream::in);

	if (file.is_open()) {
		file >> temp;
		file.close();
		return temp;
	}
}
void MeshLoadManager::loadFaceDataFromTxt(char *dataString, int textureIndex)
{
	int faceNum=0;
	int faceIndex = 0;
	int vectorIndex = 0;
	double textureCoord = 0;
	char delimiterChars[] = { ',' };
	char * lastToken = NULL;

	if (textureInfoVector[textureIndex].uv.vertexHandleIndex.size())
	{
		textureInfoVector[textureIndex].uv.vertexHandleIndex.clear();
		textureInfoVector[textureIndex].uv.u.clear();
		textureInfoVector[textureIndex].uv.v.clear();
	}
	
	faceNum = atoi(stringToken(dataString, delimiterChars,&lastToken));//�s���X�ӭ�	
	faceIndex = atoi(stringToken(NULL, delimiterChars,&lastToken));
	while (faceIndex){
		for (int i = 0; i<3; i++)
		{
			vectorIndex = atoi(stringToken(NULL, delimiterChars, &lastToken));
			textureInfoVector[textureIndex].uv.vertexHandleIndex.push_back(vectorIndex);
			textureCoord = atof(stringToken(NULL, delimiterChars, &lastToken));//�s�I��cx
			textureInfoVector[textureIndex].uv.u.push_back(textureCoord);
			textureCoord = atof(stringToken(NULL, delimiterChars, &lastToken));//�s�I��cy
			textureInfoVector[textureIndex].uv.v.push_back(textureCoord);
		}

		faceIndex = atoi(stringToken(NULL, delimiterChars, &lastToken));
	}
}

void MeshLoadManager::loadDemoDataFromTxt(char* dataString)
{
	int textureNum = 0;
	char * name = (char*) malloc(sizeof(char)*200000);
	char * c = (char*)malloc(sizeof(char)* 200000);
	char * lastToken = NULL;
	std::fstream file;
	std::string tempString;

	FILE * fp;
	textureNum = atoi(stringToken(dataString, delimiterChars, &lastToken));//�s���X�i�K��

	for (int i = 0; i < textureNum; i++){
		name = stringToken(NULL, delimiterChars, &lastToken);//fine txt
		//printf("%s", name);
		textureInfoVector[i].name = tempString.assign(name);
		file.open(name, std::fstream::in);
		//�h��Ƨ���W�r�@�˪����
		if (file.is_open()){ //�����ɦW�ö}�Ҧ��\
			file >> c;
			loadFaceDataFromTxt(c,i);
			
		}
		file.close();
		name = stringToken(NULL, delimiterChars, &lastToken);//bind png
		textureInfoVector[i].meshTextureName = tempString.assign(name);
		//std::cout << "textureInfo Vecotr .t name = " << textureInfoVector[i].meshTextureName;
		//}
		

	}
	printLoadData();
	
}
// string 
char *  MeshLoadManager::stringToken(char* inputString, char* delimiterChars,char ** lastToken){
	
	char *tmp;
	if (inputString == NULL){
		inputString = *lastToken;
		if (inputString == NULL)//�r��S���Ѿl��token�F
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