
#include "packet.h"

using namespace net;

Packet::Packet(int MyID){
   id = MyID;
   packetLen = 0;
   return;
}

Packet::Packet(unsigned char* ready, size_t len){
	
   while(len--)
      finalPacket.push_front(ready[len]);

   id = static_cast <int> (getBYTE());
   packetLen = getBYTE();
   return;
}

void Packet::addBYTE(unsigned char byte){
	
   finalPacket.push_back(byte);
   return;
}

void Packet::addWORD(unsigned short word){
	
   finalPacket.push_back(static_cast <unsigned char> ((word >> 8) & 0xFF) );
   finalPacket.push_back(static_cast <unsigned char> ((word >> 0) & 0xFF) );
   return;
}

void Packet::addDWORD(unsigned int dword){
	
   finalPacket.push_back(static_cast <unsigned char> ((dword >> 24) & 0xFF) );
   finalPacket.push_back(static_cast <unsigned char> ((dword >> 16) & 0xFF) );
   finalPacket.push_back(static_cast <unsigned char> ((dword >>  8) & 0xFF) );
   finalPacket.push_back(static_cast <unsigned char> ((dword >>  0) & 0xFF) );
   return;
}

void Packet::addString(const std::string& strg, size_t len){
	
   std::string temp = strg;
   if(len && temp.size() < (len - 1))
      temp.resize(len - 1);
   temp.push_back(0);
   for(size_t i = 0; i < temp.size(); i++)
      finalPacket.push_back(temp[i]);
}

int Packet::getID() const{
   return (int)id;
}

unsigned short Packet::getLen() const{
   return packetLen;
}

unsigned char Packet::getBYTE() throw(errors::PacketException){
   if(finalPacket.size() < 1)
      throw errors::PacketException("Packet underflow");
   unsigned char ret = finalPacket[0];
   finalPacket.erase(finalPacket.begin(), finalPacket.begin() + 1);
   return ret;
}

unsigned short Packet::getWORD() throw(errors::PacketException){
	
   unsigned short ret = 0;

   if(finalPacket.size() < 2)
      throw errors::PacketException("Packet underflow");

   ret = (finalPacket[0] << 8) | (finalPacket[1]);
   finalPacket.erase(finalPacket.begin(), finalPacket.begin() + 2);
   return ret;
}

unsigned int Packet::getDWORD() throw(errors::PacketException){
	
   unsigned int ret = 0;

   if(finalPacket.size() < 4)
      throw errors::PacketException("Packet underflow");

   ret = (finalPacket[0] << 24) | (finalPacket[1] << 16) |
         (finalPacket[2] << 8) | (finalPacket[3]);
   finalPacket.erase(finalPacket.begin(), finalPacket.begin() + 4);
   return ret;
}

std::string Packet::getString(int len) throw(errors::PacketException){
	
   std::string final;
   int i = 0;

   if(finalPacket.size() < static_cast <size_t> (len))
      throw errors::PacketException("Packet underflow");

   while(finalPacket.size())
   {
      char cur = finalPacket[0];
      finalPacket.pop_front();
      if(cur && cur != '\r' && cur != '\n' && cur != '\t') {
         final.push_back(cur);
      } else {
         if(i >= len)
            break;
      }
      i++;
      if(len != 0 && i >= len)
         break;
   }
   return final;
}

void Packet::seal(){
	
   packetLen = static_cast <unsigned short> (finalPacket.size() + 2);

   finalPacket.push_front(static_cast <unsigned char> (packetLen));
   finalPacket.push_front(static_cast <unsigned char> (id));
}
