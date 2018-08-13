/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* 
* Program : route table driver
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*/  
/*      @doc RTL_LAYEREDDRV_API

        @module rtl865x_route.c - RTL865x Home gateway controller Layered driver API documentation       |
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
//#include <net/rtl/rtl865x_ppp.h>
#include <net/rtl/rtl865x_netif.h>
#include "common/rtl_errno.h"
//#include "rtl_utils.h"
#include "common/rtl865x_netif_local.h"
#include "rtl865x_ppp_local.h"
#include "rtl865x_route.h"
#include "rtl865x_ip.h"
#include "rtl865x_nexthop.h"
#include "rtl865x_arp.h"
    
//#include "common/rtl_glue.h"
#include "common/rtl865x_eventMgr.h" /*call back function....*/
#include "common/rtl865x_vlan.h"
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865x_asicL2.h"
#include "AsicDriver/rtl865x_asicL3.h"
#else /* 
#include "AsicDriver/rtl865xC_tblAsicDrv.h"
#endif /* 
#include "l2Driver/rtl865x_fdb.h"
#include "AsicDriver/rtl865xc_asicregs.h"
#include <net/rtl/rtl865x_fdb_api.h>
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#include "rtl8198c_arpIpv6.h"
#include "rtl8198c_nexthopIpv6.h"
#endif /* 



#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
static RTL_DECLARE_MUTEX(route_sem);

#endif /* 
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
extern int32 _rtl865x_getIpv6DsLiteEntryByName(char *devName);


#endif /* 
#endif /* 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)	//&&defined(REINIT_SWITCH_CORE)
static rtl865x_route_t rtl865x_route_inused_bak[RT_DRV_ENTRY_NUM];

#endif /* 
#if 0
void _rtl865x_route_print(void) 
{
	
	
	
	
	
		
		
		    ("asicIdx(%d),ip(0x%x),mask(0x%x),nextHop(0x%x),process(0x%x),dst(%s) valid(%d)\n",
		     rt->asicIdx, rt->ipAddr, rt->ipMask, rt->nextHop,
		     rt->process, rt->dstNetif->name, rt->valid);
		
		
	
	
	
		
		
		
		
	



#endif /* 

{
	
	
	
		
		
			
		
		
	



						  ipaddr_t ipMask) 
{
	
	
	
		
		
		     && ((rt->ipAddr & rt->ipMask) == (ipAddr & ipMask))
		     && (rt->ipMask == ipMask))
			
		
		
	



{
	
	
	
	
	
	
	
	
		
		
			__LINE__);
		
		
	
	    /*common information */ 
	    asic_t.ipAddr = rt_t->ipAddr;
	
	
	
	
	    /*if the dstNetif is attach on another interface, the netifIdx should the master interface's index */ 
	    if (rt_t->dstNetif->is_slave == 1)
		
		
		    //printk("========%s(%d), ip(0x%x),mask(0x%x),netif(%s)\n",__FUNCTION__,__LINE__,rt_t->ipAddr,rt_t->ipMask,rt_t->dstNetif->name);
		    dstNetif = _rtl865x_getNetifByName(rt_t->dstNetif->name);
		
			
		
	
	else
		
	
		
		
	
	
	
	
	
	
		
	
		
		
		
		    /*
		     *if process==RT_PPPOE, the mac address of pppoe server is add in pppoe module,
		     *so, we read the FDB information directly....
		     */ 
		    ret =
		    rtl865x_getVlanFilterDatabaseId(rt_t->dstNetif->vid, &fid);
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (ether_addr_t *) rt_t->un.
					     pppoe.macInfo, FDB_DYNAMIC,
					     &columIdx, &asic_l2);
		
			
		
		    /*FIXME_hyking: update mac/fdb table reference count */ 
		    asic_t.nextHopRow =
		    rtl8651_filterDbIndex(rt_t->un.pppoe.macInfo, fid);
		
		
	
		
		    /*
		     * NOTE:this type not used now...
		     * if we want to use it, please add FDB entry to sure this L2 entry in both software FDB table and Asic L2 table.
		     */ 
		    ret =
		    rtl865x_getVlanFilterDatabaseId(rt_t->dstNetif->vid, &fid);
		
		    rtl865x_Lookup_fdb_entry(fid,
					     (ether_addr_t *) rt_t->un.
					     direct.macInfo, FDB_STATIC,
					     &columIdx, &asic_l2);
		
			
			    ("can't get l2 entry by mac.....***************\n");
		
		    /*FIXME_hyking: update mac/fdb table reference count */ 
		    asic_t.nextHopRow =
		    rtl8651_filterDbIndex(rt_t->un.direct.macInfo, fid);
		
		
	
		
		    /*FIXME_hyking: update arp table reference count?? */ 
		    asic_t.arpStart = rt_t->un.arp.arpsta;
		
		
		
	
	
		
		    /*do nothing */ 
		    break;
	
		
		
		    rt_t->un.nxthop.nxtHopEnd - rt_t->un.nxthop.nxtHopSta + 1;
		
		
		
		
	
		
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    
	    /*for dislite */ 
	    asic_t.DSLEG = rt_t->DSLEG;
	
	
