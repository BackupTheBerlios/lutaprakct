#ifndef PACKET_H_
#define PACKET_H_

#include "../errors/exceptions.h"
#include <deque>


namespace net{
	
	class Packet{
		
		private:
		
			std::deque <unsigned char> finalPacket;
			int id;
			unsigned short packetLen;
			
		public:
		
			Packet(int MyID);
			Packet(unsigned char* ready, size_t len);

			// Add
			void addBYTE(unsigned char byte);
			void addWORD(unsigned short word);
			void addDWORD(unsigned int dword);
			void addString(const std::string& strg, size_t len = 0);

			// Get
			int getID() const;
			unsigned short getLen() const;
			unsigned char getBYTE() throw(errors::PacketException);
			unsigned short getWORD() throw(errors::PacketException);
			unsigned int getDWORD() throw(errors::PacketException);
			std::string getString(int len = 0) throw(errors::PacketException);

			// Operate
			void seal();
	};
	
};

#endif /*PACKET_H_*/
