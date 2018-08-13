/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* 
* Program : nexthop table driver
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*/  
    
/*      @doc RTL_LAYEREDDRV_API

        @module rtl865x_nexthop.c - RTL865x Home gateway controller Layered driver API documentation       |
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
#include <net/rtl/rtl865x_netif.h>
#include "common/rtl_errno.h"
#include "common/rtl865x_netif_local.h" 
#include "rtl865x_ip.h"
#include "rtl865x_nexthop.h"
//#include "rtl865x_ppp.h"
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
    
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
#ifdef CONFIG_RTL_HW_DSLITE_SUPPORT
#include "l3Driver/rtl865x_dslite.h"
extern inv6_addr_t gw_ipv6_addr;

#endif /* 
#endif /* 


#define NEXTHOP_TABLE_INDEX(entry)	(entry - rtl865x_nxtHopTable)
static int32 _rtl865x_nextHop_register_event(void);



#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
static RTL_DECLARE_MUTEX(nxthop_sem);

#endif /* 
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
extern int32 _rtl865x_referPpp(uint32 sessionId);


#endif /* 
    
#if 0
static void _print_softNxtHop(void) 
{
	
	
	
	
		
		
		    ("idx(%d): valid(%d),dst(%s),nexthop(%d),nexthopType(%d),refCnt(%d)\n",
		     i, entry->valid, entry->dstNetif->name, 
		     entry->nextHopType, entry->refCnt);
		



#endif /* 
    
/*
@func int32 | rtl865x_initNxtHopTable |initialize the nexthop table
@rvalue SUCCESS | success.
@rvalue FAILED | failed. system should reboot.
@comm	
*/ 
    int32 rtl865x_initNxtHopTable(void) 
{
	
		       NXTHOP_ENTRY_NUM);
	
		sizeof(rtl865x_nextHopEntry_t) * NXTHOP_ENTRY_NUM);
	
	



/*
@func int32 | rtl865x_reinitNxtHopTable |reinitialize the nexthop table
@rvalue SUCCESS | success.
@comm	
*/ 
    int32 rtl865x_reinitNxtHopTable(void)
{
	
	
	
		
		
			
		
	
	



#if defined CONFIG_RTL_LOCAL_PUBLIC
extern int rtl865x_getLocalPublicArpMapping(unsigned int ip,
					    rtl865x_arpMapping_entry_t *
					    arp_mapping);

#endif /* 
static int32 _rtl865x_synNxtHopToAsic(rtl865x_nextHopEntry_t * entry_t) 
{
	
	
	
	
	
	
	
	
	
	
	
		
		
		
	
		
		
		
		
		    /*if the arp info of nexthop is not found, reserved to cpu Mac is used for trap packet to CPU */ 
#if defined (CONFIG_RTL_LOCAL_PUBLIC)
		    if (entry_t->nexthop)
			
			
			    rtl865x_getArpMapping(entry_t->nexthop, &arp_t);
			
				
				
				    /*try to match local pulbic ip */ 
				    ret_arpFound =
				    rtl865x_getLocalPublicArpMapping
				    (entry_t->nexthop, &arp_t);
				
			
		
#else /* 
		    if (entry_t->nexthop)
			
			    rtl865x_getArpMapping(entry_t->nexthop, &arp_t);
		
#endif /* 
		    
						     &fid);
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (ret_arpFound ==
					      SUCCESS) ? &arp_t.mac :
					     &reservedMac, FDB_DYNAMIC,
					     &columIdx, &asic_l2);
		
		    rtl8651_filterDbIndex((ret_arpFound ==
					   SUCCESS) ? &arp_t.mac : &reservedMac,
					  fid);
		
		
		
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    
	else if (entry_t->nextHopType == IF_DSLT)
		
		
		
		
		    /*if the arp info of nexthop is not found, reserved to cpu Mac is used for trap packet to CPU */ 
		    
		    rtl8198c_dslite_Ipv6ArpMapping(gw_ipv6_addr, &arp_t);
		
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (ret_arpFound ==
					      SUCCESS) ? &arp_t.mac :
					     &reservedMac, FDB_DYNAMIC,
					     &columIdx, &asic_l2);
		
		    rtl8651_filterDbIndex((ret_arpFound ==
					   SUCCESS) ? &arp_t.mac : &reservedMac,
					  fid);
		
		
		
		
		    //printk("%d,%d,[%s]:[%d].\n",asic.nextHopRow,asic.nextHopColumn,__FUNCTION__,__LINE__);
		}
	
