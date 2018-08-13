/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* 
* Program : ip table driver
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*/  
    
/*      @doc RTL_LAYEREDDRV_API

        @module rtl865x_ip.c - RTL865x Home gateway controller Layered driver API documentation       |
        This document explains the API interface of the table driver module. Functions with rtl865x prefix
        are external functions.
        @normal Hyking Liu (Hyking_liu@realsil.com.cn) <date>

        Copyright <cp>2008 Realtek<tm> Semiconductor Cooperation, All Rights Reserved.

        @head3 List of Symbols |
        Here is a list of all functions and variables in this module.
        
        @index | RTL_LAYEREDDRV_API
*/ 
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include "common/rtl_errno.h"
//#include "rtl_utils.h"
//#include <net/rtl/rtl865x_ip_api.h>
#include "rtl865x_ip.h"
#if defined (CONFIG_RTL_LOCAL_PUBLIC)
#include <net/rtl/rtl865x_localPublic.h>
#endif /* 
#include "common/rtl865x_eventMgr.h" /*call back function....*/
    
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865x_asicL3.h"	
#else /* 
#include "AsicDriver/rtl865xC_tblAsicDrv.h"
#endif /* 


#define IP_TABLE_INDEX(entry)	(entry - rtl865x_ipTable)
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
static RTL_DECLARE_MUTEX(ip_sem);

#endif /* 
static int32 _rtl865x_delIp(ipaddr_t extIp);

/*
@func int32 | rtl865x_initIpTable | initialize ip table.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed,system should be reboot.
*/ 
    int32 rtl865x_initIpTable(void) 
{
	
	
	



/*
@func int32 | rtl865x_initIpTable | reinitialize ip table.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed.
*/ 
    int32 rtl865x_reinitIpTable(void)
{
	
	
		
		
			
		
	



				 uint32 ip_type) 
{
	
	
	
	
	
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
	int empty_entry = -1;
	
#endif /* 
	    
		
	
	    /*duplicate check */ 
	    /*found a valid entry */ 
	    for (i = 0; i < IP_NUMBER; i++)
		
		
			
			
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
			    if (empty_entry == -1)
				
			
#else /* 
			    entry = &rtl865x_ipTable[i];
			
			
#endif /* 
			}
		
		else
			
			
				
			
			       && rtl865x_ipTable[i].type == IP_TYPE_NAPT
			       && rtl865x_ipTable[i].defNaptIp == 1)
				
			
		
	
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
	    if (empty_entry != -1)
		
	
#endif /* 
	    
		
	
	    /*update releated information */ 
	    entry->valid = 1;
	
	
	
	
	    /*from 865xC, this field is invalid... */ 
	    entry->nexthop = NULL;
	
	    /*add this ip entry to asic */ 
	    /* Set asic */ 
	    bzero(&asicIp, sizeof(rtl865x_tblAsicDrv_extIntIpParam_t));
	
	
	
	
	
	
	    rtl8651_setAsicExtIntIpTable(IP_TABLE_INDEX(entry), &asicIp);
	
		
	



{
	
	
	    /*found the entry */ 
	    for (i = 0; i < IP_NUMBER; i++)
		
		
			
			
			
		
	



{
	
	
	
	    /*found the entry */ 
	    for (i = 0; i < IP_NUMBER; i++)
		
		
		     && rtl865x_ipTable[i].extIp == extIp)
			
			
			
			
		
	
	    /*update asic ip table */ 
	    if (entry != NULL)
		
		
		
		
	
	else
		
	
	    //no entry in ip table, set operation to layer 2
	    if (_rtl865x_ipTableIsNull() == SUCCESS)
		
		
#if defined(CONFIG_RTL_HARDWARE_MULTICAST)
		    rtl8651_setAsicOperationLayer(3);
		
#else /* 
		    rtl8651_setAsicOperationLayer(2);
		
#endif /* 
		}
	



{
	
	
	
		
		     && rtl865x_ipTable[i].extIp == extIp)
			
			
			
			
	



/*
@func rtl865x_ip_entry_t* | rtl865x_getIpEntryByIp | get ip entry .
@parm ipaddr_t | extIp | ip address
@rvalue ip_entry | Success.
@rvalue NULL | Failed
*/ 
    rtl865x_ip_entry_t * rtl865x_getIpEntryByIp(ipaddr_t extIp) 
{
	



/*
@func int32 | rtl865x_getIpIdxByExtIp | get asic idex .
@parm ipaddr_t | extIp | ip address
@parm int32* | idx | index
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed
*/ 
    int32 rtl865x_getIpIdxByExtIp(ipaddr_t extIp, int32 * idx) 
{
	
	
	
	
		
		
			
		
		
	



/*
@func int32 | rtl865x_addIp | add ip table entry.
@parm ipaddr_t | intIp | internal ip address
@parm ipaddr_t | extIp | external ip address
@parm uint32 | ip_type | entry type. support IP_TYPE_NAPT/IP_TYPE_NAT/IP_TYPE_LOCALSERVER
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDINPUT | Invalid input.
@rvalue RTL_EENTRYALREADYEXIST | entry already exist.
@rvalue RTL_ENOFREEBUFFER | not enough buffer in System.
@rvalue FAILED | Failed.
@comm
the extIp is the primary key of the ip table.
*/ 
    int32 rtl865x_addIp(ipaddr_t intIp, ipaddr_t extIp, uint32 ip_type) 
{
	
	
	
	    //rtl_down_interruptible(&ip_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&ip_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_delIp | delete ip table entry.
@parm ipaddr_t | extIp | external ip address
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDINPUT | Invalid input.
@rvalue RTL_EENTRYNOTFOUND | not found.
@rvalue FAILED | Failed.
@comm
the extIp is the primary key of the ip table.
*/ 
    int32 rtl865x_delIp(ipaddr_t extIp) 
{
	
	
	
	    //rtl_down_interruptible(&ip_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&ip_sem);
	    SMP_UNLOCK_ETH(flags);
	



{
	
		
		
		
		
	



#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
extern int rtl_check_extIp_exist_in_ps(uint32 extIp);

{
	
	
		
		
		
			
			     (rtl865x_ipTable[i].extIp) == SUCCESS)
				
			
			    /*Delete the ip not exist in protocol stack */ 
			    if (found == 0) {
				
			
		
		
	



#endif /* 
/*
@func int32 | rtl865x_getIpIdxByIpRange | get asic idex .
@parm ipaddr_t | ip | ip address
@parm ipaddr_t | mask | ip address
@parm int32* | idx | index
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed
*/ 
    int32 rtl865x_getIpIdxByIpRange(ipaddr_t ip, ipaddr_t mask, int32 * idx) 
{
	
	
	
	
	for (i = 0; i < IP_NUMBER; i++)
		
		
		     && ((rtl865x_ipTable[i].extIp & mask) == (ip & mask)))
			
			
			
			
		
	
		
		
			
		
		
	


