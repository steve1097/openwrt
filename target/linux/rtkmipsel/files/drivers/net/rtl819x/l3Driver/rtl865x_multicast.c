/*
 *
 *  Copyright (c) 2011 Realtek Semiconductor Corp.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License version 2 as
 *  published by the Free Software Foundation.
 */  
    
#ifdef __linux__
#include <linux/version.h>
    
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
#include <linux/kconfig.h>
#else /* 
#include <linux/config.h>
#endif /* 
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/proc_fs.h>
#endif /* 
    
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
//#include "common/rtl_utils.h"
//#include "common/assert.h"
    
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include "AsicDriver/rtl865x_asicCom.h"
#include "AsicDriver/rtl865x_asicL3.h"
#else /* 
#include "AsicDriver/rtl865xC_tblAsicDrv.h" 
#include "common/rtl865x_tblDrvPatch.h"
#endif /* 
    
#include "AsicDriver/asicRegs.h"
#include "AsicDriver/asicTabs.h"
    
#include "common/rtl8651_tblDrvProto.h"
    
#include "common/rtl865x_eventMgr.h"
#include "common/rtl865x_vlan.h"
#include <net/rtl/rtl865x_netif.h>
    
#include "l3Driver/rtl865x_ip.h"
    
#ifdef RTL865X_TEST
#include <string.h>
#endif /* 
    
#include <net/rtl/rtl865x_multicast.h>
#include <net/rtl/rtl865x_igmpsnooping.h>
    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
    int32 rtl8198C_initMulticastv6(void);


#endif /* 
/********************************************************/ 
/*			Multicast Related Global Variable			*/ 
/********************************************************/ 





#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
static rtl8198c_mcast_fwd_descriptor6_t *rtl8198c_mcastFwdDescPool6 = NULL;




#endif /* 
#if defined(__linux__) && defined(__KERNEL__)
static struct timer_list rtl865x_mCastSysTimer;	/*igmp timer */

#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
static struct timer_list rtl8198c_mCast6SysTimer;	/*MLD timer */

#endif /* 
#endif /* 
    
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
extern int hwwifiEnable;

#endif /* 
    
#if defined (CONFIG_RT_MULTIPLE_BR_SUPPORT)
extern int rtl_get_brIgmpModuleIndexbyName(char *name, int *index);


#endif /* 

{
	
	
	
			 rtl865x_mcast_fwd_descriptor_t,
			 MAX_MCAST_FWD_DESCRIPTOR_CNT);
	
		
		
			MAX_MCAST_FWD_DESCRIPTOR_CNT *
			sizeof(rtl865x_mcast_fwd_descriptor_t));
		
	
	else
		
		
		
	
		
		
				     &rtl865x_mcastFwdDescPool[i], next);
		
	



{
	
	
	
		
		
		
		
	



					  descPtr) 
{
	
		
		
		
	
	
	



						descChainHead) 
{
	
	
		
		
		
	
	
		
		
		
		    /*remove from the old descriptor chain */ 
		    MC_LIST_REMOVE(curDesc, next);
		
		    /*return to the free descriptor chain */ 
		    _rtl865x_freeMCastFwdDesc(curDesc);
		
		
	



						 queueHead,
						 
						 rtl865x_mcast_fwd_descriptor_t
						 * enqueueDesc) 
{
	
	
	
		
		
		
	
		
		
		
	
	    /*multicast forward descriptor is internal maintained,always alloc new one */ 
	    newDesc = _rtl865x_allocMCastFwdDesc();
	
		
		
			sizeof(rtl865x_mcast_fwd_descriptor_t));
		
		    //memset(&(newDesc->next), 0, sizeof(MC_LIST_ENTRY(rtl865x_mcast_fwd_descriptor_s)));
		    newDesc->next.le_next = NULL;
		
		
	
	else
		
		
		    /*no enough memory */ 
		    return FAILED;
		
	
		  curDesc = nextDesc)
		
		
		
		    /*merge two descriptor */ 
		    //      if((strcmp(curDesc->netifName,newDesc->netifName)==0) && (curDesc->vid==newDesc->vid))
		    if (strcmp(curDesc->netifName, newDesc->netifName) == 0)
			
			
				
				
				
			
			
			
		
	
	    /*not matched descriptor is found */ 
	    MC_LIST_INSERT_HEAD(queueHead, newDesc, next);
	



						  targetChainHead,
						  
						  rtl865x_mcast_fwd_descriptor_t
						  * srcChain) 
{
	
	
		
		
		
	
		curDesc = MC_LIST_NEXT(curDesc, next))
		
		
		
	



{
	
	
	
			 MAX_MCAST_TABLE_ENTRY_CNT);
	
	
		
		
		
				   &multiCast_t[index], nextMCast);
		
	
			 RTL8651_MULTICASTTBL_SIZE);
	
		RTL8651_MULTICASTTBL_SIZE * sizeof(rtl865x_tblDrv_mCast_t));
	
	
		
		
		
	



{
	
	
	
		
		
		
	
	
	    /*initialize it */ 
	    if (MC_LIST_FIRST(&newEntry->fwdDescChain) != NULL)
		
		
		
	
	
	
			     nextMCast);
	



{
	
		
		
		
	
	
	



					uint32 hashIndex) 
{
	
		
		
		
	
			nextMCast);
	
	
			   nextMCast);
	



							  * mCastEntry) 
{
	
	
		
		
		
	
		curDesc != NULL; curDesc = nextDesc)
		
		
		
			
			    curDesc->fwdPortMask & (~(1 << mCastEntry->port));
			
				
				
				    /*remove from the old chain */ 
				    MC_LIST_REMOVE(curDesc, next);
				
				    /*return to the free descriptor chain */ 
				    _rtl865x_freeMCastFwdDesc(curDesc);
				
		
		
	



#if defined(CONFIG_RTL_MULTI_LAN_DEV) && defined(CONFIG_RTL_HW_MCAST_WIFI)
static uint32
rtl865x_genMCastEntryAsicFwdMaskIgnoreCpuFlag(rtl865x_tblDrv_mCast_t *
					      mCastEntry) 
{
	
	
	
		
		
		
	
		
	
	
	



#endif /* 

						  mCastEntry) 
{
	
	
	
		
		
		
	
		
			
			
			    (curDesc->fwdPortMask &
			     ((1 << RTL8651_MAC_NUMBER) - 1));
			
		
		else
			
			
			
	
	
	



					      mCastEntry) 
{
	
	
	
		
		
		
	
		
		
		
	
		
		     (memcmp(curDesc->netifName, RTL_WLAN_NAME, 4) == 0))
			
			
			
	
	



#if defined (CONFIG_RTL_IGMP_SNOOPING)
/*for linux bridge level igmp snooping usage*/ 
#if !defined(CONFIG_RTL_MULTI_LAN_DEV)
static uint32 rtl865x_getMCastEntryDescPortMask(rtl865x_tblDrv_mCast_t *
						mCastEntry) 
{
	
	
	
		
		
		
	
		
	
	



#endif /* 
#endif /* 
/*=======================================
  * Multicast Table APIs
  *=======================================*/ 
#define RTL865X_MULTICASE_TABLE_APIs

{
	
	
		index < RTL8651_PORT_NUMBER + rtl8651_totalExtPortNum;
		index++) {
		
						      (rtl865x_externalMulticastPortMask
						       & (1 << index)) ? FALSE :
						      TRUE);
	



{
	
	


/*
@func int32	| rtl865x_addMulticastExternalPort	| API to add a hardware multicast external port.
@parm  uint32 | extPort	| External port number to be added. 
@rvalue SUCCESS	|Add hardware multicast external port successfully.
@rvalue FAILED	|Add hardware multicast external port failed.
*/ 
    int32 rtl865x_addMulticastExternalPort(uint32 extPort) 
{
	
	
	



/*
@func int32	| rtl865x_delMulticastExternalPort	| API to delete a hardware multicast external port.
@parm  uint32 | extPort	| External port number to be deleted.
@rvalue SUCCESS	|Delete external port successfully.
@rvalue FAILED	|Delete external port failed.
*/ 
    int32 rtl865x_delMulticastExternalPort(uint32 extPort) 
{
	
	
	



/*
@func int32	| rtl865x_setMulticastExternalPortMask	| API to set hardware multicast external port mask.
@parm  uint32 | extPortMask	| External port mask to be set.
@rvalue SUCCESS	|Set external port mask successfully.
@rvalue FAILED	|Set external port mask failed.
*/ 
    int32 rtl865x_setMulticastExternalPortMask(uint32 extPortMask) 
{
	
	
	



/*
@func int32	| rtl865x_addMulticastExternalPortMask	| API to add hardware multicast external port mask.
@parm  uint32 | extPortMask	| External port mask to be added.
@rvalue SUCCESS	|Add external port mask successfully.
@rvalue FAILED	|Add external port mask failed.
*/ 
    int32 rtl865x_addMulticastExternalPortMask(uint32 extPortMask) 
{
	
	
	



/*
@func int32	| rtl865x_delMulticastExternalPortMask	|  API to delete hardware multicast external port mask.
@parm  uint32 | extPortMask	| External port mask to be deleted.
@rvalue SUCCESS	|Delete external port mask successfully.
@rvalue FAILED	|Delete external port mask failed.
*/ 
    int32 rtl865x_delMulticastExternalPortMask(uint32 extPortMask) 
{
	
	
	



{
	



					      mCast_t) 
{
	
	
	
	    /* patch: keep cache in software if one vlan's interface is pppoe */ 
	    MC_LIST_FOREACH(curDesc, &(mCast_t->fwdDescChain), next) 
		
		     SUCCESS)
			
			
			    /*how about pptp,l2tp? */ 
			    if (netifType == IF_PPPOE)
				
				
				    RTL865X_MULTICAST_PPPOEPATCH_CPUBIT;
				
				
			
	
	



#if 0
static int _rtl865x_checkMulticastEntryEqual(rtl865x_tblDrv_mCast_t *
					     mCastEntry1,
					     rtl865x_tblDrv_mCast_t *
					     mCastEntry2) 
{
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	
		
		
		
	



#endif /* 
#ifdef CONFIG_PROC_FS
static unsigned int mcastAddOpCnt = 0;

#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
static unsigned int mcastAddOpCnt6 = 0;

#endif /* 
unsigned int _rtl865x_getAddMcastOpCnt(void) 
{
	



#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
unsigned int _rtl8198C_getAddMcastv6OpCnt(void) 
{
	



#endif /* 


#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
static unsigned int mcastDelOpCnt6 = 0;

#endif /* 
unsigned int _rtl865x_getDelMcastOpCnt(void) 
{
	



#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
unsigned int _rtl8198C_getDelMcastv6OpCnt(void) 
{
	



#endif /* 
#endif /* 
/* re-select Multicast entry to ASIC for the index ""entryIndex */ 
static void _rtl865x_arrangeMulticast(uint32 entryIndex) 
{
	
	
	
	
	
	
			 nextMCast) 
		
#ifdef CONFIG_RTL_HW_MCAST_WIFI
		    if (((hwwifiEnable)
			 || ((hwwifiEnable == 0)
			     && (mCast_t->cpu ==
				 0))) 
					    RTL865X_MULTICAST_PPPOEPATCH_CPUBIT))
			
#else /* 
		    if ((mCast_t->cpu == 0)
			&& !(mCast_t->flag &
			     RTL865X_MULTICAST_PPPOEPATCH_CPUBIT))
			
#endif /* 
		{		/* Ignore cpu=1 */
			
				
				
					
					
					
				
				else
					
					
					    /*impossible, two flow in one asic entry */ 
					    swapOutEntry->inAsic = FALSE;
					
					
				
			
				
				
					 && (select_t->unKnownMCast == TRUE))
					
					
					    /*replace unknown multicast */ 
					    select_t = mCast_t;
					
				
				else
					
					
					    /*select the heavy load */ 
					    if ((mCast_t->count) >
						(select_t->count))
						
						
						
					
				
			
			else
				
				
				
		
		
		else
			
			
			
	
	
		
		
		     && (select_t->unKnownMCast == TRUE))
			
			
			    /*replace unknown multicast */ 
			    select_t = swapOutEntry;
			
		
		else
			
			
			      (swapOutEntry->count +
			       RTL865X_HW_MCAST_SWAP_GAP)))
				
			
		
	
	    /*
	       if(swapOutEntry)
	       {
	       printk("%s:%d,swapOutEntry->count:%d,swapOutEntry->dip is 0x%x,swapOutEntry->mbr is 0x%x\n",__FUNCTION__,__LINE__,swapOutEntry->count,swapOutEntry->dip,swapOutEntry->mbr);
	       
	       }
	       
	       if (select_t) 
	       {
	       printk("%s:%d,select_t->count:%d,select_t->dip is 0x%x,select_t->mbr is 0x%x\n",__FUNCTION__,__LINE__,select_t->count,select_t->dip,select_t->mbr);
	       }
	     */ 
	    if (select_t)
		
		
			
			
			
			       sizeof(rtl865x_tblAsicDrv_multiCastParam_t));
			
				(uint32) &
				(((rtl865x_tblDrv_mCast_t *) 0)->extIp));
			
				
				
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3
				    int32 ipIdx;
				
				     (select_t->extIp, &ipIdx) == SUCCESS)
					
					
					
				
#else /* 
				    asic_mcast.extIdx = 0;
				
#endif /* 
				
			
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
			    asic_mcast.idx = (uint16) entryIndex;
			
#endif /* 
			    retval =
			    rtl8651_setAsicIpMulticastTable(&asic_mcast);
			
#ifdef CONFIG_PROC_FS
			    mcastAddOpCnt++;
			
#endif /* 
			    assert(retval == SUCCESS);
			
				
				
				
			
			else
				
				
				
				
#ifdef CONFIG_PROC_FS
				    mcastDelOpCnt++;
				
#endif /* 
				}
			
			
				      select_t, nextMCast);
			
					   inuseList.mCastTbl[entryIndex],
					   select_t, nextMCast);
			
		
		else		/*(swapOutEntry!=NULL) && (select_t!=swapOutEntry) */
			
			
			    /*disable swap and only explicit joined mulicast flow can replace unknown multicast flow */ 
			    if (1)
				
				
				    /*don't forget to set swapOutEntry's inAsic flag */ 
				    swapOutEntry->inAsic = FALSE;
				
				    RTL865X_MULTICAST_TABLE_ASIC_AGE;
				
				       sizeof
				       (rtl865x_tblAsicDrv_multiCastParam_t));
				
					(uint32) &
					(((rtl865x_tblDrv_mCast_t *)
					  0)->extIp));
				
					
					
