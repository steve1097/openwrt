#include "rtknflash.h"
#include <linux/kernel.h>
#ifndef __UBOOT__
#include <linux/slab.h>
#endif /* 

/* realtek bbt */ 
/*	1. first remap v2r bbt: 	block ----> v2r_block
	2. second create rba bbt:	v2r_block ----> rba_block
	3. mark block bad function. 
		a.mark v2r_block bad (oob write)
		b.update rba bbt
	4. recreate bbt function
		a. v2r bbt and rba bbt
			only based on  oob flag
	5. mtd check if block is bad
		a. always return 0(not bad) because of remap bbt 		
	6. for pagesize > 512 nand flash, badblock pos is 5,others is 0
*/ 
    
#ifdef CONFIG_RTK_REMAP_BBT
static int RBA;







#endif /* 
#ifdef CONFIG_RTK_NORMAL_BBT
static int bbt_num;

#endif /* 
/*
	 * Bad block marker is stored in the last page of each block on Samsung
	 * and Hynix MLC devices; stored in first two pages of each block on
	 * Micron devices with 2KiB pages and on SLC Samsung, Hynix, Toshiba,
	 * AMD/Spansion, and Macronix.  All others scan only the first page.
	default store in first and second page and read in first page
*/ 
static int isLastPage = 0;

/* copy from nand_bbt.c */ 
/* scan read bbt */ 
    
#if 0
static spinlock_t lock_nand;

{
	while (1) {
		if ((rtk_readl(NACR) & 0x80000000) == 0x80000000)
			break;
	}
}


