#save txt file to

./textureInfo/ "Demo.txt,座標檔案，圖片檔案都放這裡"

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

	void MainWindow::on_saveFaceButton_clicked()
	{
		QString filename = QFileDialog::getSaveFileName(this, tr("Save Text"), "", tr("*.txt"));
		QFile fileq(filename);
		std::string a = fileq.fileName().toStdString();

		ui->glFramework->mesh->savePath(a);
	}
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


#2.讀取面的資料,<br>讀完可以在meshLoadManager->textureInfo取得
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
	
#4.印出內容

	meshLoadManager->printLoadData();


#5.一鍵Demo

	void MainWindow::on_DemoButton_clicked()
	{
		std::string fileName = "./textureInfo/Demo.txt";
		meshLoadManager = ui->glFramework->mesh->meshLoadManager;
		meshLoadManager->openFileAndLoadData(fileName);
	}

使用 
	int tIVSize = meshLoadManager->textureInfoVectorSize //int vector size
	
	meshLoadManager->textureInfoVector[  ].faceHandleIndex[  ]
	meshLoadManager->textureInfoVector[  ].uv.vertexHandleIndex[  ]
	meshLoadManager->textureInfoVector[  ].uv.u[ ]
	meshLoadManager->textureInfoVector[  ].uv.v[ ]
	
	meshLoadManager->textureInfoVector[  ].meshTextureName;
	meshLoadManager->textureInfoVector[  ].meshCooreName;
	meshLoadManager->textureInfoVector[  ].delta;
	
	meshLoadManager->printLoadData(); //
	
# external 存face iterator idx

UI與之前 savePath 相同作法 呼叫 GUA的 saveFaceIteratorIdxPath 
即可將idx存檔

	void Tri_Mesh::saveFaceIteratorIdxPath(std::string fileName)
	{
		fstream file;
		file.open(fileName, fstream::out);
		
		if (file.is_open()) {
			file << (int)這裡放faceiteratoridx << ',';			
		}
		file.close();
	}

GUA_OM.cpp 使用時
	
	char * temp = (char*)malloc(sizeof(char)* 100000);
	temp = meshLoadManager->loadPathTxt(fileName); // 傳進去要讀的檔名
	meshLoadManager->loadFaceIterIdxFromTxt(temp); // 執行後 將idx 存進meshLoadManager->faceIteratorIdxVector


	
