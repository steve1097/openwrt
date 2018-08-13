#ifndef RTL865X_ARP_IPV6_API_H
#define RTL865X_ARP_IPV6_API_H

#define RTL8198C_IPV6_ARPTBL_SIZE 256

typedef struct rtl8198c_ipv6_arpMapping_entry_s 
	
	
	
	


	


/*for linux protocol stack sync*/
int32 rtl8198c_addIpv6Arp(inv6_addr_t ip, ether_addr_t * mac);




				  rtl8198c_ipv6_arpMapping_entry_t *
				  arp_mapping);

				       uint32 new_subnetIdx);

#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#if defined(CONFIG_RTL_HW_DSLITE_SUPPORT)
    int32 rtl8198c_dslite_Ipv6ArpMapping(inv6_addr_t ip,
					 rtl8198c_ipv6_arpMapping_entry_t *
					 arp_mapping);

#endif	/* 
#endif	/* 
#endif	/* 
    