#ifdef DECODECOMPONENT_EXPORTS
#define DECODECOMPONENT_API __declspec(dllexport)
#else
#define DECODECOMPONENT_API __declspec(dllimport)
#endif
#include "exportinclude/decoderinterface.h"


DECODECOMPONENT_API int fngetDecocdeComponentHelper(void);

extern "C" DECODECOMPONENT_API DecodeComponentHelper* fn_getDecocdeComponentHelper();

