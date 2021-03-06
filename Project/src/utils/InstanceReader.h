#ifndef INSTANCEREADER_H_
#define INSTANCEREADER_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>

#include "../model/Instance.h"

using namespace std;

class InstanceReader {
public:
	InstanceReader(string file );
	virtual ~InstanceReader();

	/**
	 * Read and return instance from file.
	 */
	Instance readInstance();

private:
	/**
	 * File name to be read
	 */
	string fileName;

	/**
	 * Non-Euclidean Instance reading
	 */
	Instance readInstanceNotEuclidean();

	/**
	 * Euclidean Instance reading
	 */
	Instance readInstanceEuclidean();

	struct Point{
		double x, y;
	};

	int **createMatrix( int a, int b ){
		int **m = new int*[a];
		for( int i = 0; i < a; i++ ){
			m[i] = new int[b];
		}
		return m;
	}
};

#endif /* INSTANCEREADER_H_ */