#endif /* 
#endif /* 
	    else
		
		
		    /*session based interface type */ 
		    rtl865x_ppp_t pppoe;
		
		
		
			
			    rtl865x_getPppBySessionId(entry_t->nexthop, &pppoe);
		
						   &fid);
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (pppoe.
					      valid) ? &pppoe.server_mac :
					     &reservedMac, FDB_DYNAMIC,
					     &columIdx, &asic_l2);
		
		    rtl8651_filterDbIndex((pppoe.
					   valid) ? &pppoe.server_mac :
					  &reservedMac, fid);
		
		
		
		
		    //printk("%s(%d): pppoeIdx(%d), pppoeType(%d), pppoevalid(%d),pppoeSid(%d)\n",__FUNCTION__,__LINE__,pppidx,pppoe.type,pppoe.valid,pppoe.sessionId);
		    asic.pppoeIdx = (pppoe.type == IF_PPPOE) ? pppidx : 0;
		
	
		
		
		
			
		
	
	else
		
	
		
	
	
		
	
	
	



{
	
	
	
		
	
		
		
		
			
		
	



				   rtl865x_netif_local_t * netif,
				   uint32 nexthop, uint32 srcIp) 
{
	
	
	
	
	    /*
	     * NOTE:
	     * parameter description:
	     * (1) attr: why need to add the nexthop entry? NEXTHOP_L3 or NEXTHOP_DEFREDIRECT_ACL?
	     * (2) ref_ptr: when attr = NEXTHOP_L3, ref_ptr point to a route structure,
	     *                                 attr = NEXTHOP_DEFREDIRECT_ACL, ref_ptr = NULL,
	     *                                 attr = others, ref_ptr = NULL
	     * (3) netif: destination network interface
	     * (4) nexthop: 
	     *              a) netif->if_type == IF_ETHER, nexthop = nexthop ip address,
	     *              b) netif->if_type == session based type, nexthop = session Id,
	     *
	     * following case should be NOTED now:
	     * (1) ETHERNET type network interface:
	     *       a) If nexthop != NULL , it means the entry is added for:
	     *              nexthop ip&mac information, nextHop = arp entry of nexthop ip address.
	     *        b) If nexthop == 0, use default route's nexthop or nexthop TOCPU
	     *
	     * (2) PPPoE/PPTP/L2TP type network interface:
	     *        The "nexthop" will explicitly specify the PPPoE session (PPTP/L2TP session).
	     */ 
	    
		
	
	    /* Allocate an empty entry for new one */ 
	    /*Note: all nexthop entry referenced by L3 must be 2 entries aligned(reference l3 Datasheet) */ 
	    for (entryIdx = 0; entryIdx < NXTHOP_ENTRY_NUM; entryIdx++)
		
		
			
			
				
			
				
				     && (entryIdx + 1) < NXTHOP_ENTRY_NUM
				     && rtl865x_nxtHopTable[entryIdx +
							    1].valid == 0)
					
					
					
					
				
			
				
				
				
			
				
				
				
			
		
	
	    /*if not found proper nextHop entry, return */ 
	    entry = NULL;

		
	
	
	
	
	
	
	
	
		
	
		
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	case IF_DSLT:
		
#endif /* 
#endif /* 
		    entry->nexthop = nexthop;
		
	
	
	
		
		    /*nexthop is sessionId */ 
		    entry->nexthop = nexthop;
		
		
	
		
		
		
		
		
		
		    /*entry1 used netif,update reference netif */ 
		    rtl865x_referNetif(netif->name);
		
		    /*entry1 used pppoe!, update reference pppoe */ 
		    if ((entry1->nextHopType == IF_PPPOE) 
			||(entry1->nextHopType == IF_PPTP) 
			||(entry1->nextHopType == IF_L2TP) 
			
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
			    _rtl865x_referPpp(nexthop);
			
#else /* 
			    rtl865x_referPpp(nexthop);
			
#endif /* 
		}
		
		    /*FIXME_hyking:lazy, update the route information right here.... */ 
		    rt_t = (rtl865x_route_t *) ref_ptr;
		
		
		
	
	else
		
	
	    /*update reference dstnetif&pppoe arp? */ 
	    rtl865x_referNetif(netif->name);
	
	     ||(entry->nextHopType == IF_PPTP) 
	     ||(entry->nextHopType == IF_L2TP) 
		
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
		    _rtl865x_referPpp(nexthop);
		
#else /* 
		    rtl865x_referPpp(nexthop);
		
#endif /* 
	}
	



{
	
	
	    //int32 retval = 0;
	    
		
	
	
		
	
		
		
			entry->refCnt);
		
		
	
	    /*now delete the entry */ 
	    //if(entry->srcIp_t)
	    //retval = rtl865x_delIp(entry->srcIp_t->extIp);
	    
		 ||(entry->nextHopType == IF_PPTP) 
		 ||(entry->nextHopType == IF_L2TP) 
		
		
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
		    _rtl865x_deReferPpp(entry->nexthop);
		
