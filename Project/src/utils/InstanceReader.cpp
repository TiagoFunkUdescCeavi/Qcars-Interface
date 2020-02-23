#include "InstanceReader.h"

#include "math.h"

InstanceReader::InstanceReader(string file) {
	this->fileName = file;
}

InstanceReader::~InstanceReader() {
}

Instance InstanceReader::readInstanceNotEuclidean(){
	int cities, cars;
	string aux;
	ifstream file( this->fileName.c_str(), ios::in );

	if( !file ){
		throw runtime_error( "Error on open file: " + this->fileName );
	}

	while( file >> aux ){
		if( aux == "DIMENSION" ){
			file >> aux;
			file >> aux;
			cities = stoi( aux );
		}
		if( aux == "CARS_NUMBER" ){
			file >> aux;
			file >> aux;
			cars = stoi( aux );
		}
		if( aux == "EDGE_WEIGHT_SECTION" ){
			break;
		}
	}

	Instance instance( cars, cities );

	for( int c = 0; c < cars; c++ ){
		Car newCar( cities );

		file >> aux;
		for( int i = 0; i < cities; i++ ){
			for( int j = 0; j < cities; j++ ){
				file >> aux;
				newCar.setEgdeWeigth( i, j, stoi( aux ) );
			}
		}

		instance.setCar( c, newCar );
	}

	file >> aux;
	for( int c = 0; c < cars; c++ ){
		Car actualCar = instance.getCar( c );

		file >> aux;
		for( int i = 0; i < cities; i++ ){
			for( int j = 0; j < cities; j++ ){
				file >> aux;
				actualCar.setReturnRate( i, j, stoi( aux ) );
			}
		}
	}

	file >> aux;
	for( int c = 0; c < cities; c++ ){
		file >> aux;
		instance.setBonusSatisfaction( c, stoi( aux ) );
	}

	file >> aux;
	if( aux != "EOF" ){
		throw runtime_error( "Read of file has incorrect: " + this->fileName );
	}

	return instance;
}

Instance InstanceReader::readInstanceEuclidean(){
	int cities = -1, cars = -1;
	std::vector< int > vec;
	string aux;
	ifstream fileReader( this->fileName.c_str(), ios::in );

	if( !fileReader ){
		throw runtime_error( "Error on open file: " + this->fileName );
	}

	while( fileReader >> aux ){
		if( aux == "DIMENSION" ){
			fileReader >> aux;
			fileReader >> aux;
			cities = stoi( aux );
		}
		if( aux == "CARS_NUMBER" ){
			fileReader >> aux;
			fileReader >> aux;
			cars = stoi( aux );
		}
		if( aux == "NODE_COORD_SECTION" ){
			break;
		}
	}

	Instance instance( cars, cities );
	std::vector< int > satisfaction( cities );
	std::vector< Point > points( cities );

	for( int i = 0; i < cities; i++ ){
		// number of city
		fileReader >> aux;

		fileReader >> aux;
		points[ i ].x = stod( aux );

		fileReader >> aux;
		points[ i ].y = stod( aux );

		fileReader >> aux;
		satisfaction[ i ] = stod( aux );
	}

	// Iniciando a matriz de dist�ncias
	std::vector< std::vector< double > > dist;

	for( int i = 0; i < cities; i++ ){
		for( int j = i; j < cities; j++ ){
			if( i == j ){
				dist[i][j] = 0;
			}else{
				dist[i][j] = (int) (sqrt(pow((points[i].x-points[j].x), 2) + pow((points[i].y-points[j].y), 2)));
				dist[j][i] = dist[i][j];
			}
		}
	}

	// EDGE_WEIGHT_SECTION
	fileReader >> aux;

	for( int c = 0; c < cars; c++ ){
		// numbers of car
		fileReader >> aux;
		std::vector< std::vector< double > > cost;
		Car newCar( cities );

		for( int i = 0; i < cities; i++ ){
			fileReader >> aux;
			vec[i] = stoi( aux );
		}

		for( int i = 0; i < cities; i++ ){
			for( int j = i; j < cities; j++ ){
				if( i == j ){
					cost[i][j] = 0;
				} else {
					cost[i][j] = ((vec[i]*2+vec[j]*3)/3)+(dist[i][j]);
//					cost[i][j] = ((vector[i]*2+vector[j]*3)/3);
					cost[j][i] = cost[i][j];
				}
			}
		}
		for( int i = 0; i < cities; i++ ){
			for( int j = i; j < cities; j++ ){
				newCar.setEgdeWeigth( i, j, cost[ i ][ j ] );
			}
		}
		instance.setCar( c, newCar );
	}

	// RETURN_RATE_SECTION
	fileReader >> aux;

	for( int c = 0; c < cars; c++ ){
		// numbers of car
		fileReader >> aux;
		std::vector< std::vector< double > > rate;
		Car actualCar = instance.getCar( c );

		for( int i = 0; i < cities; i++ ){
			fileReader >> aux;
			vec[i] = stoi( aux );
		}

		for( int i = 0; i < cities; i++ ){
			for( int j = 0; j < cities; j++ ){
				if( i == j ){
					rate[i][j] = 0;
				} else {
					for (int k=0; k < cities; k++){
						rate[i][j] = ((vec[i]*3+vec[j])*4)/2;
					}
//					rate[i][j] = ((vector[i]*3+vector[j]*4)/2);
				}
			}
		}

		for( int i = 0; i < cities; i++ ){
			for( int j = 0; j < cities; j++ ){
				actualCar.setReturnRate( i, j, rate[ i ][ j ] );
			}
		}
	}

	fileReader >> aux;
	if( aux != "EOF" ){
		string s = "Read of file has incorrect: " + fileName;
		throw runtime_error( s );
	}

	return instance;
}

Instance InstanceReader::readInstance(){
	char type = ' ';
	for( int i = this->fileName.size()-1; i >= 0; i++ ){
		if( fileName[ i ] == '.' && fileName[ i-1 ] == 'n' ){
			type = 'n';
			break;
		}
		if( fileName[ i ] == '.' && fileName[ i-1 ] == 's' ){
			type = 's';
			break;
		}
	}

	switch( type ){
		case 'n': return readInstanceNotEuclidean();
		case 's': return readInstanceEuclidean();
		default: throw runtime_error( "Type of instance not found" );
	}
}