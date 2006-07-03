#ifndef SKYDOME_H_
#define SKYDOME_H_


class Skydome{
	
public:

	Skydome();
	Skydome(int sides, int slides);
	~Skydome();
	
	void getSlices(){ return slices; };
	void getSide(){ return sides; };
	
	void setSlices(int slices){ this->slices = slices; };
	void setSides(int sides){ this->sides = sides; };


private:

	int slices, sides;
	
	
};


#endif /*SKYDOME_H_*/
