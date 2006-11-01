#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <string>

namespace errors
{

	class Exception{
		private:
			const std::string errorText;
		public:
			Exception(const std::string & text = "No Description") : errorText(text) { }
			virtual const std::string & getText() const{
				return errorText;
			}
			virtual ~Exception(){ }
	};

	class FileException : public Exception{
		private:
			const std::string fileName;
		public:
			FileException(const std::string & text, const std::string & file) :
			Exception(text), fileName(file) { }
			const std::string & getText() const{
			static std::string final = "FileException: '" + Exception::getText() + "' while processing '" + fileName + "'";
				return final;
			}
   };


	class NetworkException : public Exception{
		public:
			NetworkException(const std::string & text) :
			Exception(text) { }
			const std::string & getText() const{
				static std::string final = "NetworkException: " + Exception::getText();
				return final;
			}
	};

	class PacketException : public NetworkException{
		public:
			PacketException(const std::string & text) :
			NetworkException(text) { }
			const std::string & getText() const{
				static std::string final = "PacketException: " + Exception::getText();

				return final;
			}
	};
   
}


#endif //_EXCEPTIONS_H_