#ifdef CONFIG_RTL_LAYERED_DRIVER_L3		
					    int32 ipIdx;
					
					     (select_t->extIp,
					      &ipIdx) == SUCCESS)
						
						
						    (uint16) ipIdx;
						
					
#else /* 
					    asic_mcast.extIdx = 0;
					
#endif /* 
					}
				
				    rtl8651_setAsicIpMulticastTable
				    (&asic_mcast);
				
#ifdef CONFIG_PROC_FS
				    mcastAddOpCnt++;
				
#endif /* 
				    assert(retval == SUCCESS);
				
					
					
					
				
				else
					
					
					
					    (entryIndex);
					
#ifdef CONFIG_PROC_FS
					    mcastDelOpCnt++;
					
#endif /* 
					}
				
						inuseList.mCastTbl[entryIndex],
						select_t, nextMCast);
				
						   inuseList.mCastTbl
						   [entryIndex], select_t,
						   nextMCast);
				
			
#if 0
			    else
				
				
					
					
					    /*maybe something is wrong, we remove the asic entry */ 
					    rtl8651_delAsicIpMulticastTable
					    (entryIndex);
					
#ifdef CONFIG_PROC_FS
					    mcastDelOpCnt++;
					
#endif /* 
					}
				
			
#endif /* 
			
		
	
	else
		
		
			
			
			
		
		
#ifdef CONFIG_PROC_FS
		    mcastDelOpCnt++;
		
#endif /* 
		}



{
	
	
	
	
	
	
	    /*free unused software forward entry */ 
	    for (index = 0; index < RTL8651_MULTICASTTBL_SIZE; index++)
		
		
		    TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
		
			
			
			
			     && (curMCastEntry->count == 0))
				
				
				
				
			
			
		
	
		
		
		
	
		
		
		    TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
		
		
			
			
			
				
				
				    rtl865x_genMCastEntryAsicFwdMask
				    (curMCastEntry);
				
					
					
								 index);
					
					
				
			
			
		
			
			
			
		
	



/*
@func rtl865x_tblDrv_mCast_t *	| rtl865x_findMCastEntry	|  API to find a hardware multicast entry.
@parm  ipaddr_t 	| mAddr	| Multicast stream destination group address. 
@parm  ipaddr_t	|  sip	| Multicast stream source ip address.
@parm  uint16		| svid	| Multicast stream input vlan index.
@parm  uint16 	| sport	| Multicast stream input port number.
*/ 
    rtl865x_tblDrv_mCast_t * rtl865x_findMCastEntry(ipaddr_t mAddr,
						    ipaddr_t sip, uint16 svid,
						    uint16 sport) 
{
	
	
	
		
		     && mCast_t->svid == svid && mCast_t->port == sport)
			
			
				
				
				
				
			
			
	
	
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    for (entry = RTL8651_IPMULTICASTTBL_SIZE;
		 entry < RTL8651_MULTICASTTBL_SIZE; entry++)
		
		
			       nextMCast) {
			
			     && mCast_t->svid == svid && mCast_t->port == sport)
				
				
					
					
					    RTL865X_MULTICAST_TABLE_AGE;
					
					
				
				
		
		
	
#endif /* 
	    return (rtl865x_tblDrv_mCast_t *) NULL;



#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)

{
	
	
		index < RTL8651_MULTICASTTBL_SIZE; index++)
		
		
			
			
			
		
	



#endif /* 
    
/*
@func int32	| rtl865x_addMulticastEntry	|  API to add a hardwawre multicast forwarding entry.
@parm  ipaddr_t 	| mAddr	| Multicast flow Destination group address. 
@parm  ipaddr_t 	| sip	| Multicast flow source ip address. 
@parm  uint16 	| svid	| Multicast flow input vlan index. 
@parm  uint16		| sport	| Multicast flow input port number. 
@parm  rtl865x_mcast_fwd_descriptor_t *	| newFwdDescChain	| Multicast flow forwarding descriptor chain to be added. 
@parm  int32 	| flushOldChain	| Flag to indicate to flush old mulicast forwarding descriptor chain or not. 1 is to flush old chain, and 0 is not to. 
@parm  ipaddr_t 	| extIp	| External source ip address used when forward multicast data from lan to wan. 
@parm  int8	| toCpu	| Cpu forwarding flag, 1 is to forward multicast data by cpu,and  0 is not.
@parm  int8	| flag	| For future usage, set to 0 at present.
@rvalue SUCCESS	|Add hardware multicast forwarding entry successfully. 
@rvalue FAILED	|Add hardware multicast forwarding entry failed.
*/ 
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
    int32 rtl865x_addMulticastEntry(ipaddr_t mAddr, ipaddr_t sip, uint16 svid,
				    uint16 sport,
				    
				    newFwdDescChain, 
				    ipaddr_t extIp, char cpuHold, uint8 flag,
				    unsigned int mapPortMask)
#else /* 
    int32 rtl865x_addMulticastEntry(ipaddr_t mAddr, ipaddr_t sip, uint16 svid,
				    uint16 sport,
				    
				    newFwdDescChain, 
				    ipaddr_t extIp, char cpuHold, uint8 flag)
#endif /* 
{
	
	
	
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    uint32 emptyCamIndex = -1;
	
#endif /* 
#if defined (CONFIG_RTL_IGMP_SNOOPING)
	struct rtl_groupInfo groupInfo;
	
#endif /* 
	    /*windows xp upnp:239.255.255.0 */ 
	    if (mAddr == 0xEFFFFFFA)
		
		
		
	
#if 0
	    /*reserved multicast address 224.0.0.x */ 
	    if ((mAddr & 0xFFFFFF00) == 0xE0000000)
		
		
		
	
#endif /* 
	    
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    mCast_t = rtl865x_findMCastEntry(mAddr, sip, svid, sport);
	
		
		
		    /*table entry collided */ 
		    if (!TAILQ_EMPTY(&mCastTbl.inuseList.mCastTbl[hashIndex]))
			
			
			
				
				
				
			
		
	
	else
		
		
		
	
#else /* 
	    /*try to match hash line */ 
	    TAILQ_FOREACH(mCast_t, &mCastTbl.inuseList.mCastTbl[hashIndex],
			  nextMCast) 
		
		     && mCast_t->svid == svid && mCast_t->port == sport)
			
	
	
#endif /* 
	    
		
		
		
			
			
			
			
				
				
				
			
		
		
		
		
		
		
		
		    //mCast_t->maxPPS               = 0;
		    
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
		    mCast_t->mapPortMbr = mapPortMask;
		
#endif /* 
		    
		
	
		
		
		
	
					   newFwdDescChain);
	
	
	
	
	
#if 0
	    mCast_t->cpu = (toCpu == TRUE ? 1 : 0);
	
#else /* 
	    mCast_t->cpuHold = cpuHold;
	
	
#endif /* 
	    mCast_t->flag = flag;
	
		
	
	else
		
	
#if defined (CONFIG_RTL_IGMP_SNOOPING)
	    rtl_getGroupInfo(mAddr, &groupInfo);
	
		
		
		
	
	else
		
		
		
	
#endif /* 
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    mCast_t->hashIndex = hashIndex;
	
#endif /* 
	    _rtl865x_patchPppoeWeak(mCast_t);
	
	



/*
@func int32	| rtl865x_delMulticastEntry	|  API to delete multicast forwarding entry related with a certain group address.
@parm  ipaddr_t 	| mcast_addr	| Group address to be mached in deleting hardware multicast forwarding entry. 
@rvalue SUCCESS	|Delete hardware multicast forwarding entry successfully. 
@rvalue FAILED	|Delete hardware multicast forwarding entry failed.
*/ 
    int32 rtl865x_delMulticastEntry(ipaddr_t mcast_addr) 
{
	
	
	
	
		
		
		
		
			
			
			
				
				
				
				
			
			
		
			
			
			
		
	



#if 0
/*the following function maybe used in future*/ 
    
				       rtl865x_mcast_fwd_descriptor_t *
				       newFwdDesc) 
{
	
	
	
	
		
		
		
	
		
		
			       nextMCast) 
			
				
			
			
			    (&mCast_t->fwdDescChain, newFwdDesc);
			
			
			
			
#ifndef RTL8651_MCAST_ALWAYS2UPSTREAM
			    if (mCast_t->flag & RTL865X_MULTICAST_UPLOADONLY)
				
				
					
					
					    ~RTL865X_MULTICAST_UPLOADONLY;
					
					    /* we assume multicast member will NEVER in External interface, so we remove
					       external ip now */ 
					    mCast_t->flag &=
					    ~RTL865X_MULTICAST_EXTIP_SET;
					
					
				
			
#endif	/* RTL8651_MCAST_ALWAYS2UPSTREAM */
			    
			
			
		
		
	
		
		
		
	



				     rtl865x_mcast_fwd_descriptor_t *
				     deadFwdDesc) 
{
	
	
	
	
		
		
			TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
			mCastEntry; mCastEntry = nextMCastEntry)
			
			
			
				
				
				
			
			
			    (&mCastEntry->fwdDescChain, deadFwdDesc);
			
			    rtl865x_genMCastEntryFwdMask(mCastEntry);
			
			
				
				
				    /*to-do:unknown multicast hardware blocking */ 
				    _rtl865x_freeMCastEntry(mCastEntry, index);
				
				
				
			
			else
				
				
				
			
		
		
	



				      uint16 svid, uint16 sport) 
{
	
	
	
		
		
			       nextMCast) 
			
			     && 
								    ||
								    mCast_t->svid
								    == svid)
			     && 
				
				
				
				
				
		
		
	



{
	
	
	
	
	
	    /* delete all upstream related to vid */ 
	    sport = 0;
	
	
		
		
			
			
			
		
		
		
	
	    /* delete all downstream related to vid */ 
	    vlanFwdDesc.vid = vid;
	
	
	



{
	
	
	
	    /* delete all upstream related to this port */ 
	    rtl865x_delMulticastUpStream(0, 0, 0, port);
	
	    /* delete all downstream related to this port */ 
	    portFwdDesc.vid = 0;
	
	
	



{
	
	
	
		
		
			       nextMCast) 
			
				
				
				
		
		
		
	



						targetChainHead,
						rtl865x_mcast_fwd_descriptor_t *
						srcChain) 
{
	
	
		
		
		
	
		curDesc = MC_LIST_NEXT(curDesc, next))
		
		
		
	



					     queueHead,
					     rtl865x_mcast_fwd_descriptor_t *
					     dequeueDesc) 
{
	
	
		
		
		
	
		
		
		
	
		curDesc = nextDesc)
		
		
		
		     || 
			  || (curDesc->vid == dequeueDesc->vid)))
			
			
			
				
				
				    /*remove from the old descriptor chain */ 
				    MC_LIST_REMOVE(curDesc, next);
				
				    /*return to the free descriptor chain */ 
				    _rtl865x_freeMCastFwdDesc(curDesc);
				
			
			
		
	
	    /*never reach here */ 
	    return SUCCESS;



#endif /* 
    
#if defined(CONFIG_BRIDGE_IGMP_SNOOPING)
    int32 rtl865x_multicastUpdate(rtl865x_mcast_fwd_descriptor_t * desc) 
{
	
	
	    //uint32 oldDescPortMask,newDescPortMask;/*for device decriptor forwarding usage*/
	    uint32 oldAsicFwdPortMask, newAsicFwdPortMask;	/*for physical port forwarding usage */
	
	
	
	
	    //printk("[%s:%d]\n",__FUNCTION__,__LINE__);
	    if (desc == NULL)
		
		
		    //printk("[%s:%d]failed\n",__FUNCTION__,__LINE__);
		    return FAILED;
		
	
	    /*check device name's validity */ 
	    if (strlen(desc->netifName) == 0)
		
		
		    //printk("[%s:%d]failed\n",__FUNCTION__,__LINE__);
		    return FAILED;
		
	
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(desc->netifName, RTL_BR_NAME, 3) == 0
		|| memcmp(desc->devName, RTL_BR1_NAME, 3) == 0)
		
#else /* 
	    if (memcmp(desc->netifName, RTL_BR_NAME, 3) == 0)
		
