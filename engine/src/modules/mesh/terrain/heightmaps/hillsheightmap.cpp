
#include "hillsheightmap.h"
#include "../../../../util/image/tgaimage.h"

#include <iostream>

void HillsHeightmap::generate(std::string filename, unsigned short	 sizex, unsigned short sizey, float hillMin,
						float hillMax, unsigned short numHills, 
						unsigned short	flattening, bool isIsland){

	this->sizex = sizex;
	this->sizey = sizey;
	this->hillMin = hillMin; 
	this->hillMax = hillMax;
	this->numHills = numHills;
	this->isIsland = isIsland;
	this->flattening = flattening;
	
	data = (unsigned char *)malloc(sizeof(unsigned char) * sizex * sizey * 3);
	tempData = new float[sizex * sizey];
	if (tempData == NULL)
		return;
	if (data == NULL)
		return;
	
	std::cout << "adicionando hills" << std::endl;
	for( int i = 1; i < numHills; i++ ){
		addHill();
	}
	std::cout << "adicionando hills2" << std::endl;
	
	std::cout << "normalizando" << std::endl;
	normalize();
	std::cout << "normalizando2" << std::endl;
	std::cout << "flatten" << std::endl;
	flatten();
	std::cout << "flatten2" << std::endl;
	std::cout << "write" << std::endl;
	writeData();
	std::cout << "write2" << std::endl;
	
	//tempData;
	std::cout << "criando tga" << std::endl;
	tgaimage *tga = new tgaimage();
	std::cout << "criando tga2" << std::endl;
	std::cout << "write tga" << std::endl;
	tga->write(filename.c_str(), sizex, sizey, 8, data);
	std::cout << "write tga2" << std::endl;
	delete tga;
}

void HillsHeightmap::clearData(){

	for(unsigned int x = 1; x <= sizex; x++ ){
		for(unsigned int y = 1; y <= sizey; y++ ){
			setCell( x, y, 0 );
		}
	}
	
}

void HillsHeightmap::setCell(unsigned int x, unsigned int y, float value){

	if (tempData == NULL)
		return;

	tempData[x + sizex*y] = value;
	
}

void HillsHeightmap::addHill(){

	if (tempData == NULL)
		return;

	float radius = ((rand() * ( hillMax - hillMin ) / RAND_MAX ) + hillMin);
	
	float x, y;
	if( isIsland ){
		// island code:
		
	/*	float fTheta = RandomRange( 0, 6.28 );
		// this determines in which direction from the center of the map the
		// hill will be placed.
		
		float fDistance = RandomRange( fRadius/2, m_uSize/2 - fRadius );
		// this is how far from the center of the map the hill be placed. note
		// that the radius of the hill is subtracted from the range to prevent
		// any part of a hill from reaching the very edge of the map.
		
		x = m_uSize/2.0 + cos( fTheta ) * fDistance;
		y = m_uSize/2.0 + sin( fTheta ) * fDistance;
		// converts theta and a distance into x and y coordinates.*/
	}else{

		x = (rand() * ( (sizex + radius) - (-radius) ) / RAND_MAX ) + (-radius); 
		y = (rand() * ( (sizex + radius) - (-radius) ) / RAND_MAX ) + (-radius); 
	}

	float radiusSq = radius * radius;
	float distSq;
	float height;
	
	//pega as celulas que serao afetadas
	float xMin = (int) (x - radius - 1);
	float xMax = (int) (x + radius + 1);
	if( xMin < 0 ) xMin = 0;
	if( xMax >= sizex ) xMax = sizex - 1;
	float yMin = (int) (y - radius - 1);
	float yMax = (int) (y + radius + 1);
	if( yMin < 0 ) yMin = 0;
	if( yMax >= sizex ) yMax = sizex - 1;
	
	// determina a altura da celula e adiciona a altura
	for( unsigned int h = xMin; h <= xMax; ++h ){
		for( unsigned int v = yMin; v <= yMax; ++v ){
			// distancia euclidiana pra achar o quao distante o ponto esta da celula
			distSq = ( x - h ) * ( x - h ) + ( y - v ) * ( y - v );
			// determina a altura da coluna
			height = (radiusSq - distSq);
			if( height > 0 ){
				addHeight( h, v, height );
			}	
		}
	}
	
}

void HillsHeightmap::addHeight(unsigned int x, unsigned int y, float value){

	if (tempData == NULL)
		return;

	tempData[x + sizex*y] += value;
	
}

void HillsHeightmap::normalize(){

	if ( tempData == NULL)
		return;
		
	float min = getCell( 0, 0 );
	float max = getCell( 0, 0 );
	
	// find the min and max
	for( int x = 0; x < sizex; ++x ){
		for( int y = 0; y < sizey; ++y ){
			float z = getCell( x, y );
			if( z < min ) min = z;
			if( z > max ) max = z;
		}
	}

	// avoiding divide by zero (unlikely with floats, but just in case)
	if( max != min ){
		// divide every height by the maximum to normalize to ( 0.0, 1.0 )
		for( int x = 0; x < sizex; ++x ){
			for( int y = 0; y < sizey; ++y ){
				setCell( x, y, ( getCell( x, y ) - min ) / ( max - min ) );
			}
		}
	}else{
		//terreno sem altura
		clearData();
	}
	
}

float HillsHeightmap::getCell(unsigned int x, unsigned int y){
	return 	tempData[x + sizex*y];	
}

void HillsHeightmap::flatten(){

	for( int x = 0; x < sizex; ++x ){
		for( int y = 0; y < sizey; ++y ){
			float flat 	= 1.0;
			float original	= getCell( x, y );
				
				for( int i = 0; i < flattening; ++i )
					flat *= original;
				
				setCell( x, y, flat );
			}
		}
	
}

void HillsHeightmap::writeData(){

	for (int x = 1; x <= sizex; x++ )
		for (int y = 1; y <= sizey; y++){
			data[x + sizey*y] = (unsigned char) ( getCell(x, y)*255 );			
			std::cout << getCell(x, y) << std::endl;
		}
	
}

