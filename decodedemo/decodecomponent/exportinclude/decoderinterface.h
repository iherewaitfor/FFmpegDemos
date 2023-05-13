#ifndef	DECODERINTERFACE_H
#define DECODERINTERFACE_H
#include <string>
#include <map>
using namespace std;


struct DecodeInterface
{
	virtual ~PlayerWindowInterface(){};
	virtual bool getNextFrame(const uint8_t *dst_data[4], const int dst_linesizes[4],
                   int pix_fmt, int width, int height) = 0;
};

#endif //DECODERINTERFACE_H