#endif /* 
	{
		
			
			
			      TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
				    //printk("[%s:%d]hw dip is:0x%x,cur dip is 0x%x\n",__FUNCTION__,__LINE__,mCastEntry->dip,desc->dip);    
				    if (mCastEntry->dip != desc->dip)
					
					
					
				
					sizeof(rtl865x_mcast_fwd_descriptor_t));
				
				
				    /*save old multicast entry forward port mask */ 
				    oldAsicFwdPortMask = mCastEntry->mbr;
				
				
				    /*sync with control plane */ 
				    newFwdDesc.fwdPortMask =
				    desc->fwdPortMask &
				    (~(1 << mCastEntry->port));
				
				
				    /*update/replace old forward descriptor */ 
				    
				    (&mCastEntry->fwdDescChain, &newFwdDesc);
				
				    rtl865x_genMCastEntryAsicFwdMask
				    (mCastEntry);
				
				    rtl865x_genMCastEntryCpuFlag(mCastEntry);
				
				
				
				    /*printk("[%s:%d]old fwPortMask is %d,newfwPortMask is %d\n",
				       __FUNCTION__,
				       __LINE__,
				       oldAsicFwdPortMask,
				       newAsicFwdPortMask); */ 
#ifndef RTL8651_MCAST_ALWAYS2UPSTREAM
				    if (mCastEntry->flag &
					RTL865X_MULTICAST_UPLOADONLY)
					
					
					     && (newAsicFwdPortMask !=
						 oldAsicFwdPortMask))
						
						
						    ~RTL865X_MULTICAST_UPLOADONLY;
						
						    /* we assume multicast member will NEVER in External interface, so we remove
						       external ip now */ 
						    mCastEntry->flag &=
						    ~RTL865X_MULTICAST_EXTIP_SET;
						
						
					
				
#endif	/* RTL8651_MCAST_ALWAYS2UPSTREAM */
				    
				
				       || (newAsicFwdPortMask !=
					   oldAsicFwdPortMask))
					
					
					
					    /*reset inAsic flag to re-select or re-write this hardware asic entry */ 
					    if (newAsicFwdPortMask == 0)
						
						
						    (mCastEntry, index);
						
					
					
				
			
	
	



#endif /* 
#if defined(CONFIG_RTL_MULTI_LAN_DEV)
extern struct net_bridge *bridge0;

					       unsigned int brFwdPortMask);

#endif /* 
#if defined(CONFIG_RT_MULTIPLE_BR_SUPPORT)
extern int rtl_get_brIgmpModuleIndexbyId(int idx, char *name);

#endif /* 

{
	
#if defined (CONFIG_RTL_IGMP_SNOOPING)
	    uint32 index;
	
#if !defined(CONFIG_RTL_MULTI_LAN_DEV)
	    uint32 oldDescPortMask = 0, newDescPortMask = 0;	/*for device decriptor forwarding usage */
	
#endif /* 
	    uint32 oldAsicFwdPortMask = 0, newAsicFwdPortMask = 0;	/*for physical port forwarding usage */
	
	
	
	
	
	
	
#if !defined(CONFIG_RTL_MULTI_LAN_DEV) && !defined(CONFIG_RT_MULTIPLE_BR_SUPPORT)
	struct rtl_multicastDeviceInfo_s bridgeMCastDev;
	
#endif /* 
	    
#if defined (CONFIG_RT_MULTIPLE_BR_SUPPORT)
	unsigned char br_name[16] = { 0 };
	
	
#if defined (CONFIG_RTL_MULTI_LAN_DEV)
	struct net_bridge *br_dev;
	
#else /* 
	unsigned int br_moduleIndex = 0xFFFFFFFF;
	
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
	unsigned int currentCpuFlag = 0;
	
#endif /* 
#endif /* 
#endif /* 
	    
#if 0				//defined(CONFIG_RTL_ISP_MULTIPLE_BR_SUPPORT) && defined(CONFIG_RTL_MULTI_LAN_DEV)
//need to check, some are used only for CONFIG_RTL_MULTI_LAN_DEV
	struct net_bridge *br_dev;
	
	
	
	
	
	
	
#endif /* 
	struct rtl_groupInfo groupInfo;
	
	
		
		
		
	
	
	    /*check device name's validity */ 
	    if (strlen(mcastEventContext.devName) == 0)
		
		
		
	
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
	    printk
	    ("%s:%d,mcastEventContext.devName is %s,moduleindex:%x, mcastEventContext.groupAddr is 0x%x,mcastEventContext.sourceAdd is 0x%x,mcastEventContext.portMask is 0x%x\n",
	     __FUNCTION__, __LINE__, mcastEventContext.devName,
	     mcastEventContext.moduleIndex, mcastEventContext.groupAddr[0],
	     mcastEventContext.sourceAddr[0], mcastEventContext.portMask);
	
#endif /* 
	    
#if defined (CONFIG_RTL_MULTI_LAN_DEV)
#if defined (CONFIG_RT_MULTIPLE_BR_SUPPORT)
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 2) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 3) == 0)
		
#endif /* 
	{
		
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
		    printk
		    ("%s:%d,multicast event from %s,mcastEventContext.groupAddr[0] is 0x%x\n",
		     __FUNCTION__, __LINE__, mcastEventContext.devName,
		     mcastEventContext.groupAddr[0]);
		
#endif /* 
		    
			
			
			      TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
				       && (mCastEntry->dip !=
					   mcastEventContext.groupAddr[0]))
					
					
					
				
					  sizeof
					  (rtl865x_mcast_fwd_descriptor_t));
				
					mcastEventContext.devName);
				
				    /*save old multicast entry forward port mask */ 
				    oldAsicFwdPortMask = mCastEntry->mbr;
				
				
				    /*sync with control plane */ 
				    multicastDataInfo.ipVersion = 4;
				
				    mCastEntry->sip;
				
				    mCastEntry->dip;
				
#if 0
				    //#if defined (CONFIG_RTL_ISP_MULTIPLE_BR_SUPPORT)
				    for (br_index = 0;
					 br_index < RTL_IMGP_MAX_BRMODULE;
					 br_index++)
					
					
					    rtl_get_brByIndex(br_index,
							      br_name);
					
						
						
						
						retVal =
						    rtl_getMulticastDataFwdInfo
						    (br_moduleIndex,
						     &multicastDataInfo,
						     &multicastFwdInfo);
						
							
						
						    rtl865x_getPhyFwdPortMask
						    (br_dev,
						     multicastFwdInfo.fwdPortMask);
						
						    fwdPortMask_tmp;
						
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
						    printk
						    ("dev:%s, multicastFwdInfo.fwdPortMask:%x, fwdPortMask_tmp:%x, in_port:%x, newFwdPortMask:%x, [%s:%d]\n",
						     
						     multicastFwdInfo.fwdPortMask,
						     fwdPortMask_tmp,
						     mCastEntry->port,
						     newFwdDesc.fwdPortMask,
						     __FUNCTION__, __LINE__);
						
#endif /* 
						}
					
					    (~(1 << mCastEntry->port));
					
				
					
				
#else /* 
				    retVal =
				    rtl_getMulticastDataFwdInfo
				    (mcastEventContext.moduleIndex,
				     &multicastDataInfo, &multicastFwdInfo);
				
				    /*fix jwj */ 
				    if (multicastFwdInfo.unknownMCast == TRUE)
					
				
					
					
					
					
				
#endif /* 
				    
#if defined CONFIG_RT_MULTIPLE_BR_SUPPORT
				    br_dev = NULL;
				
				      br_index < RTL_IMGP_MAX_BRMODULE;
				      br_index++)
					
					
					    rtl_get_brByIndex(br_index,
							      br_name);
					
					     (br_name,
					      mcastEventContext.devName) == 0)
						
					
				
					
				
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					    rtl865x_getPhyFwdPortMask(br_dev,
								      multicastFwdInfo.fwdPortMask)
					    & (~(1 << mCastEntry->port));
					
						
						
						     TRUE)
							
							
							    //wifi entry exist
							    newFwdDesc.fwdPortMask
							    |= (0x01 << 6);
							
						
					
				
				else
					
					
					    rtl865x_getPhyFwdPortMask(br_dev,
								      multicastFwdInfo.fwdPortMask)
					    & (~(1 << mCastEntry->port));
					
				
#else /* 
				    newFwdDesc.fwdPortMask =
				    rtl865x_getPhyFwdPortMask(br_dev,
							      multicastFwdInfo.fwdPortMask)
				    & (~(1 << mCastEntry->port));
				
#endif /* 
#else /* 
				    
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					    rtl865x_getPhyFwdPortMask(bridge0,
								      multicastFwdInfo.fwdPortMask)
					    & (~(1 << mCastEntry->port));
					
						
						
						     TRUE)
							
							
							    //wifi entry exist
							    newFwdDesc.fwdPortMask
							    |= (0x01 << 6);
							
						
					
				
				else
					
					
					    rtl865x_getPhyFwdPortMask(bridge0,
								      multicastFwdInfo.fwdPortMask)
					    & (~(1 << mCastEntry->port));
					
				
#else /* 
				    newFwdDesc.fwdPortMask =
				    rtl865x_getPhyFwdPortMask(bridge0,
							      multicastFwdInfo.fwdPortMask)
				    & (~(1 << mCastEntry->port));
				
#endif /* 
#endif /* 
				    
				    multicastFwdInfo.cpuFlag;
				
#if defined	CONFIG_RTL865X_MUTLICAST_DEBUG
				    panic_printk
				    ("newFwdDesc.tocpu %d, newFwdDesc.fwdPortMask:%x,[%s:%d]\n",
				     multicastFwdInfo.cpuFlag,
				     newFwdDesc.fwdPortMask, __FUNCTION__,
				     __LINE__);
				
#endif /* 
				    /*update/replace old forward descriptor */ 
				    _rtl865x_mergeMCastFwdDescChain
				    (&mCastEntry->fwdDescChain, &newFwdDesc);
				
				    /*tocpu flag=1, DescFwdMask will be ignored, to cpu flag */ 
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					    rtl865x_genMCastEntryAsicFwdMaskIgnoreCpuFlag
					    (mCastEntry);
					
				
				else
					
					
					    rtl865x_genMCastEntryAsicFwdMask
					    (mCastEntry);
					
				
#else /* 
				    mCastEntry->mbr =
				    rtl865x_genMCastEntryAsicFwdMask
				    (mCastEntry);
				
#endif /* 
				    mCastEntry->cpu =
				    rtl865x_genMCastEntryCpuFlag(mCastEntry);
				
				
				
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
				    printk
				    ("%s:%d,oldAsicFwdPortMask is %d,newAsicFwdPortMask is %d\n",
				     __FUNCTION__, __LINE__, oldAsicFwdPortMask,
				     newAsicFwdPortMask);
				
#endif /* 
				    
#ifndef RTL8651_MCAST_ALWAYS2UPSTREAM
				    if (mCastEntry->flag &
					RTL865X_MULTICAST_UPLOADONLY)
					
					
					     && (newAsicFwdPortMask !=
						 oldAsicFwdPortMask))
						
						
						    ~RTL865X_MULTICAST_UPLOADONLY;
						
						    /* we assume multicast member will NEVER in External interface, so we remove
						       external ip now */ 
						    mCastEntry->flag &=
						    ~RTL865X_MULTICAST_EXTIP_SET;
						
						
					
				
#endif	/* RTL8651_MCAST_ALWAYS2UPSTREAM */
				    
						      &groupInfo);
				
					
					
					
				
				else
					
					
					
				
#if defined CONFIG_RTL865X_MUTLICAST_DEBUG				
				    printk
				    ("old FwdPortMask:%x, newAsicFwdPortMask:%x, [%s:%d]\n",
				     oldAsicFwdPortMask, newAsicFwdPortMask,
				     __FUNCTION__, __LINE__);
				
#endif /* 
				    
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
				    newAsicFwdPortMask &=
				    (mCastEntry->mapPortMbr | (0x01 << 6));
				
#endif /* 
				    
#if defined(CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					      (~(1 << 6))) == 0)
						
					
				
#endif /* 
				    
#if defined CONFIG_RTL865X_MUTLICAST_DEBUG
				    printk
				    ("old FwdPortMask:%x, newAsicFwdPortMask:%x, [%s:%d]\n",
				     oldAsicFwdPortMask, newAsicFwdPortMask,
				     __FUNCTION__, __LINE__);
				
#endif /* 
				    if ((oldCpuFlag != newCpuFlag)
					|| (newAsicFwdPortMask !=
					    oldAsicFwdPortMask))
					
					
					
					    /*reset inAsic flag to re-select or re-write this hardware asic entry */ 
					    if (newAsicFwdPortMask == 0)
						
						
						    (mCastEntry, index);
						
					
					
				
			
	
	
#else //CONFIG_RTL_MULTI_LAN_DEV
	    /*case 1:this is multicast event from bridge */ 
	    /*sync wlan and ethernet */ 
	    //hyking:[Fix me] the RTL_BR_NAME...
#if defined (CONFIG_OPENWRT_SDK)
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 6) == 0
		|| memcmp(mcastEventContext.devName, RTL_BR1_NAME, 3) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 6) == 0)
		
#endif /* 
#else /* 
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 3) == 0
		|| memcmp(mcastEventContext.devName, RTL_BR1_NAME, 3) == 0)
		
