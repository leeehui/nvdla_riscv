// See LICENSE for license details.

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    


#define debug(filter, msg, ...)\
do\
{\
	if (filter)\
	{\
		printf("Debug > %s(%d) " msg "\n",\
		__func__, __LINE__, ##__VA_ARGS__);\
	}\
}while(0)


#ifdef __cplusplus
}
#endif
