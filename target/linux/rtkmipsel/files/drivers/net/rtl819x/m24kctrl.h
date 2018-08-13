/*
 *  Performance Profiling Header File
 *
 *  $Id: m24kctrl.h,v 1.1 2009/11/06 12:26:48 victoryman Exp $
 *
 *  Copyright (c) 2015 Realtek Semiconductor Corp.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */  
    
#include <net/rtl/rtl_types.h>
#include <linux/math64.h>
//#include <asm/rlxregs.h>
    
/***
typedef unsigned long long	uint64;
typedef signed long long		int64;
typedef unsigned int	uint32;
typedef signed int		int32;
typedef unsigned short	uint16;
typedef signed short	int16;
typedef unsigned char	uint8;
typedef signed char		int8;
***/ 
    
	
	
#ifdef PERF_DUMP_CP3_DUAL_COUNTER_EN
	 uint64 accCycle[8];
	
	
	
	
	
	
#else				/* 
	 uint64 accCycle[4];
	
	
#endif				// PERF_DUMP_CP3_DUAL_COUNTER_EN
	 uint32 reEnterIdx;
	
	



#define CP3ROMEPERF_INDEX_MAX 20
extern rtl8651_romeperf_stat_t cp3romePerfStat[CP3ROMEPERF_INDEX_MAX];


extern unsigned long int cp3Count[4];



// see Table 6.46 and 6.47 of MD00343-2B-24K-SUM-03.11.pdf for all of the event and counter0/1 meaning
#define PERF_EVENT_CYCLE				0x0100	// Counter 0: Cycles; Counter 1: Instructions completed
#define PERF_EVENT_ICACHE_MISS			0x0909	// Counter 0: Instruction Cache accesses; Counter 1: Instruction cache misses
#define PERF_EVENT_ICACHE_MISS_CYCLE	0x2525	// Counter 0: I$ Miss stall cycles; Counter 1: D$ miss stall cycles
#define PERF_EVENT_DCACHE_MISS			0x010B	// Counter 0: Data cache misses; Counter 1: Instructions completed
    
#if 0
// example:
// part 1: add test code
    file_1 
#include "m24kctrl.h"
    FUNC_A()
{
	
	... 
		
		
	
	
	return;



#include "m24kctrl.h"
    FUNC_B()
{
	
	
		
		
	
	
	



// part 2: test and get cp3 result
0. after DUT power on, the global array is summed when FUNC_A or FUNC_B is executed. 
    
#endif /* 
    