#elif defined (CONFIG_RT_MULTIPLE_BR_SUPPORT)
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 2) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 3) == 0)
		
#endif /* 
#endif /* 
	{
		
			
			
			      TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
				       && (mCastEntry->dip !=
					   mcastEventContext.groupAddr[0]))
					
					
					
				
						    &groupInfo);
				
					
					
					
				
				else
					
					
					
				
				    rtl865x_getMCastEntryDescPortMask
				    (mCastEntry);
				
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					
					
				
#endif /* 
				    
#if defined CONFIG_RT_MULTIPLE_BR_SUPPORT
				    newDescPortMask = 0;
				
				
#if defined CONFIG_RTL_HW_MCAST_WIFI
				    currentCpuFlag = 0;
				
#endif /* 
				    for (br_index = 0;
					 br_index < RTL_IMGP_MAX_BRMODULE;
					 br_index++)
					
					
					    rtl_get_brIgmpModuleIndexbyId
					    (br_index, br_name);
					
						
					
					    /*sync with control plane */ 
					    memset(&newFwdDesc, 0,
						   sizeof
						   (rtl865x_mcast_fwd_descriptor_t));
					
					
					
					    mCastEntry->sip;
					
					    mCastEntry->dip;
					
					    rtl_getMulticastDataFwdInfo
					    (br_moduleIndex, &multicastDataInfo,
					     &multicastFwdInfo);
					
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
					    if (hwwifiEnable)
						
						
							
							
								
								    = 0;
							
							else
								
								    = 1;
							
						
						    multicastFwdInfo.cpuFlag;
						
							
						else
							
						
						    newAsicFwdPortMask;
						
						    currentCpuFlag;
						
#if defined CONFIG_RTL865X_MUTLICAST_DEBUG
						    printk
						    ("newFwdDesc.fwdPortMask = %x, newFwdDesc.toCpu = %d, [%s:%d]\n",
						     newFwdDesc.fwdPortMask,
						     newFwdDesc.toCpu,
						     __FUNCTION__, __LINE__);
						
#endif /* 
						    _rtl865x_mergeMCastFwdDescChain
						    (&mCastEntry->fwdDescChain,
						     &newFwdDesc);
						
					
#endif /* 
					    
						
						
						    multicastFwdInfo.cpuFlag;
						
					
				
				    //printk("br:%s :oldAsicPortMask:%x,newAsicPortMask:%x,oldCpuFlag:%d,newCpuFlag:%d,[%s]:[%d].\n",devName,oldAsicPortMask,newAsicPortMask,oldCpuFlag,newCpuFlag,__FUNCTION__,__LINE__);
				    
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					    rtl865x_genMCastEntryAsicFwdMask
					    (mCastEntry);
					
					    rtl865x_genMCastEntryCpuFlag
					    (mCastEntry);
					
					
					
						
						
						
						
					
						(~(1 << 6))) == 0)
						
						
						    //only cpu port
						    newAsicFwdPortMask = 0;
						
					
					       || (newAsicFwdPortMask !=
						   oldAsicFwdPortMask))
						
						
							
							    //printk("[%s]:[%d].\n",__FUNCTION__,__LINE__);
							    _rtl865x_freeMCastEntry
							    (mCastEntry, index);
						
						
						    (index);
						
					
				
				else
					
					
						
					
						
						
						    (mCastEntry, index);
						
						    (index);
						
					
				
#else /* 
				    if (mCastEntry->unKnownMCast == TRUE)
					
				
					
					
								 index);
					
					
				
#endif /* 
#else //CONFIG_RT_MULTIPLE_BR_SUPPORT
				    
				    /*sync with control plane */ 
				    memset(&newFwdDesc, 0,
					   sizeof
					   (rtl865x_mcast_fwd_descriptor_t));
				
					mcastEventContext.devName);
				
				
				    mCastEntry->sip;
				
				    mCastEntry->dip;
				
				    rtl_getMulticastDataFwdInfo
				    (mcastEventContext.moduleIndex,
				     &multicastDataInfo, &multicastFwdInfo);
				
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
						
						
						    multicastFwdInfo.cpuFlag;
						
							
							    (1 <<
							     RTL8651_MAC_NUMBER);
						
						else
							
						
					
					else
						
						
						
						
					
					    //this fwdDesc is used to set cpu port, here to update br fwdDesc
					    newFwdDesc.fwdPortMask =
					    newAsicFwdPortMask;
					
					
					    //printk("br:%s :oldAsicPortMask:%x,newAsicPortMask:%x,oldCpuFlag:%d,newCpuFlag:%d,[%s]:[%d].\n",mcastEventContext.devName,oldAsicPortMask,newAsicPortMask,oldCpuFlag,newCpuFlag,__FUNCTION__,__LINE__);
					    _rtl865x_mergeMCastFwdDescChain
					    (&mCastEntry->fwdDescChain,
					     &newFwdDesc);
					
					    rtl865x_genMCastEntryAsicFwdMask
					    (mCastEntry);
					
					    rtl865x_genMCastEntryCpuFlag
					    (mCastEntry);
					
					
					
					    //printk("br:%s :oldAsicPortMask:%x,newAsicPortMask:%x,oldCpuFlag:%d,newCpuFlag:%d,[%s]:[%d].\n",mcastEventContext.devName,oldAsicPortMask,newAsicPortMask,oldCpuFlag,newCpuFlag,__FUNCTION__,__LINE__);
					    //just cpu port not add hw entry
					    if ((newAsicFwdPortMask &
						 (~(1 << 6))) == 0) {
						
					
					
					     || (newAsicFwdPortMask !=
						 oldAsicFwdPortMask))
						
						
							
							    (mCastEntry, index);
						
						    (index);
						
					
				
				else
					
					
						
						
						
					
					    rtl_getIgmpSnoopingModuleDevInfo
					    (mcastEventContext.moduleIndex,
					     &bridgeMCastDev);
					
						
						
						
					
					    multicastFwdInfo.fwdPortMask;
					
					    //shirley note:oldDescPortMask is always 0, the judge condision is equal to (newDescPortMask & bridgeMCastDev.swPortMask)!=0
					    if ((oldDescPortMask !=
						 newDescPortMask)
						&&
						
						    bridgeMCastDev.swPortMask)
						   != 0)
						  ||
						  
						      bridgeMCastDev.swPortMask)
						     != 0)
						    &&
						    ((newDescPortMask &
						      bridgeMCastDev.swPortMask)
						     == 0))))
						
						
						    /*this multicast entry should be re-generated at linux protocol stack bridge level */ 
						    _rtl865x_freeMCastEntry
						    (mCastEntry, index);
						
						    (index);
						
					
				
#else /* 
				    
					
					
					
				
				    rtl_getIgmpSnoopingModuleDevInfo
				    (mcastEventContext.moduleIndex,
				     &bridgeMCastDev);
				
					
					
					
				
				
				    //shirley note:oldDescPortMask is always 0, the judge condision is equal to (newDescPortMask & bridgeMCastDev.swPortMask)!=0
				    if ((oldDescPortMask != newDescPortMask)
					&&
					
					    bridgeMCastDev.swPortMask) != 0)
					  ||
					  
					      bridgeMCastDev.swPortMask) != 0)
					    &&
					    ((newDescPortMask &
					      bridgeMCastDev.swPortMask) ==
					     0))))
					
					
					    /*this multicast entry should be re-generated at linux protocol stack bridge level */ 
					    _rtl865x_freeMCastEntry(mCastEntry,
								    index);
					
					
				
#endif /* 
#endif /* 
				}
			
		
	
	
/*update ethernet forwarding port mask*/ 
	    
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(mcastEventContext.devName, "eth*", 4) == 0
		|| memcmp(mcastEventContext.devName, RTL_PS_ETH_NAME_ETH2,
			  4) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, "eth*", 4) == 0)
		
#endif /* 
	{
		
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
		    printk
		    ("%s:%d,multicast event from %s,mcastEventContext.groupAddr[0] is 0x%x\n",
		     __FUNCTION__, __LINE__, mcastEventContext.devName,
		     mcastEventContext.groupAddr[0]);
		
#endif /* 
		    
			
			
			      TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
				       && (mCastEntry->dip !=
					   mcastEventContext.groupAddr[0]))
					
					
					
				
					  sizeof
					  (rtl865x_mcast_fwd_descriptor_t));
				
					mcastEventContext.devName);
				
				    /*save old multicast entry forward port mask */ 
				    oldAsicFwdPortMask = mCastEntry->mbr;
				
				
				    /*sync with control plane */ 
				    multicastDataInfo.ipVersion = 4;
				
				    mCastEntry->sip;
				
				    mCastEntry->dip;
				
				    rtl_getMulticastDataFwdInfo
				    (mcastEventContext.moduleIndex,
				     &multicastDataInfo, &multicastFwdInfo);
				
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
						
						
						
						
					
					else
						
						
						    multicastFwdInfo.fwdPortMask
						    &
						    (~(1 << mCastEntry->port));
						
						    multicastFwdInfo.cpuFlag;
						
					
				
				else
					
#endif /* 
				{
					
					    /*fix jwj */ 
					    if (multicastFwdInfo.unknownMCast ==
						TRUE)
						
						    TRUE;
					
					    multicastFwdInfo.fwdPortMask &
					    (~(1 << mCastEntry->port));
					
					    multicastFwdInfo.cpuFlag;
				
				
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
				    newFwdDesc.fwdPortMask &=
				    mCastEntry->mapPortMbr;
				
#endif /* 
				    
				    /*update/replace old forward descriptor */ 
				    
				    (&mCastEntry->fwdDescChain, &newFwdDesc);
				
				    rtl865x_genMCastEntryAsicFwdMask
				    (mCastEntry);
				
				    rtl865x_genMCastEntryCpuFlag(mCastEntry);
				
				
				
#if defined (CONFIG_RTL_HW_MCAST_WIFI)
				    if (hwwifiEnable)
					
					
					     == 0)
						
					
				
#endif /* 
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
				    printk
				    ("%s:%d,oldAsicFwdPortMask is %d,newAsicFwdPortMask is %d\n",
				     __FUNCTION__, __LINE__, oldAsicFwdPortMask,
				     newAsicFwdPortMask);
				
#endif /* 
				    
#ifndef RTL8651_MCAST_ALWAYS2UPSTREAM
				    if (mCastEntry->flag &
					RTL865X_MULTICAST_UPLOADONLY)
					
					
					     && (newAsicFwdPortMask !=
						 oldAsicFwdPortMask))
						
						
						    ~RTL865X_MULTICAST_UPLOADONLY;
						
						    /* we assume multicast member will NEVER in External interface, so we remove
						       external ip now */ 
						    mCastEntry->flag &=
						    ~RTL865X_MULTICAST_EXTIP_SET;
						
						
					
				
#endif	/* RTL8651_MCAST_ALWAYS2UPSTREAM */
				    
						      &groupInfo);
				
					
					
					
				
				else
					
					
					
				
					 || (newAsicFwdPortMask !=
					     oldAsicFwdPortMask))
					
					
					
					    /*reset inAsic flag to re-select or re-write this hardware asic entry */ 
					    if (newAsicFwdPortMask == 0)
						
						
						    (mCastEntry, index);
						
					
					
				
			
	
	
#endif /* 
#endif /* 
	    return EVENT_CONTINUE_EXECUTE;



{
	
	
	
	
	
	
	



{
	
	
	
	
	
	
	



#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
extern void ConvertMulticatIPtoMacAddr(__u32 group, unsigned char *gmac);


					       unsigned int fwdPortMask);


{
	
	
	
	
	
	
		
		
		
	
	
		
		
		
	
		
		
		    //only deal with eth event.
		    return EVENT_CONTINUE_EXECUTE;
		
	
		
		
		    //only deal with eth event.
		    return EVENT_CONTINUE_EXECUTE;
		
	
	
	    //l2 multicast only support igmpv1 and igmpv2, sourceip is not meaningful
	    multicastDataInfo.sourceIp[0] = mcastEventContext.sourceAddr[0];
	
	
	
	    rtl_getMulticastDataFwdInfo(mcastEventContext.moduleIndex,
					&multicastDataInfo, &multicastFwdInfo);
	
		
		
		    //need to delete l2 table entry
		    ret = rtl_delFilterDatabaseEntryforMCast(mac);
		
		    //printk("delFilter return:%d\n", ret);
		}
	
	else
		
		
		    //update l2 table entry
		    ret =
		    rtl_addFilterDatabaseEntryforMCast(mac,
						       multicastFwdInfo.fwdPortMask);
		
		    //printk("addFilter return:%d\n", ret);
		}
	



