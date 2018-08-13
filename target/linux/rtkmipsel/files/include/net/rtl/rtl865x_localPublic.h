#ifndef RTL865X_LOCAL_PUBLIC_H
#define RTL865X_LOCAL_PUBLIC_H

#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
#include <common/rtl865x_netif.h>
#endif	/* 
    
#define FROM_LOCAL_PUBLIC	1
#define TO_LOCAL_PUBLIC		2	
#define RX_LAN_PACKET	1
#define RX_WAN_PACKET	2
#define TX_LAN_PACKET	3
#define TX_WAN_PACKET	4
    
#define MAX_HW_LOCAL_PUBLIC_NUM 2
#define DEF_LOCAL_PUBLIC_NUM	32
#define MAX_LOCAL_PUBLIC_NUM	32
    
#define LOCAL_PUBLIC_VLAN_START 	3198
#define LOCAL_PUBLIC_VLAN_END		4094
#define MCAST_NETIF_VLAN_ID		3197	

	
	
	
	
	
	
	
	
	
	
	
	
	    //must at the tail...
	struct 
		
		
	


#if defined(CONFIG_RTL_PUBLIC_SSID)
struct rtl865x_public_ssid_entry 
	
	
	


#endif	/* 

	
	    /*input parameter */ 
	unsigned char *data;
	
	
	
	
	    /*output parameter */ 
	unsigned char *arpHdr;
	
	
	
	
	


	


	
	
	
	
	
	
	
	








				  struct rtl865x_localPublic *localPublicInfo);



			       int arraySize);

#if defined(CONFIG_RTL_HW_QOS_SUPPORT)
int rtl_checkLocalPublicNetifIngressRule(rtl865x_AclRule_t * rule);

#endif	/* 
#if defined(CONFIG_RTL_PUBLIC_SSID)
int rtl865x_is_public_ssid_entry(unsigned int ipAddr);


#endif	/* 


#endif	/* 