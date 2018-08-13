#ifndef	RTL_SCHED_HOOKS_H
#define	RTL_SCHED_HOOKS_H		1
#include <net/pkt_sched.h>
#include <net/sch_generic.h>
#include <net/act_api.h>
#include <net/pkt_cls.h>
#include <linux/netfilter/x_tables.h>

#if	defined(CONFIG_RTL_HW_QOS_SUPPORT)
#if 0
enum nf_inet_hooks { 
	    
};

#endif	/* 
/* IP Hooks */ 
/* After promisc drops, checksum checks. */ 
#define NF_IP_PRE_ROUTING	0
/* If the packet is destined for this box. */ 
#define NF_IP_LOCAL_IN		1
/* If the packet is destined for another interface. */ 
#define NF_IP_FORWARD		2
/* Packets coming from a local process. */ 
#define NF_IP_LOCAL_OUT		3
/* Packets about to hit the wire. */ 
#define NF_IP_POST_ROUTING	4
#define NF_IP_NUMHOOKS		5
#endif	/* 
    
#define HTSIZE (PAGE_SIZE/sizeof(struct fw_filter *))
    struct fw_filter {
	
	
	
	
#ifdef CONFIG_NET_CLS_IND
	char indev[IFNAMSIZ];
	
#endif	/* CONFIG_NET_CLS_IND */
	struct tcf_exts exts;


	
	


	
	
	
	
	
	
	
	
	
	
	
	
	
	


    /*for htb */ 
    /* used internaly to keep status of single class */ 
    enum htb_cmode { 
	    HTB_MAY_BORROW, /* class can't send but may borrow */ 
	    HTB_CAN_SEND /* class can send */  
};

	
	/* general class parameters */
	struct gnet_stats_basic_packed bstats;
	struct gnet_stats_queue qstats;
	struct gnet_stats_rate_est rate_est;
	struct tc_htb_xstats xstats;	/* our special stats */
	int refcnt;		/* usage count of this class */

	/* topology */
	int level;		/* our level (see above) */
	unsigned int children;
	struct htb_class *parent;	/* parent class */

	u32 prio;		/* these two are used only by leaves... */
	int quantum;		/* but stored for parent-to-leaf return */

	union {
		struct htb_class_leaf {
			struct Qdisc *q;
			int deficit[TC_HTB_MAXDEPTH];
			struct list_head drop_list;
		} leaf;
		struct htb_class_inner {
			struct rb_root feed[TC_HTB_NUMPRIO];	/* feed trees */
			struct rb_node *ptr[TC_HTB_NUMPRIO];	/* current class ptr */
			/* When class changes from state 1->2 and disconnects from
			 * parent's feed then we lost ptr value and start from the
			 * first child again. Here we store classid of the
			 * last valid ptr (used when ptr is NULL).
			 */
			u32 last_ptr_id[TC_HTB_NUMPRIO];
		} inner;
	} un;
	struct rb_node node[TC_HTB_NUMPRIO];	/* node for self or feed tree */
	struct rb_node pq_node;	/* node for event queue */
	s64 pq_key;

	int prio_activity;	/* for which prios are we active */
	enum htb_cmode cmode;	/* current mode of the class */
	
	    /* class attached filters */
	struct tcf_proto *filter_list;
	int filter_cnt;

	/* token bucket parameters */
	struct psched_ratecfg rate;
	struct psched_ratecfg ceil;
	s64 buffer, cbuffer;	/* token bucket depth/rate */
	s64 mbuffer;		/* max wait time */
	s64 tokens, ctokens;	/* current number of tokens */
	s64 t_c;		/* checkpoint time */
};

	
	
	
	    /* self list - roots of self generating tree */ 
	struct rb_root row[TC_HTB_MAXDEPTH][TC_HTB_NUMPRIO];
	
	
	
	
	    /* self wait list - roots of wait PQs per row */ 
	struct rb_root wait_pq[TC_HTB_MAXDEPTH];
	
	    /* time of nearest event per level (row) */ 
	 psched_time_t near_ev_cache[TC_HTB_MAXDEPTH];
	
	
	    /* filters for qdisc itself */ 
	struct tcf_proto *filter_list;
	
	
	
	
	    /* non shaped skbs; let them go directly thru */ 
	struct sk_buff_head direct_queue;
	
	
	
#define HTB_WARN_TOOMANYEVENTS	0x1
	unsigned int warned;	/* only one warning */
	


#if 1
    
#define	SM_SHIFT	(30 - PSCHED_SHIFT)
#define	ISM_SHIFT	(8 + PSCHED_SHIFT)
    
#define	SM_MASK		((1ULL << SM_SHIFT) - 1)
#define	ISM_MASK	((1ULL << ISM_SHIFT) - 1)
    
	
	
	
	
	
	


/* runtime service curve */ 
    struct runtime_sc {
	
	
	
	
	
	
	
	


};

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
				   real-time criteria */
	
	
	
	
				   link-sharing, max(myf, cfmin) */
	
				   class's own upperlimit curve) */
	
				   history dependence) */
	
				   with cl_myf to obtain cl_f) */
	
				   children fit for link-sharing
				   (monotonic within a period) */
	
				   adjustment */
	
	
	
	
				   time */
	
	
	
	
	
	
	
	
	
	
	


	
	
	
	
	
					   dropping) */
	


#define	HT_INFINITY	0xffffffffffffffffULL	/* infinite time value */
    
#endif	/* 
    
#if	defined(CONFIG_RTL_HW_QOS_SUPPORT)
    
#if defined(__linux__) && defined(__KERNEL__)
static struct timer_list rtlQosTimer;	/* timer for qos sync */

#endif	/* 
struct iptables_update_hook 
	
	




#define RTL_DELAY_PROCESS_TIME	2
#endif	/* 
    
#define RTL_HTB_TYPE	0x1 
#define RTL_HFSC_TYPE	0x2 
#define RTL_CBQ_TYPE	0x3
    
#define RTL_TBF_TYPE	0x4 
#define RTL_SFQ_TYPE	0x5
#define RTL_DRR_TYPE	0x6 
#define RTL_DSMARK_TYPE 0x7 
    
#define	BANDWIDTH_GAP_FOR_PORT		10000
#if defined(CONFIG_RTL_8196C) ||defined(CONFIG_RTL_819XD) ||defined(CONFIG_RTL_8196E) || defined(CONFIG_RTL_8197F)
#if defined CONFIG_RTL_8367_QOS_SUPPORT
#define	FULL_SPEED	1000000000
#else	/* 
#define	FULL_SPEED	100000000
#endif	/* 
#elif defined(CONFIG_RTL_8198)||defined(CONFIG_RTL_8198C)
#define	FULL_SPEED	1000000000
#else	/* 
#error "Please select the correct chip model."
#endif	/* 
#if defined(CONFIG_RTL_8198C)
#define RTL_MAX_HWQUEUE_NUM		6
#else	/* 
#define RTL_MAX_HWQUEUE_NUM		4
#endif	/* 
    
#if defined (CONFIG_RTL_QOS_SYNC_SUPPORT)
struct qos_conf 
	
	
	
	


    //to-do: multi wan
#define 	RTL_MAX_QOSCONFIG_DEV_NUM 2
struct qos_conf qosConf[RTL_MAX_QOSCONFIG_DEV_NUM];

#endif	/* 
    
#endif	/* 
    