#if 0
static int rtkn_ecc_read_page0(struct mtd_info *mtd, struct nand_chip *chip,
			       
{
	nand_printf("[%s]:%d\n", __func__, __LINE__);
	struct rtknflash *rtkn = (struct rtknflash *)chip->priv;
	int dma_counter = 4, page_shift, page_num[3], buf_pos = 0;
	int dram_sa, oob_sa;
	unsigned long flash_addr_t = 0;
	unsigned int flags_nand = 0;
	uint8_t *oobBuf = chip->oob_poi;
	int orig_block = page / (mtd->erasesize / mtd->writesize);

	int i;
	//printk("[%s]:%d,page=%x\n",__func__,__LINE__,page);
	spin_lock_irqsave(&lock_nand, flags_nand);

	/* get the real page */ 
	    //__flush_cache_all();
	    /* addr */
	    uint8_t * oob_area, *data_area, data_area0[512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4];	//data,oob point must 32 cache aligment
	memset(data_area0, 0xff,
	       512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4);
	data_area = data_area0;
	oob_area = (uint8_t *) data_area + 512;
	oob_sa = ((uint32_t) (oob_area) & (~M_mask));
	dram_sa = ((uint32_t) data_area) & (~M_mask);

	/* flash addr */
	for (page_shift = 0; page_shift < 3; page_shift++) {
		page_num[page_shift] = ((page >> (8 * page_shift)) & 0xff);
		flash_addr_t |= (page_num[page_shift] << (12 + 8 * page_shift));
	}

	rtk_writel(0xC00FFFFF, NACR);	//Enable ECC  
	rtk_writel(0x0000000F, NASR);	//clear NAND flash status register

	while (dma_counter > 0) {

		int lastSec = dma_counter - 1;
		//set DMA RAM DATA start address                
		rtk_writel(dram_sa, NADRSAR);
		//set DMA RAM oob start address , always use oob_sa buffer
		rtk_writel(oob_sa, NADTSAR);
		//set DMA flash start address,
		rtk_writel(flash_addr_t, NADFSAR);

		dma_cache_wback_inv((uint32_t *) data_area, 528);
		//DMA read command
		rtk_writel(((~TAG_DIS) & (DESC0 | DMARE | LBC_64)), NADCRR);
		check_ready();

		if (lastSec <= 0)
			lastSec = 1;
		else
			lastSec = 0;

		if (rtk_check_pageData
		    (mtd, 0, page, buf_pos * (512 + 16), lastSec) == -1) {
			goto Error;
		}
		//copy data
		memcpy(buf + (buf_pos * 512), data_area, 512);
		//copy oob
		memcpy(oobBuf + (buf_pos * 16), oob_area, 16);

		flash_addr_t += 528;
		dma_counter--;
		buf_pos++;
	}

#ifdef SWAP_2K_DATA
	if (orig_block >= BOOT_BLOCK) {
		if (!NAND_ADDR_CYCLE) {
			/*switch bad block info */
			unsigned char temp_val = 0;
			{
				temp_val = buf[DATA_BBI_OFF];
				{
					buf[DATA_BBI_OFF] = oobBuf[OOB_BBI_OFF];
					oobBuf[OOB_BBI_OFF] = temp_val;
				}
			}
		}
	}
#endif

	nand_printf("[%s]:%d\n", __func__, __LINE__);
	spin_unlock_irqrestore(&lock_nand, flags_nand);
	return 0;

Error:
/* read function donot need do bbt */ 
	    spin_unlock_irqrestore(&lock_nand, flags_nand);
	printk("rtk_check_pageData return fail...\n");
	return -1;



#endif /* 

			      
{
	
	
	
	
	
		
		
		
	



#if 0
static int rtkn_ecc_write_page0(struct mtd_info *mtd, struct nand_chip *chip,
				
{
	int i;
	struct rtknflash *rtkn = (struct rtknflash *)chip->priv;
	int page = rtkn->curr_page_addr, dma_counter =
	    4, page_shift, page_num[3], buf_pos = 0;
	int dram_sa, oob_sa;
	unsigned long flash_addr_t = 0;
	unsigned int flags_nand = 0;
	unsigned int ppb = mtd->erasesize / mtd->writesize;
	uint8_t *dataBuf = buf, *oobBuf = chip->oob_poi;
	int orig_block = page / ppb, res = 0;
	
	//__flush_cache_all();

	/* addr */
	uint8_t *oob_area, *data_area, data_area0[512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4];	//data,oob point must 32 cache aligment
	memset(data_area0, 0xff,
	       512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4);
	data_area = (uint8_t *) ((uint32_t) (data_area0 + 12) & 0xFFFFFFF0);
	oob_area = (uint8_t *) data_area + 512;
	oob_sa = ((uint32_t) (oob_area) & (~M_mask));
	dram_sa = ((uint32_t) data_area) & (~M_mask);

#ifdef SWAP_2K_DATA
	if (orig_block >= BOOT_BLOCK) {
		if (!NAND_ADDR_CYCLE) {
			unsigned char temp_val;
			{
				temp_val = dataBuf[DATA_BBI_OFF];
				{
					dataBuf[DATA_BBI_OFF] =
					    oobBuf[OOB_BBI_OFF];
					oobBuf[OOB_BBI_OFF] = temp_val;
				}
			}
		}
	}
#endif

	/* flash addr */
	for (page_shift = 0; page_shift < 3; page_shift++) {
		page_num[page_shift] = ((page >> (8 * page_shift)) & 0xff);
		flash_addr_t |= (page_num[page_shift] << (12 + 8 * page_shift));
	}
	rtk_writel(0xC00FFFFF, NACR);	//Enable ECC  
	rtk_writel(0x0000000F, NASR);	//clear NAND flash status register

	while (dma_counter > 0) {

		int lastSec = dma_counter - 1;
		memcpy(oob_area, oobBuf + (buf_pos * 16), 16);
		memcpy(data_area, dataBuf + (buf_pos * 512), 512);
		dma_cache_wback_inv((uint32_t *) data_area, 528);	//512+16
		rtk_writel(rtk_readl(NACR) & (~RBO) & (~WBO), NACR);
		//write data/oob address
		rtk_writel(dram_sa, NADRSAR);
		rtk_writel(oob_sa, NADTSAR);
		rtk_writel(flash_addr_t, NADFSAR);
		rtk_writel((DESC0 | DMAWE | LBC_64 & (~TAG_DIS)), NADCRR);
		check_ready();

		if (lastSec <= 0)
			lastSec = 1;
		else
			lastSec = 0;
		
		     (mtd, 0, page, buf_pos * (512 + 16), lastSec) == -1) {
			goto Error;

		}
		

		flash_addr_t += (528);	//512+16 one unit

		dma_counter--;
		buf_pos++;
	}
#ifdef SWAP_2K_DATA
	if (orig_block >= BOOT_BLOCK) {
		if (!NAND_ADDR_CYCLE) {
			unsigned char temp_val;
			{
				temp_val = dataBuf[DATA_BBI_OFF];
				{
					dataBuf[DATA_BBI_OFF] =
					    oobBuf[OOB_BBI_OFF];
					oobBuf[OOB_BBI_OFF] = temp_val;
				}
			}
		}
	}
#endif /* 

	spin_unlock_irqrestore(&lock_nand, flags_nand);
	return 0;

Error:	
	printk("rtk_check_pageData return fail...\n");
	return -1;



#endif /* 
/* Scan write data with oob to flash */
static int rtk_scan_write_bbt(struct mtd_info *mtd, int page, size_t len,
			      
{
	
	
	
	
	
	


#if 0
/* scan erase bbt */ 
static int rtknflash_erase1_cmd0(struct mtd_info *mtd, struct rtknflash *rtkn) 
{
	int addr_cycle[5], page_shift, res = 0;
	
	unsigned int flags_nand = 0;

	spin_lock_irqsave(&lock_nand, flags_nand);
	
	    //printk("[%s]:%d,page=%x\n",__func__,__LINE__,page_addr);
	    check_ready();
	rtk_writel((rtk_readl(NACR) | ECC_enable), NACR);
	rtk_writel((NWER | NRER | NDRS | NDWS), NASR);
	rtk_writel(0x0, NACMR);
	rtk_writel((CECS0 | CMD_BLK_ERASE_C1), NACMR);
	check_ready();
	addr_cycle[0] = addr_cycle[1] = 0;
	for (page_shift = 0; page_shift < 3; page_shift++) {
		addr_cycle[page_shift + 2] =
		    (page_addr >> (8 * page_shift)) & 0xff;
	}
	//rtk_writel( (enNextAD|AD2EN|AD1EN|AD0EN|(addr_cycle[2]<<CE_ADDR2)),NAADR);
	rtk_writel(((~enNextAD) & AD2EN | AD1EN | AD0EN |
		    (addr_cycle[2] << CE_ADDR0) | (addr_cycle[3] << CE_ADDR1) |
		    (addr_cycle[4] << CE_ADDR2)), NAADR);
	check_ready();
	rtk_writel((CECS0 | CMD_BLK_ERASE_C2), NACMR);
	check_ready();
	rtk_writel((CECS0 | CMD_BLK_ERASE_C3), NACMR);
	check_ready();

	
		goto Error;
	}
	
	return 0;

Error:	
	//printk("[%s] erasure is not completed at block %d\n", __FUNCTION__, page/ppb);
	printk("erase error\n");
	return -1;



#endif /* 

{
	
	
	
	



#endif /* 
/*  buf = data + oob */ 
static int rtk_block_isbad(struct mtd_info *mtd, u16 chipnr, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	unsigned char block_status_p1;
	
	
	
	
	page_offset = page & (ppb - 1);
	block = page / ppb;

	if (isLastPage) {
		page = block * ppb + (ppb - 1);
		
			
				page);
			return 1;
		}
		
#ifdef SWAP_2K_DATA
		    block_status_p1 = rtkn->buf[page_size + OOB_BBI_OFF];
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	
		
			
				page);
			return 1;
		}
		
#ifdef SWAP_2K_DATA
		    block_status_p1 = rtkn->buf[page_size + OOB_BBI_OFF];
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	
	
#if defined(CONFIG_RTK_REMAP_BBT) || defined(CONFIG_RTK_NORMAL_BBT)
	    if (block_status_p1 == BBT_TAG) {
		printk
		    ("INFO: Stored BBT in Die %d: block=%d , block_status_p1=0x%x\n",
		     chipnr, block, block_status_p1);
	} else
#endif
	if (block_status_p1 != 0xff) {
		
		    ("WARNING: Die %d: block=%d is bad, block_status_p1=0x%x\n",
		     chipnr, block, block_status_p1);
		return -1;
	}
	
}


/***********************************REMAP BBT********************************/ 
#ifdef CONFIG_RTK_REMAP_BBT

{
	
	
	
	
	
	
	
	
	
		
			
				
				    //read_remap_block = realblock = rtkn->bbt[i].remap_block;
				    realblock = rtkn->bbt[i].remap_block;
			
		
			
	
	
	
	    //page = block*ppb + page_offset;  
	    



{
	printk("[%s] Nand BBT Content\n", __FUNCTION__);
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	int BBs = 0;
	for (i = 0; i < RBA; i++) {
		
			
			break;
		}
		
			
				rtkn->bbt[i].BB_die, rtkn->bbt[i].bad_block,
				
			
		}
#if 0
		else {
			printk("[%d] (%d, %u, %d, %u)\n", i,
			       this->bbt[i].BB_die, this->bbt[i].bad_block,
			       this->bbt[i].RB_die, this->bbt[i].remap_block);
		}
#endif
	}
	
	    /* how much BBs */ 
	    rtkn->BBs = BBs;



{
	int i;
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	

	for (i = 0; i < RBA; i++) {
		if (rtkn->bbt[i].bad_block == blk)
			
			printk("blk 0x%x already exist\n", blk);
			return -1;
			}
	}
	return 0;
}


{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	__u32 addr;
	int block_num = (1 << this->chip_shift) / (1 << this->phys_erase_shift);
	
	int table_index = 0;
	int remap_block[RBA];
	int remap_count = 0;
	int i, j;
	int numchips = this->numchips;
	int chip_size = this->chipsize;
	int rc = 0;
	
	    //this->active_chip = numchips-1;
	    //this->select_chip(mtd, numchips-1);
	    
	if (!block_status) {
		printk("%s: Error, no enough memory for block_status\n",
		       __FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset((__u32 *) block_status, 0, block_num);

	//printk("[%s, line %d] this->numchips = %d\n",__FUNCTION__,__LINE__,this->numchips);
	for (addr = 0; addr < chip_size; addr += block_size) {
		if (rtk_block_isbad(mtd, numchips - 1, addr)) {
			int bb = addr >> this->phys_erase_shift;
			block_status[bb] = 0xff;
		}
	}

	//printk("[%s, line %d] this->numchips = %d\n",__FUNCTION__,__LINE__,this->numchips);
	for (i = 0; i < RBA; i++) {
		if (block_status[(block_num - 1) - i] == 0x00) {
			remap_block[remap_count] = (block_num - 1) - i;
			remap_count++;
		}
	}
	
	    /* if remap block is RB_INIT,remap block is bad block */ 
	    if (remap_count < RBA + 1) {
		for (j = remap_count + 1; j < RBA + 1; j++) {
			//printk("[j=%d]\n",j);
			remap_block[j - 1] = RB_INIT;
		}
	}
	//printk("[%s, line %d] this->numchips = %d\n",__FUNCTION__,__LINE__,this->numchips);
	for (i = table_index; table_index < RBA; table_index++) {
		rtkn->bbt[table_index].bad_block = BB_INIT;
		
		    /* only support one chip now */ 
		    rtkn->bbt[table_index].BB_die = numchips - 1;
		
#if 0
		    rtkn->bbt[table_index].BB_die = BB_DIE_INIT;
		
#endif /* 
		    rtkn->bbt[table_index].remap_block =
		    remap_block[table_index];
		
	
	
	    //printk("[%s, line %d] this->numchips = %d\n",__FUNCTION__,__LINE__,this->numchips);
	    kfree(block_status);

	//printk("[%s, line %d] this->numchips = %d\n",__FUNCTION__,__LINE__,this->numchips);
	dma_cache_wback((unsigned long)rtkn->bbt, sizeof(BB_t) * RBA);	//czyao

EXIT:
	if (rc) {
		if (block_status)
			kfree(block_status);
	}

	return 0;
}


{
	//printk("[%s] nand driver creates B%d !!\n", __FUNCTION__, page ==0?0:1);
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter = 0;
	
	    (1 << this->phys_erase_shift) / (1 << this->page_shift);
	
#if 1
	    //printk("[%s, line %d] this->numchips = %d\n",__FUNCTION__,__LINE__,this->numchips);
	    if (scan_last_die_BB(mtd)) {
		printk("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1;
	}
	
#endif /* 
	    //printk("[%s, line %d]\n",__FUNCTION__,__LINE__);
	    mem_page_num = (sizeof(BB_t) * RBA + page_size - 1) / page_size;
	temp_BBT = kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!temp_BBT) {
		printk("%s: Error, no enough memory for temp_BBT\n",
		       __FUNCTION__);
		return -ENOMEM;
	}
	//printk("[%s, line %d]\n",__FUNCTION__,__LINE__);
	memset(temp_BBT, 0xff, mem_page_num * page_size);

	//this->select_chip(mtd, 0);

	if (rtk_scan_erase_bbt(mtd, page)) {
		
		    //printk("[%s]erase block %d failure !!\n", __FUNCTION__, page/ppb);
		    rc = -1;
		
#ifdef SWAP_2K_DATA
		    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
		
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    
		    //mark as bad block;
		    if (isLastPage) {
			
					    temp_BBT, &rtkn->buf[page_size]);
			
					    temp_BBT, &rtkn->buf[page_size]);
		
			
					    &rtkn->buf[page_size]);
			
					    temp_BBT, &rtkn->buf[page_size]);
		
		
	}
	
#ifdef SWAP_2K_DATA
	    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
	
	
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	    memcpy(temp_BBT, rtkn->bbt, sizeof(BB_t) * RBA);
	
		
		     (mtd, (page + page_counter), page_size,
		      temp_BBT + page_counter * page_size,
		      &rtkn->buf[page_size])) {
			
				__FUNCTION__, page == 0 ? 0 : 1,
				page + page_counter);
			
			
			
#ifdef SWAP_2K_DATA
			    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
			
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    //mark as bad block;
			    if (isLastPage) {
				
						    page_size, temp_BBT,
						    &rtkn->buf[page_size]);
				
						    page_size, temp_BBT,
						    &rtkn->buf[page_size]);
			
				
						    temp_BBT,
						    &rtkn->buf[page_size]);
				
						    temp_BBT,
						    &rtkn->buf[page_size]);
			
			
		
		page_counter++;
		mem_page_num--;
	}

