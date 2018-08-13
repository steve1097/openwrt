/*
* Copyright c                  Realtek Semiconductor Corporation, 2013  
* All rights reserved.
* 
* Program : ipv6 nexthop table driver
* Abstract : 
* Author : Jia Wenjian (wenjain_jai@realsil.com.cn)  
*/  
    
/*      @doc RTL_LAYEREDDRV_API

        @module rtl8196c_nexthopIpv6.c - RTL865x Home gateway controller Layered driver API documentation       |
        This document explains the API interface of the table driver module. Functions with rtl8198c prefix
        are external functions.
        @normal Jia Wenjian (wenjain_jai@realsil.com.cn) <date>

        Copyright <cp>2013 Realtek<tm> Semiconductor Cooperation, All Rights Reserved.

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
#include "rtl8198c_nexthopIpv6.h"
//#include "rtl865x_ppp.h"
#include "rtl865x_ppp_local.h"
#include "rtl8198c_routeIpv6.h"
#include "rtl8198c_arpIpv6.h"
    
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
#include "rtl865x_route.h"
#include "rtl865x_arp.h"
#include "rtl865x_nexthop.h"
#endif /* 
    
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
#ifdef CONFIG_RTL_HW_6RD_SUPPORT
#include <linux/netdevice.h>
#include <net/ip_tunnels.h>
#include "rtl865x_6rd.h"
extern ipaddr_t br_ip_addr;

#endif /* 
#endif /* 


#define IPV6_NEXTHOP_TABLE_INDEX(entry)	(entry - rtl865x_ipv6_nxtHopTable)
static int32 _rtl8198c_ipv6_nextHop_register_event(void);



#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
extern int32 _rtl865x_referPpp(uint32 sessionId);


#endif /* 
    
#if 0
static void _print_softNxtHop(void) 
{
	
	
	
	
		
		
		    ("idx(%d): valid(%d),dst(%s),nexthop(0x%x%x%x%x),nexthopType(%d),refCnt(%d)\n",
		     i, entry->valid, entry->dstNetif->name,
		     
		     entry->un.nexthop.v6_addr32[1],
		     entry->un.nexthop.v6_addr32[2],
		     
		     entry->refCnt);
		



#endif /* 
    
/*
@func int32 | rtl8198c_initIpv6NxtHopTable |initialize the nexthop table
@rvalue SUCCESS | success.
@rvalue FAILED | failed. system should reboot.
@comm	
*/ 
    int32 rtl8198c_initIpv6NxtHopTable(void) 
{
	
		       IPV6_NXTHOP_ENTRY_NUM);
	
		sizeof(rtl8198c_ipv6_nextHopEntry_t) * IPV6_NXTHOP_ENTRY_NUM);
	
	



