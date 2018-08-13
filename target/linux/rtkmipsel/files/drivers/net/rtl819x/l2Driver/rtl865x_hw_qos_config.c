#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/kernel_stat.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/net.h>
#include <linux/socket.h>

#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/string.h>
#include <net/ip.h>
#include <net/protocol.h>
#include <net/route.h>
#include <net/sock.h>
#include <net/arp.h>
#include <net/raw.h>
#include <net/checksum.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netlink.h>
#include <linux/inetdevice.h>
#include <linux/icmp.h>
#include <net/udp.h>
#include <net/tcp.h>
    
#include <net/rtl/rtl_types.h>
#ifdef CONFIG_NETFILTER
#include <net/netfilter/nf_conntrack.h>
#include <net/rtl/fastpath/fastpath_core.h>
#endif /* 
#include <net/rtl/rtl865x_netif.h>
#include <net/rtl/rtl_nic.h>
    
#ifdef CONFIG_RTL_LAYERED_ASIC_DRIVER
#include <AsicDriver/asicRegs.h>
#include <AsicDriver/rtl865x_asicCom.h>
#include <AsicDriver/rtl865x_asicL2.h>
#else /* 
#include <AsicDriver/asicRegs.h>
#include <AsicDriver/rtl8651_tblAsicDrv.h>
#endif /* 
#ifdef __KERNEL__
#include <linux/version.h>
#endif /* 
    
#ifdef CONFIG_RTL_8197F
#include <common/rtl865x_vlan.h>
#include <common/rtl_errno.h>
#endif /* 
    
#define CHLOE_FOR_TEST 1


	
	
		
			
			
		
		
			
			
		
		
			
			
			
		
		
