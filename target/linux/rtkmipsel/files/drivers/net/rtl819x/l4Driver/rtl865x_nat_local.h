#ifndef	RTL865X_NAT_LOCAL_H 
#define	RTL865X_NAT_LOCAL_H

	
	


	
	
	
	


	
	
	
	
	
	
#if defined(CONFIG_RTL_EXT_PORT_SUPPORT)
	 uint32 isExtNaptEntry;
	
#endif				/* 
#if defined (CONFIG_RTL_INBOUND_COLLISION_AVOIDANCE)
	 uint32 reserveTime;
	
#endif				/* 
	
#define int_ip_					tuple_info.int_host.ip
#define int_port_					tuple_info.int_host.port
#define ext_ip_					tuple_info.ext_host.ip
#define ext_port_					tuple_info.ext_host.port
#define rem_ip_					tuple_info.rem_host.ip
#define rem_port_					tuple_info.rem_host.port
#define proto_					tuple_info.proto


	
	
	
	
	


	
	
	
	
	
	
	


#endif /* 
    