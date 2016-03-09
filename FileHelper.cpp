#include "FileHelper.h"

FileHelper::FileHelper() {
}

int FileHelper::numOfConnections = 0;
int FileHelper::numOfVertices = 0;

void FileHelper::ReadData(string fileName, float* &vertices, int* &connections) {
	ifstream inStream;
	inStream.open(fileName.c_str());
	
	if (!inStream) {
		cout << "Can not open this file" << endl;
	} else {
		// read vertices
		inStream >> FileHelper::numOfVertices;
		vertices = new float[FileHelper::numOfVertices * 3];
		// loop through all float numbers
		// number of floats = number of vertices * 3
		for (int i=0; i < FileHelper::numOfVertices * 3; i++) {
			inStream >> vertices[i];
		}
		
		// read connections
		inStream >> FileHelper::numOfConnections;
		connections = new int[FileHelper::numOfConnections * 3];
		// loop through all int numbers
		// number of ints = number of connections * 3
		for (int i=0; i < FileHelper::numOfConnections * 3; i++) {
			inStream >> connections[i];
		}
	}
	inStream.close();
}
