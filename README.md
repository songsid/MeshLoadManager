#save txt file to
QOpenGL_1_1\Demo1.txt <br>
QOpenGL_1_1\textureInfo\

#error _USE_MATH_DEFINES
property -> C/C++ -> Preprocessor -> Preprocessor Definitions <br>
add _USE_MATH_DEFINES <br>


#Init
若要在Tri_Msh呼叫MeshLoadManager 請於此初始化 <br>
.h要宣告MeshLoadManager * meshLoadManager;

    Tri_Mesh::Tri_Mesh()
    {
	meshLoadManager = new MeshLoadManager;
    }


#1.選面後執行savePatch ，存面的資料


    void Tri_Mesh::savePath(std::string fileName){
	fstream file;
	file.open(fileName, fstream::out);
	if (file.is_open()) {
		file << m_select_faces.size() <<',';
		for (FIter f_it = faces_begin(); f_it != faces_end(); ++f_it){
			for (int i = 0; i < m_select_faces.size(); i++){
				if (m_select_faces[i] == f_it.handle()) {

					file << f_it.handle().idx()<<',';
				
					for (FVIter fv_it = fv_iter(f_it); fv_it; ++fv_it)
					{
						file << fv_it.handle().idx()<<',';
						file <<'1' << ',' << '1' << ',';

					}
				}
			}
		}
		file.close();
	}
    }


#2.讀取面的資料,讀完可以在meshLoadManager->textureInfo取得
    void Tri_Mesh::loadPath(std::string fileName){

	char * temp = (char*)malloc(sizeof(char)* 100000);

	//return all char in txt
	temp = meshLoadManager->loadPathTxt(fileName);

	//stringToken
	meshLoadManager->loadFaceDataFromTxt(temp,0);
	free(temp);
    }

#3.一鍵讀Demo.txt檔

	std::string fileName = "./textureInfo/Demo.txt";

	//open, read and push_back to vector
	meshLoadManager->openFileAndLoadData(fileName);



