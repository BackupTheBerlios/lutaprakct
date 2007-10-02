#ifndef STRINGTOKENIZER_H_
#define STRINGTOKENIZER_H_

#include <iostream>
#include <string>

class StringTokenizer{
	
	public:
		
			StringTokenizer(const std::string&s, const char* delim = NULL):
			str(s), count(-1), begin(0), end(0){
				
				if (!delim)
					delim = " \f\n\r\t\v";
				else
					this->delim = delim;
					
				begin = str.find_first_not_of(delim);
				end = str.find_first_of(delim, begin);
				
			}
			
			unsigned int countTokens(){
				if (count >= 0)
					return count;
				
				std::string::size_type n = 0;
				std::string::size_type i = 0;
				
				for(;;){
					if  ((i = str.find_first_not_of(delim, i)) == std::string::npos)
						break;
					i = str.find_first_of(delim, i+1);
					n++;
					if (i == std::string::npos)
						break;
				}
				return (count = n);
			}
			
			bool hasMoreTokens() { return (begin!= end); }
			
			void nextToken(std::string& s){
				
				if (begin != std::string::npos && end != std::string::npos){
					s = str.substr(begin, end-begin);
					begin = str.find_first_not_of(delim, end);
					end = str.find_first_of(delim, begin);
				}else if (begin != std::string::npos && end == std::string::npos){
					s = str.substr(begin, str.length()-begin);
					begin = str.find_first_not_of(delim, end);
				}
			}
			
	private:
	
		StringTokenizer(){};
		
		std::string delim;
		std::string str;
		
		int count;
		int begin;
		int end;
			
};


#endif /*STRINGTOKENIZER_H_*/