#endif /* 
#endif /* 
	    if (rt_t->asicIdx > RT_ASIC_ENTRY_NUM - 1)
		
		
		
		
	
	



					    int32 action) 
{
	
	
	
	
	
		
	
	    /*delete nexthop which is add by default route */ 
	    if (rt->process == RT_NEXTHOP)
		
		      i <= entry->un.nxthop.nxtHopEnd
		      && entry->un.nxthop.nxtHopEnd != 0; i++)
			
			
			
	
	
	
		
	
		
		    rtl865x_addNxtHop(NEXTHOP_L3, (void *)entry,
				      entry->dstNetif, 0, entry->srcIp);
		
	
		
			
			
				
			
				
				    rtl865x_addNxtHop(NEXTHOP_L3, (void *)rt,
						      rt->dstNetif, rt->nextHop,
						      entry->srcIp);
				
			
				
					
					
					    rtl865x_getPppByNetifName
					    (rt->dstNetif->name);
					
						
						
						    /*got pppoe session */ 
						    retval =
						    rtl865x_addNxtHop
						    (NEXTHOP_L3, (void *)rt,
						     rt->dstNetif,
						     pppoe->sessionId,
						     entry->srcIp);
						
					
					else
						
						    /*nexthop's action is to CPU */ 
						    retval =
						    rtl865x_addNxtHop
						    (NEXTHOP_L3, (void *)rt,
						     rt->dstNetif, 0,
						     entry->srcIp);
				
				
		
		
		
	
	



				      int32 start_idx) 
{
	
	
	
	
	
		
		
			
			
			    /*if the rule is default route... */ 
			    if (rt->ipMask == 0)
				
			
			else
				
				
				    /* entry number more than asic table's capacity */ 
				    /* entry index=RT_ASIC_ENTRY_NUM-1 is reserved for default route */ 
				    if ((start_idx + count >
					 RT_ASIC_ENTRY_NUM - 2))
					
				
				    /*delete old asic entry firstly... */ 
				    if (start_idx + count < rt->asicIdx
					&& rt->asicIdx < RT_ASIC_ENTRY_NUM - 1)
					
				
				
				
			
		
		    /*next entry */ 
		    rt = rt->next;
		
		
	
	    /*more route entry need to add? */ 
	    if (rt)
		
		
		    /*not enough asic table entry! have to update default route's action TOCPU */ 
		    rt = _rtl865x_getDefaultRoute();
		
		
	
	else
		
		
		
		
	



{
	
	
	
	
	
	
	    /*always set 0x0f when init..., this value would be reset in arrange route */ 
	    rt->asicIdx = 0x0f;
	
	
	    /*find the right position... */ 
	    while (entry)
		
		
			
			
				
				
				
			
		
		
		
	
	    /*insert this rule after insert_entry */ 
	    if (fore_rt)
		
		
		
		
		
		
	
	else
		
		
		    /*insert head... */ 
		    rt->next = rtl865x_route_inusedHead;
		
		
		
		
	
	
	    //_rtl865x_route_print();
	    return retval;



{
	
	
	
	
		
		
			
		
		
		
	
	    /*fore_rt == NULL means delete list head */ 
	    if (fore_rt == NULL)
		
		
		
		
		
	
	else
		
		
		
		
		
	
	    /*delete route from asic */ 
	    if (rt->asicIdx < RT_ASIC_ENTRY_NUM)
		
	
	
	
	    //_rtl865x_route_print();
	    



{
	
	
	
		
		
			
		
		
	



				      ipaddr_t nextHop, int8 * ifName,
				      ipaddr_t srcIp) 
{
	
	
	
	
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    int32 dsltIndex = FAILED;
	
#endif /* 
#endif /* 
	    
		
		
			return RTL_EINVNETIFNAME;
	
	
	    /*para check */ 
	    if (ifName == NULL)
		
	
	else
		
	
#if 0
	    if ((ipAddr & ipMask) == 0xc0a80200)
		
	
#endif /* 
	    if (netif == NULL)
		
	
		
	
	
		
			
	
	
		
	
#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
	    if (swconfig_vlan_enable) {
		
		     && 
				 MAX_IFNAMESIZE)
		     && 
				 MAX_IFNAMESIZE))
			
	
	
#endif /* 
	    
	    /*
	     *duplicate entry check:
	     *      in Driver system, default route is always exist.
	     *      so if ipMask == 0, it's means that default route should be update...
	     */ 
	    if (ipMask != 0
		&& (rt = _rtl865x_getRouteEntry(ipAddr, ipMask)) != NULL)
		
		
		    //rt->ref_count++;
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
		    rt->exist_in_ps = 1;
		
#endif /* 
		    return RTL_EENTRYALREADYEXIST;
		
	
	    /*add default route: just update the default route becase the default route always exist! */ 
	    if (ipMask == 0)
		
		
		
		    /*deference rt's orginal netif */ 
		    if (rt && rt->dstNetif) {
			
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
			    if (rt->nextHop == nextHop) {
				
					
					     (rt->dstNetif->name, ifName,
					      MAX_IFNAMESIZE) == 0) {
						
						
					
				
					
					
				
			
			
#endif /* 
			    rtl865x_deReferNetif(rt->dstNetif->name);
		
		
	
	    /*allocate a new buffer for adding entry */ 
	    if (rt == NULL)
		
		
		
			
			
			
		
	
		
		
		    /*no buffer, default route should be TOCPU? */ 
		    return RTL_ENOFREEBUFFER;
		
	
	    /*common information */ 
	    rt->ipAddr = ipAddr & ipMask;
	
	
	
	
	
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
	    rt->exist_in_ps = 1;
	
#endif /* 
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    if (netif->if_type == IF_DSLT)
		
		
		
		    /*hook default gw for dslist interface */ 
		    if (ipAddr == 0 && ipMask == 0 && nextHop != 0
			&& srcIp != 0)
			
			
				
				
			
			
			else
				
				
				
				
			
		
	
#endif /* 
#endif /* 
	    
	    /*don't specify the nexthop ip address, it's means that:
	     * all packet match this route entry should be forward by network interface with arp
	     */ 
	    
		
		
			
		
			
			
			
				
				
				     && tmp_rt->dstNetif == netif)
					
					    tmp_rt->un.arp.arpend -
					    tmp_rt->un.arp.arpend + 1;
				
				
			
				
				
					usedArpCnt, netSize);
				
				
			
			    /*allocate arp entry for this route rule... */ 
			    
			
				
				
				    ("error!!can't allocate arp for this route entry....retval(%d)\n",
				     retval);
				
				
			
			    //rt->un.arp.arpIpIdx = 0; /*FIXME_hyking[this field is invalid, right?]*/
			    rtl865x_getIpIdxByIpRange(ipAddr, ipMask,
						      &rt->un.arp.arpIpIdx);
			
			    //printk("%s %d ipAddr=0x%x ifName=%s rt->un.arp.arpIpIdx=%d\n", __FUNCTION__, __LINE__, ipAddr, ifName, rt->un.arp.arpIpIdx);
			    break;
		
			
				
				
				
				
					
					
					    ("error!!can't get pppoe session information by interface name(%s)\n",
					     netif->name);
					
					
				
				
				
				    /*update reference... */ 
				    rtl865x_referPpp(ppp->sessionId);
				
#if 0				//defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
				    retval =
				    rtl865x_getNxtHopIdx
				    (NEXTHOP_DEFREDIRECT_ACL, netif,
				     ppp->sessionId);
				
					
					    rtl865x_addNxtHop
					    (NEXTHOP_DEFREDIRECT_ACL,
					     (void *)rt, netif, ppp->sessionId,
					     srcIp);
					
						
						    ("Warning!!add pppoe nexthop for redirect acl fail! retval (%d)\n",
						     retval);
						
					
				
				
#endif /* 
			}
			
		
		
			
				
				
				
				
					
					
					    /*printk("Warning!!CAn't get pptp/l2tp session information by interface name(%s)\n",netif->name); */ 
					    goto addFailed;
					
				
			
			
			
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
		case IF_DSLT:
			
				
				
				    /*
				       set L3 table
				       All packet dip equal to tunnel local ip,trap to cpu.
				     */ 
				extern int get_P2P_local_ip(unsigned char
							    *ifname, unsigned int
							    *ipAddr);
				
				    /*get p2p device local ip ****************** */ 
				    if (!get_P2P_local_ip
					(netif->name, &(rt->ipAddr)))
					
					
						__FUNCTION__, __LINE__);
					
				
				
			
			