{
	
	
	
	
	
	
	



{
	
	
	
	
	
	
	



#endif /* 
void _rtl865x_timeUpdateMulticast(uint32 secPassed) 
{
	
	
	
	
	
	    /* check to Aging and HW swapping */ 
	    for (entry = 0; entry < RTL8651_MULTICASTTBL_SIZE; entry++) {
		
		
		
		
			
			    /*save the next entry first */ 
			    nextMCast_t = TAILQ_NEXT(mCast_t, nextMCast);
			
				
				
				    /* Entry is in the ASIC */ 
				    if (mCast_t->age <= secPassed)
					
					
						
						
						    (mCast_t, entry);
						
						
					
					else
						
						
						    RTL865X_MULTICAST_TABLE_AGE;
						
					
				
				else
					
					
					
				
			
			else
				
				
				    /* Entry is not in the ASIC */ 
				    if (mCast_t->age <= secPassed)
					
					
								 entry);
					
				
				else
					
					
					
				
			
			    /*won't count multicast entry forwarded by cpu */ 
			    if (mCast_t->cpu == 0)
				
				
				
				    //printk("------------hashLineCnt:%d,[%s]:[%d].\n",hashLineCnt,__FUNCTION__,__LINE__);
				    if (hashLineCnt >= 2)
					
					
					
				
			
			    //mCast_t->count = 0;
			    mCast_t = nextMCast_t;
		
		
			
			
			    //printk("------------entry:%d,hashLineCnt:%d,[%s]:[%d].\n",entry,hashLineCnt,__FUNCTION__,__LINE__);
			    _rtl865x_arrangeMulticast(entry);
			
		
		
			
			    /*save the next entry first */ 
			    nextMCast_t = TAILQ_NEXT(mCast_t, nextMCast);
			
				
			
		
	



#if defined(__linux__) && defined(__KERNEL__)
static void _rtl865x_mCastSysTimerExpired(uint32 expireDada) 
{
	
	


static void _rtl865x_initMCastSysTimer(void) 
{
	
	
	
	
	


static void _rtl865x_destroyMCastSysTimer(void) 
{
	del_timer(&rtl865x_mCastSysTimer);


#endif

/*
@func int32	| rtl865x_initMulticast	|  Init hardware ip multicast module.
@parm  rtl865x_mCastConfig_t *	| mCastConfigPtr	| Pointer of hardware multicast configuration. 
@rvalue SUCCESS	|Initialize successfully.
@rvalue FAILED	|Initialize failed.
*/ 
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
static void _rtl8198C_initMCastv6SysTimer(void);

#endif /* 
    int32 rtl865x_initMulticast(rtl865x_mCastConfig_t * mCastConfigPtr) 
{
	
	
#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    _rtl865x_L2multicastUnRegisterEvent();
	
#endif /* 
	    _rtl865x_initMCastEntryPool();
	
	
	
		
		
		    (mCastConfigPtr->externalPortMask);
		
	
#if defined(__linux__) && defined(__KERNEL__)
	    _rtl865x_initMCastSysTimer();
	
#endif /* 
#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    rtl8651_setAsicOperationLayer(2);
	
#else /* 
	    rtl8651_setAsicOperationLayer(3);
	
#endif /* 
	    rtl8651_setAsicMulticastMTU(1522);
	
#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    rtl8651_setAsicMulticastEnable(FALSE);
	
#else /* 
	    rtl8651_setAsicMulticastEnable(TRUE);
	
#endif /* 
	    rtl865x_setAsicMulticastAging(TRUE);
	
	
#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    _rtl865x_L2multicastRegisterEvent();
	
#endif /* 
#if (defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)) && defined(CONFIG_RTL_MLD_SNOOPING)
	    rtl8198C_initMulticastv6();
	
#endif /* 
	    return SUCCESS;



/*
@func int32	| rtl865x_reinitMulticast	|  Re-init hardware ip multicast module.
@rvalue SUCCESS	|Re-initialize successfully.
@rvalue FAILED	|Re-initialize failed.
*/ 
    int32 rtl865x_reinitMulticast(void)
{
	
	
#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    _rtl865x_L2multicastUnRegisterEvent();
	
#endif /* 
	    /*delete all multicast entry */ 
	    rtl8651_setAsicMulticastEnable(FALSE);
	
	
#if defined(__linux__) && defined(__KERNEL__)
	    _rtl865x_destroyMCastSysTimer();
	
	
#endif /* 
	    
	    /*regfster twice won't cause any side-effect, 
	       because event management module will handle duplicate event issue */ 
	    rtl8651_setAsicMulticastMTU(1522);
	
#if !defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    rtl8651_setAsicMulticastEnable(TRUE);
	
#endif /* 
	    rtl865x_setAsicMulticastAging(TRUE);
	
	
#if defined CONFIG_RTL_L2_HW_MULTICAST_SUPPORT
	    _rtl865x_L2multicastRegisterEvent();
	
#endif /* 
#if 0				//defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    rtl8198C_reinitMulticastv6();
	
#endif /* 
	    return SUCCESS;



#ifdef CONFIG_PROC_FS
extern int32 rtl8651_getAsicMulticastSpanningTreePortState(uint32 port,
							   uint32 * portState);

#ifdef CONFIG_RTL_PROC_NEW
    int32 rtl_dumpSwMulticastInfo(struct seq_file *s) 
{
	
	
	
	
	
	
	
	
	
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    rtl8198c_tblDrv_mCastv6_t * mCastv6_t, *nextMCastv6_t;
	
	
#endif /* 
	    uint32 entry;
	
	
		    "----------------------------------------------------\n");
	
		    rtl8651_getAsicOperationLayer());
	
	
		
		
			    (mCastEnable == TRUE) ? "Enable" : "Disable");
		
	
	else
		
		
		
	
	
		
		
		
	
	else
		
		
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    ret = rtl8198C_getAsicMulticastv6Enable(&mCastEnable);
	
		
		
			    (mCastEnable == TRUE) ? "Enable" : "Disable");
		
	
	else
		
		
			    "Read Asic IPV6 Multicast Table Enable Bit Error\n");
		
	
	
		
		
		
	
	else
		
		
		
	
#endif /* 
	    for (index = 0;
		 index < RTL8651_PORT_NUMBER + rtl8651_totalExtPortNum; index++)
		
		
		
			
			
				
				
				
			
			else
				
				
				
			
		
	
		      internalPortMask, externalPortMask);
	
		    "----------------------------------------------------\n");
	
	
	      index++)
		
		
		    rtl8651_getAsicMulticastSpanningTreePortState(index,
								  &portStatus);
		
			
			
			
				
				
				
			
			else if (portStatus == RTL8651_PORTSTA_BLOCKING)
				
				
				
			
			else if (portStatus == RTL8651_PORTSTA_LEARNING)
				
				
				
			
			else if (portStatus == RTL8651_PORTSTA_FORWARDING)
				
				
				
			
		
	
		    "----------------------------------------------------\n");
	
	
	    /* check to Aging and HW swapping */ 
	    for (entry = 0; entry < RTL8651_MULTICASTTBL_SIZE; entry++) {
		
#if defined(CONFIG_RTL_WTDOG)
		    rtl_periodic_watchdog_kick(entry, WATCHDOG_NUM_OF_TIMES);
		
#endif /* 
		    mCast_t = TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[entry]);
		
			
			    /*save the next entry first */ 
			    nextMCast_t = TAILQ_NEXT(mCast_t, nextMCast);
			
				    "\t[%2d]  dip:%d.%d.%d.%d, sip:%d.%d.%d.%d, mbr:0x%x, svid:%d, spa:%d, \n",
				    entry, 
				    (mCast_t->dip & 0x00ff0000) >> 16,
				    (mCast_t->dip & 0x0000ff00) >> 8,
				    (mCast_t->dip & 0xff), 
				    (mCast_t->sip & 0x00ff0000) >> 16,
				    (mCast_t->sip & 0x0000ff00) >> 8,
				    (mCast_t->sip & 0xff), 
				    mCast_t->svid, mCast_t->port);
			
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
			    seq_printf(s,
				       "\t      extIP:0x%x,age:%d, cpu:%d, count:%d, inAsic:%d, (%s), portMappingMask:0x%x\n",
				       
				       mCast_t->cpu, mCast_t->count,
				       mCast_t->inAsic,
				       mCast_t->unKnownMCast ? "UnknownMCast" :
				       "KnownMCast", mCast_t->mapPortMbr);
			
#else /* 
			    seq_printf(s,
				       "\t      extIP:0x%x,age:%d, cpu:%d, count:%d, inAsic:%d, (%s)\n",
				       
				       mCast_t->cpu, mCast_t->count,
				       mCast_t->inAsic,
				       mCast_t->unKnownMCast ? "UnknownMCast" :
				       "KnownMCast");
			
#endif /* 
			    cnt = 0;
			
			
				
				
				
					    "\t      netif(%s),descPortMask(0x%x),toCpu(%d),fwdPortMask(0x%x)\n",
					    curDesc->netifName,
					    curDesc->descPortMask,
					    curDesc->toCpu,
					    curDesc->fwdPortMask);
				
				
			
			
		
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    seq_printf(s,
		       "----------------------------------------------------\n");
	
	
		
#if defined(CONFIG_RTL_WTDOG)
		    rtl_periodic_watchdog_kick(entry, WATCHDOG_NUM_OF_TIMES);
		
#endif /* 
		    mCastv6_t =
		    TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[entry]);
		
			
			    /*save the next entry first */ 
			    nextMCastv6_t = TAILQ_NEXT(mCastv6_t, nextMCast);
			
				    "\t[%2d]  dip:%08x:%08x%08x:%08x\n\t      sip:%08x:%08x:%08x:%08x\n\t      mbr:0x%x, svid:%d, spa:%d, ",
				    
				    mCastv6_t->dip.v6_addr32[1],
				    
				    mCastv6_t->dip.v6_addr32[3],
				    
				    mCastv6_t->sip.v6_addr32[1],
				    
				    mCastv6_t->sip.v6_addr32[3],
				    
				    
			
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
			    seq_printf(s,
				       "age:%d, cpu:%d, count:%d, inAsic:%d, (%s), portMappingMask:0x%x\n",
				       
				       mCastv6_t->count, mCastv6_t->inAsic,
				       mCastv6_t->unKnownMCast ? "UnknownMCast"
				       : "KnownMCast", mCastv6_t->mapPortMbr);
			
#else /* 
			    seq_printf(s,
				       "age:%d, cpu:%d, count:%d, inAsic:%d, (%s)\n",
				       
				       mCastv6_t->count, mCastv6_t->inAsic,
				       mCastv6_t->unKnownMCast ? "UnknownMCast"
				       : "KnownMCast");
			
#endif /* 
			    cnt = 0;
			
			
				
				
				
					    "\t      netif(%s),descPortMask(0x%x),toCpu(%d),fwdPortMask(0x%x)\n",
					    curDescv6->netifName,
					    curDescv6->descPortMask,
					    curDescv6->toCpu,
					    curDescv6->fwdPortMask);
				
				
			
			
		
	
	
#endif /* 
	    



#else /* 
    int32 rtl_dumpSwMulticastInfo(char *page, int *ret_len) 
{
	
	
	
	
	
	
	
	
	
	
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    rtl8198c_tblDrv_mCastv6_t * mCastv6_t, *nextMCastv6_t;
	
	
#endif /* 
	    uint32 entry;
	
	
	    sprintf(page + len,
		    "----------------------------------------------------\n");
	
	    sprintf(page + len, "Asic Operation Layer :%d\n",
		    rtl8651_getAsicOperationLayer());
	
	
		
		
		    sprintf(page + len, "Asic Multicast Table:%s\n",
			    (mCastEnable == TRUE) ? "Enable" : "Disable");
		
	
	else
		
		
		    sprintf(page + len,
			    "Read Asic Multicast Table Enable Bit Error\n");
		
	
	
		
		
		    sprintf(page + len, "Asic Multicast MTU:%d\n", mCastMtu);
		
	
	else
		
		
		
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    ret = rtl8198C_getAsicMulticastv6Enable(&mCastEnable);
	
		
		
		    sprintf(page + len, "Asic IPV6 Multicast Table:%s\n",
			    (mCastEnable == TRUE) ? "Enable" : "Disable");
		
	
	else
		
		
		    sprintf(page + len,
			    "Read Asic IPV6 Multicast Table Enable Bit Error\n");
		
	
	
		
		
		    sprintf(page + len, "Asic IPV6 Multicast MTU:%d\n",
			    mCastMtu);
		
	
	else
		
		
		    sprintf(page + len, "Read Asic IPV6 Multicast MTU Error\n");
		
	
#endif /* 
	    for (index = 0;
		 index < RTL8651_PORT_NUMBER + rtl8651_totalExtPortNum; index++)
		
		
		
			
			
				
				
				
			
			else
				
				
				
			
		
	
	    sprintf(page + len,
		    "Internal Port Mask:0x%x\nExternal Port Mask:0x%x\n",
		    internalPortMask, externalPortMask);
	
	    sprintf(page + len,
		    "----------------------------------------------------\n");
	
	
	      index++)
		
		
		    rtl8651_getAsicMulticastSpanningTreePortState(index,
								  &portStatus);
		
			
			
			
				
				
				
			
			else if (portStatus == RTL8651_PORTSTA_BLOCKING)
				
				
				
			
			else if (portStatus == RTL8651_PORTSTA_LEARNING)
				
				
				
			
			else if (portStatus == RTL8651_PORTSTA_FORWARDING)
				
				
				
			
		
	
	    sprintf(page + len,
		    "----------------------------------------------------\n");
	
	
	    /* check to Aging and HW swapping */ 
	    for (entry = 0; entry < RTL8651_MULTICASTTBL_SIZE; entry++) {
		
#if defined(CONFIG_RTL_WTDOG)
		    rtl_periodic_watchdog_kick(entry, WATCHDOG_NUM_OF_TIMES);
		
#endif /* 
		    mCast_t = TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[entry]);
		
			
			    /*save the next entry first */ 
			    nextMCast_t = TAILQ_NEXT(mCast_t, nextMCast);
			
			    sprintf(page + len,
				    "\t[%2d]  dip:%d.%d.%d.%d, sip:%d.%d.%d.%d, mbr:0x%x, svid:%d, spa:%d, \n",
				    entry, 
				    (mCast_t->dip & 0x00ff0000) >> 16,
				    (mCast_t->dip & 0x0000ff00) >> 8,
				    (mCast_t->dip & 0xff), 
				    (mCast_t->sip & 0x00ff0000) >> 16,
				    (mCast_t->sip & 0x0000ff00) >> 8,
				    (mCast_t->sip & 0xff), 
				    mCast_t->svid, mCast_t->port);
			
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
			    len +=
			    sprintf(page + len,
				    "\t	  extIP:0x%x,age:%d, cpu:%d, count:%d, inAsic:%d, (%s), portMappingMask:0x%x\n",
				    
				    mCast_t->cpu, mCast_t->count,
				    mCast_t->inAsic,
				    mCast_t->unKnownMCast ? "UnknownMCast"
				    : "KnownMCast", mCast_t->mapPortMbr);
			