EXIT:
	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}


{
	
	
	
	
	__u8 isbbt;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter = 0, mem_page_num_tmp = 0;
	u8 load_bbt_error = 0, is_first_boot = 1, error_count = 0;
	int numchips = this->numchips;
	unsigned int bbt_page;
	
	    (1 << this->phys_erase_shift) / (1 << this->page_shift);
	
	
	
	    //__u8 check0, check1, check2, check3;
	    dma_cache_wback((unsigned long)rtkn->bbt, sizeof(BB_t) * RBA);	//czyao

	//bbt_page = ((BOOT_SIZE/block_size)-BACKUP_BBT)*ppb;
	bbt_page = ((REMAP_BBT_POS / block_size) + BACKUP_BBT) * ppb;
	
	
	    /* check */ 
	    if (mem_page_num > ppb)
		
		
			mem_page_num);
		
		
	
		  __LINE__, mem_page_num, bbt_page);

	temp_BBT = kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!temp_BBT) {
		printk("%s: Error, no enough memory for temp_BBT\n",
		       __FUNCTION__);
		return -ENOMEM;
	}
	
	//NEW method!
	for (i = 0; i < BACKUP_BBT; i++) {
		
		    rtk_scan_read_oob(mtd, rtkn->buf, (bbt_page + (i * ppb)),
				      page_size);
		
#ifdef SWAP_2K_DATA
		    isbbt = rtkn->buf[page_size + OOB_BBI_OFF];
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    
			
				is_first_boot = 0;
		}
	}
	//printk("%s: is_first_boot:%d\n\r",__FUNCTION__, is_first_boot);
	//is_first_boot = 1;
	
#if 1
	    for (i = 0; i < BACKUP_BBT; i++) {
		mem_page_num_tmp = mem_page_num;
		page_counter = 0;
		load_bbt_error = 0;
		rc = rtk_block_isbad(mtd, numchips - 1,
				     (bbt_page + (i * ppb)) * page_size);
		if (!rc) {
			printk("load bbt table:%d page:%d\n\r", i,
			       (bbt_page + (i * ppb)));
			//rc = rtk_read_ecc_page(bbt_page+(i*ppb), &NfDataBuf, &NfSpareBuf,page_size);
			rc = rtk_scan_read_oob(mtd, rtkn->buf,
					       (bbt_page + (i * ppb)),
					       page_size);
			
#ifdef SWAP_2K_DATA
			    isbbt = rtkn->buf[page_size + OOB_BBI_OFF];
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    
				
#if 1
				    if (isbbt == BBT_TAG) {
					
					    //if(0){
					    printk
					    ("[%s] have created bbt table:%d on block %d, just loads it !!\n\r",
					     __FUNCTION__, i,
					     (bbt_page / ppb) + i);
					
					    //memcpy( temp_BBT, &NfDataBuf, page_size );
					    memcpy(temp_BBT, rtkn->buf,
						   page_size);
					
					mem_page_num_tmp--;
					while (mem_page_num_tmp > 0) {
						
#if 1
						    if (rtk_scan_read_oob
							(mtd, rtkn->buf,
							 (bbt_page + (i * ppb) +
							  page_counter),
							 page_size)) {
							
							    ("[%s] load bbt table%d error!!\n\r",
							     __FUNCTION__, i);
							
									    (bbt_page
									     +
									     (ppb
									      *
									      i)));
							
#ifdef SWAP_2K_DATA
							    memset(rtkn->buf,
								   0xff,
								   MAX_RTKN_BUF_SIZE);
							
								   OOB_BBI_OFF]
							    = 0x00;
							
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
							    
								
								    (mtd,
								     (bbt_page +
								      (ppb *
								       i) +
								      (ppb -
								       1)),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
								
								    (mtd,
								     (bbt_page +
								      (ppb *
								       i) +
								      (ppb -
								       2)),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
							
								
								    (mtd,
								     (bbt_page +
								      (ppb *
								       i)),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
								
								    (mtd,
								     (bbt_page +
								      (ppb *
								       i) + 1),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
							
							
							
							break;
						}
						
#endif /* 
#if 1
#ifdef SWAP_2K_DATA
						    isbbt =
						    rtkn->buf[page_size +
							      OOB_BBI_OFF];
						
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
						    if (isbbt == BBT_TAG) {	//check bb tag in each page!
							memcpy(temp_BBT +
							       page_counter *
							       page_size,
							       rtkn->buf,
							       page_size);
							
							
						
							load_bbt_error = 1;
							error_count++;
							printk
							    ("[%s] check bbt table%d tag:0x%x fail!!\n\r",
							     __FUNCTION__, i,
							     isbbt);
							break;
						}
						
#endif /* 
					}
					if (!load_bbt_error) {
						memcpy(rtkn->bbt, temp_BBT,
						       sizeof(BB_t) * RBA);
						
						    ("check bbt table:%d OK\n\r",
						     i);
						goto CHECK_BBT_OK;
					}
				} else {
					if (is_first_boot) {
						printk
						    ("Create bbt table:%d is_first_boot:%d\n\r",
						     i, is_first_boot);
						rtk_create_bbt(mtd,
							       bbt_page +
							       (i * ppb));
					
				}
				
#endif /* 
			} else {
				printk("read bbt table:%d page:%d\n\r", i,
				       (bbt_page + (i * ppb)));
				
						    (bbt_page + (ppb * i)));
				
#ifdef SWAP_2K_DATA
				    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
				
				
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
				    
					
							    (bbt_page +
							     (ppb * i) + (ppb -
									  1)),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_page +
							     (ppb * i) + (ppb -
									  2)),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
				
					
							    (bbt_page +
							     (ppb * i)),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_page +
							     (ppb * i) + 1),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
				
			
		} else {
			printk("bbt table:%d block:%d page:%d is bad\n\r", i,
			       (bbt_page / ppb) + i, bbt_page + (i * ppb));
			error_count++;
		}
	}
	
#endif /* 
CHECK_BBT_OK:
	dump_BBT(mtd);

	if (temp_BBT)
		kfree(temp_BBT);
	
		rc = -1;
		printk("%d bbt table are all bad!(T______T)\n\r", BACKUP_BBT);
	}
	
	
}

static int create_v2r_remapping(struct mtd_info *mtd, unsigned int page,
				unsigned int block_v2r_num)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	unsigned char mem_page_num, page_counter = 0;
	unsigned char *temp_BBT = 0;
	int rc = 0;
	int numchips = this->numchips;
	unsigned int search_region = 0, count = 0;
	unsigned int block_size = (1 << this->phys_erase_shift);
	unsigned int page_size = (1 << this->page_shift);
	
	search_region = (block_v2r_num << this->phys_erase_shift);
	
	    (1 << this->phys_erase_shift) / (1 << this->page_shift);
	
	    /* need modify */ 
	    while (offs_real < search_region) {
		
			offs_real += block_size;
		
			//this->bbt_v2r[count].block_v = (offs >> this->phys_erase_shift);
			rtkn->bbt_v2r[count].block_r =
			    (offs_real >> this->phys_erase_shift);
			
			offs_real += block_size;
			//printk("bbt_v2r[%d].block_v %d,  bbt_v2r[%d].block_r %d\n",count,bbt_v2r[count].block_v,count,bbt_v2r[count].block_r);
			count++;
		}
	}
	//printk("[%s, line %d] block_v2r_num %d\n\r",__FUNCTION__,__LINE__, block_v2r_num);

	mem_page_num =
	    ((sizeof(BB_v2r) * block_v2r_num) + page_size - 1) / page_size;
	//printk("[%s, line %d] mem_page_num = %d\n\r",__FUNCTION__,__LINE__,mem_page_num);

	//temp_BBT = (unsigned char *) malloc( mem_page_num*page_size);
	temp_BBT =
	    (unsigned char *)kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!temp_BBT) {
		printk("%s: Error, no enough memory for temp_BBT v2r\n\r",
		       __FUNCTION__);
		rc = -1;
		goto EXIT_V2R;
	}
	memset(temp_BBT, 0xff, mem_page_num * page_size);
	
		
		    //printk("[%s]erase block %d failure !!\n\r", __FUNCTION__, page/this->ppb);
		    rc = -1;
		
#ifdef SWAP_2K_DATA
		    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
		
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    
		    //mark as bad block;
		    if (isLastPage) {
			
					    rtkn->buf, &rtkn->buf[page_size]);
			
					    rtkn->buf, &rtkn->buf[page_size]);
		
			
					    &rtkn->buf[page_size]);
			
					    rtkn->buf, &rtkn->buf[page_size]);
		
		
	}
	
#ifdef SWAP_2K_DATA
	    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
	
	
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	    
	
	    //dump_mem((unsigned int)temp_BBT,512);
	    while (mem_page_num > 0) {
		
		     (mtd, (page + page_counter), page_size,
		      temp_BBT + page_counter * page_size,
		      &rtkn->buf[page_size])) {
			
				__FUNCTION__, page + page_counter);
			
			
			