/*
@func int32 | rtl8198c_reinitIpv6NxtHopTable |reinitialize the nexthop table
@rvalue SUCCESS | success.
@comm	
*/ 
    int32 rtl8198c_reinitIpv6NxtHopTable(void)
{
	
	
	
		
		
			
		
	
	



					      entry_t) 
{
	
	
	
	
	
	
	
	
	
	
		
	
		
		
		
		    /*if the arp info of nexthop is not found, reserved to cpu Mac is used for trap packet to CPU */ 
		    if ((entry_t->un.nexthop.v6_addr32[0] != 0)
			|| (entry_t->un.nexthop.v6_addr32[1] != 0)
			|| 
			|| (entry_t->un.nexthop.v6_addr32[3] != 0))
			
			    rtl8198c_getIpv6ArpMapping(entry_t->un.nexthop,
						       &arp_t);
		
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
#ifdef CONFIG_RTL_HW_6RD_SUPPORT
	    else if (entry_t->nextHopType == IF_6RD)
		
		
		
		
		    /*if the arp info of nexthop is not found, reserved to cpu Mac is used for trap packet to CPU */ 
		    
		    rtl8198c_6rd_Ipv6ArpMapping(br_ip_addr, &arp_t);
		
		
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
		
		
		
			
			    rtl865x_getPppBySessionId(entry_t->un.pppSessionId,
						      &pppoe);
		
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
		
	
		
		
			
	
		
	
	
		
	
	
	    //printk("%s(%d), entryIdx(%d),asic.isPPPoe(%d),asic.pppoeIdx(%d),asic.dvid(%d)\n", __FUNCTION__,__LINE__,entry_t->entryIndex,asic.isPppoe,asic.pppoeIdx,asic.dvid);
	    rtl8198C_setAsicNextHopTableV6(entry_t->entryIndex, &asic);
	



{
	
	
	
		
	
		
		
		
			
		
	



					rtl865x_netif_local_t * netif,
					inv6_addr_t nexthop) 
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
	    for (entryIdx = 0; entryIdx < IPV6_NXTHOP_ENTRY_NUM; entryIdx++)
		
		
			
				
			
				
				     && ((entryIdx + 1) < IPV6_NXTHOP_ENTRY_NUM)
				     &&
				     
				       [entryIdx + 1].valid == 0)) {
					
					    &rtl865x_ipv6_nxtHopTable[entryIdx];
					
				
				
			
				
				
				
			
				
					attr);
				
				
		
		
	
	    /*if not found proper nextHop entry, return */ 
	    entry = NULL;

		
	
	
	
	
	
	
	
		
	
		
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	case IF_6RD:
		
#endif /* 
#endif /* 
		    memcpy(&entry->un.nexthop, &nexthop, sizeof(inv6_addr_t));
		
	
	
	
		
		    /*nexthop is sessionId */ 
		    entry->un.pppSessionId = nexthop.v6_addr32[0];
		
		
	
		
		
		
		
		
		    /*entry1 used netif,update reference netif */ 
		    rtl865x_referNetif(netif->name);
		
		    /*entry1 used pppoe!, update reference pppoe */ 
		    if ((entry1->nextHopType == IF_PPPOE)
			|| (entry1->nextHopType == IF_PPTP)
			|| (entry1->nextHopType == IF_L2TP)) {
			
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
			    _rtl865x_referPpp(nexthop.v6_addr32[0]);
			
#else /* 
			    rtl865x_referPpp(nexthop.v6_addr32[0]);
			
#endif /* 
		}
		
		    /*FIXME_hyking:lazy, update the route information right here.... */ 
		    rt_t = (rtl8198c_ipv6_route_t *) ref_ptr;
		
		
	
	
	else {
		
	
	
	    /*update reference dstnetif&pppoe arp? */ 
	    rtl865x_referNetif(netif->name);
	
	     || (entry1->nextHopType == IF_PPTP)
	     || (entry1->nextHopType == IF_L2TP)) {
		
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
		    _rtl865x_referPpp(nexthop.v6_addr32[0]);
		
#else /* 
		    rtl865x_referPpp(nexthop.v6_addr32[0]);
		
#endif /* 
	}
	



{
	
	
		
	
	
		
	
		
			entry->refCnt);
		
	
	
	       || (entry->nextHopType == IF_PPTP)
	       || (entry->nextHopType == IF_L2TP)) {
		
#if LINUX_VERSION_CODE > KERNEL_VERSION(3,4,0)
		    _rtl865x_deReferPpp(entry->un.pppSessionId);
		
#else /* 
		    rtl865x_deReferPpp(entry->un.pppSessionId);
		
#endif /* 
	}
	
	
	
	    /*jwj: Here not call _rtl8198c_arrangeIpv6NxtHop,because nexthop entry
	       is used for default router, and default router's nexthop will always exist. */ 
	    /*update asic nextHop table */ 
	    //_rtl8198c_arrangeIpv6NxtHop(entryIdx,1);
	    



