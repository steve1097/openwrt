/*
* Copyright c                  Realtek Semiconductor Corporation, 2014  
* All rights reserved.
* 
* Program : dslite table driver
* Abstract : 
* Author : annti_hu/ethan_ding
*/  
    
/*      @doc RTL_LAYEREDDRV_API

        @module rtl865x_dslite.c - RTL865x Home gateway controller Layered driver API documentation       |
        This document explains the API interface of the table driver module. Functions with rtl865x prefix
        are external functions.

        Copyright <cp>2014 Realtek<tm> Semiconductor Cooperation, All Rights Reserved.

        @head3 List of Symbols |
        Here is a list of all functions and variables in this module.
        
        @index | RTL_LAYEREDDRV_API
*/ 
    
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include <net/rtl/rtl865x_netif.h>
#include "common/rtl_errno.h"
#include "common/rtl865x_netif_local.h" 
#include "rtl865x_ip.h"
#include "rtl865x_nexthop.h"
#include "rtl865x_ppp_local.h"
#include "rtl865x_route.h"
#include "rtl865x_arp.h"
    
#include "common/rtl865x_vlan.h"
#include "common/rtl865x_eventMgr.h" /*call back function....*/
    
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865x_asicL2.h"
#include "AsicDriver/rtl865x_asicL3.h"
#else /* 
#include "AsicDriver/rtl865xC_tblAsicDrv.h"
#endif /* 
#include "l2Driver/rtl865x_fdb.h"
#include <net/rtl/rtl865x_fdb_api.h>
#include <linux/version.h>
    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#include "rtl8198c_arpIpv6.h"
#include "rtl8198c_nexthopIpv6.h"
#endif /* 
    
#include "rtl865x_dslite.h"
    
/*ipv6 ds-lite*/ 
#define IPV6_DSLT_TABLE_INDEX(entry)	(entry - rtl865x_ipv6_DsLiteTable)
#define IPV6_DSLT_ENTRY_NUM	8




/*
@func int32 | rtl8198c_initIpv6DsLiteTable |initialize the dslite table
@rvalue SUCCESS | success.
@rvalue FAILED | failed. system should reboot.
@comm	
*/ 
    int32 rtl8198c_initIpv6DsLiteTable(void) 
{
	
		       IPV6_DSLT_ENTRY_NUM);
	
		sizeof(rtl865x_dslite_s) * IPV6_DSLT_ENTRY_NUM);
	
	