#ifdef SWAP_2K_DATA
			    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
			
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    
			    //mark as bad block;
			    if (isLastPage) {
				
						    page_size, temp_BBT,
						    &rtkn->buf[page_size]);
				
						    page_size, temp_BBT,
						    &rtkn->buf[page_size]);
			
				
						    temp_BBT,
						    &rtkn->buf[page_size]);
				
						    temp_BBT,
						    &rtkn->buf[page_size]);
			
			
		
		//printk("[%s, line %d] mem_page_num = %d page_counter %d\n\r",__FUNCTION__,__LINE__,mem_page_num, page_counter);
		page_counter++;
		
	
EXIT_V2R:
		kfree(temp_BBT);
	return rc;


static int rtk_scan_v2r_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int bbt_v2r_page;
	int rc = 0, i = 0, error_count = 0;
	unsigned char isbbt = 0;
	unsigned char mem_page_num = 0, page_counter = 0, mem_page_num_tmp = 0;
	unsigned char *temp_BBT = NULL;
	unsigned int block_v2r_num = 0;
	unsigned int block_size = (1 << this->phys_erase_shift);
	unsigned int page_size = (1 << this->page_shift);
	
	
	
	struct rtknflash *rtkn = this->priv;
	
	    (1 << this->phys_erase_shift) / (1 << this->page_shift);
	
	    //bbt_v2r_page = ((BOOT_SIZE/block_size)-(2*BACKUP_BBT))*ppb;
	    bbt_v2r_page = (REMAP_BBT_POS / block_size) * ppb;
	
	
		  (1 << this->chip_shift) / block_size);
	
#if 0
	    block_v2r_num =
	    (unsigned int)(this->chip_size) / block_size -
	    ((unsigned int)(this->chipsize) / block_size) * RBA_PERCENT / 100;
	
#endif /* 
	    
		    block_v2r_num);
	
	    //printk("[%s, line %d] block_v2r_num %d bbt_v2r_page %x this->phys_erase_shift:%x\n\r",__FUNCTION__,__LINE__, block_v2r_num, bbt_v2r_page,this->phys_erase_shift);
	    //create virtual block to real good block remapping!!!
	    dma_cache_wback((unsigned long)rtkn->bbt_v2r, (sizeof(BB_v2r) * block_v2r_num));	//czyao
	
	    ((sizeof(BB_v2r) * block_v2r_num) + page_size - 1) / page_size;
	
	    /* check */ 
	    if (mem_page_num > ppb)
		
		
			mem_page_num);
		
		
	
	    (unsigned char *)kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!temp_BBT) {
		printk("%s: Error, no enough memory for temp_BBT_v2r\n",
		       __FUNCTION__);
		return -1;
	}
	
	
	    //test NEW method!
	    for (i = 0; i < BACKUP_BBT; i++) {
		
		
		    rtk_scan_read_oob(mtd, rtkn->buf,
				      (bbt_v2r_page + (i * ppb)), page_size);
		
		
#ifdef SWAP_2K_DATA
		    isbbt = rtkn->buf[page_size + OOB_BBI_OFF];
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    
			if (isbbt == BBT_TAG)	//bbt has already created
				is_first_boot = 0;
		}
	}
	
	
	    //is_first_boot = 1;
	    //printk("%s: is_first_boot:%d\n\r",__FUNCTION__, is_first_boot);
	    for (i = 0; i < BACKUP_BBT; i++) {
		mem_page_num_tmp = mem_page_num;
		page_counter = 0;
		load_bbt_error = 0;
		rc = rtk_block_isbad(mtd, numchips - 1,
				     (bbt_v2r_page + (i * ppb)) * page_size);
		if (!rc) {
			printk("load bbt v2r table:%d page:%d\n\r", i,
			       (bbt_v2r_page + (i * ppb)));
			rc = rtk_scan_read_oob(mtd, rtkn->buf,
					       (bbt_v2r_page + (i * ppb)),
					       page_size);
			
#ifdef SWAP_2K_DATA
			    isbbt = rtkn->buf[page_size + OOB_BBI_OFF];
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    
			
				if (isbbt == BBT_TAG) {
					
					    //if(0){
					    printk
					    ("[%s] have created v2r bbt table:%d on block %d, just loads it !!\n\r",
					     __FUNCTION__, i,
					     (bbt_v2r_page / ppb) + i);
					memcpy(temp_BBT, rtkn->buf, page_size);
					
					mem_page_num_tmp--;
					
						     __LINE__);
					
						//if( rtk_read_ecc_page((bbt0_block_num+(i*ppb)+page_counter), &NfDataBuf, &NfSpareBuf, page_size)){
						if (rtk_scan_read_oob
						    (mtd, rtkn->buf,
						     (bbt_v2r_page + (i * ppb) +
						      page_counter),
						     page_size)) {
							
							    ("[%s] load v2r bbt table%d error!!\n\r",
							     __FUNCTION__, i);
							rtk_scan_erase_bbt(mtd,
									   (bbt_v2r_page
									    +
									    (ppb
									     *
									     i)));
							
#ifdef SWAP_2K_DATA
							    memset(rtkn->buf,
								   0xff,
								   MAX_RTKN_BUF_SIZE);
							
								   OOB_BBI_OFF]
							    = 0x00;
							
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
							    
								
								    (mtd,
								     (bbt_v2r_page
								      +
								      (ppb *
								       i) +
								      (ppb -
								       1)),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
								
								    (mtd,
								     (bbt_v2r_page
								      +
								      (ppb *
								       i) +
								      (ppb -
								       2)),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
							
								rtk_scan_write_bbt
								    (mtd,
								     (bbt_v2r_page
								      +
								      (ppb *
								       i)),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
								
								    (mtd,
								     (bbt_v2r_page
								      +
								      (ppb *
								       i) + 1),
								     page_size,
								     temp_BBT,
								     &rtkn->buf
								     [page_size]);
							
							load_bbt_error = 1;
							error_count++;
							break;
						}
						
							     __func__,
							     __LINE__);
						
#ifdef SWAP_2K_DATA
						    isbbt =
						    rtkn->buf[page_size +
							      OOB_BBI_OFF];
						
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
						    if (isbbt == BBT_TAG) {	//check bb tag in each page!
							nand_printf("[%s]:%d\n",
								    __func__,
								    __LINE__);
							
								page_counter *
								page_size,
								rtkn->buf,
								page_size);
							
							    ("[%s]:%d\n",
							     __func__,
							     __LINE__);
							
							mem_page_num_tmp--;
						} else {
							load_bbt_error = 1;
							error_count++;
							printk
							    ("[%s] check v2r bbt table%d tag:0x%x fail!!\n\r",
							     __FUNCTION__, i,
							     isbbt);
							break;
						}
					}
					if (!load_bbt_error) {
						
							       __func__,
							       __LINE__);
						
							sizeof(BB_v2r) *
							(block_v2r_num));
						
						    ("check v2r bbt table:%d OK\n\r",
						     i);
						goto CHECK_BBT_OK;
					}
				} else {
					if (is_first_boot) {
						printk
						    ("Create v2r bbt table:%d is_first_boot:%d\n\r",
						     i, is_first_boot);
						create_v2r_remapping(mtd,
								     bbt_v2r_page
								     +
								     (i * ppb),
								     block_v2r_num);
					}
				}
			} else {
				printk("read v2r bbt table:%d page:%d\n\r", i,
				       (bbt_v2r_page + (i * ppb)));
				rtk_scan_erase_bbt(mtd,
						   (bbt_v2r_page + (ppb * i)));
				
#ifdef SWAP_2K_DATA
				    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
				
				
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
				    if (isLastPage) {
					
							    (bbt_v2r_page +
							     (ppb * i) + (ppb -
									  1)),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_v2r_page +
							     (ppb * i) + (ppb -
									  2)),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
				
					
							    (bbt_v2r_page +
							     (ppb * i)),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_v2r_page +
							     (ppb * i) + 1),
							    page_size, temp_BBT,
							    &rtkn->buf
							    [page_size]);
				
			
		} else {
			printk("v2r bbt table:%d block:%d page:%d is bad\n\r",
			       i, (bbt_v2r_page / ppb) + i,
			       bbt_v2r_page + (i * ppb));
			error_count++;
		}
	}
CHECK_BBT_OK:
	    /* test */ 
	    
		kfree(temp_BBT);
	
		rc = -1;
		printk("%d v2r table are all bad!(T______T)\n\r", BACKUP_BBT);
	}

	return rc;
}


