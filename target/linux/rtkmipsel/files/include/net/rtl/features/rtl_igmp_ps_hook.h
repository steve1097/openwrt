#ifndef	RTL_IGMP_PS_HOOKS_H
#define	RTL_IGMP_PS_HOOKS_H		1

#include <net/rtl/rtl_types.h>
#include <linux/mroute.h>
    
/*macro*/ 
#define MULTICAST_MAC(mac) 	   ((mac[0]==0x01)&&(mac[1]==0x00)&&(mac[2]==0x5e))
#define DEBUG_PRINT(fmt, args...)
//#define DBG_ICMPv6
#define MCAST_TO_UNICAST
#define IGMP_EXPIRE_TIME (260*HZ)
#define M2U_DELAY_DELETE_TIME (10*HZ)
#if defined (CONFIG_RTL_MLD_SNOOPING)
#define IPV6_MULTICAST_MAC(mac) ((mac[0]==0x33)&&(mac[1]==0x33) && mac[2]!=0xff)
#if defined (MCAST_TO_UNICAST)
#define IPV6_MCAST_TO_UNICAST
#endif	/* 
#define IN6_IS_ADDR_MULTICAST(a) (((__u8 *) (a))[0] == 0xff)
#endif	/*CONFIG_RTL_MLD_SNOOPING*/
    
#define MCAST_QUERY_INTERVAL 30
    
#if defined (CONFIG_RTL_QUERIER_SELECTION)
#define MAX_QUERIER_RECORD 8
#define QUERIER_EXPIRED_TIME 255
#define HOP_BY_HOP_OPTIONS_HEADER 0
#define ROUTING_HEADER 43
#define FRAGMENT_HEADER 44
#define DESTINATION_OPTION_HEADER 60
#define NO_NEXT_HEADER 59
#define ICMP_PROTOCOL 58
#define IPV4_ROUTER_ALTER_OPTION 0x94040000
#define IPV6_ROUTER_ALTER_OPTION 0x05020000
#define IPV6_HEADER_LENGTH 40
#define MLD_QUERY 130
#define MLDV1_REPORT 131
#define MLDV1_DONE 132
#define MLDV2_REPORT 143
#define S_FLAG_MASK 0x08
#endif	/* 
    
#define MAX_UNKNOWN_MULTICAST_NUM 16
//#define MAX_UNKNOWN_MULTICAST_PPS 1500
#define BLOCK_UNKNOWN_MULTICAST 1
    
/*struct*/ 
#if defined (CONFIG_RTL_QUERIER_SELECTION)
struct querierInfo 
	
	
	
	


#endif	/* 

	
	
	
	


#if defined(CONFIG_RTL_IGMP_PROXY)
    struct mr_table {
	
	
#ifdef CONFIG_NET_NS
	struct net *net;
	
#endif	/* 
	 u32 id;
	
	
	
	
	
	
	
	
	
	
#if defined(CONFIG_IP_PIMSM_V1) || defined(CONFIG_IP_PIMSM_V2)
	int mroute_reg_vif_num;
	
#endif	/* 
};

#endif	/* 
    
/*prototype*/ 
void rtl_br_forward(const struct net_bridge_port *to, struct sk_buff *skb);

			const struct sk_buff *skb);





			  struct net_bridge_fdb_entry *f);

#if defined (CONFIG_RTL_MLD_SNOOPING)
int re865x_getIpv6TransportProtocol(struct ipv6hdr *ipv6h);

#endif	/* 
    int32 rtl_getGroupNum(uint32 ipVersion);

#if defined (CONFIG_NETFILTER)
extern unsigned int (*IgmpRxFilter_Hook) (struct sk_buff * skb,
					  
					  
					  
					  

#endif	/* 
int rtl_check_ReservedMCastAddr(uint32 groupAddr);

#if defined(CONFIG_RTL_IGMP_PROXY)
struct mr_table *rtl_ipmr_get_table(struct net *net, u32 id);


				       __be32 mcastgrp);


#endif	/* 



				  const unsigned char *dest,
				  struct sk_buff *skb);

			       struct net_bridge_fdb_entry *f);




				 struct sk_buff *skb2);

#if defined (CONFIG_RTL_HARDWARE_MULTICAST)
int rtl865x_HwMcast_Setting_HOOK(struct net_bridge *br, struct net_device *dev);


#endif	/* 
struct net_bridge_port *rtl_maybe_deliver(struct net_bridge_port *prev,
					  struct net_bridge_port *p,
					  struct sk_buff *skb,
					  void (*__packet_hook) (const struct
								 net_bridge_port
								 * p,
								 struct sk_buff
								 * skb));

		       void (*__packet_hook) (const struct net_bridge_port * p,
					      struct sk_buff * skb));

/*inline*/ 
static inline bool is_allF_ether_addr(const u8 * addr) 
{
	
		 && (addr[3] == 0xff) && (addr[4] == 0xff)
		 && (addr[5] == 0xff));



{
	
		 && (addr[3] == 0xff) && (addr[4] == 0xff)
		 && (addr[5] == 0xff));



{
	



/*for test*/ 
//#define IGMP_DEBUG
//#define TEST_PACKETS(mac) (mac[0]==0x01 && mac[1]==0x00 && mac[2]==0x5e && mac[3]==0x01 && mac[4]==0x02 && mac[5]==0x03)
//#define TEST_V6PACKETS(mac)(mac[0]==0x33 && mac[1]==0x33 && mac[2]==0x00 && mac[3]==0x00 && mac[4]==0x00 && mac[5]==0x01)
    
#endif	/* 