#endif /* 
#endif /* 
		default:
			
				netif->if_type);
			
			
		
	
	else
		
		
		    /*if default is valid, delete nexthop firstly... */ 
		    if (rt->valid == 1 && rt->process == RT_NEXTHOP)
			
			
			
			      i <= rt->un.nxthop.nxtHopEnd; i++)
				
				
				
			
		
		    /*use nexthop type */ 
		    rt->process = RT_NEXTHOP;
		
			
		
			
			    rtl865x_addNxtHop(NEXTHOP_L3, (void *)rt, netif,
					      nextHop, srcIp);
			
		
		
		
			
				
				
				    rtl865x_getPppByNetifName(netif->name);
				
					
					
					    /*got pppoe session */ 
					    retval =
					    rtl865x_addNxtHop(NEXTHOP_L3,
							      (void *)rt, netif,
							      pppoe->sessionId,
							      srcIp);
					
				
				else
					
					    /*nexthop's action is to CPU */ 
					    retval =
					    rtl865x_addNxtHop(NEXTHOP_L3,
							      (void *)rt, netif,
							      0, srcIp);
			
			
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
		
			
				
				    rtl865x_addNxtHop(NEXTHOP_L3, (void *)rt,
						      netif, nextHop, srcIp);
			
			
#endif /* 
#endif /* 
		
			
			
			
		
			
			
				retval);
			
			
		
		
		
	
	
	
	    /*update reference.... */ 
	    rtl865x_referNetif(netif->name);
	
		
	
		
		
		
	
	else
		
		
		    /*insert the adding route to inused list */ 
		    retval = _rtl865x_addRouteToInusedList(rt);
		
	
	    /*if route is add, please enable Routing for the releated netif */ 
	    retval = rtl865x_enableNetifRouting(netif);
	

		
		
		
	
	else
		
		
		    /*free this route entry and return error code... */ 
		    memset(rt, 0, sizeof(rtl865x_route_t));
		
		
		
	