{
	int rc = 0, i = 0, error_count = 0;
	struct nand_chip *this = mtd->priv;
	
	
	    //unsigned char active_chip = this->active_chip;
	unsigned int ppb =
	    (1 << this->phys_erase_shift) / (1 << this->page_shift);
	
	
	unsigned char mem_page_num, page_counter = 0, mem_page_num_tmp = 0;
	int numchips = this->numchips;

	u8 *temp_BBT = 0;

	//bbt_page = ((BOOT_SIZE >> this->phys_erase_shift)-BACKUP_BBT)*ppb;
	bbt_page =
	    ((REMAP_BBT_POS >> this->phys_erase_shift) + BACKUP_BBT) * ppb;
	
	
		mem_page_num, bbt_page);

	temp_BBT = kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!(temp_BBT)) {
		printk("%s: Error, no enough memory for temp_BBT\n",
		       __FUNCTION__);
		return -1;
	}

	memset(temp_BBT, 0xff, mem_page_num * page_size);
	memcpy(temp_BBT, bbt, sizeof(BB_t) * rtkn->RBA);
	
#ifdef SWAP_2K_DATA
	    rtkn->buf[page_size + OOB_BBI_OFF] = BBT_TAG;
	
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	    
	    //this->select_chip(mtd, numchips-1);   
	    
		mem_page_num_tmp = mem_page_num;
		page_counter = 0;
		
#ifdef SWAP_2K_DATA
		    rtkn->buf[page_size + OOB_BBI_OFF] = BBT_TAG;
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    
		    //this->select_chip(mtd, numchips-1);                           
		    if (rtk_scan_erase_bbt(mtd, (bbt_page + (ppb * i)))) {
			
				__FUNCTION__, i, bbt_page + (ppb * i));
			/*erase fail: mean this block is bad, so do not write data!!! */ 
#ifdef SWAP_2K_DATA
			    rtkn->buf[page_size + OOB_BBI_OFF] = BBT_TAG;
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    //mark as bad block;
			    if (isLastPage) {
				
						    (bbt_page + (ppb * i) +
						     ppb - 1), page_size,
						    temp_BBT,
						    &rtkn->buf[page_size]);
				
						    (bbt_page + (ppb * i) +
						     ppb - 2), page_size,
						    temp_BBT,
						    &rtkn->buf[page_size]);
			
				
						    page_size, temp_BBT,
						    &rtkn->buf[page_size]);
				
						    (bbt_page + (ppb * i) + 1),
						    page_size, temp_BBT,
						    &rtkn->buf[page_size]);
			
			
			error_count++;
		}
		while (mem_page_num_tmp > 0) {
			
			     (mtd, (bbt_page + (ppb * i) + page_counter),
			      page_size, temp_BBT + page_counter * page_size,
			      &rtkn->buf[page_size])) {
				
						    (bbt_page + (ppb * i)));
				
				    //this->erase_block(mtd, numchips-1, bbt_page+(ppb*i));
#ifdef SWAP_2K_DATA
				    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
				
				
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
				    //mark as bad block;
				    if (isLastPage) {
					
							    (bbt_page +
							     (ppb * i) + ppb -
							     1), page_size,
							    temp_BBT,
							    &rtkn->buf[page_size
								       +
								       OOB_BBI_OFF]);
					
							    (bbt_page +
							     (ppb * i) + ppb -
							     2), page_size,
							    temp_BBT,
							    &rtkn->buf[page_size
								       +
								       OOB_BBI_OFF]);
				
					
							    (bbt_page +
							     (ppb * i)),
							    page_size, temp_BBT,
							    &rtkn->buf[page_size
								       +
								       OOB_BBI_OFF]);
					
							    (bbt_page +
							     (ppb * i) + 1),
							    page_size, temp_BBT,
							    &rtkn->buf[page_size
								       +
								       OOB_BBI_OFF]);
				
				
				
			
			
			mem_page_num_tmp--;
		}

	}
	
	    //this->select_chip(mtd, active_chip);
EXIT:
	if (temp_BBT)
		kfree(temp_BBT);
	if (error_count >= BACKUP_BBT) {
		rc = -1;
		printk("%d bbt table are all bad!(T______T)\n\r", BACKUP_BBT);
	}
	return rc;
}


#if 0
/* erase|write|read function for ops */ 
static rtk_remapBBT_erase(struct mtd_info *mtd, unsigned int page_addr) 
{
	
	

	spin_lock_irqsave(&lock_nand, flags_nand);
	
	    //printk("[%s]:%d,page=%x\n",__func__,__LINE__,page_addr);
	    check_ready();
	rtk_writel((rtk_readl(NACR) | ECC_enable), NACR);
	rtk_writel((NWER | NRER | NDRS | NDWS), NASR);
	rtk_writel(0x0, NACMR);
	rtk_writel((CECS0 | CMD_BLK_ERASE_C1), NACMR);
	check_ready();
	addr_cycle[0] = addr_cycle[1] = 0;
	for (page_shift = 0; page_shift < 3; page_shift++) {
		addr_cycle[page_shift + 2] =
		    (page_addr >> (8 * page_shift)) & 0xff;
	}
	//rtk_writel( (enNextAD|AD2EN|AD1EN|AD0EN|(addr_cycle[2]<<CE_ADDR2)),NAADR);
	rtk_writel(((~enNextAD) & AD2EN | AD1EN | AD0EN |
		    (addr_cycle[2] << CE_ADDR0) | (addr_cycle[3] << CE_ADDR1) |
		    (addr_cycle[4] << CE_ADDR2)), NAADR);
	check_ready();
	rtk_writel((CECS0 | CMD_BLK_ERASE_C2), NACMR);
	check_ready();
	rtk_writel((CECS0 | CMD_BLK_ERASE_C3), NACMR);
	check_ready();
	
		
	
	
	



			    int oob_required, int page) 
{
	
	
	
	int dma_counter = 4, page_shift, page_num[3], buf_pos = 0;
	int dram_sa, oob_sa;
	unsigned long flash_addr_t = 0;
	unsigned int flags_nand = 0;
	uint8_t *oobBuf = chip->oob_poi;
	int orig_block = page / (mtd->erasesize / mtd->writesize);

	int i;
	//printk("[%s]:%d,page=%x\n",__func__,__LINE__,page);
	spin_lock_irqsave(&lock_nand, flags_nand);

	/* get the real page */ 
	    //__flush_cache_all();
	    /* addr */
	    uint8_t * oob_area, *data_area, data_area0[512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4];	//data,oob point must 32 cache aligment
	memset(data_area0, 0xff,
	       512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4);
	data_area = data_area0;
	oob_area = (uint8_t *) data_area + 512;
	oob_sa = ((uint32_t) (oob_area) & (~M_mask));
	dram_sa = ((uint32_t) data_area) & (~M_mask);

	/* flash addr */
	for (page_shift = 0; page_shift < 3; page_shift++) {
		page_num[page_shift] = ((page >> (8 * page_shift)) & 0xff);
		flash_addr_t |= (page_num[page_shift] << (12 + 8 * page_shift));
	}

	rtk_writel(0xC00FFFFF, NACR);	//Enable ECC  
	rtk_writel(0x0000000F, NASR);	//clear NAND flash status register

	while (dma_counter > 0) {

		int lastSec = dma_counter - 1;
		//set DMA RAM DATA start address                
		rtk_writel(dram_sa, NADRSAR);
		//set DMA RAM oob start address , always use oob_sa buffer
		rtk_writel(oob_sa, NADTSAR);
		//set DMA flash start address,
		rtk_writel(flash_addr_t, NADFSAR);

		dma_cache_wback_inv((uint32_t *) data_area, 528);
		//DMA read command
		rtk_writel(((~TAG_DIS) & (DESC0 | DMARE | LBC_64)), NADCRR);
		check_ready();

		if (lastSec <= 0)
			lastSec = 1;
		else
			lastSec = 0;

		if (rtk_check_pageData
		    (mtd, 0, page, buf_pos * (512 + 16), lastSec) == -1) {
			goto Error;
		}
		//copy data
		memcpy(buf + (buf_pos * 512), data_area, 512);
		//copy oob
		memcpy(oobBuf + (buf_pos * 16), oob_area, 16);

		flash_addr_t += 528;
		dma_counter--;
		buf_pos++;
	}

#ifdef SWAP_2K_DATA
	if (orig_block >= BOOT_BLOCK) {
		if (!NAND_ADDR_CYCLE) {
			/*switch bad block info */
			unsigned char temp_val = 0;
			{
				temp_val = buf[DATA_BBI_OFF];
				{
					buf[DATA_BBI_OFF] = oobBuf[OOB_BBI_OFF];
					oobBuf[OOB_BBI_OFF] = temp_val;
				}
			}
		}
	}
#endif

	nand_printf("[%s]:%d\n", __func__, __LINE__);
	spin_unlock_irqrestore(&lock_nand, flags_nand);
	return 0;



			     int page, int oob_required) 
{
	
	
	int page = rtkn->curr_page_addr, dma_counter =
	    4, page_shift, page_num[3], buf_pos = 0;
	int dram_sa, oob_sa;
	unsigned long flash_addr_t = 0;
	unsigned int flags_nand = 0;
	unsigned int ppb = mtd->erasesize / mtd->writesize;
	uint8_t *dataBuf = buf, *oobBuf = chip->oob_poi;
	int orig_block = page / ppb, res;

	spin_lock_irqsave(&lock_nand, flags_nand);
	//__flush_cache_all();

	/* addr */
	uint8_t *oob_area, *data_area, data_area0[512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4];	//data,oob point must 32 cache aligment
	memset(data_area0, 0xff,
	       512 + 16 + CACHELINE_SIZE + CACHELINE_SIZE - 4);
	data_area = (uint8_t *) ((uint32_t) (data_area0 + 12) & 0xFFFFFFF0);
	oob_area = (uint8_t *) data_area + 512;
	oob_sa = ((uint32_t) (oob_area) & (~M_mask));
	dram_sa = ((uint32_t) data_area) & (~M_mask);

#ifdef SWAP_2K_DATA
	if (orig_block >= BOOT_BLOCK) {
		if (!NAND_ADDR_CYCLE) {
			unsigned char temp_val;
			{
				temp_val = dataBuf[DATA_BBI_OFF];
				{
					dataBuf[DATA_BBI_OFF] =
					    oobBuf[OOB_BBI_OFF];
					oobBuf[OOB_BBI_OFF] = temp_val;
				}
			}
		}
	}
#endif

	/* flash addr */
	for (page_shift = 0; page_shift < 3; page_shift++) {
		page_num[page_shift] = ((page >> (8 * page_shift)) & 0xff);
		flash_addr_t |= (page_num[page_shift] << (12 + 8 * page_shift));
	}
	rtk_writel(0xC00FFFFF, NACR);	//Enable ECC  
	rtk_writel(0x0000000F, NASR);	//clear NAND flash status register

	while (dma_counter > 0) {

		int lastSec = dma_counter - 1;
		memcpy(oob_area, oobBuf + (buf_pos * 16), 16);
		memcpy(data_area, dataBuf + (buf_pos * 512), 512);
		dma_cache_wback_inv((uint32_t *) data_area, 528);	//512+16
		rtk_writel(rtk_readl(NACR) & (~RBO) & (~WBO), NACR);
		//write data/oob address
		rtk_writel(dram_sa, NADRSAR);
		rtk_writel(oob_sa, NADTSAR);
		rtk_writel(flash_addr_t, NADFSAR);
		rtk_writel((DESC0 | DMAWE | LBC_64 & (~TAG_DIS)), NADCRR);
		check_ready();

		if (lastSec <= 0)
			lastSec = 1;
		else
			lastSec = 0;
		
		     (mtd, 0, page, buf_pos * (512 + 16), lastSec) == -1) {
			goto Error;

		}
		

		flash_addr_t += (528);	//512+16 one unit

		dma_counter--;
		buf_pos++;
	}
