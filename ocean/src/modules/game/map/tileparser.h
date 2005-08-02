#ifndef _TILEPARSER_H_
#define _TILEPARSER_H_

#include <string>
#include <vector>

struct tileInfo
{
    std::string name;
    int rectX;
    int rectY;
    int rectW;
    int rectH;
    int offsetH;
    int offsetV;
};

struct tileImage
{
    std::string filename;
    std::vector<tileInfo> tiles;
};

typedef std::vector<tileImage> tileset;

class tilesetParser{
	
public:
	tilesetParser();
	~tilesetParser();
    
	tileset &getTileset() { return Tileset; }
        
	void parse(std::string filename);
	  
private:

	std::string imageFilename;
    
	tileset Tileset;
};

#endif //_TILEPARSER_H_
