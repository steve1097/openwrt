
#ifndef CONFIG_WRT_BARRIER_BREAKER
    
#if defined(CONFIG_RTK_NAND_FLASH_STORAGE)
#define NAND_FLASH_SIZE		(0x6400000)	// max value= %90 * flash size
#endif /* 
    
#ifndef __UBOOT__
#if 0				//def CONFIG_MTD_CMDLINE_PARTS
static const char *probes[] = { "cmdlinepart", NULL };


#else /* 
#if !defined(CONFIG_RTK_NAND_FLASH_STORAGE)
#ifndef CONFIG_RTL_FLASH_DUAL_IMAGE_ENABLE
static struct mtd_partition rtl8196_parts1[] = { 
		

    /* add new partition */ 
#if 0
, 

#endif /* 
};


#else //!CONFIG_RTL_FLASH_DUAL_IMAGE_ENABLE
static struct mtd_partition rtl8196_parts1[] = { 
 CONFIG_RTL_ROOT_IMAGE_OFFSET),
		  

};


#endif /* 
#else /* 
    //defined CONFIG_RTK_NAND_FLASH_STORAGE
static struct mtd_partition rtl8196_parts1[] = { 

};


#endif /* 
#endif /* 
#endif /* 
    
#if !defined(CONFIG_RTK_NAND_FLASH_STORAGE)
#if !defined(CONFIG_MTD_RTKXX_PARTS)
static int detect_rootfs_flash_map(void) 
{
	
	
	
	
#ifdef CONFIG_RTL_FLASH_DUAL_IMAGE_ENABLE
	    
		
			
	
	
#else /* 
	    dualpartition = ARRAY_SIZE(rtl8196_parts1);
	
#endif /* 
	    
		
			
			
			    CONFIG_RTL_FLASH_SIZE - size;
		
			
				
				    ("donnot have space for rootfs partition\n");
				
			
			
			
		
	
	
#ifdef CONFIG_RTL_FLASH_DUAL_IMAGE_ENABLE
	    for (i = ARRAY_SIZE(rtl8196_parts1) - 1; i >= dualpartition; i--) {
		
			
			
			    CONFIG_RTL_FLASH_SIZE - size;
		
			
				
				    ("donnot have space for rootfs2 partition\n");
				
			
			
			
		
	
	
#endif /* 
	    



#endif /* 
#endif /* 
    
#endif /* 