#ifdef SWAP_2K_DATA
	if (orig_block >= BOOT_BLOCK) {
		if (!NAND_ADDR_CYCLE) {
			unsigned char temp_val;
			{
				temp_val = dataBuf[DATA_BBI_OFF];
				{
					dataBuf[DATA_BBI_OFF] =
					    oobBuf[OOB_BBI_OFF];
					oobBuf[OOB_BBI_OFF] = temp_val;
				}
			}
		}
	}
#endif /* 

	spin_unlock_irqrestore(&lock_nand, flags_nand);
	return 0;



#endif /* 

			     const uint8_t * buf, int oob_required) 
{
	
	
	
	    (mtd->erasesize) / (mtd->writesize), block;
	
	
		
		
			
			     && rtkn->bbt[i].remap_block != RB_INIT) {
				
				    /* do have one chip */ 
#if 0
				    if (chipnr != chipnr_remap)
					
				
				else
					
				
#endif /* 
				    rtkn->bbt[i].bad_block = page / ppb;
				
				
			
		
		
			
				__FUNCTION__);
			
		
		
		
			
			
		
		
	
	
	
	
#ifdef CONFIG_JFFS2_FS
	    /* need read cleanmarker */ 
	    if (backup_offset == 0)
		
	
#endif /* 
	    
	
		block * ppb, block * ppb + backup_offset - 1);
	
	    //memset(rtkn->buf,0xff,MAX_RTKN_BUF_SIZE);
	    for (i = 0; i < backup_offset; i++) {
		
				   page_size);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
	
	    /* check */ 
	    if (oob_required) {
		
	
	
			      page_size, buf, &rtkn->buf[page_size]);
	
		block_remap * ppb + backup_offset);
	
	
#ifdef SWAP_2K_DATA
	    rtkn->buf[page_size + OOB_BBI_OFF] = 0x00;
	
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	    
	
	
		
		
				    rtkn->buf, &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
		
		
				    &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
	



{
	
	
	
	    (mtd->erasesize) / (mtd->writesize), block, block_remap =
	    0x12345678, page_size = (1 << this->page_shift);
	
	
		
		
			
			     && rtkn->bbt[i].remap_block != RB_INIT) {
				
				    /* do have one chip */ 
#if 0
				    if (chipnr != chipnr_remap)
					
				
				else
					
				
#endif /* 
				    rtkn->bbt[i].bad_block = page / ppb;
				
				
			
		
		
			
				__FUNCTION__);
			
		
		
		
			
			
		
		
	
	
	
#ifdef SWAP_2K_DATA
	    rtkn->buf[page_size + OOB_BBI_OFF] = 0x00;
	
#else /* 
#error "should open SWAP_2K_DATA macro"
#endif /* 
	    if (isLastPage) {
		
		
				    rtkn->buf, &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
		
		
				    &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
	



{
	
	
	
	    (mtd->erasesize) / (mtd->writesize), block, block_remap =
	    0x12345678, page_size = (1 << this->page_shift);
	
	
		
		
			
			     && rtkn->bbt[i].remap_block != RB_INIT) {
				
				    /* do have one chip */ 
#if 0
				    if (chipnr != chipnr_remap)
					
				
				else
					
				
#endif /* 
				    rtkn->bbt[i].bad_block = page / ppb;
				
				
			
		
		
			
				__FUNCTION__);
			
		
		
		
			
			
		
		
	
	
	
#ifdef SWAP_2K_DATA
	    rtkn->buf[page_size + OOB_BBI_OFF] = 0x00;
	
#else /* 
#error "should open SWAP_2K_DATA macro"
#endif /* 
	    if (isLastPage) {
		
		
				    rtkn->buf, &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
		
		
				    &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
	
	    /* erase remap block */ 
	    rtk_scan_erase_bbt(mtd, block_remap * ppb);
	



#endif /* 
    
/*********************************************NORMAL BBT***************************************************/ 
#ifdef CONFIG_RTK_NORMAL_BBT
static int scan_normal_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	int block_size = 1 << this->phys_erase_shift;
	int table_index = 0;
	int i;
	int numchips = this->numchips;
	int chip_size = this->chipsize;
//      this->active_chip = numchips-1;
//      this->select_chip(mtd, numchips-1);
	for (addr = 0; addr < chip_size; addr += block_size) {
		int block_index = addr >> this->phys_erase_shift;
		if (rtk_block_isbad(mtd, numchips - 1, addr)) {
			printk("block[%d] is bad\n", block_index);
			rtkn->bbt_nor[table_index].bad_block = block_index;
			
			
			
			
		}
		if (table_index >= bbt_num) {
			printk("bad block number %d exceed bbt_num %d\n",
			       table_index, bbt_num);
			return -1;
		}
	}
	for (i = table_index; table_index < bbt_num; table_index++) {
		rtkn->bbt_nor[table_index].bad_block = BB_INIT;
		
		
		
	
	return 0;
}

static int rtk_create_normal_bbt(struct mtd_info *mtd, int page)
{
	printk("[%s] nand driver creates normal B%d !!\n", __FUNCTION__,
	       page == 0 ? 0 : 1);
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	    (mtd->erasesize) / (mtd->writesize);
	
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter = 0;
	if (scan_normal_BB(mtd)) {
		printk("[%s] scan_normal_BB() error !!\n", __FUNCTION__);
		return -1;
	}
#if 0
	if (this->numchips > 1) {
		printk("[%s, line %d]\n", __FUNCTION__, __LINE__);
		if (scan_other_normal_BB(mtd)) {
			printk("[%s] scan_last_die() error !!\n", __FUNCTION__);
			return -1;
		}
	}
#endif
	mem_page_num =
	    (sizeof(BBT_normal) * bbt_num + page_size - 1) / page_size;
	temp_BBT = kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!temp_BBT) {
		printk("%s: Error, no enough memory for temp_BBT\n",
		       __FUNCTION__);
		return -ENOMEM;
	}
	memset(temp_BBT, 0xff, mem_page_num * page_size);
//      this->select_chip(mtd, 0);
	if (rtk_scan_erase_bbt(mtd, page)) {
		
			page / ppb);
		
#ifdef SWAP_2K_DATA
		    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
		
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    if (isLastPage) {
			
					    rtkn->buf, &rtkn->buf[page_size]);
			
					    rtkn->buf, &rtkn->buf[page_size]);
		
			
					    &rtkn->buf[page_size]);
			
					    rtkn->buf, &rtkn->buf[page_size]);
		
		rc = -1;
		goto EXIT;
	}
	
#ifdef SWAP_2K_DATA
	    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
	
	
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	    
	
		
		     (mtd, (page + page_counter), page_size,
		      temp_BBT + page_counter * page_size,
		      &rtkn->buf[page_size])) {
			
				__FUNCTION__, page + page_counter);
			
			
			