#else /* 
		    rtl865x_deReferPpp(entry->nexthop);
		
#endif /* 
		
	
	
	
	    /*update asic nextHop table */ 
	    //_rtl865x_arrangeNxtHop(entryIdx,1);
	    



#if defined(CONFIG_RTL_MULTIPLE_WAN)  ||defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
static int32 _rtl865x_synNxtHop_by_arp_entry(rtl865x_nextHopEntry_t * entry_t,
					     rtl865x_arpMapping_entry_t * arp) 
{
	
	
	
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
	
	
	
	
	
	
	
	
	
		
		
		
	
		
		
		
		    memcmp(arp->mac.octet, zero_mac.octet, ETHER_ADDR_LEN);
		
						   &fid);
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (mac_valid) ? &arp->mac :
					     &reservedMac, FDB_DYNAMIC,
					     &columIdx, &asic_l2);
		
		    rtl8651_filterDbIndex((mac_valid) ? &arp->mac :
					  &reservedMac, fid);
		
		
		
		
	
	else
		
		
		    /*session based interface type */ 
		    rtl865x_ppp_t pppoe;
		
		
		
			
			    rtl865x_getPppBySessionId(entry_t->nexthop, &pppoe);
		
						   &fid);
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (pppoe.
					      valid) ? &pppoe.server_mac :
					     &reservedMac, FDB_DYNAMIC,
					     &columIdx, &asic_l2);
		
		    rtl8651_filterDbIndex((pppoe.
					   valid) ? &pppoe.server_mac :
					  &reservedMac, fid);
		
		
		
		
		    //printk("%s(%d): pppoeIdx(%d), pppoeType(%d), pppoevalid(%d),pppoeSid(%d)\n",__FUNCTION__,__LINE__,pppidx,pppoe.type,pppoe.valid,pppoe.sessionId);
		    asic.pppoeIdx = (pppoe.type == IF_PPPOE) ? pppidx : 0;
		
	
		
		
		
			
		
	
	else
		
	
		
	
	
		
	
	
	    //printk("%s(%d), entryIdx(%d),asic.isPPPoe(%d),asic.pppoeIdx(%d),asic.dvid(%d)\n", __FUNCTION__,__LINE__,entry_t->entryIndex,asic.isPppoe,asic.pppoeIdx,asic.dvid);
	    rtl8651_setAsicNextHopTable(entry_t->entryIndex, &asic);
	



