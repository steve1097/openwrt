#include "rtknflash.h"
#include <linux/kernel.h>
#include <linux/version.h>
#ifndef __UBOOT__
#include <linux/slab.h>
#endif /* 

/* api for other module use */ 
#ifndef __UBOOT__
extern struct mtd_info rtkn_mtd_info;
struct mtd_info *rtk_get_nand_mtd(void)
{
	return &rtkn_mtd_info;
}

EXPORT_SYMBOL(rtk_get_nand_mtd);
#endif

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,0)
/* erase based on block */ 
int rtk_nand_erase(struct mtd_info *mtd, loff_t offs, size_t len) 
{
	
	
	
	struct rtknflash *rtkn = (struct rtknflash *)this->priv;
	
		
		    /* do nothing */ 
		    return 0;
	
	
	    /*  according to */
	struct erase_info einfo;
	
	
	    (size_t) (((offs + (loff_t) len - 1) >> this->bbt_erase_shift) + 1);
	
		
		
		
		
		
		
			
	
	


EXPORT_SYMBOL(rtk_nand_erase);

		     
{
	
	




			
{
	
	




#if 0
int rtk_nand_read_oob(struct mtd_info *mtd, uint8_t * buf, loff_t offs,
		      
{
	struct mtd_oob_ops ops;
	int res, ret = 0;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	
	
		ops.datbuf = buf;
		ops.len = min(len, (size_t) mtd->writesize);
		ops.oobbuf = buf + ops.len;

		res = mtd_read_oob(mtd, offs, &ops);
		if (res) {
			
				return res;
			else if (mtd_is_eccerr(res) || !ret)
				ret = res;
		
		
		
		
	}
	return ret;
}



			    
{
	
	
	
	
	
	
	
	
	




#endif /* 
    
#else /* 
int rtk_nand_erase(struct mtd_info *mtd, loff_t offs, size_t len) 
{
	
	
	
	
	
		
		    /* do nothing */ 
		    return 0;
	
	
	    /*  according to */ 
	struct erase_info einfo;
	
	
	    (size_t) (((offs + (loff_t) len - 1) >> this->bbt_erase_shift) + 1);
	
		
		
		
		
		
		
			
	
	




		       
{
	
	




		      
{
	
	




#if 0
int rtk_nand_write_oob(struct mtd_info *mtd, loff_t offs, size_t len,
		       
{
	
	
	
	
	
	
	
	




#endif /* 
#endif /* 