#include "decoder.h"

Decoder::Decoder(const std::string &encodedFile, const std::string &directoryToSave) {
	std::string decodedFile;

	if(!directoryToSave.empty()) {
		decodedFile += directoryToSave;
		auto it = std::find(encodedFile.rbegin(), encodedFile.rend(), '/');
		decodedFile += encodedFile.substr(std::abs(std::distance(encodedFile.rend(), it)));
	} else {
		decodedFile = encodedFile;
	}

	auto it = std::find(decodedFile.rbegin(), decodedFile.rend(), '.');
	decodedFile = decodedFile.substr(0, std::abs(std::distance(decodedFile.rend(), it)));
	decodedFile += "mp3";

	encoded = encodedFile;
	fin.open(encoded, std::ios::out | std::ios::binary);

	if(!fin.is_open()) {
		std::cerr << "Bad name";
		exit(-1);
	}

    	fout.open(decodedFile);
}


void Decoder::applyOffsets() {
	int fileByte = 0;
	
	while (!fin.eof()) {
        	int byte;

        	fin.read(reinterpret_cast<char*>(&byte), 1);
        	byte ^= offsets.at(fileByte);
       	 	fout.write(reinterpret_cast<char*>(&byte), 1);

        	offsets.at(fileByte) += 0x010;

        	if (fileByte < 15)
            		++fileByte;
        	else
            		fileByte ^= fileByte;
    }
}

void Decoder::close() {
    	fin.close();
    	fout.close();

    	delete this;
}