{
	
	
	
	
		
	
	
	
		
		
			
			
			    /*update nexthop */ 
			    if (entry->nexthop == arp->ip)
				
				
				
			
		
	



{
	
	
	
	
		
	
	
	
	    //set mac to 0 for sync nexthop
	    memset(arp->mac.octet, 0, ETHER_ADDR_LEN);
	
		
		
			
			
			    /*update nexthop */ 
			    if (entry->nexthop == arp->ip)
				
			
		
	



#endif /* 
    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
extern int32 _rtl865x_eventHandle_6rd_addArp(rtl865x_arpMapping_entry_t * arp);


#endif /* 
#endif /* 

{
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	extern int sixrd_hw_fw;
	
#endif /* 
#endif /* 
	    rtl865x_arpMapping_entry_t * arp;
	
	
	
		
	
	
	
		
		
		    /*skip ipv6 nexthop update to let ipv6 routing packet trap to cpu!!!! */ 
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
		    if (!sixrd_hw_fw)
			
			
#endif /* 
#endif /* 
			    if (entry->valid && entry->nextHopType == IF_ETHER)
				
				
				    /*update nexthop */ 
				    if (entry->nexthop == arp->ip)
					
				
			
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
			}
		
#endif /* 
#endif /* 
		}
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	    _rtl865x_eventHandle_6rd_addArp(arp);
	
#endif /* 
#endif /* 
	    return EVENT_CONTINUE_EXECUTE;



{
	
	
	
	
		
	
	
	
		
		
			
			
			    /*update nexthop */ 
			    if (entry->nexthop == arp->ip)
				
			
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	    _rtl865x_eventHandle_6rd_delArp(arp);
	
#endif /* 
#endif /* 
	    return EVENT_CONTINUE_EXECUTE;



{
	
	
	
	
		
	
	
	
		
		
			
			     ||(entry->nextHopType == IF_PPTP) 
			     ||(entry->nextHopType == IF_L2TP) 
				
				
				    /*update nexthop */ 
				    if (entry->nexthop == pppoe->sessionId)
					
					
					    /*update the action(TOCPU) */ 
					    entry->nexthop = 0;
					
					
				
		
	



{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



/*
@func int32 | rtl865x_addNxtHop |add a nexthop entry
@parm uint32 | attr | attribute. NEXTHOP_L3/NEXTHOP_REDIRECT.
@parm void* | ref_ptr | entry pointer who refer this nexthop entry.
@parm rtl865x_netif_local_t* | netif | network interface.
@parm uint32 | nexthop | nexthop. ip address when linktype is ethernet, session id when linktype is ppp session based.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl865x_addNxtHop(uint32 attr, void *ref_ptr,
			    rtl865x_netif_local_t * netif, uint32 nexthop,
			    uint32 srcIp)
{
	
	
	
	    //rtl_down_interruptible(&nxthop_sem);  
	    SMP_LOCK_ETH_HW(flags);
	
	
	    //rtl_up(&nxthop_sem);  
	    SMP_UNLOCK_ETH_HW(flags);
	



/*
@func int32 | rtl865x_delNxtHop |delete nexthop entry
@parm uint32 | attr | attribute. NEXTHOP_L3/NEXTHOP_REDIRECT.
@parm uint32 | entryIdx | entry index.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl865x_delNxtHop(uint32 attr, uint32 entryIdx) 
{
	
	
	
	    //rtl_down_interruptible(&nxthop_sem);
	    SMP_LOCK_ETH_HW(flags);
	
	
	    //rtl_up(&nxthop_sem);
	    SMP_UNLOCK_ETH_HW(flags);
	



#if defined (CONFIG_RTL_LOCAL_PUBLIC) || defined(CONFIG_RTL_MULTIPLE_WAN) ||defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)||defined(CONFIG_RTL_EXT_PORT_SUPPORT)
    int32 rtl865x_getNxtHopIdx(uint32 attr, rtl865x_netif_local_t * netif,
			       uint32 nexthop) 
{
	
	
	
	
		
		
		     (entry->flag == attr) && 
		     (entry->dstNetif == netif) && 
			
			
			
		
	



#endif /* 
    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
    int32 _rtl865x_eventHandle_addIpv6Arp(rtl8198c_ipv6_arpMapping_entry_t *
					  arp) 
{
	
	
	
	
	
		
	
	
		
		
			
			
			    /*update nexthop */ 
			    if (entry->nexthop)
				
				
				    _rtl865x_getIpv6DsLiteEntryByName
				    (entry->dstNetif->name);
				
					
					    _rtl865x_getIpv6DsLiteEntryByIndex
					    (dsltIndex);
				
					
					
					     (&gw_ipv6_addr, &arp->ip,
					      sizeof(inv6_addr_t)) == 0)
						
						
						    (entry);
						
					
				
			
		
	



					 arp) 
{
	
	
	
	
	
		
	
	
		
		
			
			
			    /*update nexthop */ 
			    dsltIndex =
			    _rtl865x_getIpv6DsLiteEntryByName(entry->
							      dstNetif->name);
			
				
				    _rtl865x_getIpv6DsLiteEntryByIndex
				    (dsltIndex);
			
				
				
				     (&gw_ipv6_addr, &arp->ip,
				      sizeof(inv6_addr_t)) == 0)
					
					
					    /*reset the gw ipv6 address to reset the default gw L3 nexthop info */ 
					    memset(&gw_ipv6_addr, 0,
						   sizeof(inv6_addr_t));
					
					
				
			
		
	



#endif /* 
#endif /* 
    
#ifdef CONFIG_RTL_PROC_NEW
    int32 sw_nexthop_read(struct seq_file * s, void *v)
{
	
	
	
	
		
		
			
		
#if 0
		{
			
			
			
			    //rtl865x_ip_entry_t *srcIp_t;          /* for nexthop source ip table index, it's invalid  now*/
			    uint32 srcIp;	/* for nexthop source ip table index */

nextHopType:		    3, /* IF_ETHER, IF_PPPOE */ 
flag:			    3;	/* bit0:referenced by l3, bit2:referenced by acl */
			
			
		
		
#endif /* 
		    sw_nxthop = &rtl865x_nxtHopTable[idx];
		
			    "  [%d]  entryIndex(%d)  type(%d) netif(%s) srcIp(%x)  nextHop(%x) \n",
			    idx, 
			    sw_nxthop->dstNetif->name, 
			    sw_nxthop->nexthop);
		
	



#else /* 
    int32 sw_nexthop_read(char *page, char **start, off_t off, int count,
			  int *eof, void *data)
{
	
	
	
	
	
		
		
			
		
		
		    sprintf(page + len,
			    "  [%d]  entryIndex(%d)  type(%d) netif(%s) srcIp(%d)  nextHop(%d) n",
			    idx, 
			    sw_nxthop->dstNetif->name, 
			    sw_nxthop->nexthop);
		
	



#endif /* 
    
			    unsigned long len, void *data)
{
	