#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
    int32 _rtl865x_eventHandle_6rd_addArp(rtl865x_arpMapping_entry_t * arp) 
{
	
	
	
	
	
		
	
	
		
		
			
			
			    /*update nexthop */ 
			    if (entry->un.nexthop.v6_addr32[0] != 0
				|| 
				|| 
				|| 
				
				
				    _rtl865x_getIpv66RDEntryByName
				    (entry->dstNetif->name);
				
					
					    _rtl865x_getIpv66RDEntryByIndex
					    (sixrdIndex);
				
					
					
						
						
						    (entry);
						
					
				
			
		
	



{
	
	
	
	
	
		
	
	
		
		
			
			
			    /*update nexthop */ 
			    sixrdIndex =
			    _rtl865x_getIpv66RDEntryByName(entry->
							   dstNetif->name);
			
				
				    _rtl865x_getIpv66RDEntryByIndex(sixrdIndex);
			
				
				
					
					
					    /*reset the gw ipv6 address to reset the default gw L3 nexthop info */ 
					    br_ip_addr = 0;
					
					
				
			
		
	



#endif /* 
#endif /* 
    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
extern int32 _rtl865x_eventHandle_addIpv6Arp(rtl8198c_ipv6_arpMapping_entry_t *
					     arp);

					      arp);

#endif /* 
#endif /* 

{
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	extern int dslite_hw_fw;
	
#endif /* 
#endif /* 
	    
	
	
	
		
	
	
	
		
		
		    /*skip ipv6 nexthop update to let ipv6 routing packet trap to cpu!!!! */ 
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
		    if (!dslite_hw_fw)
			
#endif /* 
#endif /* 
			    if (entry->valid
				&& (entry->nextHopType == IF_ETHER)) {
				
				    /*update nexthop */ 
				    if (memcmp
					(&entry->un.nexthop, &arp->ip,
					 sizeof(inv6_addr_t)) == 0)
					
			
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    /*for dslite tunnel to update nexthop info */ 
	    _rtl865x_eventHandle_addIpv6Arp(arp);
	
#endif /* 
#endif /* 
	    



{
	
	
	
	
		
	
	
	
		
		
			
			    /*update nexthop */ 
			    if (memcmp
				(&entry->un.nexthop, &arp->ip,
				 sizeof(inv6_addr_t)) == 0)
				
		
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    /*for dslite tunnel to update nexthop info */ 
	    _rtl865x_eventHandle_delIpv6Arp(arp);
	
#endif /* 
#endif /* 
	    return EVENT_CONTINUE_EXECUTE;



{
	
	
	
	
		
	
	
	
		
		
					(entry->nextHopType == IF_PPTP)
					|| (entry->nextHopType == IF_L2TP))) {
			
			    /*update nexthop */ 
			    if (entry->un.pppSessionId == pppoe->sessionId) {
				
				    /*update the action(TOCPU) */ 
				    entry->un.pppSessionId = 0;
				
			
		
		
	



{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	



/*
@func int32 | rtl8198c_addIpv6NxtHop |add a nexthop entry
@parm uint32 | attr | attribute. IPV6_NEXTHOP_L3/IPV6_NEXTHOP_REDIRECT.
@parm void* | ref_ptr | entry pointer who refer this nexthop entry.
@parm rtl865x_netif_local_t* | netif | network interface.
@parm inv6_addr_t | nexthop | nexthop. ipv6 ip address when linktype is ethernet, session id when linktype is ppp session based.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_addIpv6NxtHop(uint32 attr, void *ref_ptr,
				 rtl865x_netif_local_t * netif,
				 inv6_addr_t nexthop)
{
	
	
	
	
	
	



/*
@func int32 | rtl8198c_delIpv6NxtHop |delete nexthop entry
@parm uint32 | attr | attribute. IPV6_NEXTHOP_L3/IPV6_NEXTHOP_REDIRECT.
@parm uint32 | entryIdx | entry index.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_delIpv6NxtHop(uint32 attr, uint32 entryIdx) 
{
	
	
	
	
	
	