/*
@func int32 | rtl8198c_reinitIpv6DsLiteTable |reinitialize the dslite table
@rvalue SUCCESS | success.
@comm	
*/ 
    int32 rtl8198c_reinitIpv6DsLiteTable(void)
{
	
	
		
		
			
		
	
	



/*
	may cause issue, carefully uesed
*/ 
    rtl865x_dslite_s * rtl865x_getDsLiteEntry(void)
{
	
	
	
		
		
		
			
			
				
				
				
			
		
	



{
	
	
	
	
	
	
	
		
	
		
		
		
			
			
			     &&(strcmp(devName, entry->name) == 0) 
				
				
				
			
		
	
	
		

	
		




{
	
	
	
		
		
			
			
			
		
	




						uint32 aftr_ipv6_mask) 
{
	
	
	
	
	
	
	
		
		
		
		     &&((entry->aftr_ipv6_addr.v6_addr32[0] ==
			 aftr_ipv6_addr.
			 v6_addr32[0]) 
					    ==
					    aftr_ipv6_addr.v6_addr32[1]) 
			&&(entry->aftr_ipv6_addr.v6_addr32[2] ==
			   aftr_ipv6_addr.
			   v6_addr32[2]) 
					      ==
					      aftr_ipv6_addr.v6_addr32[3]) 
			
			
			
		
	
	
		

	
		




					  rtl865x_dslite_s * entry) 
{
	
	
	
		
		
		
	




{
	
	
	
		
	
	    entry_t->host_ipv6_addr.v6_addr32[0];
	
	    entry_t->host_ipv6_addr.v6_addr32[1];
	
	    entry_t->host_ipv6_addr.v6_addr32[2];
	
	    entry_t->host_ipv6_addr.v6_addr32[3];
	
	
	    entry_t->aftr_ipv6_addr.v6_addr32[0];
	
	    entry_t->aftr_ipv6_addr.v6_addr32[1];
	
	    entry_t->aftr_ipv6_addr.v6_addr32[2];
	
	    entry_t->aftr_ipv6_addr.v6_addr32[3];
	
	
	
	
	
	



				     uint32 host_ipv6_mask,
				     inv6_addr_t aftr_ipv6_addr,
				     uint32 aftr_ipv6_mask, char *devName,
				     unsigned int mtu)
{
	
	
	
	
	    //entry = _rtl865x_getIpv6DsLiteEntry(host_ipv6_addr,host_ipv6_mask,aftr_ipv6_addr,aftr_ipv6_mask,devName);
	    printk("[%s]:[%d].host:%x:%x:%x:%x,%d,after:%x:%x:%x:%x,%d,%s,%d\n",
		   __FUNCTION__, __LINE__, 
		   host_ipv6_addr.v6_addr32[1], host_ipv6_addr.v6_addr32[2],
		   host_ipv6_addr.v6_addr32[3], host_ipv6_mask,
		   
		   aftr_ipv6_addr.v6_addr32[2], aftr_ipv6_addr.v6_addr32[3],
		   aftr_ipv6_mask, 
	
	
		
	
	else
		
		
		    /* Allocate an empty entry for new one */ 
		    /*
		       pppoe ----> index 0
		       direct ---> index 1
		       nexthop ---> index 2
		       arp ------> index 3
		     */ 
		    //now test just for direct ,so use index 1 to use.
		    //for (entryIdx = 0; entryIdx < IPV6_DSLT_ENTRY_NUM; entryIdx++)                        
		    //for (entryIdx = 1; entryIdx < IPV6_DSLT_ENTRY_NUM; entryIdx++)
		    for (entryIdx = 2; entryIdx < IPV6_DSLT_ENTRY_NUM;
			 entryIdx++)
			
			
				
				
				
			
			
		
	
	    /*if not found proper nextHop entry, return */ 
	    entry = NULL;

		
	
	    /*common information */ 
	    entry->host_ipv6_addr.v6_addr32[0] =
	    htonl(host_ipv6_addr.v6_addr32[0]);
	
	    htonl(host_ipv6_addr.v6_addr32[1]);
	
	    htonl(host_ipv6_addr.v6_addr32[2]);
	
	    htonl(host_ipv6_addr.v6_addr32[3]);
	
	
	    htonl(aftr_ipv6_addr.v6_addr32[0]);
	
	    htonl(aftr_ipv6_addr.v6_addr32[1]);
	
	    htonl(aftr_ipv6_addr.v6_addr32[2]);
	
	    htonl(aftr_ipv6_addr.v6_addr32[3]);
	
	
	
	
	
	
	
	    ("[%s]:[%d].retVal:%d,host:%x:%x:%x:%x,%d,after:%x:%x:%x:%x,%d,%s,%d\n",
	     __FUNCTION__, __LINE__, retVal, 
	     host_ipv6_addr.v6_addr32[1], host_ipv6_addr.v6_addr32[2],
	     host_ipv6_addr.v6_addr32[3], host_ipv6_mask,
	     
	     aftr_ipv6_addr.v6_addr32[2], aftr_ipv6_addr.v6_addr32[3],
	     aftr_ipv6_mask, 
	



{
	
	
	
		
	
	
		
	
	    /*delete route from asic */ 
	    if (entry->index < IPV6_DSLT_ENTRY_NUM)
		
	
	



/*
@func int32 | rtl8198c_addIpv6DsLiteEntry |add a dslite entry
@parm uint32 | attr | attribute. IPV6_NEXTHOP_L3/IPV6_NEXTHOP_REDIRECT.
@parm void* | ref_ptr | entry pointer who refer this nexthop entry.
@parm rtl865x_netif_local_t* | netif | network interface.
@parm inv6_addr_t | nexthop | nexthop. ipv6 ip address when linktype is ethernet, session id when linktype is ppp session based.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_addIpv6DsLiteEntry(inv6_addr_t host_ipv6_addr,
				      uint32 host_ipv6_mask,
				      inv6_addr_t aftr_ipv6_addr,
				      uint32 aftr_ipv6_mask, char *devName,
				      unsigned int mtu)
{
	
	
	
	
	    _rtl865x_addIpv6DsLiteEntry(host_ipv6_addr, host_ipv6_mask,
					aftr_ipv6_addr, aftr_ipv6_mask, devName,
					mtu);
	
	



/*
@func int32 | rtl8198c_delIpv6DsLiteEntry |delete dslite entry
@parm uint32 | attr | attribute. IPV6_NEXTHOP_L3/IPV6_NEXTHOP_REDIRECT.
@parm uint32 | entryIdx | entry index.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_delIpv6DsLiteEntry(uint32 attr, uint32 entryIdx) 
{
	
	
	
	
	
	


