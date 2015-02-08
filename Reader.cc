#include "Reader.hh"

#define isASCII(b)  ((b & 0x80) == 0)
#define isAlpha(b)  (((b>='a') && (b<='z')) || \
											((b>='A') && (b<='Z')) || \
											((b>='0') && (b<='9')))

//Read single word with UTF-8 encode
const Byte* Reader::readSingleWord(int &len, bool &ascii) {
	int count = 0;
	bool alpha = false;

	len = 0;
	ascii = true;

	if(byteReader == null) {
		ret[len] =  0;
		return ret;
	}	

	while(len <= MAX_WORD_LEN) {
		Byte b;

		if(rollBackByte == 0) {
			b = byteReader->read(); 
		}
		else {
			b = rollBackByte;
		}

		if(b == 0)//end of input
			break;


		ret[len]  = b;
		++len;

		if(count > 0) {
			--count;
			if(count == 0) {
				rollBackByte = 0; //read next byte;
				break;
			}
			else {
				continue;
			}
		}

		if(isASCII(b)) { //ASCII
			if(!isAlpha(b)) {
				if(len == 1) {
					rollBackByte = 0; //read next byte;
					break;
				}
				else {
					--len;
					rollBackByte = b; //rollback
					break;
				}
			}
			else {
				alpha = true;
				rollBackByte = 0; //read next byte;
			}
		}
		else {
			if(alpha) {
				--len;
				rollBackByte = b; //rollback
				break;
			}
			else if((b >> 4) == 0x0E) { //3 bytes encode like UTF-8 Chinese
				count = 2;
				rollBackByte = 0; //read next byte;
			}
			else if((b >> 3) == 0x1E) { //4 bytes encode
				count = 3;
				rollBackByte = 0; //read next byte;
			}
			else if((b >> 2) == 0x3E) { //5 bytes encode
				count = 4;
				rollBackByte = 0; //read next byte;
			}
			else if((b >> 1) == 0x7E) { //6 bytes encode
				count = 5;
				rollBackByte = 0; //read next byte;
			}
		}
	}

	if((ret[0] & 0x80) != 0)
		ascii = false;

	ret[len] =  0;
	return ret;
}
