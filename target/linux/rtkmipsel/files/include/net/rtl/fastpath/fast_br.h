#ifndef FAST_BR_H
#define FAST_BR_H

#include <linux/netdevice.h>
    
#define RTL_FAST_BR_HEAD_SIZE 1
#define RTL_FAST_BR_HASH_SIZE 4
#define RTL_FAST_BR_ENTRY_NUM 16
#define RTL_FAST_BR_SALT 3
#define RTL_FAST_BR_ENTRY_TIME_OUT 180*HZ
    
#define RTL_FAST_BR_SUCCESS 0
#define RTL_FAST_BR_FAILED -1
#define RTL_FAST_BR_ENTRY_EXPIRED 1
#define RTL_FAST_BR_ENTRY_NOT_EXPIRED 0
    
#define ERR_RTL_FAST_BR_ENTRY_EXIST -1000
#define ERR_RTL_FAST_BR_ENTRY_NOT_EXIST -1001
#define ERR_RTL_FAST_BR_NO_BUFFER -1002

	


	
	
	
	
	




#endif	/* 
    