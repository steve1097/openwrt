#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/switch.h>
#include "rtl819x_switch.h"

	
	
	
	
	
	
	
	    //struct rtl8366_smi_ops        *ops;
	int vlan_enabled;
	
	
	



//############## call driver layer
    
//extern from rtl_nic.c
extern void rtk_reset_rtl819x_setting(void);


//extern unsigned int rtk_get_port_status(int port , char *buf, int buf_len);
unsigned int rtk_get_port_status(int port, struct switch_port_link *link);






			    unsigned int untag, unsigned int fid);



{
	


//###############
static inline struct rtl819x_smi *sw_to_rtl819x_smi(struct switch_dev *sw) 
{
	


						  *attr,
						  
{
	
	
	    //printk(" Not support swconfig get_learning_enable yet! ----- \n");    
	    
	



					       
					       
{
	
	    (" Not support swconfig rtl819x_sw_set_learning_enable yet! ----- \n");
	
#if 0
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	
	
	
		
	
	    /* set learning for all ports */ 
	    REG_WR(smi, RTL8366S_SSCR0, portmask);
	
	    /* set auto ageing for all ports */ 
	    REG_WR(smi, RTL8366S_SSCR1, portmask);
	
#endif /* 
	    return 0;



				  
				  
{
	
	
	    //printk("rtl819x_sw_set_vlan_enable ----- \n");
	    
	
	
	



				  
				  
{
	
	
	    //printk("rtl819x_sw_get_vlan_enable ----- \n");
	    if (attr->ofs > 2)
		
	
		
	
	else
		
	


	    {
	     "enable_learning", 
	     "Enable learning, enable aging", 
	     rtl819x_sw_set_learning_enable, 
	     rtl819x_sw_get_learning_enable, 
							     SWITCH_TYPE_INT,
							     
							     "enable_vlan",
							     
							     "Enable VLAN mode",
							     
							     rtl819x_sw_set_vlan_enable,
							     
							     rtl819x_sw_get_vlan_enable,
							     
							     1 
								    SWITCH_TYPE_INT,
								    
								    "enable_vlan4k",
								    
								    =
								    "Enable VLAN 4K mode",
								    
								    rtl819x_sw_set_vlan_enable,
								    
								    rtl819x_sw_get_vlan_enable,
								    
								    1, 
								    2 
#if 0
{
 "Reset all MIB counters", 
								SWITCH_TYPE_INT,
								
								"blinkrate",
								
								"Get/Set LED blinking rate (0 = 43ms, 1 = 84ms,"
								
								" 2 = 120ms, 3 = 170ms, 4 = 340ms, 5 = 670ms)",
								
								rtl8366s_sw_set_blinkrate,
								
								rtl8366s_sw_get_blinkrate,
								
#endif /* 
};


#if 0				//mark_bb
static int rtl819x_sw_get_port_link(struct switch_dev *dev,
				    
				    
{
	
	
	
	
		
	
	
	
	
	
	



#endif /* 
static int rtl819x_sw_get_port_link(struct switch_dev *dev, 
				    
{
	
	    //struct rtl819x_smi *smi = sw_to_rtl819x_smi(dev);     
	    
		
	



				       
				       
{
	
	    //printk("rtl819x_sw_reset_port_mibs ----- \n");
	    rtk_reset_mibCounter();
	



			       
			       
{
	
	
	
	    //unsigned long long counter = 0;
	char *buf = smi->buf;
	
	    //printk("rtl819x_sw_get_port_mib ----- \n");
	    
		
	
	    snprintf(buf + len, sizeof(smi->buf) - len,
		     
	
		
		    snprintf(buf + len, sizeof(smi->buf) - len, 
			     (char *)rtk_get_mibCounter_name(i));
		
		    snprintf(buf + len, sizeof(smi->buf) - len, 
			     (unsigned int)
			     rtk_get_mibCounter_val(val->port_vlan, i));
	
	
	



#if 0				//mark_bb , move to main ops in latest swconfig ops       
	{
	 "Get port link information", 
	 rtl819x_sw_get_port_link, 
#endif /* 
	{
	 "Reset single port MIB counters", 
	 rtl819x_sw_reset_port_mibs, 
					  "mib", 
					  "Get MIB counters for port", 
					  33, 
					  rtl819x_sw_get_port_mib, 
#if 0
	{
	 "Get/Set port group (0 - 3) led mode (0 - 15)", 
	 rtl8366s_sw_set_port_led, 
#endif /* 
};


{
	
	
	
		
	
	



				
				
{
	
	
	
	
	
	
	
	    //if (!smi->ops->is_vlan_valid(smi, val->port_vlan))
	    //return -EINVAL;
	    
	
	
		
	
	    snprintf(buf + len, sizeof(smi->buf) - len, 
		     vlan4k.vid);
	
		
			
		
		    snprintf(buf + len, sizeof(smi->buf) - len, "%d%s", i,
			     
	
	
	    snprintf(buf + len, sizeof(smi->buf) - len,
		     
		     vlan4k.untag, vlan4k.fid);
	
	
	



				 
				 
{
	
	
	    //struct rtl819x_smi *smi = sw_to_rtl819x_smi(dev);
	int err;
	
	    //if (!smi->ops->is_vlan_valid(smi, val->port_vlan))
	    //return -EINVAL;
	    
	
		
	
	



				 
				 
{
	
	    //printk("rtl819x_sw_set_vlan_fid ----- \n");
	    return 0;



				 struct switch_val *val) 
{
	
	
	
	
	
	    //printk("rtl819x_sw_get_vlan_ports ----- \n");
	    
	    //if (!smi->ops->is_vlan_valid(smi, val->port_vlan))
	    //      return -EINVAL;
	    
	
	
	
		
			
		
		
		    (vlan4k.untag & BIT(i)) ? 
		
		
	
	



				 struct switch_val *val) 
{
	
	    //struct rtl819x_smi *smi = sw_to_rtl819x_smi(dev);
	struct switch_port *port;
	
	
	
	
	
	    //printk("rtl819x_sw_set_vlan_ports -----vid=%d \n",val->port_vlan );
	    port = &val->value.ports[0];
	
		
		
			
			
			
			    //only change port's pvid if it is untag port in this vlan
			    err = rtk_set_port_pvid(port->id, val->port_vlan);
			
	
	



{
	
	
	    //printk("rtl819x_sw_get_port_pvid port%d=%d ----- \n",port,*val);
	    



{
	
	
	    //printk("rtl819x_sw_set_port_pvid ----- \n");
	    err = rtk_set_port_pvid(port, val);
	



{
	
	    //printk("rtl819x_sw_reset_switch ----- \n");
	    rtk_reset_layer2_setting();
	


	    {
	     "Get vlan information", 
	     rtl819x_sw_get_vlan_info, 
					    "fid", 
					    "Get/Set vlan FID", 
					    RTL819X_FIDMAX, 
					    rtl819x_sw_set_vlan_fid, 
					    rtl819x_sw_get_vlan_fid, 
};

};


{
	
	
	
	
	    //rtl819x_smi_driver_p->num_vlan_mc = RTL8366S_NUM_VLANS;
	    //rtl819x_smi_driver_p->mib_counters = rtl819x_mib_counters;
	    rtl819x_smi_driver_p->num_mib_counters = rtk_get_mibCounter_num();
	
	return 0;



{
	
	
	
	
	
	
	
	
	
	
	    //dev->alias = dev_name(smi->parent);
	    
	    //err = register_switch(dev, NULL);
	    err = register_switch(dev, netdev);
	
		
	


