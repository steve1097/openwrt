#include "rtknflash.h"
#include "rtkn_parallel_regs.h"
#include "rtkn_chip_param.h"




#define VIR_TO_PHY(x) (x & (~0xa0000000))
    
//need check
static unsigned int monflg = 0x0;

/*---------------------------------------------------------------------------------------------------------------------------------*/ 
void WAIT_DONE(unsigned int addr, unsigned int mask, unsigned int value) 
{
	
		
		
		
		



{
	



//----------------------------------------------------------------------------
int is_saturn_cpu(void) 
{
	



//----------------------------------------------------------------------------
int is_darwin_cpu(void) 
{
	



//----------------------------------------------------------------------------

{
	



//----------------------------------------------------------------------------
int is_nike_cpu(void) 
{
	



//----------------------------------------------------------------------------
int is_venus_cpu(void) 
{
	



//----------------------------------------------------------------------------
int is_neptune_cpu(void) 
{
	



//----------------------------------------------------------------------------
int is_mars_cpu(void) 
{
	



//----------------------------------------------------------------------------
int is_macarthur2_cpu(void) 
{
	



{
	
	
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 
	
	    //Set PP
	    REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0));	//Data read to      DRAM from NAND through PP               
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL1, 0x0);	//Set PP starting assdress[7:0]
	
	    //Set command
	    REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0xef));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done
	
	    //Set address, 
	    REG_WRITE_U32(REG_ND_PA0, 0x89);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]          
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done
	
	    //Reset PP
	    REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0));	//Data read to      DRAM from NAND through PP               
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable
	
	    //Set data
	    REG_WRITE_U32(REG_SRAM_CTL, NF_SRAM_CTL_map_sel(1) | NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, P1);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));	//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode         
	WAIT_DONE(REG_ND_CTL, 0xc0, 0x40);	//Wait xfer done
} 

/*---------------------------------------------------------------------------------------------------------------------------------*/ 
    
/* select chip cmd */ 
int rtkn_select_chip_cmd(int chipid)
{
	
	
		
		
	
	
	
	
		
		
	
		
	
	



{
	
	
		i++)
		
		
			
			
			
			
				
			
			
				
			
			else if (nand_chip_id[i].sycnmode == 1) {
				
				    // sync mode 
				    REG_WRITE_U32(REG_NF_MODE, 0x2);
				
					
					
						       NF_MULTI_CHNL_MODE_edo
						       (0x00));
				
			
			
			
			    nand_chip_id[i].isLastPage;
			
			
			
			
			
			    nand_chip_id[i].ecc_select;
			
			
			    nand_chip_id[i].g_enReadRetrial;
			
			
			    nand_chip_id[i].max_read_retry_cnt;
			
			    /* set feature */ 
			    switch (id_chain) {
			
			
				
				
				    &rtk_set_feature_micron;
				
				    &rtk_set_feature_micron;
				
				
#if 0
			case TC58TEG6DCJT:
			
				
				    //case TC58TEG6DDK:
				    rtkn->chip_param.set_chip_pre_param =
				    &rtk_set_pre_condition_toshiba;
				
				    &rtk_set_pre_condition_toshiba;
				
				    &rtk_set_pre_condition_toshiba;
				
				
#endif /* 
			default:
				
				
				
				    NULL;
			
			
		
		
	
		
			id_chain);
	



/* read id cmd */ 
int parallel_nand_read_id_cmd(unsigned char *id_data) 
{
	
	
	
	
	    //Set PP
	    REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0x0));
	
	
	
	    //Set command
	    REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(CMD_READ_ID));
	
	
	
	    //Set address
	    REG_WRITE_U32(REG_ND_PA0, 0);
	
	
	
			 NF_ND_CTL_xfer(1) | NF_ND_CTL_tran_mode(1));
	
	
	    //Enable XFER mode
	    REG_WRITE_U32(REG_ND_CTL,
			  NF_ND_CTL_xfer(1) | NF_ND_CTL_tran_mode(4));
	
	
	    //Reset PP
	    REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_reset(1));
	
	    //Move data to DRAM from SRAM
	    REG_WRITE_U32(REG_SRAM_CTL,
			  NF_SRAM_CTL_map_sel(1) | NF_SRAM_CTL_access_en(1) |
			  NF_SRAM_CTL_mem_region(0));
	
	
	    //printk("id_chain 1 = 0x%x \n", id_chain);
	    id_data[0] = id_chain1 & 0xff;
	
	
	
	
	
	
	    //printk("id_chain 2 = 0x%x \n", id_chain);
	    id_data[4] = id_chain2 & 0xff;
	
	
	
	
	
	
	    /* 97F little endian */ 
	    id_chain1 =
	    (id_data[0] << 24) | (id_data[1] << 16) | (id_data[2] << 8) |
	    id_data[3];
	
	



