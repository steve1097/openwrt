#ifndef	RTL_FEATURES_H
#define	RTL_FEATURES_H		1

#include <linux/version.h>
    
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
#include <linux/seq_file.h>
#include <linux/inetdevice.h>
extern struct proc_dir_entry proc_root;

#endif	/* 




//#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT) || defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
#define IS_CLASSD_ADDR(__ipv4addr__)				((((uint32)(__ipv4addr__)) & 0xf0000000) == 0xe0000000)
#define IS_ALLZERO_ADDR(__ipv4addr__)				((((uint32)(__ipv4addr__)) & 0xffffffff) == 0)
#define IS_BROADCAST_ADDR(__ipv4addr__)			((((uint32)(__ipv4addr__)) & 0xffffffff) == 0xffffffff)
//#endif
    
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
struct tcp_state_hash_head 
	enum tcp_conntrack state;
	
};
struct udp_state_hash_head {
	uint8_t state;
	struct list_head *state_hash;
};

#define UDP_UNREPLY (TCP_CONNTRACK_MAX+1)
#define UDP_ASSURED (TCP_CONNTRACK_MAX+2)

struct DROP_PRORITY {
	u_int8_t state;
	u_int16_t threshold;
};

extern struct tcp_state_hash_head Tcp_State_Hash_Head[];
extern struct udp_state_hash_head Udp_State_Hash_Head[];


	PROT_ICMP,
	PROT_TCP,
	PROT_UDP,
	PROT_MAX
};
#endif	/* 

#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
#if defined(CONFIG_PROC_FS)
extern unsigned long rtl_gc_overflow_timout;


#endif	/* 
void clean_from_lists(void *ct, void *net);


			const struct nf_conntrack_tuple *repl);

			 const struct nf_conntrack_tuple *repl);



#endif	/* 
    
#if defined(CONFIG_RTL_IPTABLES_FAST_PATH)
int rtl_fpTimer_update(void *ct);

#endif	/* 


#ifdef CONFIG_RTL_FAST_IPV6
int rtl_AddV6ConnCache(struct nf_conn *ct, struct sk_buff *skb);



#endif	/* 
    
#if defined(CONFIG_RTL_LOCAL_PUBLIC) || defined(CONFIG_RTL_MULTIPLE_WAN)  ||defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN) || (defined(CONFIG_NET_SCHED)&&defined(CONFIG_RTL_IPTABLES_FAST_PATH)) || defined(CONFIG_RTL_HW_QOS_SUPPORT)
extern struct net_device *rtl865x_getWanDev(void);
extern struct net_device *rtl865x_getLanDev(void);
#endif

#if defined (CONFIG_RTL_LOCAL_PUBLIC) || defined(CONFIG_RTL_HW_QOS_SUPPORT)
extern int rtl865x_attainDevType(unsigned char *devName, unsigned int *isLanDev,
				 unsigned int *isWanDev);
#endif	/* 

#if defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT)
/*2007-12-19*/
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
extern int tcp_get_timeouts_by_state(u_int8_t state, void *ct_or_cp, int is_ct);
#else
extern int tcp_get_timeouts_by_state(u_int8_t state);

#endif
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
extern unsigned int udp_get_timeouts_by_state(enum udp_conntrack state,
					      void *ct_or_cp, int is_ct);

#else
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
extern unsigned int udp_get_timeouts_by_state(enum udp_conntrack state);

#else	/* 
extern unsigned int nf_ct_udp_timeout;
extern unsigned int nf_ct_udp_timeout_stream;

#endif	/* 
#endif
void rtl_check_for_acc(struct nf_conn *ct, unsigned long expires);



#endif	/* 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)
    int32 rtl865x_handle_nat(struct nf_conn *ct, int act, struct sk_buff *skb);


#ifndef CONFIG_RTL_EXT_PORT_SUPPORT
#define CONFIG_RTL_AVOID_ADDING_WLAN_PKT_TO_HW_NAT 1
#endif	/* 
#endif	/* 
    
#if defined(IMPROVE_QOS) && (defined(CONFIG_RTL_IPTABLES_FAST_PATH) || defined(CONFIG_RTL_HARDWARE_NAT))
void rtl_addConnCache(struct nf_conn *ct, struct sk_buff *skb);

#endif	/* 
    
#if defined(CONFIG_RTL_819X)
    int32 rtl_nat_init(void);

#endif	/* 
    
#if defined(CONFIG_NET_SCHED)
extern int gQosEnabled;



#endif	/* 
    
#if defined(CONFIG_RTL_FAST_BRIDGE)
    int32 rtl_fb_add_br_entry(skb) 
#endif	/* 
    
//#define CONFIG_HARDWARE_NAT_DEBUG
    
