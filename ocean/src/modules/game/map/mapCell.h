#ifndef _MAPCELL_H_
#define _MAPCELL_H_

#include <vector>

class mapCell{
	
public:
	mapCell() {};
	~mapCell(){};
	
	void addTile (unsigned char tile) { tileList.push_back(tile); }
	std::vector<unsigned char> &getTileList() { return tileList; };
	const std::vector<unsigned char> &getTileList() const { return tileList; };
	
private:

	std::vector<unsigned char> tileList;
};	

#endif //_MAPCELL_H_
