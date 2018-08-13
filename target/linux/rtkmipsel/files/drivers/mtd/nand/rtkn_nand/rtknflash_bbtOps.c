#include "rtknflash.h"
#include <linux/kernel.h>
#ifndef __UBOOT__
#include <linux/slab.h>
#endif /* 


#if 0
static void check_ready()
{
	while (1) {
		if ((rtk_readl(NACR) & 0x80000000) == 0x80000000)
			break;
	}
}


#endif /* 

				
{
	struct rtknflash *rtkn = (struct rtknflash *)chip->priv;
	//uint8_t* oobBuf = chip->oob_poi;
	unsigned long flags_nand = 0;
	unsigned int chunk_size = mtd->writesize;
	int realpage = page;
	int spare_step = chunk_size / 512;
	
	
#if defined(CONFIG_SPI_NAND_FLASH)
#ifdef RTK_BUILT_IN_ECC
	unsigned char tmpBuf[64];	//temp code
	int ret = 0;
	
#endif /* 
#endif /* 
#if defined(CONFIG_PARALLEL_NAND_FLASH)
	int i;
	
#endif /* 
	    
#if 0				//def CONFIG_RTK_REMAP_BBT
	realpage = rtkn_bbt_get_realpage(mtd, realpage);
	
#endif /* 
	    
#if defined(CONFIG_SPI_NAND_FLASH)
#ifdef RTK_BUILT_IN_ECC
	    
	    winbond_2KB_chunk_read_with_ecc_decode(rtkn->buf, realpage, tmpBuf);
	if (ret < 0) {
		goto Error;
	}

	memcpy(buf, rtkn->buf, chunk_size);
	if (oob_required) {
		
	
#else
	    winbond_dma_read_data(buf, chunk_size, realpage);
#endif /* 
#elif defined(CONFIG_PARALLEL_NAND_FLASH)
	    if (parallel_nand_read_page
		(rtkn, rtkn->buf, rtkn->buf + chunk_size, realpage) < 0)
		goto Error;
	
	
		/* spare area 8 byte aligned */ 
		    for (i = 0; i < spare_step; i++)
			
				6);
	}
	
#endif /* 
	    spin_unlock_irqrestore(&lock_nand, flags_nand);
	return 0;

Error:
/* read function donot need do bbt */ 
	    spin_unlock_irqrestore(&lock_nand, flags_nand);
	printk("rtk_check_pageData return fail...\n");
	return -1;



				     struct nand_chip *chip,
				     
				     int oob_required) 
{
	struct rtknflash *rtkn = (struct rtknflash *)chip->priv;
	//unsigned char* oobBuf = chip->oob_poi;
	int page = rtkn->curr_page_addr;
	unsigned int chunk_size = mtd->writesize;
	unsigned long flags_nand = 0;
	int spare_step = chunk_size / 512;
	
#if defined(CONFIG_SPI_NAND_FLASH)
#ifdef RTK_BUILT_IN_ECC
	unsigned char tmpBuf[64];	//temp code
#endif /* 
#endif /* 
#if defined(CONFIG_PARALLEL_NAND_FLASH)
	int i;
	
#endif /* 
	    
#if 0				//def CONFIG_RTK_REMAP_BBT
	page = rtkn_bbt_get_realpage(mtd, page);
#endif /* 
	
#if defined(CONFIG_SPI_NAND_FLASH)
#ifdef RTK_BUILT_IN_ECC
	    
	
	
		
	
	

	/* read to check if this chunk write failed */
	if (winbond_2KB_chunk_read_with_ecc_decode(rtkn->buf, page, tmpBuf) < 0) {
		goto Error;
	}
	
#else
	    winbond_dma_write_data(buf, chunk_size, page);
#endif /* 
#elif defined(CONFIG_PARALLEL_NAND_FLASH)
	    memset(rtkn->buf, 0xff, chunk_size + mtd->oobsize);
	memcpy(rtkn->buf, buf, chunk_size);
	if (oob_required) {
		/* spare area 8 byte aligned */ 
		    for (i = 0; i < spare_step; i++)
			
				6);
	}
	
	     (rtkn, rtkn->buf, rtkn->buf + chunk_size, page) < 0)
		goto Error;
#endif /* 

	spin_unlock_irqrestore(&lock_nand, flags_nand);
	return 0;

Error:	
	printk("rtk_check_pageData return fail...\n");
	return -1;



/* scan erase bbt */ 
static int rtknflash_erase1_cmd0(struct mtd_info *mtd, struct rtknflash *rtkn) 
{
	
	
	spin_lock_irqsave(&lock_nand, flags_nand);
	
#if 0				//def CONFIG_RTK_REMAP_BBT
	    page_addr = rtkn_bbt_get_realpage(mtd, page_addr);
#endif
	
#if defined(CONFIG_SPI_NAND_FLASH)
	    if (winbond_block_erase(page_addr) < 0)
		goto Error;
#elif defined(CONFIG_PARALLEL_NAND_FLASH)
	    if (paralledl_nand_erase_cmd(page_addr) < 0)
		
#endif /* 
	
	return 0;

Error:	
	//printk("[%s] erasure is not completed at block %d\n", __FUNCTION__, page/ppb);
	printk("erase error\n");
	return -1;



/*write data and oob */ 
int rtk_scan_write_bbt(struct mtd_info *mtd, int page, size_t len,
		       
{
	
	
	
	
	    //memcpy(this->oob_poi,oob,oobsize);
	    



/* read data and oob */ 
int rtk_scan_read_oob(struct mtd_info *mtd, uint8_t * buf, int page,
		      
{
	
	
	
	
	    //memcpy(buf+page_size,this->oob_poi,oobsize);
	    



{
	
	
	
	
