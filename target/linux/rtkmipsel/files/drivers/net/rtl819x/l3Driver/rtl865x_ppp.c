/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* 
* Program : ppp table driver
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*/  
    
/*      @doc RTL_LAYEREDDRV_API

        @module rtl865x_ppp.c - RTL865x Home gateway controller Layered driver API documentation       |
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
#include <net/rtl/rtl865x_ppp.h>
#include <net/rtl/rtl865x_netif.h>
#include <net/rtl/rtl865x_fdb_api.h>
    
#include "common/rtl_errno.h"
#include "common/rtl865x_netif_local.h"
#include "rtl865x_ppp_local.h"
    
#include "common/rtl865x_eventMgr.h" /*call back function....*/
    
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865x_asicL2.h"
#include "AsicDriver/rtl865x_asicL3.h"
#else /* 
#include "AsicDriver/rtl865xC_tblAsicDrv.h"
#endif /* 
    
#include "common/rtl865x_vlan.h"
#include "l2Driver/rtl865x_fdb.h"


#if defined(CONFIG_RTL_HARDWARE_NAT)
static rtl865x_ppp_t rtl865x_pppTable_bak[PPP_NUMBER];

#endif /* 
    
#define PPP_TABLE_INDEX(entry)	(entry - rtl865x_pppTable)
#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
static RTL_DECLARE_MUTEX(ppp_sem);

#endif /* 