#else /* 
			    len +=
			    sprintf(page + len,
				    "\t      extIP:0x%x,age:%d, cpu:%d, count:%d, inAsic:%d, (%s)\n",
				    
				    mCast_t->count, mCast_t->inAsic,
				    mCast_t->unKnownMCast ? "UnknownMCast" :
				    "KnownMCast");
			
#endif /* 
			    cnt = 0;
			
			
				
				
				
				    sprintf(page + len,
					    "\t      netif(%s),descPortMask(0x%x),toCpu(%d),fwdPortMask(0x%x)\n",
					    curDesc->netifName,
					    curDesc->descPortMask,
					    curDesc->toCpu,
					    curDesc->fwdPortMask);
				
				
			
			
		
	
	
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
	    len +=
	    sprintf(page + len,
		    "----------------------------------------------------\n");
	
	
		
#if defined(CONFIG_RTL_WTDOG)
		    rtl_periodic_watchdog_kick(entry, WATCHDOG_NUM_OF_TIMES);
		
#endif /* 
		    mCastv6_t =
		    TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[entry]);
		
			
			    /*save the next entry first */ 
			    nextMCastv6_t = TAILQ_NEXT(mCastv6_t, nextMCast);
			
			    sprintf(page + len,
				    "\t[%2d]  dip:%08x:%08x:%08x:%08x\n\t      sip:%08x:%08x:%08x:%08x\n\t      mbr:0x%x, svid:%d, spa:%d, ",
				    
				    mCastv6_t->dip.v6_addr32[1],
				    
				    mCastv6_t->dip.v6_addr32[3],
				    
				    mCastv6_t->sip.v6_addr32[1],
				    
				    mCastv6_t->sip.v6_addr32[3],
				    
				    
			
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
			    len +=
			    sprintf(page + len,
				    "age:%d, cpu:%d, count:%d, inAsic:%d, (%s), portMappingMask:0x%x\n",
				    
				    mCastv6_t->count, mCastv6_t->inAsic,
				    mCastv6_t->unKnownMCast ? "UnknownMCast" :
				    "KnownMCast", mCastv6_t->mapPortMbr);
			
#else /* 
			    len +=
			    sprintf(page + len,
				    "age:%d, cpu:%d, count:%d, inAsic:%d, (%s)\n",
				    
				    mCastv6_t->count, mCastv6_t->inAsic,
				    mCastv6_t->unKnownMCast ? "UnknownMCast" :
				    "KnownMCast");
			
#endif /* 
			    cnt = 0;
			
			
				
				
				
				    sprintf(page + len,
					    "\t      netif(%s),descPortMask(0x%x),toCpu(%d),fwdPortMask(0x%x)\n",
					    curDescv6->netifName,
					    curDescv6->descPortMask,
					    curDescv6->toCpu,
					    curDescv6->fwdPortMask);
				
				
			
			
		
	
	
#endif /* 
	    *ret_len = len;
	



#endif /* 
#endif

					  uint32 fwdPortMask,
					  rtl865x_mcast_fwd_descriptor_t *
					  fwdDescriptor)
{

	if (fwdDescriptor == NULL) {
		return FAILED;
	}

	memset(fwdDescriptor, 0, sizeof(rtl865x_mcast_fwd_descriptor_t));
	fwdDescriptor->toCpu = forceToCpu;
	fwdDescriptor->fwdPortMask = fwdPortMask;
	return SUCCESS;

}


#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
int rtl865x_blockMulticastFlow(unsigned int srcVlanId, unsigned int srcPort,
			       unsigned int srcIpAddr, unsigned int destIpAddr,
			       unsigned int mapPortMask) 
#else /* 
int rtl865x_blockMulticastFlow(unsigned int srcVlanId, unsigned int srcPort,
			       unsigned int srcIpAddr,
			       unsigned int destIpAddr) 
#endif				/* 
{
	
	
	
	    rtl865x_findMCastEntry(destIpAddr, srcIpAddr, (uint16) srcVlanId,
				   (uint16) srcPort);
	
		
		
			
			
			
		
	
	
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
	    rtl865x_addMulticastEntry(destIpAddr, srcIpAddr,
				      (unsigned short)srcVlanId,
				      (unsigned short)srcPort, &fwdDescriptor,
				      TRUE, 0, 0, 0, mapPortMask);
	
#else /* 
	    rtl865x_addMulticastEntry(destIpAddr, srcIpAddr,
				      (unsigned short)srcVlanId,
				      (unsigned short)srcPort, &fwdDescriptor,
				      TRUE, 0, 0, 0);
	
#endif /* 
	    return SUCCESS;



/*
@func int32	| rtl865x_flushHWMulticastEntry	|  API to delete all multicast 
forwarding entry
@rvalue SUCCESS	|Delete hardware multicast forwarding entry successfully. 
@rvalue FAILED	|Delete hardware multicast forwarding entry failed.
*/ 
    
{
	
	
	
		
		
		    TAILQ_FIRST(&mCastTbl.inuseList.mCastTbl[entry]);
		
			
			
			
				
				
				
				
			
			
		
	



{
	



{
	
	
	
	
		
		
		
	
		
		
		
		    /* exclude 0->1 and 1->0 */ 
		    if (!
			((hashMethod == HASH_METHOD_SIP_DIP0
			  && oldHashMethod == HASH_METHOD_SIP_DIP1)
			 || 
			      && oldHashMethod == HASH_METHOD_SIP_DIP0)))
			
			
			
		
	



#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
static int is_ip6_addr_equal(inv6_addr_t addr1, inv6_addr_t addr2) 
{
	
	     && 
	     && 
	     && 
		
	
	else
		



{
	
	
	
			 MAX_MCASTV6_TABLE_ENTRY_CNT);
	
	
		
		
			sizeof(rtl8198c_tblDrv_mCastv6_t));
		
				   &multiCast_t[index], nextMCast);
		
	
			 RTL8651_MULTICASTTBL_SIZE);
	
		RTL8651_MULTICASTTBL_SIZE * sizeof(rtl8198c_tblDrv_mCastv6_t));
	
	
		
		
		
	



					     descPtr) 
{
	
		
		
		
	
	
	



    * _rtl8198C_allocMCastv6FwdDesc(void) 
{
	
	
	
		
		
		
		
	



						queueHead,
						
						rtl8198c_mcast_fwd_descriptor6_t
						* enqueueDesc) 
{
	
	
	
		
		
		
	
		
		
		
	
	    /*multicast forward descriptor is internal maintained,always alloc new one */ 
	    newDesc = _rtl8198C_allocMCastv6FwdDesc();
	
		
		
			sizeof(rtl8198c_mcast_fwd_descriptor6_t));
		
			sizeof(MC_LIST_ENTRY
			       (rtl8198c_mcast_fwd_descriptor6_t)));
		
		
		
	
	else
		
		
		    /*no enough memory */ 
		    return FAILED;
		
	
		  curDesc = nextDesc)
		
		
		
		    /*merge two descriptor */ 
		    if ((strcmp(curDesc->netifName, newDesc->netifName) == 0)
			&& (curDesc->vid == newDesc->vid))
			
			     0)
				
				
					
					
					    curDesc->descPortMask;
					
				
				
				
		
	
	    /*not matched descriptor is found */ 
	    MC_LIST_INSERT_HEAD(queueHead, newDesc, next);
	



						   * descChainHead) 
{
	
	
		
		
		
	
	
		
		
		
		    /*remove from the old descriptor chain */ 
		    MC_LIST_REMOVE(curDesc, next);
		
		    /*return to the free descriptor chain */ 
		    _rtl8198C_freeMCastv6FwdDesc(curDesc);
		
		
	



					      mCastEntry) 
{
	
		
		
		
	
	
	



					     mCastEntry, uint32 hashIndex) 
{
	
		
		
		
	
			nextMCast);
	
	
			   nextMCast);
	



{
	
	
	
	
	
	
	
	
		       nextMCast) 
		
		     && !(mCast_t->flag & RTL865X_MULTICAST_PPPOEPATCH_CPUBIT))
			
			
				
				
					
					
					
				
				else
					
					
					    /*impossible, two flow in one asic entry */ 
					    swapOutEntry->inAsic = FALSE;
					
					
				
			
				
				
				     && (select_t->unKnownMCast == TRUE))
					
					
					    /*replace unknown multicast */ 
					    select_t = mCast_t;
					
				
				else
					
					
					    /*select the heavy load */ 
					    if ((mCast_t->count) >
						(select_t->count))
						
						
						
					
				
			
			else
				
				
				
			
		
		else
			
			
			
	
	
		
		
		     && (select_t->unKnownMCast == TRUE))
			
			
			    /*replace unknown multicast */ 
			    select_t = swapOutEntry;
			
		
		else
			
			
			      (swapOutEntry->count +
			       RTL865X_HW_MCAST_SWAP_GAP)))
				
			
		
	
		
		
			
			
			
			       sizeof(rtl8198C_tblAsicDrv_multiCastv6Param_t));
			
//                      memcpy(&asic_mcast, select_t, (uint32)&(((rtl8198c_tblDrv_mCastv6_t *)0)->six_rd_idx));
			    memcpy(&asic_mcast, select_t,
				   sizeof
				   (rtl8198C_tblAsicDrv_multiCastv6Param_t));
			
			    rtl8198C_setAsicIpMulticastv6Table(hashMethod,
							       &asic_mcast);
			
#ifdef CONFIG_PROC_FS
			    mcastAddOpCnt6++;
			
#endif /* 
			    assert(retval == SUCCESS);
			
				
				
				
			
			else
				
				
				
				
#ifdef CONFIG_PROC_FS
				    mcastDelOpCnt6++;
				
#endif /* 
				}
			
			
				      select_t, nextMCast);
			
					   inuseList.mCastTbl[entryIndex],
					   select_t, nextMCast);
			
		
		else		/*(swapOutEntry!=NULL) && (select_t!=swapOutEntry) */
			
			
			    /*disable swap and only explicit joined mulicast flow can replace unknown multicast flow */ 
			    if (1)
				
				
				    /*don't forget to set swapOutEntry's inAsic flag */ 
				    swapOutEntry->inAsic = FALSE;
				
				    RTL865X_MULTICAST_TABLE_ASIC_AGE;
				
				       sizeof
				       (rtl8198C_tblAsicDrv_multiCastv6Param_t));
				
					(uint32) &
					(((rtl8198C_tblAsicDrv_multiCastv6Param_t *) 0)->six_rd_idx));
				
				    rtl8198C_setAsicIpMulticastv6Table
				    (hashMethod, &asic_mcast);
				
				    //printk("asic_mcast:dip:%x,[%s]:[%d].\n",asic_mcast.dip,__FUNCTION__,__LINE__);
#ifdef CONFIG_PROC_FS
				    mcastAddOpCnt6++;
				
#endif /* 
				    assert(retval == SUCCESS);
				
					
					
					
				
				else
					
					
					
					    (entryIndex);
					
#ifdef CONFIG_PROC_FS
					    mcastDelOpCnt6++;
					
#endif /* 
					}
				
						inuseList.mCastTbl[entryIndex],
						select_t, nextMCast);
				
						   inuseList.mCastTbl
						   [entryIndex], select_t,
						   nextMCast);
				
			
#if 0
			    else
				
				
				    //printk("swapOutEntry:%d,select:%d,[%s]:[%d].\n",swapOutEntry->unKnownMCast,select_t->unKnownMCast,__FUNCTION__,__LINE__);
				    if (swapOutEntry->inAsic == FALSE)
					
					
					    /*maybe something is wrong, we remove the asic entry */ 
					    rtl8651_delAsicIpMulticastTable
					    (entryIndex);
					
#ifdef CONFIG_PROC_FS
					    mcastDelOpCnt6++;
					
#endif /* 
					}
				
			
#endif /* 
			
		
	
	else
		
		
			
			
			
		
		
#ifdef CONFIG_PROC_FS
		    mcastDelOpCnt6++;
		
#endif /* 
		}



