/*
* Copyright c                  Realtek Semiconductor Corporation, 2013  
* All rights reserved.
* 
* Program : ipv6 route table driver
* Abstract : 
* Author : Jia Wenjian (wenjain_jai@realsil.com.cn)  
*/  
/*      @doc RTL_LAYEREDDRV_API

        @module rtl8198c_routeIpv6.c - RTL865x Home gateway controller Layered driver API documentation       |
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
//#include <net/rtl/rtl865x_ppp.h>
#include <net/rtl/rtl865x_netif.h>
#include "common/rtl_errno.h"
//#include "rtl_utils.h"
#include "common/rtl865x_netif_local.h"
#include "rtl865x_ppp_local.h"
#include "rtl8198c_routeIpv6.h"
//#include "rtl865x_ip.h"
#include "rtl8198c_nexthopIpv6.h"
#include "rtl8198c_arpIpv6.h"
    
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
#include <net/ipv6.h>
#include <linux/in6.h>
#include <net/addrconf.h>
    
#if defined(CONFIG_RTL_HARDWARE_IPV6_SUPPORT)
static rtl8198c_ipv6_route_t
    rtl8198c_ipv6_route_inused_back[IPV6_RT_DRV_ENTRY_NUM];

#endif /* 



#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
extern ipaddr_t br_ip_addr;




#endif /* 
#endif /* 

{
	
	
	
		
		
		     && (rt->asicIdx == (IPV6_RT_ASIC_ENTRY_NUM - 1)))
			
		
		
	



							     int fc_len) 
{
	
	
	
		
		
		     &&
		     (ipv6_prefix_equal
		      ((struct in6_addr *)(&rt->ipAddr),
		       (struct in6_addr *)(&ipAddr), rt->fc_dst_len)))
			
		
		
	



//get globle route count by interface name.
//For pppoe, only one globle route should be added to hw route table, and add more will fail
static int32 _rtl8198c_getIpv6GloRouteCountByIfname(char *ifname, int fc_len) 
{
	
	
	
		return 0;
	
	
	    //printk("%s:%d ifName=%s count=%d\n",__FUNCTION__,__LINE__,ifname,count);
	    
		
		
		     &&(fc_len == 0 || rt->fc_dst_len == fc_len) 
		     &&((rt->ipAddr.v6_addr32[0] >> 16) != 0xfe80
			&& (rt->ipAddr.v6_addr32[0] >> 16) !=
			0x0) 
				  && (strcmp(rt->dstNetif->name, ifname) ==
				      0)) 
			
		
		
	
	    //printk("%s:%d ifName=%s count=%d\n",__FUNCTION__,__LINE__,ifname,count);
	    return count;



{
	
	
	
	
	
	
	
	
		
			__LINE__);
		
	
	
	    /*common information */ 
	    
	
	
	    /*if the dstNetif is attach on another interface, the netifIdx should the master interface's index */ 
	    if (rt_t->dstNetif->is_slave == 1) {
		
		    //printk("========%s(%d), ip(0x%x),mask(0x%x),netif(%s)\n",__FUNCTION__,__LINE__,rt_t->ipAddr,rt_t->ipMask,rt_t->dstNetif->name);
		    dstNetif = _rtl865x_getNetifByName(rt_t->dstNetif->name);
		
			
	
		
	
	
		
		
	
	
	
	
		
	
		
		
		
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
		
			
		
		    /*update mac/fdb table reference count */ 
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
		
			
		
		    /*update mac/fdb table reference count */ 
		    asic_t.nextHopRow =
		    rtl8651_filterDbIndex(rt_t->un.direct.macInfo, fid);
		
		
	
		
		
	
	
		
		    /*do nothing */ 
		    break;
	
		
		
		    rt_t->un.nxthop.nxtHopEnd - rt_t->un.nxthop.nxtHopSta + 1;
		
		
		
	
		
			rt_t->process);
		
	
		
		
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	    asic_t.six_rd_eg = rt_t->sixRd_eg;
	
	
#endif /* 
#endif /* 
	    
	



						 int32 action) 
{
	
	
	
	
	
	
		
	
	    /*delete nexthop which is add by default route */ 
	    if (rt->process == IPV6_RT_NEXTHOP) {
		
		      i <= entry->un.nxthop.nxtHopEnd
		      && entry->un.nxthop.nxtHopEnd != 0; i++)
			
			
			
	
	
	
	
		
	
		
		
		    rtl8198c_addIpv6NxtHop(IPV6_NEXTHOP_L3, (void *)entry,
					   entry->dstNetif, tmp_nexthop);
		
	
		
			
			
				
			
				
				    rtl8198c_addIpv6NxtHop(IPV6_NEXTHOP_L3,
							   (void *)rt,
							   rt->dstNetif,
							   rt->nextHop);
				
			
				
					
					
						sizeof(inv6_addr_t));
					
					    rtl865x_getPppByNetifName
					    (rt->dstNetif->name);
					
						
						    /*got pppoe session */ 
						    tmp_nexthop.v6_addr32[0] =
						    pppoe->sessionId;
						
						    rtl8198c_addIpv6NxtHop
						    (IPV6_NEXTHOP_L3,
						     (void *)rt, rt->dstNetif,
						     tmp_nexthop);
					
						
						    /*nexthop's action is to CPU */ 
						    retval =
						    rtl8198c_addIpv6NxtHop
						    (IPV6_NEXTHOP_L3,
						     (void *)rt, rt->dstNetif,
						     tmp_nexthop);
				
				
		
		
		
	
	



					   int32 start_idx) 
{
	
	
	
	
	
		
		
			
			    /*if the rule is default route... */ 
			    if (rt->fc_dst_len == 0) {
				
			
				
				    /* entry number more than asic table's capacity */ 
				    /* entry index=RT_ASIC_ENTRY_NUM-1 is reserved for default route */ 
				    if ((start_idx + count >
					 IPV6_RT_ASIC_ENTRY_NUM - 2))
					
				
				    /*delete old asic entry firstly... */ 
				    if (start_idx + count < rt->asicIdx
					&& rt->asicIdx <
					IPV6_RT_ASIC_ENTRY_NUM - 1)
					
				
				
				    /*jwj: arp subnetIdx need to keep the same with rt->asicIdx. */ 
				    if (rt->process == IPV6_RT_ARP) {
					
						
						    /*rt->asicIdx change, so its arp->subnetIdx need to change
						       also with the new rt->asicIdx. */ 
						    if (rt->arp.subnetIdx != 0xf)	/*The new add router no need call rtl8198c_changeIpv6ArpSubnetIdx */
							
							    (rt->arp.subnetIdx,
							     rt->asicIdx);
						
						    rt->asicIdx;
					
				
				
			
		
		
		    /*next entry */ 
		    rt = rt->next;
		
		
	
	    /*more route entry need to add? */ 
	    if (rt) {
		
		    /*not enough asic table entry! have to update default route's action TOCPU */ 
		    rt = _rtl8198c_getDefaultIpv6Route();
		
						  IPV6_RT_DEFAULT_RT_NEXTHOP_CPU);
	
		
		
						  IPV6_RT_DEFAULT_RT_NEXTHOP_NORMAL);
	
	



{
	
	
	
	
	
	
	    /*always set 0x0f when init..., this value would be reset in arrange route */ 
	    rt->asicIdx = 0x0f;
	
	
	    /*find the right position... */ 
	    while (entry)
		
		
			
				
			
		
		
		
		
	
	    /*insert this rule after insert_entry */ 
	    if (fore_rt) {
		
		
		
		
	
		
		    /*insert head... */ 
		    rt->next = rtl8198c_ipv6_route_inusedHead;
		
		
		
	
	
	



						     rt) 
{
	
	
	    NULL;
	
	
		
		
			
		
		
		
	
	    /*fore_rt == NULL means delete list head */ 
	    if (fore_rt == NULL) {
		
		    rtl8198c_ipv6_route_inusedHead->next;
		
		
	
		
		
		
	
	
	    /*delete route from asic */ 
	    if (rt->asicIdx < IPV6_RT_ASIC_ENTRY_NUM)
		
	
	
	



{
	
	
	
		
		
			
		
		
	



#if 1
static int32 _rtl8198c_Ipv6ToCpu(rtl8198c_ipv6_route_t * rt,
				 rtl865x_netif_local_t * netif) 
{
	
	
	
	    /*link local ipv6 route entry always to cpu */ 
	    rt->process = IPV6_RT_NEXTHOP;
	
	
	
	    rtl8198c_addIpv6NxtHop(IPV6_NEXTHOP_L3, (void *)rt, netif,
				   tmp_nexthop);
	
		
	
	
	    /*update reference.... */ 
	    rtl865x_referNetif(netif->name);
	
	
	
	
		
	
	



#endif /* 
    
#if 0
static void print_ipv6_addr(void *addr, int prefix, const char *function,
			    int line) 
{
	
	
		
		ipAddr.v6_addr32[3], prefix);
	



#endif /* 
static void htonl_array_hwv6(u32 * org_buf, u32 * dst_buf, unsigned int words) 
{
	
	
		
	
		
		
	
	



							    int fc_dst_len,
							    inv6_addr_t nextHop,
							    rtl865x_netif_local_t
							    * netif) 
{
	
	
	    /*allocate a new buffer for adding entry */ 
	    rt = rtl8198c_ipv6_route_freeHead;
	
		
	
		
	
	
	    /*common information */ 
	    ipv6_addr_prefix((struct in6_addr *)(&rt->ipAddr),
			     (struct in6_addr *)(&ipAddr), fc_dst_len);
	
	
	
	



				     inv6_addr_t nextHop, int8 * ifName) 
{
	
	
	
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	    int32 sixrdIndex = FAILED;
	
#endif /* 
#endif /* 
	    
	    /*para check */ 
	    if (ifName == NULL)
		
	
	else
		
	
		
	
		
	
#if 0
	    printk
	    ("%s.%d.ipAddr(0x%8x%8x%8x%8x),fc_dst_len(%d)nextHop(0x%8x%8x%8x%8x),ifName(%s)\n",
	     
	     ipAddr.v6_addr32[2], ipAddr.v6_addr32[3], 
	     
	     nextHop.v6_addr32[3], 
	
#endif /* 
	    /*
	     *duplicate entry check:
	     *      in Driver system, default route is always exist.
	     *      so if ipMask == 0, it's means that default route should be update...
	     */ 
	    if (fc_dst_len != 0
		&& (rt =
		    _rtl8198c_getIpv6RouteEntry(ipAddr, fc_dst_len)) != NULL) {
		
		    //rt->ref_count++;
		    return RTL_EENTRYALREADYEXIST;
	
	
	    /*add default route: just update the default route becase the default route always exist! */ 
#ifdef CONFIG_RTL_IPV6READYLOGO
	    if ((fc_dst_len == 0)
		|| !((nextHop.v6_addr32[0] == 0) && (nextHop.v6_addr32[1] == 0)
		     && (nextHop.v6_addr32[2] == 0)
		     && (nextHop.v6_addr32[3] == 0)))
		
#else /* 
	    if (fc_dst_len == 0)
		
#endif /* 
	{
		
		
		    /*deference rt's orginal netif */ 
		    if (rt && rt->dstNetif)
			
	
	
	    /*allocate a new buffer for adding entry */ 
	    if (rt == NULL) {
		
		    _rtl8198c_getNewRouteEntry(ipAddr, fc_dst_len, nextHop,
					       netif);
	
	
		
		    /*no buffer, default route should be TOCPU? */ 
		    return RTL_ENOFREEBUFFER;
	
	
#if 1
	    if ((ipAddr.v6_addr32[0] >> 16) == 0xFE80)
		
		
		    //      printk("%s:%d ifName=%s ipAddr.v6_addr16[0]=%x\n",__FUNCTION__,__LINE__,ifName,(ipAddr.v6_addr32[0]>>16));
		    
		
			
		
		
		
	
	    //when pppoe add its ipv6 route to cpu
	    
		 && ((ipAddr.v6_addr32[0] >> 16) != 0x0 && (ipAddr.v6_addr32[0] >> 16) != 0xFE80))	//global ip
	{
		
		
		
		
		
		
		
		    //printk("%s:%d ifName=%s\n",__FUNCTION__,__LINE__,ifName);
		    
			
				
						    addr.s6_addr32[0],
						    (u32 *) &
						    ifaAddr.s6_addr32[0], 4);
				
				    //print_ipv6_addr(&ifaAddr,ifa->prefix_len,__FUNCTION__,__LINE__);
				    if (ipv6_prefix_equal
					(&ifaAddr,
					 (struct in6_addr *)&rt->ipAddr,
					 rt->fc_dst_len)) {
					
					    NULL;
					
					    _rtl8198c_getNewRouteEntry(*
								       ((inv6_addr_t *) (&ifaAddr)), 128, nextHop, netif);
					
						
						    /*no buffer, default route should be TOCPU? */ 
						    return RTL_ENOFREEBUFFER;
					
					
					    //print_ipv6_addr(&rt_pppGlo->ipAddr,rt_pppGlo->fc_dst_len,__FUNCTION__,__LINE__);
					    
					    (_rtl8198c_getIpv6GloRouteCountByIfname
					     (ifName, 128) != 0) {
						
					
					
					    //printk("%s:%d ifName=%s\n",__FUNCTION__,__LINE__,ifName);
					    
					    _rtl8198c_Ipv6ToCpu(rt_pppGlo,
								netif);
					
						
					
				
				
				    //printk("%s:%d ifName=%s\n",__FUNCTION__,__LINE__,ifName);
			}
			
			    //printk("%s:%d ifName=%s\n",__FUNCTION__,__LINE__,ifName);
		}
	
	
#endif /* 
	    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
	    if (((ipAddr.v6_addr32[0] == 0) && (ipAddr.v6_addr32[1] == 0) && 
		 (ipAddr.v6_addr32[2] == 0) && (ipAddr.v6_addr32[3] == 0)) 
		&&
		((nextHop.v6_addr32[0] != 0) || (nextHop.v6_addr32[1] != 0) || 
		 (nextHop.v6_addr32[2] != 0) || (nextHop.v6_addr32[3] != 0)) 
		
		
		
		
	
#endif /* 
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	    if (netif->if_type == IF_6RD)
		
		
		      && 
		      && (ipAddr.v6_addr32[3] ==
			  0)) 
				    && (nextHop.v6_addr32[1] == 0)
				    && 
				    && (nextHop.v6_addr32[3] != 0)) 
			
			
			
			
		
	
#endif /* 
#endif /* 
	    
	    /*don't specify the nexthop ip address, it's means that:
	     * all packet match this route entry should be forward by network interface with arp
	     */ 
	    
		  && (nextHop.v6_addr32[2] == 0) && (nextHop.v6_addr32[3] == 0))
		 && (fc_dst_len != 0)) {
		
			
		
			
			    //printk("%s,%d.add arp info to asic ...........\n",__FUNCTION__,__LINE__);
			    rt->process = IPV6_RT_ARP;
			
			    /*rt->arp.subnetIdx will be updated as rt->asicIdx later in _rtl865x_arrangeRoute */ 
			    break;
		
			
				
				
				
				
					
					    ("Ipv6 error!!can't get pppoe session information by interface name(%s)\n",
					     netif->name);
					
				
				
				
				
				    /*update reference... */ 
				    rtl865x_referPpp(ppp->sessionId);
			
			
		
		
			
				
				
				
				
					
					    /*printk("Warning!!CAn't get pptp/l2tp session information by interface name(%s)\n",netif->name); */ 
					    goto addFailed;
				
				
			
			
			
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
		case IF_6RD:
			
			    //do nothing
			    return SUCCESS;
			
#endif /* 
#endif /* 
		default:
			
				netif->if_type);
			
			
	
	
	else {
		
		    /*if default is valid, delete nexthop firstly... */ 
		    if ((rt->valid == 1) && (rt->process == IPV6_RT_NEXTHOP)) {
			
			
			      i <= rt->un.nxthop.nxtHopEnd; i++)
				
				
				    rtl8198c_delIpv6NxtHop(IPV6_NEXTHOP_L3, i);
				
		
		
#ifdef CONFIG_RTL_IPV6READYLOGO
		    if (strncmp
			(netif->name, RTL_DRV_LAN_NETIF_NAME,
			 sizeof(RTL_DRV_LAN_NETIF_NAME)) == 0)
			
			
			
			
							  IPV6_RT_DEFAULT_RT_NEXTHOP_CPU);
			
		
		else
			
#endif /* 
		{
			
			    /*use nexthop type */ 
			    rt->process = IPV6_RT_NEXTHOP;
			
			    //for restore nexthop table, when hw l3v6 cleared.
			    memcpy(&rt->nextHop, &nextHop, sizeof(inv6_addr_t));
			
				
			
				
				    rtl8198c_addIpv6NxtHop(IPV6_NEXTHOP_L3,
							   (void *)rt, netif,
							   nextHop);
				
			
			
			
				
					
					
						sizeof(inv6_addr_t));
					
					    rtl865x_getPppByNetifName
					    (netif->name);
					
						
						    /*got pppoe session */ 
						    tmp_nexthop.v6_addr32[0] =
						    pppoe->sessionId;
						
						    rtl8198c_addIpv6NxtHop
						    (IPV6_NEXTHOP_L3,
						     (void *)rt, netif,
						     tmp_nexthop);
					
					
					else {
						
						    /*nexthop's action is to CPU */ 
						    retval =
						    rtl8198c_addIpv6NxtHop
						    (IPV6_NEXTHOP_L3,
						     (void *)rt, netif,
						     tmp_nexthop);
				
				
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
			case IF_6RD:
				
				    rtl8198c_addIpv6NxtHop(IPV6_NEXTHOP_L3,
							   (void *)rt, netif,
							   nextHop);
				
				
#endif /* 
#endif /* 
			
				
				
				
			
				
				    ("error!!add ipv6 nexthop error! retval (%d)\n",
				     retval);
				
			
			
		
	
	
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_6RD_SUPPORT)
	    if (netif->if_type == IF_6RD)
		
		
		
		    /*hook default gw for 6rd interface */ 
		    if (((ipAddr.v6_addr32[0] == 0)
			 && (ipAddr.v6_addr32[1] == 0)
			 && 
			 && (ipAddr.v6_addr32[3] == 0)) 
			&& 
			     && (nextHop.v6_addr32[1] == 0)
			     && 
			     && (nextHop.v6_addr32[3] != 0)))
			
			
				
				
				
				
			
			else
				
				
				
				
			
		
	
#endif /* 
#endif /* 
	    
	    /*update reference.... */ 
	    rtl865x_referNetif(netif->name);
	
		
	
		
	
	
	else {
		
		    /*insert the adding route to inused list */ 
		    retval = _rtl8198c_addIpv6RouteToInusedList(rt);
	
	
	    /*if route is add, please enable Routing for the releated netif */ 
	    retval = rtl865x_enableNetifRoutingV6(netif);
	

		
#ifdef CONFIG_RTL_IPV6READYLOGO
		    rt->process = IPV6_RT_NEXTHOP;
		
#endif /* 
		    _rtl8198c_updateDefaultIpv6Route(rt,
						     IPV6_RT_DEFAULT_RT_NEXTHOP_CPU);
	
	
	else {
		
		    /*free this route entry and return error code... */ 
		    memset(rt, 0, sizeof(rtl8198c_ipv6_route_t));
		
		
		
	
	



{
	
	
	
	
	
		
	
		
		    /*if default route
		     * 1. reset default route
		     * 2. reset entry->netif...
		     */ 
		    rtl865x_netif_local_t * netif = NULL;
		
		
		
			
		
		
			
			
			
		
		
		    _rtl8198c_updateDefaultIpv6Route(entry,
						     IPV6_RT_DEFAULT_RT_NEXTHOP_CPU);
	
		
		    /*not default route */ 
		    switch (entry->process)
			
		
			
				
				
					
			
			
		
			
			    /*
			     * NOTE:this type not used now...
			     * if we want to use it, please DELETE FDB entry to sure this L2 entry is deleted both software FDB table and Asic L2 table.
			     */ 
			    break;
		
			
			    /*free arp */ 
			    retval =
			    rtl8198c_delIpv6ArpBySubnetIdx(entry->
							   arp.subnetIdx);
			
				
				    ("======Ipv6 error!!can't FREE arp entry for this route entry....retval(%d)\n",
				     retval);
			
			
		
		
			
			    /*do nothing */ 
			    
		
			
			    /*delete nexthop which is add by l3 */ 
			    for (i = entry->un.nxthop.nxtHopSta;
				 i <= entry->un.nxthop.nxtHopEnd; i++)
				
				
				    rtl8198c_delIpv6NxtHop(IPV6_NEXTHOP_L3, i);
				
			
			
		
		    /*update netif reference count */ 
		    rtl865x_deReferNetif(entry->dstNetif->name);
		
		    /*remove from inused list... */ 
		    _rtl8198c_delIpv6RouteFromInusedList(entry);
		
		       FAILED)
			
		
		    /*add to free list */ 
		    memset(entry, 0, sizeof(rtl8198c_ipv6_route_t));
		
		
		
		
	
	



{
	
	
	
	
	
		
		
		     &&
		     (ipv6_prefix_equal
		      ((struct in6_addr *)(&rt->ipAddr),
		       (struct in6_addr *)(&dst), rt->fc_dst_len))
		     && fc_len <= rt->fc_dst_len) {
			
			
		
		
		



/*
@func int32 | rtl8198c_addIpv6Route |add a route entry.
@parm inv6_addr_t | ipAddr | ip address.
@parm int | fc_dst_len | ip prefix len.
@parm inv6_addr_t | nextHop | the route's next hop.
@parm int8* | ifName | destination network interface. 
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@rvalue RTL_EINVALIDINPUT | invalid input.
@rvalue RTL_ENOLLTYPESPECIFY | network interface's link type is not specified.
@rvalue RTL_EENTRYALREADYEXIST | route entry is already exist.
@rvalue RTL_ENOFREEBUFFER | not enough memory in system.
@comm
	if ifName=NULL, it means the destionation network interface of route entry with ip/ipMask/nextHop is default wan.
*/ 
    int32 rtl8198c_addIpv6Route(inv6_addr_t ipAddr, int fc_dst_len,
				inv6_addr_t nextHop, int8 * ifName)
{
	
	
	
	    //printk("========%s(%d), ip(0x%x%x%x%x),fc_dst_len(%d),ifname(%s),nxthop(0x%x)\n",__FUNCTION__,__LINE__,
	    //ipAddr.s6_addr32[0], ipAddr.s6_addr32[1],ipAddr.s6_addr32[2],ipAddr.s6_addr32[3],fc_dst_len,ifName,nextHop);
	    SMP_LOCK_ETH(flags);
	
	
	
	    //printk("========%s(%d), ip(0x%x%x%x%x),fc_dst_len(%d),ifname(%s),nxthop(0x%x),retval(%d)\n",__FUNCTION__,__LINE__,
	    //ipAddr.s6_addr32[0], ipAddr.s6_addr32[1],ipAddr.s6_addr32[2],ipAddr.s6_addr32[3],,fc_dst_len,ifName,nextHop,retval);
	    return retval;



/*
@func int32 | rtl8198c_delIpv6Route |delete a route entry.
@parm inv6_addr_t | ipAddr | ipAddress.
@parm int | fc_dst_len | ip prefix len.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@rvalue RTL_EENTRYNOTFOUND | not found the entry.
@comm	
*/ 
    int32 rtl8198c_delIpv6Route(inv6_addr_t ipAddr, int fc_dst_len)
{
	
	
	
	    //printk("========%s(%d), ip(0x%x%x%x%x),fc_dst_len(%d)\n",__FUNCTION__,__LINE__,ipAddr.s6_addr32[0],
	    //ipAddr.s6_addr32[1],ipAddr.s6_addr32[2],ipAddr.s6_addr32[3],fc_dst_len);
	    SMP_LOCK_ETH(flags);
	
	
	
	    //printk("==================================retval(%d)\n",retval);
	    return retval;



/*
@func int32 | rtl8198c_getIpv6RouteEntryByIp |according the destination ip address, get the matched route entry.
@parm inv6_addr_t | dst | destionation ip address.
@parm rtl8198c_ipv6_route_t* | rt | retrun value: route entry pointer
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_getIpv6RouteEntryByIp(inv6_addr_t dst,
					 rtl8198c_ipv6_route_t * rt) 
{
	
	
	
	
		
		
	
	



/*
@func int32 | rtl198c_initIpv6RouteTable |initialize route tabel.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_initIpv6RouteTable(void)
{
	
	
	
	
	
	    /*malloc buffer */ 
	    TBL_MEM_ALLOC(rt, rtl8198c_ipv6_route_t, IPV6_RT_DRV_ENTRY_NUM);
	
	
		
		
		
		
		
	
#if defined(CONFIG_RTL_HARDWARE_IPV6_SUPPORT)
	    memset((void *)&rtl8198c_ipv6_route_inused_back, 0,
		   sizeof(rtl8198c_ipv6_route_inused_back));
	
#endif /* 
	    



/*
@func int32 | rtl198c_reinitIpv6RouteTable |reinitialize route tabel.
@rvalue SUCCESS | success.
@rvalue FAILED | failed.
@comm	
*/ 
    int32 rtl8198c_reinitIpv6RouteTable(void)
{
	
	
	
		
		
		
		
	
	    /*delete the last route */ 
	    rt = rtl8198c_ipv6_route_inusedHead;
	
		
		
		    /*update netif reference count */ 
		    rtl865x_deReferNetif(rt->dstNetif->name);
		
		    /*remove from inused list... */ 
		    _rtl8198c_delIpv6RouteFromInusedList(rt);
		
		    /*add to free list */ 
		    memset(rt, 0, sizeof(rtl8198c_ipv6_route_t));
		
		
		
		
	



#if defined(CONFIG_RTL_HARDWARE_IPV6_SUPPORT)
int rtl819x_save_inused_ipv6_route(void) 
{
	
	
	
		  sizeof(rtl8198c_ipv6_route_t) * IPV6_RT_DRV_ENTRY_NUM);
	
		
		
			
				sizeof(rtl8198c_ipv6_route_t));
			
			
				
		
		
		
	



{
	
	
	
	
		
		
			
			
			    rtl8198c_addIpv6Route(rt->ipAddr, rt->fc_dst_len,
						  rt->nextHop,
						  rt->dstNetif->name);
			
#if 0
			    panic_printk
			    ("%s %d ret=%d ip=0x%x:%x:%x:%x rt->fc_dst_len=%d nexthop=0x%x:%x:%x:%x rt->dstNetif->name=%s \n",
			     __FUNCTION__, __LINE__, ret,
			     rt->ipAddr.v6_addr32[0], 
			     rt->ipAddr.v6_addr32[2], rt->ipAddr.v6_addr32[3],
			     rt->fc_dst_len, 
			     rt->nextHop.v6_addr32[1], rt->nextHop.v6_addr32[2],
			     rt->nextHop.v6_addr32[3], rt->dstNetif->name);
			
#endif /* 
		}
		
	



#endif /* 
    