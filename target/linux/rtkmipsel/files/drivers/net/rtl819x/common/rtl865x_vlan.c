/*
* Copyright c                  Realtek Semiconductor Corporation, 2008  
* All rights reserved.
* 
* Program : Vlan driver
* Abstract : 
* Author : hyking (hyking_liu@realsil.com.cn)  
*/  
#include <net/rtl/rtl_types.h>
#include <net/rtl/rtl_glue.h>
#include "rtl_errno.h"
//#include "rtl_utils.h"
//#include "rtl_glue.h"
#include "rtl865x_vlan.h"
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include "AsicDriver/rtl865x_asicCom.h"
#else /* 
#include "AsicDriver/rtl865xC_tblAsicDrv.h"
#endif /* 
#include "rtl865x_eventMgr.h"


#include <linux/version.h>
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,2,0)
static RTL_DECLARE_MUTEX(vlan_sem);

#endif /* 
static int32 _rtl865x_delVlan(uint16 vid);

				     rtl865x_vlan_entry_t * vlanEntry) 
{
	
	
	
	    /*add this entry to asic table */ 
	    asicEntry.fid = vlanEntry->fid;
	
	
	
#if defined(CONFIG_RTL_8197F)
	    asicEntry.hp = vlanEntry->hp;
	
#endif /* 
	    
	



#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
static rtl865x_vlan_entry_t *rtl_getVlanEntryByVid(uint16 vid) 
{
	
	
	
		
		
			
			
		
		
	



{
	
	
	
		
		
			
			
		
		
	



#endif /* 

{
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
	    
	
		
	
#else /* 
	    
	
#endif /* 
	    
		
	
	



{
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    
	
		
	
#else /* 
	    
	
#endif /* 
	    
		
	
	



{
	
	
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    entry = rtl_findEmptyVlanEntry();
	
		
	
#else /* 
	    entry = &vlanTbl[vid];
	
		
	
#endif /* 
	    
	    /*add new vlan entry */ 
	    memset(entry, 0, sizeof(rtl865x_vlan_entry_t));
	
	
	
	
	    /*add this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, entry);
	



{
	
	
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)		
	    vlanEntry = rtl_getVlanEntryByVid(vid);
	
		
	
#else /* 
	    vlanEntry = &vlanTbl[vid];
	
#endif /* 
	    if (0 == vlanEntry->valid)
		
	
	    /*
	       if(vlanEntry->refCnt > 1)
	       {
	       printk("vid(%d),reference(%d)\n",vid,vlanEntry->refCnt);
	       return RTL_EREFERENCEDBYOTHER;
	       }
	     */ 
	    
	
	    /*delete vlan entry */ 
	    vlanEntry->valid = 0;
	
	    /*ignor other member... */ 
	    
	
		
		
		    /*if vlan entry is deleted, this information should be noticed by uplayer module */ 
#if 0
		    do_eventAction(EV_DEL_VLAN, (void *)&org);
		
#else /* 
		    rtl865x_raiseEvent(EVENT_DEL_VLAN, (void *)&org);
		
#endif /* 
		}
	



{
	
	
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    vlanEntry = rtl_getVlanEntryByVid(vid);
	
		
	
#else /* 
	    vlanEntry = &vlanTbl[vid];
	
#endif /* 
	    if (vlanEntry->valid == 0)
		
	
	    /*add member port */ 
	    vlanEntry->memberPortMask |= portMask;
	
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



					    uint32 untagPortMask) 
{
	
	
	
	
		
	
	    /*add member port */ 
	    vlanEntry->memberPortMask = portMask;
	
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



				    uint32 untagPortMask) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



{
	
	
	
	    //rtl865x_tblAsicDrv_vlanParam_t asicEntry;
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    vlanEntry = rtl_getVlanEntryByVid(vid);
	
		
	
#else /* 
	    vlanEntry = &vlanTbl[vid];
	
#endif /* 
	    
		
	
	    /*add member port */ 
	    vlanEntry->memberPortMask &= ~portMask;
	
	
		
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



					  uint8 tag) 
{
	
	
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
	    vlanEntry = rtl_getVlanEntryByVid(vid);
	
		
	
#else /* 
	    vlanEntry = &vlanTbl[vid];
	
#endif /* 
	    
		
	
		
		    vlanEntry->memberPortMask & portMask;
	
	else
		
		    ~(vlanEntry->memberPortMask & portMask);
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



{
	
	
	
		
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    vlanEntry = rtl_getVlanEntryByVid(vid);
	
		
	
#else /* 
	    vlanEntry = &vlanTbl[vid];
	
#endif /* 
	    
		
	
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



{
	
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
	    rtl865x_vlan_entry_t * vlanEntry;
	
#endif /* 
	    
		
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
	    
	
		
	
		
#else /* 
	    
		
#endif /* 
	{
		
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
		    *fid = vlanEntry->fid;
		
#else /* 
		    *fid = vlanTbl[vid].fid;
		
#endif /* 
		    retval = SUCCESS;
	
	
	else
		
		
		    /*jwj: Because I may change eth1 netif vid to 1 when CONFIG_RTL_VLAN_BASED_NETIF
		       enabled in rtl_set_wanport_vlanconfig() */ 
#if !defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
#ifndef CONFIG_RTL_IVL_SUPPORT
		extern int rtl865x_curOpMode;
		
			printk("%s(%d):the vlan[%d] is invalid!\n",
			       __FUNCTION__, __LINE__, vid);
		
#endif /* 
#endif /* 
		    retval = FAILED;
		
	



{
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)
	    rtl865x_vlan_entry_t * vlanEntry;
	
		
	
	
	
#else /* 
	    if (vlanTbl[vid].valid == 1)
		
	
	
#endif /* 
}


/*
@func int32 | rtl865x_referVlan | reference a VLAN entry.
@parm uint16 | vid | VLAN ID.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@comm
if a vlan entry is referenced, please call this API.
*/ 
    int32 rtl865x_referVlan(uint16 vid) 
{
	
	
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH_HW(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH_HW(flags);
	



/*
@func int32 | rtl865x_deReferVlan | dereference a VLAN entry.
@parm uint16 | vid | VLAN ID.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@comm
if a vlan entry is dereferenced, please call this API.
NOTE: rtl865x_deReferVlan should be called after rtl865x_referVlan.
*/ 
    int32 rtl865x_deReferVlan(uint16 vid) 
{
	
	
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH_HW(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH_HW(flags);
	



/*
@func int32 | rtl865x_addVlan | Add a VLAN.
@parm uint16 | vid | VLAN ID.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@rvalue RTL_EVLANALREADYEXISTS | Vlan already exists.
*/ 
    int32 rtl865x_addVlan(uint16 vid) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_delVlan | Delete a VLAN.
@parm uint16 | vid | VLAN ID.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@rvalue RTL_EREFERENCEDBYOTHER | the Vlan is referenced by other,please delete releated table entry first.
*/ 
    int32 rtl865x_delVlan(uint16 vid) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_addVlanPortMember | configure vlan member port
@parm uint16 | vid | VLAN ID.
@parm uint32 | portMask | Port mask.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@comm
the parm portMask is the MASK of port. bit0 mapping to physical port 0,bit1 mapping to physical port 1.
*/ 
    int32 rtl865x_addVlanPortMember(uint16 vid, uint32 portMask) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_delVlanPortMember | delete vlan's member port
@parm uint16 | vid | VLAN ID.
@parm uint32 | portMask | Port mask.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@comm
the parm portMask is the MASK of port. bit0 mapping to physical port 0,bit1 mapping to physical port 1.
*/ 
    int32 rtl865x_delVlanPortMember(uint16 vid, uint32 portMask) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func uint32 | rtl865x_getVlanPortMask | get the member portMask of a vlan
@parm uint16 | vid | VLAN ID.
@comm
if the retrun value is zero, it means vlan entry is invalid or no member port in this vlan.
*/ 
    uint32 rtl865x_getVlanPortMask(uint32 vid) 
{
	
	
		
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    
	
		
	
#else /* 
	    
	
#endif /* 
	    if (vlanEntry->valid == 0)
		
	



/*
@func int32 | rtl865x_setVlanPortTag | configure member port vlan tag attribute
@parm uint16 | vid | VLAN ID.
@parm uint32 | portMask | Port mask.
@parm uint8 | portMask | vlantag or untag.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@comm
the parm portMask is the MASK of port. bit0 mapping to physical port 0,bit1 mapping to physical port 1.
parm tag is used to indicated physical port is vlantag or untag. value 1 means vlan tagged, and vlan 0 means vlan untagged.
*/ 
    int32 rtl865x_setVlanPortTag(uint16 vid, uint32 portMask, uint8 tag) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_setVlanFilterDatabase | configure the filter database for a vlan.
@parm uint16 | vid | VLAN ID.
@parm uint32 | fid | filter data base ID.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@rvalue RTL_EINVALIDFID | Invalid filter database ID.
@comm
in realtek 865x, 4 filter databases are support.
if you want to configure SVL for all vlan, please set the fid of vlan is same.
default configure is SVL.
*/ 
    int32 rtl865x_setVlanFilterDatabase(uint16 vid, uint32 fid) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);//Lock resource
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



/*
@func int32 | rtl865x_getVlanFilterDatabaseId | get the vlan's filter database ID.
@parm uint16 | vid | VLAN ID.
@parm uint32 | fid | filter data base ID.
@rvalue SUCCESS | Success.
@rvalue RTL_EINVALIDVLANID | Invalid VLAN ID.
@comm
*/ 
    int32 rtl865x_getVlanFilterDatabaseId(uint16 vid, uint32 * fid) 
{
	
	
	



#if defined(CONFIG_RTL_ISP_MULTI_WAN_SUPPORT)
static int32 _rtl865x_modVlanPortMember(uint16 vid, uint32 portMask,
					uint32 untagset) 
{
	
	
	
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
	    vlanEntry = rtl_getVlanEntryByVid(vid);
	
		
	
#else /* 
	    vlanEntry = &vlanTbl[vid];
	
#endif /* 
	    if (vlanEntry->valid == 0)
		
	
	    /*add member port */ 
	    vlanEntry->memberPortMask = portMask;
	
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



				   uint32 untagset) 
{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if (vid < 1 || vid > VLAN_NUMBER - 1)
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



#endif	/* CONFIG_RTL_ISP_MULTI_WAN_SUPPORT */
    
/*
@func int32 | rtl865x_initVlanTable | initialize vlan table.
@rvalue SUCCESS | Success.
@rvalue FAILED | Failed,system should be reboot.
*/ 
    int32 rtl865x_initVlanTable(void)
{
	
	
	



/*
@func int32 | rtl865x_reinitVlantable | initialize vlan table.
@rvalue SUCCESS | Success.
*/ 
    int32 rtl865x_reinitVlantable(void)
{
	
	
		
		
			
			
#if defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_819XD)	
			    _rtl865x_delVlan(vlanTbl[i].vid);
			
#else /* 
			    _rtl865x_delVlan(i);
			
#endif /* 
			}
		
	



#if defined(CONFIG_RTL_8197F)
static int32 _rtl865x_setVlanHp(uint16 vid, uint8 hp) 
{
	
	
	
	
		
	
	    /*add vid priority */ 
	    vlanEntry->hp = hp;
	
	    /*update this entry to asic table */ 
	    retval = _rtl865x_setAsicVlan(vid, vlanEntry);
	



{
	
	
	
	    /* vid should be legal vlan ID */ 
	    if ((vid < 1) || (vid > VLAN_NUMBER - 1) || (hp < 0) || (hp > 7))
		
	
	    //rtl_down_interruptible(&vlan_sem);
	    SMP_LOCK_ETH(flags);
	
	
	    //rtl_up(&vlan_sem);
	    SMP_UNLOCK_ETH(flags);
	



{
	
	
	    /* vid should be legal vlan ID */ 
	    if ((vid < 1) || (vid > VLAN_NUMBER - 1) || (hp == NULL))
		
	
	
		
	
	



#endif	/* CONFIG_RTL_8197F */
    