{
	
	
	
	
	
	    //printk("[%s:%d]\n",__FUNCTION__,__LINE__);
	    /* check to Aging and HW swapping */ 
	    for (entry = 0; entry < RTL8651_MULTICASTTBL_SIZE; entry++) {
		
		
		
		
			
			    /*save the next entry first */ 
			    nextMCast_t = TAILQ_NEXT(mCast_t, nextMCast);
			
				
				
				    /* Entry is in the ASIC */ 
				    if (mCast_t->age <= secPassed)
					
					
						
						
						    (mCast_t, entry);
						
						
					
					else
						
						
						    RTL865X_MULTICAST_TABLE_AGE;
						
					
				
				else
					
					
					
				
			
			else
				
				
				    //printk("------------mCast_t->count:%d,[%s]:[%d].\n",mCast_t->count,__FUNCTION__,__LINE__);
				    
				    //mCast_t->count=0;
				    
				    /* Entry is not in the ASIC */ 
				    if (mCast_t->age <= secPassed)
					
					
								    entry);
					
				
				else
					
					
					
				
			
			    /*won't count multicast entry forwarded by cpu */ 
			    if (mCast_t->cpu == 0)
				
				
				
				    //printk("------------hashLineCnt:%d,[%s]:[%d].\n",hashLineCnt,__FUNCTION__,__LINE__);
				    if (hashLineCnt >= 2)
					
					
					
				
			
			    //mCast_t->count = 0;
			    mCast_t = nextMCast_t;
		
		
			
			
			    //printk("------------entry:%d,hashLineCnt:%d,[%s]:[%d].\n",entry,hashLineCnt,__FUNCTION__,__LINE__);
			    _rtl8198C_arrangeMulticastv6(entry);
			
		
		
			
			    /*save the next entry first */ 
			    nextMCast_t = TAILQ_NEXT(mCast_t, nextMCast);
			
				
			
		
	



#if defined(__linux__) && defined(__KERNEL__)
static void _rtl8198C_mCastv6SysTimerExpired(uint32 expireDada) 
{
	
	

{
	
	
	
	
	    (void *)_rtl8198C_mCastv6SysTimerExpired;
	

{
	

#endif /* 
    
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)

{
	
	
		index < RTL8651_MULTICASTTBL_SIZE; index++)
		
		
			
			
			
		
	



#endif /* 

{
	
	
	
		       rtl8198c_mcast_fwd_descriptor6_t,
		       MAX_MCASTV6_FWD_DESCRIPTOR_CNT);
	
		
		
			MAX_MCASTV6_FWD_DESCRIPTOR_CNT *
			sizeof(rtl8198c_mcast_fwd_descriptor6_t));
		
	
	else
		
		
		
	
		
		
				     &rtl8198c_mcastFwdDescPool6[i], next);
		
	



								 hashIndex) 
{
	
	
	
		
		
		
	
	
	    /*initialize it */ 
	    if (MC_LIST_FIRST(&newEntry->fwdDescChain) != NULL)
		
		
		
	
	
	
			     nextMCast);
	



						   * targetChainHead,
						   
						   rtl8198c_mcast_fwd_descriptor6_t
						   * srcChain) 
{
	
	
		
		
		
	
		curDesc = MC_LIST_NEXT(curDesc, next))
		
		
		
	



_rtl8198C_doMCastv6EntrySrcVlanPortFilter(rtl8198c_tblDrv_mCastv6_t *
					  mCastEntry) 
{
	
	
		
		
		
	
		curDesc != NULL; curDesc = nextDesc)
		
		
		
			
			    curDesc->fwdPortMask & (~(1 << mCastEntry->port));
			
				
				
				    /*remove from the old chain */ 
				    MC_LIST_REMOVE(curDesc, next);
				
				    /*return to the free descriptor chain */ 
				    _rtl8198C_freeMCastv6FwdDesc(curDesc);
				
		
		
	



						       * mCastEntry) 
{
	
	
	
		
		
		
	
		
			
			
			    (curDesc->fwdPortMask &
			     ((1 << RTL8651_MAC_NUMBER) - 1));
			
		
		else
			
			
			
	
	
	



						 mCastEntry) 
{
	
	
	
		
		
		
	
		
		
		
	
		
		     (memcmp(curDesc->netifName, RTL_WLAN_NAME, 4) == 0))
			
			
			
	
	



{
	
	
	      index++) {
		
						      (rtl865x_externalMulticastPortMask
						       & (1 << index)) ? FALSE :
						      TRUE);
	



{
	
	
	
	
	
	
	    /*free unused software forward entry */ 
	    for (index = 0; index < RTL8651_MULTICASTTBL_SIZE; index++)
		
		
		    TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[index]);
		
			
			
			
			     && (curMCastEntry->count == 0))
				
				
							    index);
				
				
			
			
		
	
		
		
		
	
		
		
		    TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[index]);
		
		
			
			
			
				
				
				    rtl8198C_genMCastv6EntryAsicFwdMask
				    (curMCastEntry);
				
					
					
					    (curMCastEntry, index);
					
					
				
			
			
		
			
			
			
		
	



						 mCast_t) 
{
	
	
	
	    /* patch: keep cache in software if one vlan's interface is pppoe */ 
	    MC_LIST_FOREACH(curDesc, &(mCast_t->fwdDescChain), next) 
		
		     SUCCESS)
			
			
			    /*how about pptp,l2tp? */ 
			    if (netifType == IF_PPPOE)
				
				
				    RTL865X_MULTICAST_PPPOEPATCH_CPUBIT;
				
				
			
	
	



//static 
    uint32 rtl8198C_getMCastv6EntryDescPortMask(rtl8198c_tblDrv_mCastv6_t *
						mCastEntry) 
{
	
	
	
		
		
		
	
		
	
	



{
	
#if defined (CONFIG_RTL_MLD_SNOOPING)
	    inv6_addr_t groupAddr;
	
	
#if !defined(CONFIG_RTL_MULTI_LAN_DEV)
	    uint32 oldDescPortMask;
	
#if !defined(CONFIG_RT_MULTIPLE_BR_SUPPOR)
	    uint32 newDescPortMask;	/*for device decriptor forwarding usage */
	
#endif /* 
#endif /* 
	    uint32 oldAsicFwdPortMask, newAsicFwdPortMask;	/*for physical port forwarding usage */
	
	
	
	
	
	
	
#if !defined(CONFIG_RTL_MULTI_LAN_DEV) && !defined(CONFIG_RT_MULTIPLE_BR_SUPPORT)
	struct rtl_multicastDeviceInfo_s bridgeMCastDev;
	
#endif /* 
#ifdef CONFIG_RTL_MLD_SNOOPING
	struct rtl_groupInfo groupInfo;
	
#endif /* 
	    
#if defined(CONFIG_RT_MULTIPLE_BR_SUPPORT)
	unsigned char br_name[16] = { 0 };
	
	
#if defined(CONFIG_RTL_MULTI_LAN_DEV)
	struct net_bridge *br_dev = NULL;
	
#else /* 
	unsigned int br_moduleIndex = 0xFFFFFFFF;
	
#endif /* 
#endif /* 
	    int32 retVal = FAILED;
	
		
		
		
	
	
	    /*check device name's validity */ 
	    if (strlen(mcastEventContext.devName) == 0)
		
		
		
	
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
	    printk
	    ("%s:%d,mcastEventContext.devName is %s, mcastEventContext.groupAddr is 0x%x,mcastEventContext.sourceIP is 0x%x,mcastEventContext.portMask is 0x%x\n",
	     __FUNCTION__, __LINE__, mcastEventContext.devName,
	     mcastEventContext.groupAddr[0], mcastEventContext.sourceAddr[0],
	     mcastEventContext.portMask);
	
#endif /* 
	    bzero(&groupAddr, sizeof(inv6_addr_t));
	
	
	    /*case 1:this is multicast event from bridge(br0) */ 
	    /*sync wlan and ethernet */ 
	    //hyking:[Fix me] the RTL_BR_NAME...
#if !defined(CONFIG_RTL_MULTI_LAN_DEV)
#if defined(CONFIG_OPENWRT_SDK)
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 6) == 0
		|| memcmp(mcastEventContext.devName, RTL_BR1_NAME, 3) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 6) == 0)
		
#endif /* 
#else /* 
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 3) == 0
		|| memcmp(mcastEventContext.devName, RTL_BR1_NAME, 3) == 0)
		
#elif defined(CONFIG_RT_MULTIPLE_BR_SUPPORT)
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 2) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 3) == 0)
		
#endif /* 
#endif /* 
	{
		
			
			
			      TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
				     (mCastEntry->dip, groupAddr))
					
					
					
				
						      mCastEntry->dip,
						      &groupInfo);
				
					
					
					
				
				else
					
					
					
				
				    rtl8198C_getMCastv6EntryDescPortMask
				    (mCastEntry);
				
				    /*sync with control plane */ 
#if defined CONFIG_RT_MULTIPLE_BR_SUPPORT
				    oldCpuFlag = mCastEntry->cpu;
				
				
				
					br_index < RTL_IMGP_MAX_BRMODULE;
					br_index++)
					
					
					    rtl_get_brIgmpModuleIndexbyId
					    (br_index, br_name);
					
						
					
					    /*sync with control plane */ 
					    memset(&newFwdDesc, 0,
						   sizeof
						   (rtl8198c_mcast_fwd_descriptor6_t));
					
					
					
						&mCastEntry->sip,
						sizeof(struct inv6_addr_s));
					
						&mCastEntry->dip,
						sizeof(struct inv6_addr_s));
					
					    rtl_getMulticastDataFwdInfo
					    (br_moduleIndex, &multicastDataInfo,
					     &multicastFwdInfo);
					
						
						
						    multicastFwdInfo.cpuFlag;
						
					
				
					
				
					
					
								    index);
					
					
				
				    //printk("br:%s :oldAsicPortMask:%x,newAsicPortMask:%x,oldCpuFlag:%d,newCpuFlag:%d,[%s]:[%d].\n",devName,oldAsicPortMask,newAsicPortMask,oldCpuFlag,newCpuFlag,__FUNCTION__,__LINE__);
#else /* 
				    memset(&newFwdDesc, 0,
					   sizeof
					   (rtl8198c_mcast_fwd_descriptor6_t));
				
					mcastEventContext.devName);
				
				
					&mCastEntry->sip, sizeof(inv6_addr_t));
				
					&mCastEntry->dip, sizeof(inv6_addr_t));
				
				    rtl_getMulticastDataFwdInfo
				    (mcastEventContext.moduleIndex,
				     &multicastDataInfo, &multicastFwdInfo);
				
					
					
					
				
				    rtl_getIgmpSnoopingModuleDevInfo
				    (mcastEventContext.moduleIndex,
				     &bridgeMCastDev);
				
					
					
					
				
				
				     (((newDescPortMask &
					bridgeMCastDev.swPortMask) != 0)
				      ||
				      
					  bridgeMCastDev.swPortMask) != 0)
					&&
					((newDescPortMask &
					  bridgeMCastDev.swPortMask) == 0))))
					
					
					    /*this multicast entry should be re-generated at linux protocol stack bridge level */ 
					    _rtl8198C_freeMCastv6Entry
					    (mCastEntry, index);
					
					
				
#endif /* 
				
			
		
	
	
	    /*case 2:this is multicast event from ethernet (eth0) */ 
	    /*update ethernet forwarding port mask */ 
	    
#ifdef CONFIG_RTK_VLAN_WAN_TAG_SUPPORT
	    if (memcmp(mcastEventContext.devName, "eth*", 4) == 0
		|| memcmp(mcastEventContext.devName, RTL_PS_ETH_NAME_ETH2,
			  4) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, "eth*", 4) == 0)
		
#endif /* 
		    
		
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
		    printk
		    ("%s:%d,multicast event from ethernet (%s),mcastEventContext.groupAddr[0] is 0x%x\n",
		     __FUNCTION__, __LINE__, mcastEventContext.devName,
		     mcastEventContext.groupAddr[0]);
		
#endif /* 
		    
			
			
			      TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
#if	0				
				    printk
				    ("mCastEntry->dip:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
				     
				     mCastEntry->dip.v6_addr16[1],
				     
				     mCastEntry->dip.v6_addr16[3],
				     
				     mCastEntry->dip.v6_addr16[5],
				     
				     mCastEntry->dip.v6_addr16[7]);
				
				    ("groupAddr:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
				     
				     groupAddr.v6_addr16[1],
				     
				     groupAddr.v6_addr16[3],
				     
				     groupAddr.v6_addr16[5],
				     
				     groupAddr.v6_addr16[7]);
				
#endif /* 
				    if (!is_ip6_addr_equal
					(mCastEntry->dip, groupAddr))
					
					
					
				
					  sizeof
					  (rtl8198c_mcast_fwd_descriptor6_t));
				
					mcastEventContext.devName);
				
				    /*save old multicast entry forward port mask */ 
				    oldAsicFwdPortMask = mCastEntry->mbr;
				
				
				    /*sync with control plane */ 
				    multicastDataInfo.ipVersion = 6;
				
					&mCastEntry->sip, sizeof(inv6_addr_t));
				
					&mCastEntry->dip, sizeof(inv6_addr_t));
				
				    rtl_getMulticastDataFwdInfo
				    (mcastEventContext.moduleIndex,
				     &multicastDataInfo, &multicastFwdInfo);
				
					
				
				    multicastFwdInfo.fwdPortMask &
				    (~(1 << mCastEntry->port));
				
				
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
				    newFwdDesc.fwdPortMask &=
				    mCastEntry->mapPortMbr;
				
