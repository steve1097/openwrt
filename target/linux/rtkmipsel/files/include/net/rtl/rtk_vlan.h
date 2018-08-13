/*
 *      Headler file of Realtek VLAN
 *
 *      $Id: rtk_vlan.h,v 1.3 2009/06/01 07:00:27 davidhsu Exp $
 */  
    
#ifndef _RTK_VLAN_H
#define _RTK_VLAN_H
    
// to_be_checked !!!
#if !defined(CONFIG_RTL_8198C) && !defined(CONFIG_RTL_8197F)
#include "rtl_types.h"
#endif	/* 
//#define CONFIG_PPPOE_VLANTAG 1
    
#if	defined (CONFIG_PPPOE_VLANTAG)
#define COPY_TAG(tag, info) { \
    tag.f.tpid = htons(ETH_P_8021Q);
\
			       ((((unsigned char)info->
				  cfi) & 0x1) << 12) | ((unsigned short)info->
							id & 0xfff));
\
\

#define STRIP_TAG(skb) { \
    memmove(skb->data + VLAN_HLEN, skb->data, ETH_ALEN * 2);
\
\
#endif	/* 
    
	
	int is_lan;		// 1: eth-lan/wlan port, 0: wan port
	int vlan;		// 0/1: disable/enable vlan
	int tag;		// 0/1: disable/enable tagging
	int id;			// 1~4090: vlan id
	int pri;		// 0~7: priority;
	int cfi;		// 0/1: cfi
//#if defined(CONFIG_RTK_BRIDGE_VLAN_SUPPORT) //mark_hwv
	int forwarding_rule;	// 0:disabled/1: bridge/2:NAT
	int index;
	
//#endif
};

	
	unsigned short pci;	// priority:3, cfi:1, id:12
};

	
		
		
	


#if defined(CONFIG_RTK_BRIDGE_VLAN_SUPPORT)
extern struct vlan_info management_vlan;


	
	





#endif	/* 
    
#ifdef CONFIG_RTL_HW_VLAN_SUPPORT
#define CONFIG_RTL_HW_VLAN_SUPPORT_HW_NAT
#endif	/* 
    
#if defined(CONFIG_RTL_HW_STP)
unsigned int rtl865x_getVlanPortMask(unsigned int vid);

#endif	/* 
    
#endif // _RTK_VLAN_H