/* reset cmd */ 
void parallel_nand_reset_cmd() 
{
	
	    /* need check */ 
	    REG_WRITE_U32(REG_ND_CMD, 0xFF);
	REG_WRITE_U32(REG_ND_CTL,
		      (NF_ND_CTL_xfer(0x01) | NF_ND_CTL_tran_mode(0)));
	


/* read status cmd */ 
void parallel_nand_read_status() 
{
	
	
	
	
	    //Set PP
	    REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0x0));
	
	
	
	    //Set command
	    REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(CMD_READ_STATUS));
	
	
	
	    //Set address
	    REG_WRITE_U32(REG_ND_PA0, 0);
	
	
	
			 NF_ND_CTL_xfer(1) | NF_ND_CTL_tran_mode(1));
	
	
	    //Enable XFER mode
	    REG_WRITE_U32(REG_ND_CTL,
			  NF_ND_CTL_xfer(1) | NF_ND_CTL_tran_mode(4));
	
	
	    //Reset PP
	    REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_reset(1));
	
	    //Move data to DRAM from SRAM
	    REG_WRITE_U32(REG_SRAM_CTL,
			  NF_SRAM_CTL_map_sel(1) | NF_SRAM_CTL_access_en(1) |
			  NF_SRAM_CTL_mem_region(0));
	
	
	
	



/* erase cmd */ 
int paralledl_nand_erase_cmd(int page_addr) 
{
	
			 NF_MULTI_CHNL_MODE_no_wait_busy(1) |
			 NF_MULTI_CHNL_MODE_edo(1));
	
	
	
	
	
	
		       NF_ND_PA2_addr_mode(0x04) |
		       NF_ND_PA2_page_addr2(page_addr >> 16));
	
		       NF_ND_PA3_page_addr3((page_addr >> 21) & 0x7));
	
			 NF_AUTO_TRIG_auto_trig(1) |
			 NF_AUTO_TRIG_spec_auto_case(1) |
			 NF_AUTO_TRIG_auto_case(2));
	
	
			 NF_POLL_FSTS_bit_sel(6) | NF_POLL_FSTS_trig_poll(1));
	
	
	
		
			__FUNCTION__, page_addr);
		
	
	



