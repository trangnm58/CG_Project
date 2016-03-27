#ifndef FileHelper_H
#define FileHelper_H

#include <fstream>
#include <iostream>

using namespace std; 

class FileHelper {
	public:
		FileHelper();

		void ReadData(string, float*&, unsigned int*&);
		
		static int numOfVertices;
		static int numOfConnections;
};

#endif // FileHelper_H