#if defined(CONFIG_RTL_HARDWARE_NAT)
#if defined(CONFIG_RTL_ISP_MULTI_WAN_SUPPORT)
#define RTL_MULTIPLE_WAN_NUM		16
#else	/* 
#define RTL_MULTIPLE_WAN_NUM		2
#endif	/* 

	unsigned int valid;
	unsigned int ipAddr;
	//struct ipt_entry *masq_entry;
	char ifName[IFNAMSIZ];
} rtl_masq_if;

#endif

#if defined(CONFIG_RTL_HARDWARE_NAT) ||defined(CONFIG_RTL_HARDWARE_IPV6_SUPPORT)
    int32 syn_asic_arp(struct neighbour *n, int add);

#endif	/* 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)
#if defined(CONFIG_RTL_MULTIPLE_WAN) ||defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
    int32 rtl_get_ps_arp_mapping(u32 ip, void *arp_entry);

#endif	/* 
#endif	/* 
    
#if defined(FAST_PATH_SPI_ENABLED)
extern struct nf_conntrack_l4proto **nf_ct_protos[PF_MAX];

rtl_nf_conntrack_in(struct net *net, unsigned int dataoff, unsigned int hooknum,
		    struct sk_buff *skb);

#endif	/* 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)
#if defined(CONFIG_RTL_REDIRECT_ACL_SUPPORT_FOR_ISP_MULTI_WAN)
extern int32 rtl_del_extIp_not_exist_in_ps(void);

					 
					 struct xt_table_info *newinfo,
					 
					 unsigned int number,
					 
					 const unsigned int *underflows);

#endif	/* 
int rtl_flush_extern_ip(void);


			     struct xt_table_info *newinfo, 
			     unsigned int size, 
			     const unsigned int *hook_entries,
			     

#endif	/* 
    
#if defined(CONFIG_RTL_HARDWARE_NAT)
    int32 rtl865x_handle_nat(struct nf_conn *ct, int act, struct sk_buff *skb);

			    struct in_ifaddr *ina);

		     struct fib_info *fi);


#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
    int32 rtl_fib_flush(u32 tb_id, u32 fn_key, u32 ip_mask);

#endif	/* 
    int32 rtl_fn_flush(int fz_order, int idx, u32 tb_id, u32 fn_key);



				     const struct sk_buff *skb,
				     struct ip_vs_protocol *pp);

				     const struct sk_buff *skb,
				     struct ip_vs_protocol *pp);

#endif	/* 
    
#if defined(CONFIG_RTL_HARDWARE_IPV6_SUPPORT)
    int32 rtl8198c_ipv6_router_add(struct rt6_info *rt);


#endif	/* 
    
#if defined(CONFIG_RTL_NF_CONNTRACK_GARBAGE_NEW)
extern int rtl_newGC_session_status_flags;
extern unsigned long rtl_newGC_session_status_time;

#if (HZ==100)
#define	RTL_FP_SESSION_LEVEL3_INTERVAL		(1)
#define	RTL_FP_SESSION_LEVEL1_INTERVAL		(200)	/* 2 second */
#elif (HZ==1000)
#define	RTL_FP_SESSION_LEVEL3_INTERVAL		(10)
#define	RTL_FP_SESSION_LEVEL1_INTERVAL		(2000)	/* 2 second */
#else
#error "Please adjust the parameter according to the HZ"
#endif
#if defined(CONFIG_RTL_8198)
#define	RTL_FP_SESSION_LEVEL3_ALLOW_COUNT	(40)
#else	/* 
#define	RTL_FP_SESSION_LEVEL3_ALLOW_COUNT	(16)
#endif	/* 
#define	RTL_FP_SESSION_LEVEL1_RX_WEIGHT		(8)
#define	RTL_FP_SESSION_LEVEL_IDLE				0
#define	RTL_FP_SESSION_LEVEL1					1
#define	RTL_FP_SESSION_LEVEL2					2
#define	RTL_FP_SESSION_LEVEL3					3
//void rtl_fp_mark_invalid(struct nf_conn *ct);
//enum LR_RESULT rtk_refreshOSConnectionTimer(void);
    
#if 1				//defined(CONFIG_RTL_GC_INDEPENDENCE_ON_KERNEL)
int rtl_gc_threshold_check(struct net *net);

















				    int flag);

				      int flag);

#endif	/* 
    
#endif
    
#define CONFIG_RTL_URL_PATCH 1
#if defined(CONFIG_RTL_URL_PATCH)
#define URL_PROTO_PORT 80
#endif	/* 
    
#if defined(CONFIG_RTL_HW_NAPT_REFINE_KERNEL_HOOKS)
extern int router_support_hw_nat;

#endif	/* 
#endif	/*	RTL_FEATURES_H	*/