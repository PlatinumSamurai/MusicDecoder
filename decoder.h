#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ios>
#include <iostream>


class Decoder {
private:
	std::string encoded;
    	std::ifstream fin;
    	std::ofstream fout;
    	std::vector<int> offsets = {0x0D, 0x1E, 0x2F, 0x40, 0x51, 0x62, 0x73, 0x84, 
		                    0x95, 0xA6, 0xB7, 0xC8, 0xD9, 0xEA, 0xFB, 0x0C};
	
public:
    	Decoder(const std::string &encodedFile, const std::string &directoryToSave = "");
    	void applyOffsets();
    	void close();
};