/*
@func int32 | rtl865x_initPppTable | initialize ppp table.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed.
*/ 
    int32 rtl865x_initPppTable(void) 
{
	
	
	
	    /*event regist.... */ 
	    _rtl865x_ppp_register_event();
	



/*
@func int32 | rtl865x_reinitPppTable | reinitialize ppp table.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed.
*/ 
    int32 rtl865x_reinitPppTable(void)
{
	
	
	
		
		
			
		
	
	



{
	
	
	
	
	
	
	    /*found the entry */ 
	    for (i = 0; i < PPP_NUMBER; i++)
		
		
		     && rtl865x_pppTable[i].sessionId == sessionId)
			
			
			
			
		
	
		
	
	    /*check reference count */ 
	    if (entry->refCnt > 1)
		
		
		    ("Please del other table entry which referenced me...ppp sessionId(%d)\n",
		     sessionId);
		
		
	
	    /*del asic ppp table */ 
	    asicppp.age = 0;
	
	
	
	    /*FIXME_hyking:dereference netif & mac */ 
	    retval = rtl865x_deReferNetif(entry->netif->name);
	
	
	    rtl865x_delFilterDatabaseEntry(RTL865x_L2_TYPEII, fid,
					   &entry->server_mac);
	
	    /*raise event?? */ 
	    rtl865x_raiseEvent(EVENT_DEL_PPP, (void *)entry);
	
	



			      uint32 sessionId, int32 type) 
{
	
	
	
	
	
	
	
	
	
	FDB_STATIC, FDB_DYNAMIC};
	
/*printk("%s(%d): ifname(%s),mac(%02x:%02x:%02x:%02x:%02x:%02x),sid(%d),type(%d)",__FUNCTION__,__LINE__,ifname,
	mac->octet[0],mac->octet[1],mac->octet[2],mac->octet[3],mac->octet[4],mac->octet[5], sessionId,type);*/ 
	    
#if 1				//Do not add hw ppp info in wisp or bridge mode
	{
		
		
			return RTL_ENETIFINVALID;
	
	
#endif /* 
	    /*duplicate check */ 
	    for (i = 0; i < PPP_NUMBER; i++)
		
		
		     && rtl865x_pppTable[i].sessionId == sessionId)
			
		
	
	
		
	
		
	
	    /*found a valid entry */ 
	    for (i = 0; i < PPP_NUMBER; i++)
		
			
			
			
			
	
		
	
	    /*update releated information */ 
	    entry->valid = 1;
	
	
	
	
	
	
	    /*add this ip entry to asic */ 
	    /* Set asic */ 
	    bzero(&asicPpp, sizeof(rtl865x_tblAsicDrv_pppoeParam_t));
	
	
	
	
	    /*FIXME_hyking:reference netif & mac */ 
	    retval = rtl865x_referNetif(netif->name);
	
	    /*add fdb entry... */ 
	    fid = 0;
	
	
	
		
		
		    /*
		       printk("%s:%d\n,fid(%d),mac(%02x:%02x:%02x:%02x:%02x:%02x)\n",__FUNCTION__,__LINE__,fid,mac->octet[0],mac->octet[1],
		       mac->octet[2],mac->octet[3],mac->octet[4],mac->octet[5]);
		       
		       printk("%s:%d\n",__FUNCTION__,__LINE__);
		     */ 
		    if (rtl865x_Lookup_fdb_entry
			(fid, mac, fdb_type[i], &column, &fdbEntry) != SUCCESS)
			
			
			
		
		    /*in case of layer2 auto learn, add hardware entry to layer 2 software table */ 
		    l2temp_entry.l2type =
		    (fdbEntry.nhFlag ==
		     0) ? RTL865x_L2_TYPEI : RTL865x_L2_TYPEII;
		
		
		
		
		
		
		
//              retval = _rtl865x_addFilterDatabaseEntry((fdbEntry.nhFlag==0)?RTL865x_L2_TYPEI: RTL865x_L2_TYPEII, fid, mac, FDB_TYPE_FWD, fdbEntry.memberPortMask, fdbEntry.auth,fdbEntry.srcBlk);
		    rtl865x_refleshHWL2Table(mac, FDB_DYNAMIC | FDB_STATIC,
					     fid);
		
	
	    /*raise event?? */ 
	    rtl865x_raiseEvent(EVENT_ADD_PPP, (void *)entry);
	



{
	
	
	
	
		
	
	
	
		
		
#if !defined(CONFIG_OPENWRT_SDK)
		    if ((entry->valid) && entry->netif == netif)
			
			    ("%s(%d): BUG....deleted netif is referenced by ppp table!\n",
			     __FUNCTION__, __LINE__);
		
#endif /* 
		}
	



{
	
	
	
	
		
	
	
	
		
		
		    //if((entry->valid) && memcmp(&entry->server_mac,&fdbEntry->macAddr,sizeof(ether_addr_t)) == 0)
		    //printk("%s(%d): BUG....deleted l2 fdb is referenced by ppp table!\n",__FUNCTION__,__LINE__);
		}
	



{
	
	
	    //rtl_down_interruptible(&ppp_sem);
	    retval = _rtl865x_eventHandle_delNetif(para);
	
	    //rtl_up(&ppp_sem);
	    return retval;



{
	
	
	    //rtl_down_interruptible(&ppp_sem);
	    retval = _rtl865x_eventHandle_delL2Fdb(para);
	
	    //rtl_up(&ppp_sem);
	    return retval;



{
	
	
	
	
	
	
	
	
	
	
	
	
	



{
	
	
	
	
	
	
	
	
	
	
	
	
	



#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
static 
#endif				/* 
 int32 _rtl865x_referPpp(uint32 sessionId) 
{
	
	
	
	
		
			
			
			
			
	



#if LINUX_VERSION_CODE < KERNEL_VERSION(3,4,0)
static 
#endif				/* 
 int32 _rtl865x_deReferPpp(uint32 sessionId) 
{
	
	
	
	
		
			
			
			
			
	



/*
@func int32 | rtl865x_referPpp |refer ppp table entry.
@parm uint32 | sessionId | ppp session ID
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed
@comm	
*/ 
    int32 rtl865x_referPpp(uint32 sessionId) 
{
	
	
	
	    //rtl_down_interruptible(&ppp_sem);
	    SMP_LOCK_ETH_HW(flags);
	
	
	    //rtl_up(&ppp_sem);
	    SMP_UNLOCK_ETH_HW(flags);
	



/*
@func int32 | rtl865x_deReferPpp |dereference ppp table entry.
@parm uint32 | sessionId | ppp session ID
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed
@comm	
*/ 
    int32 rtl865x_deReferPpp(uint32 sessionId) 
{
	
	
	
	    //rtl_down_interruptible(&ppp_sem);
	    SMP_LOCK_ETH_HW(flags);
	
	
	    //rtl_up(&ppp_sem);
	    SMP_UNLOCK_ETH_HW(flags);
	



/*
@func int32 | rtl865x_addPpp |add ppp session information.
@parm uint8* | ifname | network interface name
@parm ether_addr_t* | mac | MAC Address of ppp session server
@parm uint32 | sessionId | ppp session ID
@parm int32 | type | connect type. should be IF_PPPOE/IF_PPTP/IF_L2TP
@rvalue SUCCESS | Success.
@rvalue RTL_EENTRYALREADYEXIST | entry already exist.
@rvalue RTL_ELINKTYPESHOULDBERESET | link type is error.
@rvalue RTL_ENOFREEBUFFER | no enough memory buffer in system.
@rvalue FAILED | Failed
@comm	
*/ 
    int32 rtl865x_addPpp(uint8 * ifname, ether_addr_t * mac, uint32 sessionId,
			 int32 type) 
{
	
	
	
	    //printk("====================%s(%d): sessionId(%d) ifname(%s) retval(%d)\n",__FUNCTION__,__LINE__,sessionId,ifname,retval);
	    //rtl_down_interruptible(&ppp_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&ppp_sem);
	    SMP_UNLOCK_ETH(flags);
	
	    //printk("====================%s(%d): sessionId(%d) retval(%d)\n",__FUNCTION__,__LINE__,sessionId,retval);
	    return retval;



/*
@func int32 | rtl865x_delPpp |delete ppp session information.
@parm uint32 | sessionId | ppp session ID
@rvalue SUCCESS | Success.
@rvalue RTL_EREFERENCEDBYOTHER | entry is refered by other table entry.
@rvalue FAILED | Failed
@comm	
*/ 
    int32 rtl865x_delPpp(uint32 sessionId) 
{
	
	
	
	    //rtl_down_interruptible(&ppp_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&ppp_sem);
	    SMP_UNLOCK_ETH(flags);
	
	    //printk("====================%s(%d): sessionId(%d) retval(%d)\n",__FUNCTION__,__LINE__,sessionId,retval);
	    return retval;



/*
@func int32 | rtl865x_delPppbyIfName |delete ppp session by network interface name.
@parm char* | name | network interface name.
@rvalue SUCCESS | Success.
@rvalue RTL_EREFERENCEDBYOTHER | entry is refered by other table entry.
@rvalue FAILED | Failed
@comm	
*/ 
    int32 rtl865x_delPppbyIfName(char *name)
{
	
	
	
	
	
	    //rtl_down_interruptible(&ppp_sem);
	    SMP_LOCK_ETH(flags);
	
		
		     &&
		     (memcmp
		      (rtl865x_pppTable[i].netif->name, name,
		       sizeof(name)) == 0))
			
			
			
			
	
		
	
	    //rtl_up(&ppp_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_getPppBySessionId |get ppp session information by session ID.
@parm uint32 | sessionId | ppp session ID
@parm rtl865x_ppp_t* | entry | ppp entry.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed
@comm	
*/ 
    int32 rtl865x_getPppBySessionId(uint32 sessionId, rtl865x_ppp_t * entry) 
{
	
	
	
	
		
		
		     && rtl865x_pppTable[i].sessionId == sessionId)
			
		
	
		
		
		
		
	



/*
@func rtl865x_ppp_t* | rtl865x_getPppByNetifName |get ppp session information by network interface name.
@parm char* | name | network interface name.
@rvalue NULL | Failed
@comm	
*/ 
    rtl865x_ppp_t * rtl865x_getPppByNetifName(char *name)
{
	
	
	
		
		
		     &&
		     (memcmp
		      (rtl865x_pppTable[i].netif->name, name,
		       sizeof(name)) == 0))
			
			
			
			
		
	



/*
@func int32 | rtl865x_getPppIdx |get ppp session entry index.
@parm rtl865x_ppp_t* | ppp | ppp entry.
@parm int32* | idx | return value for index.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl865x_getPppIdx(rtl865x_ppp_t * ppp, int32 * idx) 
{
	
	
	
	
		
		
			
			
				
			
			
		
	



/*
int32 rtl865x_printPpp(void)
{
	int i;
	for(i = 0; i < PPP_NUMBER; i++)
	{
		printk("====idx(%d),rtl865x_pppTable.valid(%d),refcnt(%d),session(%d),type(%d)\n", i,rtl865x_pppTable[i].valid,rtl865x_pppTable[i].refCnt,rtl865x_pppTable[i].sessionId,rtl865x_pppTable[i].type);
	}
	return SUCCESS;
}
*/ 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)
int rtl819x_save_hw_ppp_table(void) 
{
	
	
	
		  sizeof(rtl865x_pppTable_bak));
	
		
		
			
			
			    rtl865x_pppTable[i].netif;
			
			    rtl865x_pppTable[i].sessionId;
			
			    rtl865x_pppTable[i].valid;
			
			    rtl865x_pppTable[i].type;
			
			    rtl865x_pppTable[i].refCnt;
			
				rtl865x_pppTable[i].server_mac.octet,
				ETHER_ADDR_LEN);
			
			    //save ppp server related l2 entry.
			    rtl865x_getVlanFilterDatabaseId(rtl865x_pppTable
							    [i].netif->vid,
							    &fid);
			
						      (ether_addr_t *) &
						      rtl865x_pppTable
						      [i].server_mac, fid);
			
		
	



{
	
	
	
		
		
			
			
					(ether_addr_t *) & entry->server_mac,
					entry->sessionId, entry->type);
		
		
	



#endif /* 
    