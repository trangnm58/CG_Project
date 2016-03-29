#include "FileHelper.h"

FileHelper::FileHelper() {
}

int FileHelper::numOfConnections = 0;
int FileHelper::numOfVertices = 0;

void FileHelper::ReadData(string fileName, float* &vertices, unsigned int* &connections) {
	ifstream inStream;
	inStream.open(fileName.c_str());
	
	if (!inStream) {
		cout << "Can not open " << fileName << " file" << endl;
	} else {
		// read vertices
		inStream >> FileHelper::numOfVertices;
		vertices = new float[FileHelper::numOfVertices * 3 * 2];
		// loop through all float numbers
		// number of floats = number of vertices * 3
		for (int i=0; i < FileHelper::numOfVertices * 3; i++) {
			inStream >> vertices[i];
		}
		// append right face vertices to 'vertices' array
		for (int i=0; i < FileHelper::numOfVertices * 3; i += 3) {
			vertices[i + FileHelper::numOfVertices * 3] = -vertices[i];
			vertices[i + 1 + FileHelper::numOfVertices * 3] = vertices[i + 1];
			vertices[i + 2 + FileHelper::numOfVertices * 3] = vertices[i + 2];
		}
		// read connections
		inStream >> FileHelper::numOfConnections;
		connections = new unsigned int[FileHelper::numOfConnections * 3 * 2];
		// loop through all numbers
		// number of ints = number of connections * 3
		for (int i=0; i < FileHelper::numOfConnections * 3; i++) {
			inStream >> connections[i];
		}
		// append right face connections to 'connections' array
		for (int i=0; i < FileHelper::numOfConnections * 3; i++) {
			connections[i + FileHelper::numOfConnections * 3] = connections[i] + FileHelper::numOfVertices;
		}
	}
	inStream.close();
}