#ifdef SWAP_2K_DATA
			    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
			
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    if (isLastPage) {
				
						    (page + ppb - 1),
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
				
						    (page + ppb - 2),
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
			
				
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
				
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
			
			goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}
EXIT:
	if (temp_BBT)
		kfree(temp_BBT);
	return rc;
}

int rtk_update_normal_bbt(struct mtd_info *mtd, BBT_normal * bbt_nor)
{
	int rc = 0, i = 0, error_count = 0;
	struct nand_chip *this = mtd->priv;
	
	
	    //unsigned char active_chip = this->active_chip;
	unsigned int bbt_page;
	unsigned char mem_page_num, page_counter = 0, mem_page_num_tmp = 0;
	int numchips = this->numchips;
	u8 *temp_BBT = 0;
	
	    (mtd->erasesize) / (mtd->writesize), page_size =
	    (1 << this->page_shift);
	
	    //bbt_page = ((NORMAL_BBT_POSITION >> this->phys_erase_shift)-BACKUP_BBT)*ppb;
	    bbt_page = (NORMAL_BBT_POSITION >> this->phys_erase_shift) * ppb;
	
	    (sizeof(BBT_normal) * rtkn->bbt_num + page_size - 1) / page_size;
	
		mem_page_num, bbt_page);
	temp_BBT = kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!(temp_BBT)) {
		printk("%s: Error, no enough memory for temp_BBT\n",
		       __FUNCTION__);
		return -1;
	}
	memset(temp_BBT, 0xff, mem_page_num * page_size);
	memcpy(temp_BBT, bbt_nor, sizeof(BBT_normal) * rtkn->bbt_num);
	
#ifdef SWAP_2K_DATA
	    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
	
	
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
	    //this->select_chip(mtd, numchips-1);   
	    for (i = 0; i < BACKUP_BBT; i++) {
		mem_page_num_tmp = mem_page_num;
		page_counter = 0;
		
#ifdef SWAP_2K_DATA
		    rtkn->buf[page_size + OOB_BBI_OFF] = BBT_TAG;
		
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
		    //this->select_chip(mtd, numchips-1);
		    
			
			    ("[%s]error: erase normal BBT%d page %d failure\n\r",
			     __FUNCTION__, i, bbt_page + (ppb * i));
			
#ifdef SWAP_2K_DATA
			    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
			
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    if (isLastPage) {
				
						    (bbt_page +
						     (ppb * i) + (ppb -
								  1)),
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
				
						    (bbt_page +
						     (ppb * i) + (ppb -
								  2)),
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
			
				
						    (bbt_page +
						     (ppb * i)),
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
				
						    (bbt_page +
						     (ppb * i) + 1),
						    page_size,
						    rtkn->buf,
						    &rtkn->buf[page_size]);
			
			mem_page_num_tmp = 0;
			error_count++;
		}
		while (mem_page_num_tmp > 0) {
			if (rtk_scan_write_bbt
			    (mtd, (bbt_page + (ppb * i) + page_counter),
			     page_size,
			     temp_BBT + page_counter * page_size,
			     &rtkn->buf[page_size])) {
				
				    ("[%s] write normal BBT%d page %d failure!!\n\r",
				     __FUNCTION__, i,
				     bbt_page + (ppb * i) + page_counter);
				
						    (bbt_page + (ppb * i)));
				
#ifdef SWAP_2K_DATA
				    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
				
				
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
				    if (isLastPage) {
					
							    (bbt_page +
							     (ppb * i) +
							     (ppb - 1)),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_page +
							     (ppb * i) +
							     (ppb - 2)),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
				
					
							    (bbt_page +
							     (ppb * i)),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_page +
							     (ppb * i) +
							     1),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
				
				error_count++;
				break;
			}
			page_counter++;
			mem_page_num_tmp--;
		}
	}
	//this->select_chip(mtd, active_chip);
EXIT:
	if (temp_BBT)
		kfree(temp_BBT);
	if (error_count >= BACKUP_BBT) {
		rc = -1;
		printk("normal %d bbt table are all bad!(T______T)\n\r",
		       BACKUP_BBT);
	}
	return rc;
}

static void dump_normal_BBT(struct mtd_info *mtd)
{
	printk("[%s] Nand normal BBT Content\n", __FUNCTION__);
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	int BBs = 0;
	for (i = 0; i < bbt_num; i++) {
		
			
			break;
		}
		if (rtkn->bbt_nor[i].bad_block != BB_INIT) {
			
				rtkn->bbt_nor[i].BB_die,
				rtkn->bbt_nor[i].bad_block,
				
				rtkn->bbt_nor[i].block_info);
			
		}
	}
	rtkn->BBs = BBs;


static int nand_scan_normal_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	__u8 isbbt;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter = 0, mem_page_num_tmp = 0;
	u8 load_bbt_error = 0, is_first_boot = 1, error_count = 0;
	
	
	
	
	//bbt_page = ((NORMAL_BBT_POSITION/mtd->erasesize)-BACKUP_BBT)*ppb;
	bbt_page = (NORMAL_BBT_POSITION / mtd->erasesize) * ppb;
	
	    (sizeof(BBT_normal) * bbt_num + page_size - 1) / page_size;
	
	    /* check */ 
	    if (mem_page_num > ppb) {
		
		    ("normal bbt data large than one block,block=%d\n",
		     mem_page_num);
		
	
	
		__FUNCTION__, __LINE__, mem_page_num, bbt_page);
	temp_BBT = kmalloc(mem_page_num * page_size, GFP_KERNEL);
	if (!temp_BBT) {
		printk("%s: Error, no enough memory for temp_BBT\n",
		       __FUNCTION__);
		return -ENOMEM;
	}
	memset(temp_BBT, 0xff, mem_page_num * page_size);
	for (i = 0; i < BACKUP_BBT; i++) {
		rc = rtk_block_isbad(mtd, numchips - 1,
				     (bbt_page + (i * ppb)) * page_size);
		if (!rc) {
			//rc = this->read_ecc_page(mtd, numchips-1, bbt_page+(i*ppb), this->g_databuf, this->g_oobbuf);
			rc = rtk_scan_read_oob(mtd, rtkn->buf,
					       (bbt_page + (i * ppb)),
					       page_size);
			
#ifdef SWAP_2K_DATA
			    isbbt = rtkn->buf[page_size + OOB_BBI_OFF];
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    if (!rc) {
				if (isbbt == BBT_TAG)	//bbt has already created
					is_first_boot = 0;
			}
		}
	}
	printk("%s: is_first_boot:%d\n\r", __FUNCTION__, is_first_boot);
	
		mem_page_num_tmp = mem_page_num;
		page_counter = 0;
		load_bbt_error = 0;
		rc = rtk_block_isbad(mtd, numchips - 1,
				     (bbt_page + (i * ppb)) * page_size);
		if (!rc) {
			printk("load normal bbt table:%d page:%d\n\r",
			       i, (bbt_page + (i * ppb)));
			
			    rtk_scan_read_oob(mtd, rtkn->buf,
					      (bbt_page + (i * ppb)),
					      page_size);
			
			    //rc = this->read_ecc_page(mtd, numchips-1, bbt_page+(i*ppb), this->g_databuf, this->g_oobbuf);
#ifdef SWAP_2K_DATA
			    isbbt = rtkn->buf[page_size + OOB_BBI_OFF];
			
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
			    if (!rc) {
				if (isbbt == BBT_TAG) {
					printk
					    ("[%s] have created normal bbt table:%d on block %d, just loads it !!\n\r",
					     __FUNCTION__, i,
					     (bbt_page / ppb) + i);
					memcpy(temp_BBT, rtkn->buf, page_size);
					
					mem_page_num_tmp--;
					while (mem_page_num_tmp > 0) {
						if (rtk_scan_read_oob
						    (mtd, rtkn->buf,
						     (bbt_page +
						      (i * ppb) +
						      page_counter),
						     page_size)) {
							
							    ("[%s] load normal bbt table%d error!! page:%d\n\r",
							     __FUNCTION__,
							     i,
							     bbt_page +
							     (i * ppb) +
							     page_counter);
							//this->erase_block(mtd, numchips-1, bbt_page+(ppb*i));
							rtk_scan_erase_bbt
							    (mtd,
							     (bbt_page +
							      (ppb * i)));
							
#ifdef SWAP_2K_DATA
							    memset
							    (rtkn->buf,
							     0xff,
							     MAX_RTKN_BUF_SIZE);
							
							    [page_size +
							     OOB_BBI_OFF]
							    = 0x00;
							
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
							    if (isLastPage) {
								
								    (mtd,
								     (bbt_page
								      +
								      (ppb * i)
								      +
								      (ppb
								       -
								       1)),
								     page_size,
								     rtkn->buf,
								     &rtkn->buf
								     [page_size]);
								
								    (mtd,
								     (bbt_page
								      +
								      (ppb * i)
								      +
								      (ppb
								       -
								       2)),
								     page_size,
								     rtkn->buf,
								     &rtkn->buf
								     [page_size]);
							
								
								    (mtd,
								     (bbt_page
								      +
								      (ppb
								       *
								       i)),
								     page_size,
								     rtkn->buf,
								     &rtkn->buf
								     [page_size]);
								
								    (mtd,
								     (bbt_page
								      +
								      (ppb * i)
								      +
								      1),
								     page_size,
								     rtkn->buf,
								     &rtkn->buf
								     [page_size]);
							
							load_bbt_error = 1;
							error_count++;
							break;
						}
						
#ifdef SWAP_2K_DATA
						    isbbt =
						    rtkn->buf[page_size
							      + OOB_BBI_OFF];
						
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
						    if (isbbt == BBT_TAG) {	//check bb tag in each page!
							memcpy(temp_BBT
							       +
							       page_counter
							       *
							       page_size,
							       rtkn->buf,
							       page_size);
							
							mem_page_num_tmp--;
						} else {
							load_bbt_error = 1;
							error_count++;
							printk
							    ("[%s] check normal bbt table%d tag:0x%x fail!!\n\r",
							     __FUNCTION__,
							     i, isbbt);
							break;
						}
					}
					if (!load_bbt_error) {
						memcpy(rtkn->bbt_nor,
						       temp_BBT,
						       sizeof
						       (BBT_normal) * bbt_num);
						
						    ("check normal bbt table:%d OK\n\r",
						     i);
						goto CHECK_BBT_OK;
					}
				} else {
					if (is_first_boot) {
						printk
						    ("Create normal bbt table:%d is_first_boot:%d\n\r",
						     i, is_first_boot);
						rtk_create_normal_bbt
						    (mtd, bbt_page + (i * ppb));
					}
				}
			} else {
				printk
				    ("read normal bbt table:%d page:%d fail!\n\r",
				     i, (bbt_page + (i * ppb)));
				
						    (bbt_page + (ppb * i)));
				
				    //this->erase_block(mtd, numchips-1, bbt_page+(ppb*i));
#ifdef SWAP_2K_DATA
				    memset(rtkn->buf, 0xff, MAX_RTKN_BUF_SIZE);
				
				
#else /* 
#error "should open SWAP_2K_DATA"
#endif /* 
				    if (isLastPage) {
					
							    (bbt_page +
							     (ppb * i) +
							     (ppb - 1)),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_page +
							     (ppb * i) +
							     (ppb - 2)),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
				
					
							    (bbt_page +
							     (ppb * i)),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
					
							    (bbt_page +
							     (ppb * i) +
							     1),
							    page_size,
							    rtkn->buf,
							    &rtkn->buf
							    [page_size]);
				
			}
		} else {
			printk
			    ("normal bbt table:%d block:%d page:%d is bad\n\r",
			     i, (bbt_page / ppb) + i, bbt_page + (i * ppb));
			error_count++;
		}
	}