/* read page */ 
int parallel_nand_read_page(struct rtknflash *rtkn, unsigned char *buf,
			    unsigned char *oobBuf, int page) 
{
	
	
	
	
	
	
	
	
	
	
		
		
	
	
		
		
		
			
			
				
				    // disable randomizer
				    REG_WRITE_U32(REG_RMZ_CTRL, 0);
				
					       NF_BLANK_CHK_blank_ena(1) |
					       NF_BLANK_CHK_read_ecc_xnor_ena
					       (1));
				
				    //printk("[DBG]ecc error, set xnor and blank to 1, REG_BLANK_CHK reg: 0x%x\n", REG_READ_U32(REG_BLANK_CHK));
			}
			
			else {
				
				    // enable randomizer
				    REG_WRITE_U32(REG_RMZ_CTRL, 1);
				
					       NF_BLANK_CHK_blank_ena(1) |
					       NF_BLANK_CHK_read_ecc_xnor_ena
					       (0));
				
				    //printk("[DBG]set xnor to 0, REG_BLANK_CHK reg: 0x%x\n", REG_READ_U32(REG_BLANK_CHK));
			}
			
			
				       NF_DATA_TL1_access_mode(1) |
				       NF_DATA_TL1_length1(4));
			
		
		else
			
			
			    // set random read
			    
			
			
			
			REG_WRITE_U32(REG_RND_SPR_STR_COL_H, page_size >> 8);	// spare start address MSB
			REG_WRITE_U32(REG_RND_SPR_STR_COL_L, page_size & 0xff);	// spare start address LSB
			REG_WRITE_U32(REG_RMZ_CTRL, 0);
			
			
				       NF_DATA_TL1_access_mode(1) |
				       NF_DATA_TL1_length1(2));
			
		
		
		    //Set PP
		    REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(1));
		
		
		
		    // enable blank check
		    //REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1) );              //need check
		    
		    //Set command
		    REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(CMD_PG_READ_C1));
		
		
		
		    //Set address
		    REG_WRITE_U32(REG_ND_PA0,
				  NF_ND_PA0_page_addr0(0xff & page));
		
			       NF_ND_PA1_page_addr1(0xff & (page >> 8)));
		
			       NF_ND_PA2_addr_mode(addr_mode) |
			       NF_ND_PA2_page_addr2(0x1f & (page >> 16)));
		
			       NF_ND_PA3_page_addr3(0x7 & (page >> 21)));
		
		
		
		
		    //Set ECC
		    if (monflg == 5566)
			
			
			
			//REG_WRITE_U32(REG_RMZ_CTRL, 1);
			}
		
		if (is_sync_mode == 0x2)
			
		
		
			
			
		
			
			
		
			
			
		
			
			
		
			
			
		
			
			
		
			
			
		
			
			
		
			
			
		
		
		    /* set oobbuf */ 
		    oob_sa = (VIR_TO_PHY((uint32_t) oobBuf) >> 3);
		
			
				       NF_SPR_DDR_CTL_spare_ddr_ena(0) |
				       NF_SPR_DDR_CTL_per_2k_spr_ena(0) |
				       NF_SPR_DDR_CTL_spare_dram_sa(oob_sa));
		
		else
			
				       NF_SPR_DDR_CTL_spare_ddr_ena(1) |
				       NF_SPR_DDR_CTL_per_2k_spr_ena(0) |
				       NF_SPR_DDR_CTL_spare_dram_sa(oob_sa));
		
		    /* set buf */ 
		    dram_sa = (VIR_TO_PHY((uint32_t) buf) >> 3);
		
		
		
		
			       NF_DMA_CTL3_ddr_wr(1) | NF_DMA_CTL3_dma_xfer(1));
		
		    // flush cache.
		    //dma_cache_inv(buf,page_size);
		    //dma_cache_inv(oobBuf,oob_size);
		    dma_cache_wback_inv((unsigned long)buf,
					(unsigned long)page_size);
		
				     (unsigned long)oob_size);
		
		    //Enable Auto mode
		    REG_WRITE_U32(REG_AUTO_TRIG,
				  NF_AUTO_TRIG_auto_trig(1) |
				  NF_AUTO_TRIG_spec_auto_case(0) |
				  NF_AUTO_TRIG_auto_case(auto_trigger_mode));
		
		
		
			
			    /* data all 0xff */ 
			    //printk("data all one \n");
			    REG_WRITE_U32(REG_BLANK_CHK,
					  NF_BLANK_CHK_blank_ena(1) |
					  NF_BLANK_CHK_read_ecc_xnor_ena(0));
			
		
		
		else if (REG_READ_U32(REG_ND_ECC) & 0x8) {
			
				
				
			
			
				
				
					if (rtkn->chip_param.
					    set_chip_pre_param != NULL)
						
						    set_chip_pre_param(0);
				
				
				
				     rtkn->chip_param.max_read_retry_cnt) {
					
					     NULL)
						
						    (rtkn->chip_param.
						     read_retry_cnt);
					
				
			
			
			    ("[DBG]ecc error... page=0x%x, REG_BLANK_CHK reg: 0x%x \n",
			     page, (unsigned int)REG_READ_U32(REG_BLANK_CHK));
			
				
					
					     set_chip_terminate_param != NULL)
						
						    set_chip_terminate_param(0);
				
			
			
				       NF_BLANK_CHK_blank_ena(1) |
				       NF_BLANK_CHK_read_ecc_xnor_ena(0));
			
		}
		
		else {
			
				
					
					     set_chip_terminate_param != NULL)
						
						    set_chip_terminate_param(0);
				
			
			
				       NF_BLANK_CHK_blank_ena(1) |
				       NF_BLANK_CHK_read_ecc_xnor_ena(0));
			
		
		
	



				unsigned char *oobBuf, int page) 
{
	
	
	
	
	    //struct nand_chip *this = (struct nand_chip *) mtd->priv;
	    //int rc = 0, i;
	    uint8_t auto_trigger_mode = 1;
	
	
	
	    //unsigned char oob_1stB;
	    
	    //unsigned char nf_oob_buf[oob_size];
	    //unsigned int chip_section = 0;
	    //unsigned int section = 0;
	    //unsigned int index = 0;
	unsigned int is_sync_mode;
	
	    //printk("[%s] entry... page : %d\n", __FUNCTION__, page);
	    
		
		
	
	
		
		
	
	
	
		
		
		    // enable randomizer
		    REG_WRITE_U32(REG_RMZ_CTRL, 1);
		
		
		
	
	else
		
		
		    // set random write
		    REG_WRITE_U32(REG_RND_EN, 1);
		
		
		REG_WRITE_U32(REG_RND_SPR_STR_COL_H, page_size >> 8);	// spare start address MSB
		REG_WRITE_U32(REG_RND_SPR_STR_COL_L, page_size & 0xff);	// spare start address LSB
		
		
		
	
	
	    //Set PP
	    REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0));	//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1, NF_PP_CTL1_pp_start_addr(0));	//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0, 0);	//add by alexchang 0208-2010
	
	    //Set command
	    REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	
	
	
	    //Set address
	    REG_WRITE_U32(REG_ND_PA0, NF_ND_PA0_page_addr0(page));
	
	
		       NF_ND_PA2_addr_mode(addr_mode) |
		       NF_ND_PA2_page_addr2(page >> 16));
	
	
	
	
	    //Set ECC
	    
	    // no ECC NF_MULTI_CHNL_MODE_ecc_pass(1)
	    is_sync_mode = (REG_READ_U32(REG_NF_MODE) & 0x2);
	
		
		
		
			       NF_MULTI_CHNL_MODE_edo(1) |
			       NF_MULTI_CHNL_MODE_ecc_pass(1) |
			       NF_MULTI_CHNL_MODE_ecc_no_check(1));
		
		    //REG_WRITE_U32(REG_RMZ_CTRL, 1);
		}
	
	else
		
	
		
	
	
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
		
		
	
	
	    // flush cache.
	    dma_cache_wback_inv((unsigned long)buf, (unsigned long)page_size);
	
	
	
	
	
	
	
		
			       NF_SPR_DDR_CTL_spare_ddr_ena(0) |
			       NF_SPR_DDR_CTL_per_2k_spr_ena(0) |
			       NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	
	else
		
			       NF_SPR_DDR_CTL_spare_ddr_ena(1) |
			       NF_SPR_DDR_CTL_per_2k_spr_ena(1) |
			       NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	
			 NF_DMA_CTL3_ddr_wr(0) | NF_DMA_CTL3_dma_xfer(1));
	
		       NF_AUTO_TRIG_auto_trig(1) |
		       NF_AUTO_TRIG_spec_auto_case(0) |
		       NF_AUTO_TRIG_auto_case(auto_trigger_mode));
	
	
	
		       NF_POLL_FSTS_bit_sel(6) | NF_POLL_FSTS_trig_poll(1));
	
	
	



/*---------------------------------------------------------------------------------------------------------------------------------*/ 