#include "Car.h"
#include <iostream>

using namespace std;

Car::Car( int dimension ) {
	this->dimension = dimension;
	this->edgeWeigth.resize( dimension );
	this->returnRate.resize( dimension );
	for( int i = 0; i < dimension; i++ ){
		this->edgeWeigth[ i ].resize( dimension );
		this->returnRate[ i ].resize( dimension );
	}
}

Car::~Car() {
}

void Car::setEgdeWeigth( int x, int y, int value ){
	this->edgeWeigth[ x ][ y ] = value;
}

void Car::setReturnRate( int x, int y, int value ){
	this->returnRate[ x ][ y ] = value;
}

int Car::getEdgeWeigth( int x, int y ){
	return this->edgeWeigth[ x ][ y ];
}

int Car::getReturnRate( int x, int y ){
	return this->returnRate[ x ][ y ];
}

void Car::toString(){
	for( int b = 0; b < this->dimension; b++ ){
		for( int c = 0; c < this->dimension; c++ ){
			cout << this->getEdgeWeigth( b, c ) << "\t";
		}
		cout << endl;
	}
	cout << "<<<<<<<<<<<<<<<<" << endl;
	for( int b = 0; b < this->dimension; b++ ){
		for( int c = 0; c < this->dimension; c++ ){
			cout << this->getReturnRate( b, c ) << "\t";
		}
		cout << endl;
	}
	cout << "<<<<<<<<<<<<<<<<" << endl;
}