{
	
	
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    int32 dsltIndex = FAILED;
	
#endif /* 
#endif /* 
	    
	
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    dsltIndex =
	    _rtl865x_getIpv6DsLiteEntryByName(entry->dstNetif->name);
	
		
		
		
	
#endif /* 
#endif /* 
	    if (entry->asicIdx == RT_ASIC_ENTRY_NUM - 1)
		
		
		    /*if default route
		     * 1. reset default route
		     * 2. reset entry->netif...
		     */ 
		    rtl865x_netif_local_t * netif = NULL;
		
		
		
			
			
			
		
			
			
			
			
			
		
		    _rtl865x_updateDefaultRoute(entry,
						RT_DEFAULT_RT_NEXTHOP_CPU);
		
	
	else
		
		
		    /*not default route */ 
		    switch (entry->process)
			
		
			
				
				
					
			
			
		
			
			    /*
			     * NOTE:this type not used now...
			     * if we want to use it, please DELETE FDB entry to sure this L2 entry is deleted both software FDB table and Asic L2 table.
			     */ 
			    break;
		
			
			    /*free arp */ 
			    retval = rtl865x_arp_tbl_free(entry);
			
				
				
				    ("======error!!can't FREE arp entry for this route entry....retval(%d)\n",
				     retval);
				
			
		
		
			
			    /*do nothing */ 
			    
		
			
			    /*delete nexthop which is add by l3 */ 
			    for (i = entry->un.nxthop.nxtHopSta;
				 i <= entry->un.nxthop.nxtHopEnd; i++)
				
				
				
			
			
		
		    /*FIXME_hyking: update netif reference count */ 
		    rtl865x_deReferNetif(entry->dstNetif->name);
		
		    /*remove from inused list... */ 
		    _rtl865x_delRouteFromInusedList(entry);
		
		       FAILED)
			
		
		    /*add to free list */ 
		    memset(entry, 0, sizeof(rtl865x_route_t));
		
		
		
		
	
	    //_rtl865x_route_print();
	    return retval;



