#if !defined(FAST_BRIDGE_H)
#define FAST_BRIDGE_H

#define	CONFIG_RTL_FASTBRIDGE		1
    
#define	RTL_FB_ENTRY_NUM				16
#define	RTL_FB_HASH_SIZE				16	/* must be 2s order */
    
#if !defined(__KERNEL__)
    struct hlist_node {
	
};

	struct hlist_node *first;
};

#endif	/* 

	
	
	


	
	
	


	
	    /* hlist MUST be the first filed */ 
	struct hlist_node hlist;	/* belongs to the same hash entry */
	
	
				  
	
	







#define	RTL_FB_RETURN_SUCCESS	0
#define	RTL_FB_RETURN_FAILED		-1
    
/*****************************************************/ 
/*		netlink										*/ 
#define	FB_CMD_NO_CMD			-1
#define	FB_CMD_SET_FWD			0
#define	FB_CMD_SET_FILTER			1
#define	FB_CMD_SET_ENTRY_NUM	2
#define	FB_CMD_GET_STATUS		3
#define	FB_CMD_GET_USED_NUM		4
#define	FB_CMD_DUMP_ENTRYS		5
    
	
	
	


	
	
	


	
	


/*****************************************************/ 
    
#endif	/* 