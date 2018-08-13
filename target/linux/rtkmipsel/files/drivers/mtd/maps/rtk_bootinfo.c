#define TAG_LEN					4
#define RTK_BOOTINFO_SIGN "hwbt"
#define RTK_MAX_VALID_BOOTCNT 16

#define BOOT_NORMAL_MODE 0
#define BOOT_DUALIMAGE_TOGGLE_MODE 1
#define BOOT_DEFAULT_MAXCNT 3
/* Config file header */ 
    
	
	unsigned int len;


	
	
		
		
		
		
	


	
	


{
	
	
	
	
	
	
#ifdef CONFIG_RTK_BOOTINFO_DUALIMAGE
	    boot->data.field.bootmode = BOOT_DUALIMAGE_TOGGLE_MODE;
	
#else /* 
	    boot->data.field.bootmode = BOOT_NORMAL_MODE;
	
#endif /* 
}


{
	
		return 1;
	
}


				       BOOTINFO_P bootinfo_ram_p) 
{
	
	
	    //flash(spi...etc)  can be read directly 
	    memcpy((char *)bootinfo_ram_p, (char *)bootinfo_addr,
		   sizeof(BOOTINFO_T));
	
#if 0
	    printk("rtk_read_bootinfo_from_flash \n");
	
		bootinfo_ram_p->header.tag[1] 
		bootinfo_ram_p->header.tag[3], bootinfo_ram_p->header.len);
	
		  bootinfo_ram_p->data.field.bootbank,
		  bootinfo_ram_p->data.field.bootcnt,
		  
	
#endif /* 



				    BOOTINFO_P bootinfo_ram_p,
				    
							 unsigned int,
							 unsigned char *)) 
{
	
#if 0
	    printk("rtk_read_bootinfo_from_flash \n");
	
		bootinfo_ram_p->header.tag[1] 
		bootinfo_ram_p->header.tag[3], bootinfo_ram_p->header.len);
	
		  bootinfo_ram_p->data.field.bootbank,
		  bootinfo_ram_p->data.field.bootcnt,
		  
		  bootinfo_ram_p->data.val);
	
#endif /* 
	    //flash(spi...etc) need flash write api
	    write_func(bootinfo_addr, sizeof(BOOTINFO_T),
		       (char *)bootinfo_ram_p);