{
	
	
	
	
	
		
		
		     && mask <= rt->ipMask) {
			
			
		
		
		
	



/*
@func int32 | rtl865x_addRoute |add a route entry.
@parm ipaddr_t | ipAddr | ip address.
@parm ipaddr_t | ipMask | ip mask.
@parm ipaddr_t | nextHop | the route's next hop.
@parm int8* | ifName | destination network interface. 
@parm ipaddr_t | srcIp |source IP
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@rvalue RTL_EINVALIDINPUT | invalid input.
@rvalue RTL_ENOLLTYPESPECIFY | network interface's link type is not specified.
@rvalue RTL_EENTRYALREADYEXIST | route entry is already exist.
@rvalue RTL_ENOFREEBUFFER | not enough memory in system.
@comm
	if ifName=NULL, it means the destionation network interface of route entry with ip/ipMask/nextHop is default wan.
*/ 
    int32 rtl865x_addRoute(ipaddr_t ipAddr, ipaddr_t ipMask, ipaddr_t nextHop,
			   int8 * ifName, ipaddr_t srcIp) 
{
	
	
	
	    //printk("========%s(%d), ip(0x%x),mask(0x%x),ifname(%s),nxthop(0x%x)\n",__FUNCTION__,__LINE__,ipAddr,ipMask,ifName,nextHop);
	    //rtl_down_interruptible(&route_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&route_sem);
	    SMP_UNLOCK_ETH(flags);
	
	    //printk("========%s(%d), ip(0x%x),mask(0x%x),ifname(%s),nxthop(0x%x),retval(%d)\n",__FUNCTION__,__LINE__,ipAddr,ipMask,ifName,nextHop,retval);
	    //_rtl865x_route_print();
	    return retval;



/*
@func int32 | rtl865x_delRoute |delete a route entry.
@parm ipaddr_t | ipAddr | ipAddress.
@parm ipaddr_t | ipMask | ipMask.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@rvalue RTL_EENTRYNOTFOUND | not found the entry.
@comm	
*/ 
    int32 rtl865x_delRoute(ipaddr_t ipAddr, ipaddr_t ipMask) 
{
	
	
	
	    //printk("========%s(%d), ip(0x%x),mask(0x%x)\n",__FUNCTION__,__LINE__,ipAddr,ipMask);
	    //rtl_down_interruptible(&route_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&route_sem);   
	    SMP_UNLOCK_ETH(flags);
	
	    //printk("==================================retval(%d)\n",retval);
	    return retval;



/*
@func int32 | rtl865x_getRouteEntry |according the destination ip address, get the matched route entry.
@parm ipaddr_t | dst | destionation ip address.
@parm rtl865x_route_t* | rt | retrun value: route entry pointer
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl865x_getRouteEntry(ipaddr_t dst, rtl865x_route_t * rt) 
{
	
	
	
	
		
		
		
		
	



/*
@func int32 | rtl865x_initRouteTable |initialize route tabel.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl865x_initRouteTable(void)
{
	
	
	
	
	
	    /*malloc buffer */ 
	    TBL_MEM_ALLOC(rt, rtl865x_route_t, RT_DRV_ENTRY_NUM);
	
	
		
		
		
		
	
#if defined(CONFIG_RTL_HARDWARE_NAT)	//&&defined(REINIT_SWITCH_CORE)
	    memset(rtl865x_route_inused_bak, 0,
		   sizeof(rtl865x_route_t) * RT_DRV_ENTRY_NUM);
	
#endif /* 
	    



/*
@func int32 | rtl865x_reinitRouteTable |reinitialize route tabel.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl865x_reinitRouteTable(void)
{
	
	
	
		
		
		
		
	
	    /*delete the last route */ 
	    rt = rtl865x_route_inusedHead;
	
		
		
		    /*FIXME_hyking: update netif reference count */ 
		    rtl865x_deReferNetif(rt->dstNetif->name);
		
		    /*remove from inused list... */ 
		    _rtl865x_delRouteFromInusedList(rt);
		
		    /*add to free list */ 
		    memset(rt, 0, sizeof(rtl865x_route_t));
		
		
		
	



#if defined (CONFIG_RTL_LOCAL_PUBLIC)
int rtl865x_getLanRoute(rtl865x_route_t routeTbl[], int tblSize) 
{
	
	
	
	
		
		
			
			
			
			
		
		
	



#endif /* 
#ifdef CONFIG_RTL_PROC_NEW
    int32 sw_l3_read(struct seq_file * s, void *v)
{
	
	
	
	
	
		
		
			
		
			      "\t[%d]  ip:%x,%x,	%x,nexthop:%x  process(%d)  asicIdx:%d, netif%s \n",
			      
			      entry->srcIp, 
			      entry->asicIdx, entry->dstNetif->name);
		
		
		
	



#else /* 
    int32 sw_l3_read(char *page, char **start, off_t off, int count, int *eof,
		     void *data)
{
	
	
	
	
	
	
		
		
			
		
		    sprintf(page + len,
			    "\t[%d]  ip:%x,%x,	%x,nexthop:%x  process(%d)  asicIdx:%d, netif:%s \n",
			    
			    entry->srcIp, 
			    entry->process, entry->asicIdx,
			    entry->dstNetif->name);
		
		
		
	



#endif /* 
    
		       void *data)
{
	



#if defined(CONFIG_RTL_EXT_PORT_SUPPORT)
int rtl865x_checkL3L2Valid(ipaddr_t ipAddr) 
{
	
	
	
	
	
	
		
	
		
		
			
			
				
				
					
				
					
					    /*fix me: to real check pppoe valid */ 
					    return 1;
					
				
					
					    /*
					     * NOTE:this type not used now...
					     * if we want to use it, please add FDB entry to sure this L2 entry in both software FDB table and Asic L2 table.
					     */ 
					    ret =
					    rtl865x_getVlanFilterDatabaseId
					    (rt->dstNetif->vid, &fid);
					
					    rtl865x_Lookup_fdb_entry(fid,
								     (ether_addr_t
								      *) rt->
								     un.direct.macInfo,
								     FDB_STATIC,
								     &columIdx,
								     &asic_l2);
					
						
						
						
					
					else
						
						
						
					
				
					
						
						
						
					
					else
						
						
						
					
				
				
					
					
				
					
						
					
						
						     (NEXTHOP_L3, rt->dstNetif,
						      rt->nextHop) != -1)
							
							
							
						
						else
							
							
							
						
					
						
						    /*fix me, to really check pppoe nexthop valid or not */ 
						    return 1;
					
					
						
						
					
						
						
						
					
				
					
					
					
				
			
		
		
	



#endif /* 

{
	
	
	
		
		
		
			
			
			     && (strncmp(rt->dstNetif->name, name, 4) == 0)) {
				
				
			
			
			
		
	



#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
int rtl_clear_router_exist_in_ps_flag(void) 
{
	
	
	
	
	
		
		
			
		
		
	
	



{
	
	
	
	
	
	
	
	
		
		
		    /*find the router entry who is not in linux ps */ 
		    if ((rt->valid == 1) && (rt->exist_in_ps == 0)) {
			
			
			
		
		
		
	
		
		
		
	
	



#endif /* 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)	//&&defined(REINIT_SWITCH_CORE)
int rtl819x_save_inused_route(void) 
{
	
	
	
		  sizeof(rtl865x_route_t) * RT_DRV_ENTRY_NUM);
	
		
		
			
				sizeof(rtl865x_route_t));
			
			
				
		
		
		
	



{
	
	
	
		
		
			
			
					  rt->dstNetif->name, rt->srcIp);
		
		
	



#endif /* 
    
#if defined(CONFIG_SWCONFIG_SUPPORT_HW_NAT)
int rtl_check_default_router_valid(void) 
{
	
	
	
	
		
		      (rt->dstNetif->name, hw_nat_wan_dev_name,
		       MAX_IFNAMESIZE) == 0)
		     ||
		     
		       (rt->dstNetif->name, RTL_SWCONFIG_DRV_PPP_NETIF_NAME,
			MAX_IFNAMESIZE) == 0))
			
	
	



#endif /* 
    