#if defined(CONFIG_RTL_8197F)
		    struct {
			
			
		
		
#endif				/* 
		    struct {
			
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
			unsigned char queue[8][8];
			
#else				/* 
			unsigned char queue[8][6];
			
#endif				/* 
			unsigned int portmask;
			
		
		
			
			
		
		
			
#if defined(CONFIG_RTL_8197F)
			char decision[6];
			
#else				/* 
			char decision[5];
			
#endif				/* 
		} pri_decision;
		
			
			
			
		
		
			
			
			
			
			
		
		
			
			
		
		
			
			
		
	


#define PORT_BASED_PRIORITY_ASSIGN 1
#define VLAN_BASED_PRIORITY_ASSIGN 2
#define DSCP_BASED_PRIORITY_ASSIGN 3
#define QUEUE_NUMBER 4
#define QUEUE_TYPE_STRICT 5
#define QUEUE_TYPE_WEIGHTED 6
#define PRIORITY_TO_QID 7
#define PRIORITY_DECISION 8
#define VLAN_REMARK 9
#define DSCP_REMARK 10
#define PORT_BASED_PRIORITY_SHOW 11
#define VLAN_BASED_PRIORITY_SHOW 12
#define DSCP_BASED_PRIORITY_SHOW 13
#define QUEUE_NUMBER_SHOW 14
#define QUEUE_TYPE_STRICT_SHOW 15
#define QUEUE_TYPE_WEIGHTED_SHOW 16
#define PRIORITY_TO_QID_SHOW 17
#define PRIORITY_DECISION_SHOW 18
#define VLAN_REMARK_SHOW 19
#define DSCP_REMARK_SHOW 20
#define QUEUE_RATE 21
#define QUEUE_RATE_SHOW 22
#define FLOW_CONTROL_ENABLE 23
#define FLOW_CONTROL_DISABLE 24
#define FLOW_CONTROL_CONFIGURATION_SHOW 25
#define PORT_RATE 26
#define PORT_RATE_SHOW 27
#define PORT_DEFAULT_8021P 28
#define PORT_DEFAULT_8021P_SHOW 29
#if defined(CONFIG_RTL_8197F)
#define VID_BASED_PRIORITY_ASSIGN 30
#define VID_BASED_PRIORITY_SHOW 31
#endif /* 
    
#if defined(CONFIG_RTL_8198C) || defined(CONFIG_RTL_8197F)
#define MAX_QUEUE_NUM		8
#else /* 
#define MAX_QUEUE_NUM		6
#endif /* 
    int32 rtl8651_setAsicPortDefPri(uint32 port, uint32 pri);


{
	
	
	
	
		
		
			
				priority);
	
	



{
	
	
	
	
		
		
			
				priority);
	
	



{
	
	
	
	
		
		
			
				priority);
	
	



#if defined(CONFIG_RTL_8197F)
static inline void vid_based_priority_show(void) 
{
	
	
	
	
	
		
		
			
	
	



#endif /* 

{
	
	
	
	
		
		
			
				qnum);
	
	



{
	
	
	
	
		
			
			
				
				    ("    Port[%d]'s  Queue[%d] type is STRICT\n",
				     i, j);
		
	
	



{
	
	
	
	
		
			
			    rtl8651_getAsicQueueWeight(i, j, &queueType,
						       &weight);
			
				
				    ("    Port[%d]'s  Queue[%d] type is WEIGHTED, and weight is %u\n",
				     i, j, weight);
		
	
	



{
	
	
	
	
		
			
			    rtl8651_getAsicPriorityToQIDMappingTable(i, j,
								     &qid);
			
				
				    ("    For Queue number[%d], priority[%d] is mapping to qid[%d]\n",
				     i, j, qid);
		
	
	



{
	
	
#if defined(CONFIG_RTL_8197F)
	unsigned int vidpri;
	
#endif /* 
	int ret;
	
	
#if defined(CONFIG_RTL_8197F)
	    ret =
	    rtl8651_getAsicPriorityDecision(&portpri, &dot1qpri, &dscppri,
					    &aclpri, &natpri, &vidpri);
	
#else /* 
	    ret =
	    rtl8651_getAsicPriorityDecision(&portpri, &dot1qpri, &dscppri,
					    &aclpri, &natpri);
	
#endif /* 
	    if (ret == SUCCESS) {
		
		
		
		
		
		
#if defined(CONFIG_RTL_8197F)
		    printk("    VID    based decision priority is %d\n",
			   vidpri);
		
#endif /* 
	}
	



{
	
	
	
		
			
			
				
				    ("    Port[%d]'s sys_pri[%d] is remarked as vlan_pri[%d]\n",
				     i, j, remark);
		
	
	



{
	
	
	
		
			
			
				
				    ("    Port[%d]'s sys_pri[%d] is remarked as dscp[%d]\n",
				     i, j, remark);
		
	
	



{
	
	
	
	
		
			
			    rtl8651_getAsicQueueRate(i, j, &ppr, &burst, &apr);
			
				
				    ("    Port[%d] queue[%d]'s  ppr is %d, burst is %d, apr is %dkbps\n",
				     i, j, ppr, burst, apr + 1);
		
	
	



{
	
	
	
	
		
		
			
	
	



{
	
	
	
	
		
		
			
			    //printk("    Port[%d]'s apr is %dMbps\n", i, (apr+1)*1024);
			    printk("    Port[%d]'s apr is %dKbps\n", i,
				   apr + 1);
	
	



{
	
	
	
	    rtl8651_getAsicQueueFlowControlConfigureRegister(0, 0,
							     &flow_control_enable);
	
		
			
		
			
		
	



{
	
	
		
	
	
	
		
		
		    ((pri & 0x7) << (16 + 12)) | (regValue & ~0x70000000);
		
	
	else
		
		
		
	
	



{
	
	
	
		
	
		
		
		
	
	else
		
		
		
	



{
	
// to_be_checked !!!
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)) && (LINUX_VERSION_CODE < KERNEL_VERSION(3,3,0))
#else /* 
#if 1				//ndef CONFIG_RTL_8198C
	unsigned int i, j;
	
	
	
	
	
	    rtk_nlrecvmsg(__skb, sizeof(struct qos_cmd_info_s), &recv_data);
	
		
	
		
	
		
			
			     port_based_priority.portmask) {
				
				    rtl8651_setAsicPortBasedPriority(i,
								     recv_data.qos_data.port_based_priority.port
								     [i]);
				
					
					    ("Port based priority set to PBPCR register failed\n ");
				
			
		
		
		
	
		
			
			     vlan_based_priority.vlanmask) {
				
				    rtl8651_setAsicDot1qAbsolutelyPriority(i,
									   recv_data.qos_data.vlan_based_priority.vlan
									   [i]);
				
					
					    ("Vlan based priority set to LPTM8021Q register failed\n ");
				
			
		
		
		
	
		
			
			      && ((1 << i) & recv_data.
				  qos_data.dscp_based_priority.dscpmask1))
			     || 
				  && ((1 << (i - 32)) &
				      recv_data.qos_data.dscp_based_priority.dscpmask2)))
			{
				
				    rtl8651_setAsicDscpPriority(i,
								recv_data.qos_data.dscp_based_priority.dscp
								[i]);
				
					
					    ("Dscp based priority set to DSCPCR register failed\n ");
				
			
		
		
		
		
#if defined(CONFIG_RTL_8197F)
	case VID_BASED_PRIORITY_ASSIGN:
		
			
				
				    //panic_printk("vid%d is %d in kernel.\n", i, recv_data.qos_data.vid_based_priority.vid[i]);
				    
					 (recv_data.qos_data.
					  vid_based_priority.vid[i] - '0')) {
					
					    ("vlan table don't have the entry of vid%c.\n",
					     recv_data.
					     qos_data.vid_based_priority.
					     vid[i]);
					
				
				
				    rtl865x_setVlanHp(recv_data.
						      qos_data.vid_based_priority.vid
						      [i] - '0',
						      recv_data.
						      qos_data.vid_based_priority.pri
						      [i] - '0');
				
					
					    ("Vid based priority set to vlan table failed\n ");
				
				
					
					    ("Invalid Vlan Id, vid%c\n",
					     recv_data.
					     qos_data.vid_based_priority.
					     vid[i]);
				
			
		
		
		
#endif /* 
	
		
			
				
				    rtl8651_setAsicOutputQueueNumber(i,
								     recv_data.qos_data.queue_num.port
								     [i]);
				
					
					    ("Queue number set to QNUMCR register failed\n ");
				
			
		
		
		
	
		
			
				
					
					     qos_data.queue_type.queuemask) {
						
						     qos_data.queue_type.
						     queue[i][j] == 255) {
							
							    rtl8651_setAsicQueueStrict
							    (i, j, STR_PRIO);
							
								
								    ("Queue type STRICT set to WFQWCR0P0 register failed\n ");
							
						
					
				
			
		
		
		
	
		
			
				
					
					     qos_data.queue_type.queuemask) {
						
						      qos_data.queue_type.
						      queue[i][j] > 0)
						     && 
							  qos_data.queue_type.queue
							  [i][j] != 255)) {
							
							    rtl8651_setAsicQueueWeight
							    (i, j, WFQ_PRIO,
							     recv_data.
							     qos_data.queue_type.queue
							     [i][j]);
							
								
								    ("Queue type WEIGHTED set to WFQWCR0P0 register failed\n ");
							
						
					
				
			
		
		
		
	
		
			
			
				
					
					
					     qos_data.sys_priority.
					     prioritymask) {
						
						    rtl8651_setAsicPriorityToQIDMappingTable
						    (queue_num, j,
						     recv_data.
						     qos_data.sys_priority.
						     priority[j]);
						
							
							    ("Priority to qid set to UPTCMCR register failed\n ");
						
					
					
			
		
		
		
	
		
#if defined(CONFIG_RTL_8197F)
		    ret =
		    rtl8651_setAsicPriorityDecision(recv_data.
						    qos_data.pri_decision.
						    decision[0],
						    recv_data.
						    qos_data.pri_decision.
						    decision[1],
						    
						    qos_data.pri_decision.
						    decision[2],
						    recv_data.
						    qos_data.pri_decision.
						    decision[3],
						    
						    qos_data.pri_decision.
						    decision[4],
						    recv_data.
						    qos_data.pri_decision.
						    decision[5]);
		
#else /* 
		    ret =
		    rtl8651_setAsicPriorityDecision(recv_data.
						    qos_data.pri_decision.
						    decision[0],
						    recv_data.
						    qos_data.pri_decision.
						    decision[1],
						    
						    qos_data.pri_decision.
						    decision[2],
						    recv_data.
						    qos_data.pri_decision.
						    decision[3],
						    
						    qos_data.pri_decision.
						    decision[4]);
		
#endif /* 
		    if (ret == FAILED) {
			
			    ("Priority decision set to QIDDPCR register failed\n ");
		
		
		
	
		
			
				
					
					     qos_data.vlan_remark.
					     prioritymask) {
						
						    rtl8651_setAsicVlanRemark(i,
									      j,
									      recv_data.qos_data.vlan_remark.remark
									      [i]
									      [j]);
						
							
							    ("Vlan remark set to RMCR1P register failed\n ");
						
					
				
			
		
		
		
	
		
			
				
					
					     qos_data.dscp_remark.
					     prioritymask) {
						
						    rtl8651_setAsicDscpRemark(i,
									      j,
									      recv_data.qos_data.dscp_remark.remark
									      [i]
									      [j]);
						
							
							    ("Dscp remark set to DSCPRM register failed\n ");
						
					
				
			
		
		
		
	
		
			
				
					
					     qos_data.queue_rate.queuemask) {
						
						    rtl8651_setAsicQueueRate(i,
									     j,
									     recv_data.qos_data.queue_rate.ppr
									     [i]
									     [j], 
									     [j], 
									     [j]);
						
							
							    ("Queue rate set to P0Q0RGCR register failed\n ");
						
					
				
			
		
		
		
	
		
			
				
				    rtl8651_setAsicPortEgressBandwidth(i,
								       recv_data.qos_data.port_rate.apr
								       [i]);
				
					
					    ("Port rate set to WFQRCRP0 register failed\n ");
				
			
		
		
		
	
		
			
				
				    rtl8651_setAsicPortDefPri(i,
							      recv_data.qos_data.
							      port_pri.pri[i]);
				
					
					    ("Port default 8021p set to PVCRx register failed\n ");
				
			
		
		
		
	
		
			
				
				    rtl8651_setAsicQueueFlowControlConfigureRegister
				    (i, j, 1);
				
					
					    ("Set Flow Control Enable failed\n ");
				
			
		
		
	
		
			
				
				    rtl8651_setAsicQueueFlowControlConfigureRegister
				    (i, j, 0);
				
					
					    ("Set Flow Control Disable failed\n ");
				
			
		
		
	
		
		
	
		
		
	
		
		
		
#if defined(CONFIG_RTL_8197F)
	case VID_BASED_PRIORITY_SHOW:
		
		
		
#endif /* 
	case QUEUE_NUMBER_SHOW:
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
			 &send_data);
	
#endif /* 
#endif /* 
	    return;



{
	
// to_be_checked !!!
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,33)
	    hw_qos_sk =
	    netlink_kernel_create(&init_net, NETLINK_RTK_HW_QOS, 0,
				  hw_qos_netlink_receive, NULL, THIS_MODULE);
	
#elif LINUX_VERSION_CODE >= KERNEL_VERSION(3,4,0)
	struct netlink_kernel_cfg cfg;
	
	
	
	
	
	
#endif /* 
	    if (!hw_qos_sk) {
		
			"Netlink[Kernel] Cannot create netlink socket for hw qos config.\n");
		
	
	
	