#endif /* 
				    
				    /*update/replace old forward descriptor */ 
				    
				    (&mCastEntry->fwdDescChain, &newFwdDesc);
				
				    rtl8198C_genMCastv6EntryAsicFwdMask
				    (mCastEntry);
				
				    rtl8198C_genMCastv6EntryCpuFlag(mCastEntry);
				
				
				
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
				    printk
				    ("%s:%d,oldAsicFwdPortMask is %d,newAsicFwdPortMask is %d\n",
				     __FUNCTION__, __LINE__, oldAsicFwdPortMask,
				     newAsicFwdPortMask);
				
#endif /* 
				    
#ifndef RTL8651_MCAST_ALWAYS2UPSTREAM
				    if (mCastEntry->flag &
					RTL865X_MULTICAST_UPLOADONLY)
					
					
					     && (newAsicFwdPortMask !=
						 oldAsicFwdPortMask))
						
						
						    ~RTL865X_MULTICAST_UPLOADONLY;
						
						    /* we assume multicast member will NEVER in External interface, so we remove
						       external ip now */ 
						    mCastEntry->flag &=
						    ~RTL865X_MULTICAST_EXTIP_SET;
						
					
				
#endif	/* RTL8651_MCAST_ALWAYS2UPSTREAM */
#ifdef CONFIG_RTL_MLD_SNOOPING	
				    rtl_getGroupInfov6((uint32 *) &
						       mCastEntry->dip,
						       &groupInfo);
				
					
					
					
				
				else
					
					
					
				
#endif /* 
				    if ((oldCpuFlag != newCpuFlag)
					|| (newAsicFwdPortMask !=
					    oldAsicFwdPortMask))
					
					
					
					    /*reset inAsic flag to re-select or re-write this hardware asic entry */ 
					    if (newAsicFwdPortMask == 0)
						
						
						    (mCastEntry, index);
						
					
					
				
			
		
	
#else	/*CONFIG_RTL_MULTI_LAN_DEV*/
#if defined (CONFIG_RT_MULTIPLE_BR_SUPPORT)
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 2) == 0)
		
#else /* 
	    if (memcmp(mcastEventContext.devName, RTL_BR_NAME, 3) == 0)
		
#endif /* 
		    
		
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
		    printk
		    ("%s:%d,multicast event from ethernet (%s),mcastEventContext.groupAddr[0] is 0x%x\n",
		     __FUNCTION__, __LINE__, mcastEventContext.devName,
		     mcastEventContext.groupAddr[0]);
		
#endif /* 
		    
			
			
			      TAILQ_FIRST(&mCastTbl6.inuseList.mCastTbl[index]);
			      mCastEntry; mCastEntry = nextMCastEntry)
				
				
				    TAILQ_NEXT(mCastEntry, nextMCast);
				
#if	0				
				    printk
				    ("mCastEntry->dip:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
				     
				     mCastEntry->dip.v6_addr16[1],
				     
				     mCastEntry->dip.v6_addr16[3],
				     
				     mCastEntry->dip.v6_addr16[5],
				     
				     mCastEntry->dip.v6_addr16[7]);
				
				    ("groupAddr:%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x\n",
				     
				     groupAddr.v6_addr16[1],
				     
				     groupAddr.v6_addr16[3],
				     
				     groupAddr.v6_addr16[5],
				     
				     groupAddr.v6_addr16[7]);
				
#endif /* 
				    if (!is_ip6_addr_equal
					(mCastEntry->dip, groupAddr))
					
					
					
				
					  sizeof
					  (rtl8198c_mcast_fwd_descriptor6_t));
				
					mcastEventContext.devName);
				
				    /*save old multicast entry forward port mask */ 
				    oldAsicFwdPortMask = mCastEntry->mbr;
				
				
				    /*sync with control plane */ 
				    multicastDataInfo.ipVersion = 6;
				
					&mCastEntry->sip, sizeof(inv6_addr_t));
				
					&mCastEntry->dip, sizeof(inv6_addr_t));
				
				    rtl_getMulticastDataFwdInfo
				    (mcastEventContext.moduleIndex,
				     &multicastDataInfo, &multicastFwdInfo);
				
					
				
#if defined CONFIG_RT_MULTIPLE_BR_SUPPORT
				    br_dev = NULL;
				
				      br_index < RTL_IMGP_MAX_BRMODULE;
				      br_index++)
					
					
					    rtl_get_brByIndex(br_index,
							      br_name);
					
					     (br_name,
					      mcastEventContext.devName) == 0)
						
					
				
					
				
				    rtl865x_getPhyFwdPortMask(br_dev,
							      multicastFwdInfo.fwdPortMask)
				    & (~(1 << mCastEntry->port));
				
#else /* 
				    newFwdDesc.fwdPortMask =
				    rtl865x_getPhyFwdPortMask(bridge0,
							      multicastFwdInfo.fwdPortMask)
				    & (~(1 << mCastEntry->port));
				
#endif /* 
				    newFwdDesc.toCpu = multicastFwdInfo.cpuFlag;
				
				    /*update/replace old forward descriptor */ 
				    
				    (&mCastEntry->fwdDescChain, &newFwdDesc);
				
				    rtl8198C_genMCastv6EntryAsicFwdMask
				    (mCastEntry);
				
				    rtl8198C_genMCastv6EntryCpuFlag(mCastEntry);
				
				
				
#ifdef CONFIG_RTL865X_MUTLICAST_DEBUG
				    printk
				    ("%s:%d,oldAsicFwdPortMask is %d,newAsicFwdPortMask is %d\n",
				     __FUNCTION__, __LINE__, oldAsicFwdPortMask,
				     newAsicFwdPortMask);
				
#endif /* 
				    
#ifndef RTL8651_MCAST_ALWAYS2UPSTREAM
				    if (mCastEntry->flag &
					RTL865X_MULTICAST_UPLOADONLY)
					
					
					     && (newAsicFwdPortMask !=
						 oldAsicFwdPortMask))
						
						
						    ~RTL865X_MULTICAST_UPLOADONLY;
						
						    /* we assume multicast member will NEVER in External interface, so we remove
						       external ip now */ 
						    mCastEntry->flag &=
						    ~RTL865X_MULTICAST_EXTIP_SET;
						
					
				
#endif	/* RTL8651_MCAST_ALWAYS2UPSTREAM */
#ifdef CONFIG_RTL_MLD_SNOOPING	
				    rtl_getGroupInfov6((uint32 *) &
						       mCastEntry->dip,
						       &groupInfo);
				
					
					
					
				
				else
					
					
					
				
#endif /* 
				    
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
				    newAsicFwdPortMask &=
				    (mCastEntry->mapPortMbr | (0x01 << 6));
				
#endif /* 
				    
					 || (newAsicFwdPortMask !=
					     oldAsicFwdPortMask))
					
					
					
					    /*reset inAsic flag to re-select or re-write this hardware asic entry */ 
					    if (newAsicFwdPortMask == 0)
						
						
						    (mCastEntry, index);
						
					
					
				
			
		
	
#endif /* 
#endif /* 
	    return EVENT_CONTINUE_EXECUTE;



{
	
	
	
	
	
	
	



{
	
	
	
	
	
	
	



{
	
	
	
	
#if defined(__linux__) && defined(__KERNEL__)
	    _rtl8198C_initMCastv6SysTimer();
	
#endif /* 
	    _rtl8198C_multicastv6RegisterEvent();
	
	
	
	



{
	
	
	
	    /*delete all multicast entry */ 
	    rtl8198C_setAsicMulticastv6Enable(FALSE);
	
	
	
#if defined(__linux__) && defined(__KERNEL__)
	    _rtl8198C_destroyMCastv6SysTimer();
	
	
#endif /* 
	    
	    /*regfster twice won't cause any side-effect, 
	       because event management module will handle duplicate event issue */ 
	    
	
	
	



{
	
	
	



{
	
	
	



{
	
	
	



{
	
	
	



{
	
	
	



{
	



							 inv6_addr_t sip,
							 uint16 svid,
							 uint16 sport) 
{
	
	
	
	
	
	
		
		     && is_ip6_addr_equal(mCast_t->sip, sip)
		     && mCast_t->port == sport)
			
			
				
				
				
				
			
			
	
	
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    for (entry = RTL8651_IPMULTICASTTBL_SIZE;
		 entry < RTL8651_MULTICASTTBL_SIZE; entry++)
		
		
			       nextMCast) {
			
			     && is_ip6_addr_equal(mCast_t->sip, sip)
			     && mCast_t->port == sport)
				
				
					
					
					    RTL865X_MULTICAST_TABLE_AGE;
					
					
				
				
		
		
	
#endif /* 
	    return (rtl8198c_tblDrv_mCastv6_t *) NULL;



#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
int rtl8198C_addMulticastv6Entry(inv6_addr_t dip, inv6_addr_t sip,
				 unsigned short svid, unsigned short sport,
				 
				 newFwdDescChain, 
				 unsigned int extIp, char cpuHold,
				 unsigned char flag,
				 unsigned int mapPortMask) 
#else /* 
int rtl8198C_addMulticastv6Entry(inv6_addr_t dip, inv6_addr_t sip,
				 unsigned short svid, unsigned short sport,
				 
				 newFwdDescChain, 
				 unsigned int extIp, char cpuHold,
				 unsigned char flag) 
#endif				/* 
{
	
	
	
#ifdef CONFIG_RTL_MLD_SNOOPING
	    uint32 groupIpAddr[4];
	
#endif /* 
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    uint32 emptyCamIndex = -1;
	
#endif /* 
	    uint32 hashMethod = 0;
	
#if defined (CONFIG_RTL_MLD_SNOOPING)
	struct rtl_groupInfo groupInfo;
	
#endif /* 
	    rtl8198C_getMCastv6HashMethod(&hashMethod);
	
	
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    mCast_t = rtl8198C_findMCastv6Entry(dip, sip, svid, sport);
	
		
		
		    /*table entry collided */ 
		    if (!TAILQ_EMPTY(&mCastTbl6.inuseList.mCastTbl[hashIndex]))
			
			
			
				
				
				
			
		
	
	else
		
		
		
	
#else /* 
	    /*try to match hash line */ 
	    TAILQ_FOREACH(mCast_t, &mCastTbl6.inuseList.mCastTbl[hashIndex],
			  nextMCast) 
		
		     && is_ip6_addr_equal(mCast_t->dip, dip)
		     && mCast_t->port == sport)
			
	
	
#endif /* 
	    
		
		
		
			
			
			
			
				
				
				
			
		
		
		
		
		
		
		
		
		
		
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
		    mCast_t->mapPortMbr = mapPortMask;
		
#endif /* 
		}
	
		
		
		
	
					      newFwdDescChain);
	
	
	
	
#if 0
	    mCast_t->cpu = (toCpu == TRUE ? 1 : 0);
	
#else /* 
	    mCast_t->cpuHold = cpuHold;
	
	
#endif /* 
	    mCast_t->flag = flag;
	
		
	
	else
		
	
#if defined (CONFIG_RTL_MLD_SNOOPING)
	    memcpy(groupIpAddr, &dip, sizeof(inv6_addr_t));
	
	
		
		
		
	
	else
		
		
		
	
#endif /* 
#if defined (CONFIG_RTL_HARDWARE_MULTICAST_CAM)
	    mCast_t->hashIndex = hashIndex;
	
#endif /* 
	    _rtl8198C_patchPppoeWeakv6(mCast_t);
	
	



{
	
	
	
	
		
		
		
		
			
			
			
				
				
				
				
			
			
		
			
			
			
		
	



					     unsigned int fwdPortMask,
					     rtl8198c_mcast_fwd_descriptor6_t *
					     fwdDescriptor) 
{
	
		
		
		
	
	
	
	



#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
int rtl8198C_blockMulticastv6Flow(unsigned int srcVlanId, unsigned int srcPort,
				  inv6_addr_t srcIpAddr, inv6_addr_t destIpAddr,
				  unsigned int mapPortMask) 
#else /* 
int rtl8198C_blockMulticastv6Flow(unsigned int srcVlanId, unsigned int srcPort,
				  inv6_addr_t srcIpAddr,
				  inv6_addr_t destIpAddr) 
#endif				/* 
{
	
	
	
	    rtl8198C_findMCastv6Entry(destIpAddr, srcIpAddr, (uint16) srcVlanId,
				      (uint16) srcPort);
	
		
		
			
			
			
		
	
	
#if defined CONFIG_RTL_MULTICAST_PORT_MAPPING
	    rtl8198C_addMulticastv6Entry(destIpAddr, srcIpAddr,
					 (unsigned short)srcVlanId,
					 (unsigned short)srcPort,
					 &fwdDescriptor, TRUE, 0, 0, 0,
					 mapPortMask);
	
#else /* 
	    rtl8198C_addMulticastv6Entry(destIpAddr, srcIpAddr,
					 (unsigned short)srcVlanId,
					 (unsigned short)srcPort,
					 &fwdDescriptor, TRUE, 0, 0, 0);
	
#endif /* 
	    return SUCCESS;



{
	
	
	
	
	
		
		
		
			
			
			
				
				
				
				
			
			
		
	



{
	



{
	
	
	
		
		
		
	
	
		
		
		
		    /* exclude 0->1 and 1->0 */ 
		    if (!
			((hashMethod == HASH_METHOD_SIP_DIP0
			  && oldHashMethod == HASH_METHOD_SIP_DIP1)
			 || 
			      && oldHashMethod == HASH_METHOD_SIP_DIP0)))
			
			
			
		
	



#endif /* 
    