CHECK_BBT_OK:
	dump_normal_BBT(mtd);
	if (temp_BBT)
		kfree(temp_BBT);
	if (error_count >= BACKUP_BBT) {
		rc = -1;
		printk("%d normal bbt table are all bad!(T______T)\n\r",
		       BACKUP_BBT);
	}
	return rc;
}
#endif //CONFIG_RTK_NORMAL_BBT

{
	
	
	
	
	
	
#ifdef CONFIG_RTK_REMAP_BBT
	    /* default */ 
	    rtkn->RBA_PERCENT = 5;
	
	
	
		__func__, __LINE__, RBA, rtkn->RBA_PERCENT);
	
	
		
		return -1;
	}
	//printk("%s, %s, line %d, REG(NACR) = 0x%08x\n",__FILE__,__func__,__LINE__,rtk_readl(NACR));
	memset(rtkn->bbt, 0, sizeof(BB_t) * RBA);
	
		  __LINE__, block_v2r_num);

	rtkn->bbt_v2r = kmalloc(sizeof(BB_v2r) * (block_v2r_num), GFP_KERNEL);
	
		
			
		
		
			__FUNCTION__);
		return -1;
	}
	//printk("%s, %s, line %d, REG(NACR) = 0x%08x\n",__FILE__,__func__,__LINE__,rtk_readl(NACR));
	memset(rtkn->bbt_v2r, 0, sizeof(BB_v2r) * block_v2r_num);
	
#endif /* 
#ifdef CONFIG_RTK_NORMAL_BBT
	    rtkn->BBT_PERCENT = 5;
	
	    ((u32) mtd->size / mtd->erasesize) * rtkn->BBT_PERCENT / 100;
	
		__func__, __LINE__, bbt_num, rtkn->BBT_PERCENT);
	
	
		
			__FUNCTION__);
		return -1;
	}
	memset(rtkn->bbt_nor, 0, sizeof(BBT_normal) * bbt_num);
	
#endif /* 
	    
#if defined(CONFIG_RTK_REMAP_BBT)
	    if (rtk_scan_v2r_bbt(mtd) < 0 
		
		
		
		
	
	
#elif defined(CONFIG_RTK_NORMAL_BBT)
	    if (nand_scan_normal_bbt(mtd) < 0) {
		
		
	
	
	
#else /* 
	    return -1;
	
#endif /* 

#ifdef CONFIG_RTK_REMAP_BBT
	    if (rtkn->bbt_v2r) {
		
	
	
		
	
	
#endif /* 
#ifdef CONFIG_RTK_NORMAL_BBT
	    if (rtkn->bbt_nor) {
		
	
	
#endif /* 
	    return -1;



{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	
	
	int i;
	int rc = 0;
	
	
	
	    (1 << this->phys_erase_shift) / (1 << this->page_shift);
	
	    //unsigned char buf[oob_size] __attribute__((__aligned__(4)));
	int chipnr, chipnr_remap;
	//nand_get_device(mtd, FL_WRITING);
#ifdef CONFIG_RTK_REMAP_BBT
	{
		i = (ofs >> this->phys_erase_shift);	//virtual block index
		ofs = (rtkn->bbt_v2r[i].block_r << this->phys_erase_shift);	//real block index, addr.
		printk("%s: blockv:%d blockr:%d ofs:%lld\n\r",
		       __FUNCTION__, i, rtkn->bbt_v2r[i].block_r, ofs);
	
#endif
	page = ((int)ofs) >> this->page_shift;
	chipnr = chipnr_remap = (int)(ofs >> this->chip_shift);
	
	block = page / ppb;

	//printk("%s: block:%d offs:%lld\n\r",__FUNCTION__,block, ofs);
#ifdef CONFIG_RTK_NORMAL_BBT
	for (i = 0; i < bbt_num; i++) {
		if (rtkn->bbt_nor[i].bad_block != BB_INIT) {
			
				
				    ("%s: block:%d is already mark as bad!\n",
				     __FUNCTION__, block);
				//nand_release_device(mtd);
				return 0;
			}
		} else
			break;
	}
#endif
	//this->select_chip(mtd, chipnr);
#ifdef CONFIG_RTK_NORMAL_BBT
	for (i = 0; i < bbt_num; i++) {
		if (rtkn->bbt_nor[i].bad_block == BB_INIT) {
			
			
			
			
			
		}
	}
	dump_normal_BBT(mtd);
	if (rtk_update_normal_bbt(mtd, rtkn->bbt_nor)) {
		
		//nand_release_device(mtd);
		return -1;
	}
#endif /* 
	
	    /* do update bbt here,not used maybe */ 
#if 0
#ifdef CONFIG_RTK_REMAP_BBT
	int block_remap = 0x12345678;
	
		
		
			
			     && rtkn->bbt[i].remap_block != RB_INIT) {
				
				    /* do have one chip */ 
#if 0
				    if (chipnr != chipnr_remap)
					
				
				else
					
				
#endif /* 
				    rtkn->bbt[i].bad_block = page / ppb;
				
				
			
		
		
			
			    ("[%s] RBA do not have free remap block\n",
			     __FUNCTION__);
			
		
		
		
			
			
		
		
	
#endif /* 
#endif /* 
	    
	
#ifdef SWAP_2K_DATA
	    rtkn->buf[page_size + OOB_BBI_OFF] = 0x00;
	
#else /* 
#error "should open SWAP_2K_DATA";
#endif /* 
	    
		
		
				    page_size, rtkn->buf,
				    &rtkn->buf[page_size]);
		
				    page_size, rtkn->buf,
				    &rtkn->buf[page_size]);
	
		
		
				    rtkn->buf, &rtkn->buf[page_size]);
		
				    rtkn->buf, &rtkn->buf[page_size]);
	
	
	    //nand_release_device(mtd);
	    return 0;
}

int rtkn_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip) 
{
	
	
#ifndef CONFIG_RTK_REMAP_BBT
	unsigned int page, block, page_offset, i;
	
	
	
	
#endif /* 
	    //nand_get_device(mtd, FL_READING);
#ifndef CONFIG_RTK_REMAP_BBT
	    page = ((int)ofs) >> this->page_shift;
	
	
	
		
			
				
					  
				
				    //nand_release_device(mtd);
				    return 1;
			
		
			
	
	
#endif /* 
	    //nand_release_device(mtd);
	    return val;



//#endif