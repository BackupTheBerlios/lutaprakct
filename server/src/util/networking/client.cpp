
#include "client.h"
#include <iostream>
using namespace net;

void Client::popPacket(){
	packets.pop();
}

void Client::send(Packet& data){
	clientSocket.sendPacket(data);
}

void Client::addChunk(unsigned char* Chunk, size_t size){

	for(size_t i = 0; i < size; i++)
		buffer.push_back(Chunk[i]);
	//if(buffer[0] != Magic)
		//Net.Disconnect(this);
		
	while(buffer.size() > 0){ // se tive algo no buffer
		unsigned short len = (buffer[2] << 8) | (buffer[3]);
		//std::cout << "len " << len << std::endl;
		len = size;
		if(buffer.size() >= len) {
			unsigned char *temp = new unsigned char[len];
			for(size_t i = 0; i < len; i++)
				temp[i] = buffer[i];
			packets.push(Packet(temp, len));
			delete [] temp;
			buffer.erase(buffer.begin(), buffer.begin() + len);
		}else {
			break;
		}
	}
	
	return;
	
}

Packet& Client::getFirstPacket(){

	return packets.front();
	
}
