/*
 * Realtek MMC/SD/SDIO driver
 *
 * Authors:
 * Copyright (C) 2008-2013 Realtek Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */  
    
#include <linux/module.h>
#include <linux/init.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/mbus.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/scatterlist.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/mmc/host.h>
#include <asm/unaligned.h>
    
#include <linux/sched.h>	//liao
#include <linux/wait.h>		//liao
#include <linux/slab.h>		//liao
#include <linux/semaphore.h>	//liao
#include <linux/mmc/card.h>	//liao
#include <linux/mmc/mmc.h>	//liao
#include <linux/mmc/sd.h>	//liao
#include <linux/workqueue.h>	//liao
#include <linux/completion.h>	//liao
//#include <rbus/reg_mmc.h>               //liao
//#include <rbus/reg_sys.h>               //liao
//#include <rbus/reg_iso.h>               //liao
#include "rtkemmc.h"		//liao
#include "rtksd_ops.h"		//liao
#include "../mmc_debug.h"	//liao
    
#ifdef MMC_DBG
static unsigned sd_reg = 0;

#endif /* 
extern volatile unsigned char g_cmd[];


#ifdef GPIO_DEBUG
void trans_db_gpio(void) 
{
	
	    //set debug GPIO
	    u32 reginfo;
	
	    //1. 0xB800_0804[31:28] = F    --> pin share as gpio
	    //2. 0x1801_BC00[4] = 1  --> output mode
	    //3. 0x1801_BC18[4]   is output data
	    cr_writel(cr_readl(GP0DIR_reg) | 0x10, GP0DIR_reg);
	
	
		
		
	
		
		
	



{
	
	    //set rst GPIO
	    u32 reginfo;
	
	
	
		
	
		
	



#else /* 
#define trans_db_gpio()
#define trans_rst_gpio()
#endif /* 

{
	
	    //asm volatile("DMB");
	    //cr_writel(0x0, 0x1801a020);
	    //asm volatile("DMB");
	    return;




//#define INT_BLOCK_R_GAP 0x200
//#define INT_BLOCK_W_GAP 5
#define TIMEOUT_MS 3000
int rtkcr_wait_opt_end(char *drv_name, struct rtksd_host *sdport, u8 cmdcode,
		       u8 cpu_mode) 
{
	
	
	
	
	
	
	
	
	    ("\n%s - info :\ncmd0 : 0x%02x,cmd1 : 0x%02x,cmd2 : 0x%02x,cmd3 : 0x%02x,cmd4: 0x%02x\n",
	     drv_name, g_cmd[0], g_cmd[1], g_cmd[2], g_cmd[3], g_cmd[4]);
	
		
	
	
	
		
		
	
		
		
		
	
	
		
	
	
	    ("\n%s - info1 :\ncmd0 : 0x%02x,cmd1 : 0x%02x,cmd2 : 0x%02x,cmd3 : 0x%02x,cmd4: 0x%02x\n",
	     drv_name, g_cmd[0], g_cmd[1], g_cmd[2], g_cmd[3], g_cmd[4]);
	
	
	
		
		
		
			
			
			
			
		
	
		
		
			"\n%s - trans dma fail (cmd/2193/status1/status2/bus_status/cfg1/cfg2/cfg3/dma) : \n\t0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%02x 0x%02x 0x%02x 0x%08x\n",
			\
			cr_readb(sdport->base + SD_TRANSFER),
			cr_readb(sdport->base + SD_STATUS1),
			cr_readb(sdport->base + SD_STATUS2),
			\
			cr_readb(sdport->base + SD_CONFIGURE1),
			cr_readb(sdport->base + SD_CONFIGURE2),
			cr_readb(sdport->base + SD_CONFIGURE3),
			cr_readl(sdport->base + CR_DMA_CTL3));
		
		
	
		
		
		
		
		
		
			
			
			
			
			     (END_STATE | IDLE_STATE))
				
				
				
				
			
		
			
			
				   "\n%s - cmd21 dma fail0 (cmd/2193/status1/status2/bus_status/cfg1/cfg2/cfg3/dma) : \n\t0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%02x 0x%02x 0x%02x 0x%08x\n",
				   drv_name, g_cmd[0],
				   cr_readb(sdport->base + SD_TRANSFER),
				   cr_readb(sdport->base + SD_STATUS1),
				   cr_readb(sdport->base + SD_STATUS2),
				   cr_readb(sdport->base + SD_BUS_STATUS),
				   cr_readb(sdport->base + SD_CONFIGURE1),
				   cr_readb(sdport->base + SD_CONFIGURE2),
				   cr_readb(sdport->base + SD_CONFIGURE3),
				   cr_readl(sdport->base + CR_DMA_CTL3));
			
			
		
		
		
		
			
			
			
			
				
				
				
			
		
			
			
				   "\n%s - cmd21 dma fail1 (cmd/2193/status1/status2/bus_status/cfg1/cfg2/cfg3/dma) : \n\t0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%02x 0x%02x 0x%02x 0x%08x\n",
				   \
				   cr_readb(sdport->base + SD_TRANSFER),
				   cr_readb(sdport->base + SD_STATUS1),
				   cr_readb(sdport->base + SD_STATUS2),
				   cr_readb(sdport->base + SD_BUS_STATUS),
				   \
				   cr_readb(sdport->base + SD_CONFIGURE2),
				   cr_readb(sdport->base + SD_CONFIGURE3),
				   cr_readl(sdport->base + CR_DMA_CTL3));
			
			
		
	




				  unsigned long msec, unsigned long dma_msec) 
{
	
	
	
	
	
	
	
	
#ifndef ENABLE_EMMC_INT_MODE
	    sdport->int_waiting = NULL;
	
#else /* 
	    sdport->int_waiting = &rtk_emmc_wait;
	
		   (unsigned int)sdport->int_waiting);
	
	    /* timeout timer fire */ 
	    if (&sdport->timer)
		
		
		
#if 0
		    if (sdport->tmout) {
			
			
		
			
#endif /* 
			    timeend = msecs_to_jiffies(msec) + sdport->tmout;
		
		
		
		
	
	    //wait for 
#endif /* 
	    rtk_int_waitfor(sdport, cmdcode, msec, dma_msec);
	
	    //smp_wmb();
	    sync();
	
	{
		
			"\n - trans error (cmd/SD_TRANS/status1/status2/bus_status/cfg1/cfg2/cfg3) : \n\t0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%02x 0x%02x 0x%02x\n",
			\
			cr_readb(sdport->base + SD_STATUS1),
			cr_readb(sdport->base + SD_STATUS2),
			cr_readb(sdport->base + SD_BUS_STATUS),
			\
			cr_readb(sdport->base + SD_CONFIGURE2),
			cr_readb(sdport->base + SD_CONFIGURE3));
		
	
	
	{
		
			"\n - trans timeout (cmd/SD_TRANS/status1/status2/bus_status/cfg1/cfg2/cfg3) : \n\t0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%02x 0x%02x 0x%02x\n",
			\
			cr_readb(sdport->base + SD_STATUS1),
			cr_readb(sdport->base + SD_STATUS2),
			cr_readb(sdport->base + SD_BUS_STATUS),
			\
			cr_readb(sdport->base + SD_CONFIGURE2),
			cr_readb(sdport->base + SD_CONFIGURE3));
		
	
	




			unsigned long msec, unsigned long dma_msec) 
{
	
#ifndef ENABLE_EMMC_INT_MODE
	unsigned long timeend = 0;
	
	    0, dma_trans = 0;
	
	
	
		
			   sdport->base, sdport->base + SD_CMD0);
		
		    (" cmd0:0x%02x cmd1:0x%02x cmd2:0x%02x cmd3:0x%02x cmd4:0x%02x cmd5:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_CMD1),
		     cr_readb(sdport->base + SD_CMD2),
		     cr_readb(sdport->base + SD_CMD3),
		     cr_readb(sdport->base + SD_CMD4),
		     cr_readb(sdport->base + SD_CMD5));
		
		    (" trans:0x%02x status1:0x%02x status2:0x%02x bus_status:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_STATUS1),
		     cr_readb(sdport->base + SD_STATUS2),
		     cr_readb(sdport->base + SD_BUS_STATUS));
		
		    (" configure1:0x%02x configure2:0x%02x configure3:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_CONFIGURE2),
		     cr_readb(sdport->base + SD_CONFIGURE3));
		
		    (" byteH:0x%02x byteL:0x%02x blkH:0x%02x blkL:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_BYTE_CNT_L),
		     cr_readb(sdport->base + SD_BLOCK_CNT_H),
		     cr_readb(sdport->base + SD_BLOCK_CNT_L));
		
		    (" CPU_ACC:0x%08x dma_ctl1:0x%08x dma_ctl2:0x%08x dma_ctl3:0x%08x\n",
		     \
		     cr_readl(sdport->base + CR_DMA_CTL1),
		     cr_readl(sdport->base + CR_DMA_CTL2),
		     cr_readl(sdport->base + CR_DMA_CTL3));
		
		    (" card_pad_drv:0x%08x cmd_pad_drv:0x%08x data_pad_drv:0x%08x EMMC_CKGEN_CTL:0x%08x, SYS_PLL_EMMC3=0x%08x\n",
		     \
		     cr_readb(sdport->base + EMMC_CMD_PAD_DRV),
		     cr_readb(sdport->base + EMMC_DATA_PAD_DRV),
		     cr_readl(sdport->base + EMMC_CKGEN_CTL),
		     cr_readl(SYS_PLL_EMMC3));
	
	
	    //cmd fire
#ifdef MMC_DBG
	    sd_reg = cr_readb(sdport->base + SD_CMD0);
	
#endif /* 
	    sync();
	
	
	
	
		
		
		      (END_STATE | IDLE_STATE)) == (END_STATE | IDLE_STATE))
			
		
		     (ERR_STATUS))
			
		
	
		
		
		
			
			
			     != (DMA_XFER))
				
			
		
		
		
	
	
	
	
	
	
	
	
		   sdport->int_status, sdport->sd_trans, sdport->sd_status1);
	
		   sdport->sd_status2, sdport->bus_status, sdport->dma_trans);
	
	
#else /* 
	    sync();
	
		
		    //if ((g_cmd[0] == 0x47)||(g_cmd[0] == 0x45)||(g_cmd[0] == 0x46)){
		    printk(" rtkemmc : register settings(base=0x%08x,0x%02x)\n",
			   sdport->base, cr_readb(sdport->base + SD_CMD0));
		
		    (" cmd0:0x%02x cmd1:0x%02x cmd2:0x%02x cmd3:0x%02x cmd4:0x%02x cmd5:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_CMD1),
		     cr_readb(sdport->base + SD_CMD2),
		     cr_readb(sdport->base + SD_CMD3),
		     cr_readb(sdport->base + SD_CMD4),
		     cr_readb(sdport->base + SD_CMD5));
		
		    (" trans:0x%02x status1:0x%02x status2:0x%02x bus_status:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_STATUS1),
		     cr_readb(sdport->base + SD_STATUS2),
		     cr_readb(sdport->base + SD_BUS_STATUS));
		
		    (" configure1:0x%02x configure2:0x%02x configure3:0x%02x\n",
		     \
		     cr_readb(sdport->base + SD_CONFIGURE2),
		     cr_readb(sdport->base + SD_CONFIGURE3));
		
			\
			cr_readb(sdport->base + SD_BYTE_CNT_L),
			cr_readb(sdport->base + SD_BLOCK_CNT_H),
			cr_readb(sdport->base + SD_BLOCK_CNT_L));
		
		    (" CPU_ACC:0x%08x dma_ctl1:0x%08x dma_ctl2:0x%08x dma_ctl3:0x%08x sample_ctl:0x%08x pull_ctl:0x%08x\n",
		     \
		     cr_readl(sdport->base + CR_DMA_CTL1),
		     cr_readl(sdport->base + CR_DMA_CTL2),
		     cr_readl(sdport->base + CR_DMA_CTL3),
		     cr_readb(sdport->base + SD_SAMPLE_POINT_CTL),
		     cr_readb(sdport->base + SD_PUSH_POINT_CTL));
		
		    (" card_pad_drv:0x%08x cmd_pad_drv:0x%08x data_pad_drv:0x%08x EMMC_CKGEN_CTL:0x%08x, SYS_PLL_EMMC3=0x%08x\n",
		     \
		     cr_readb(sdport->base + EMMC_CMD_PAD_DRV),
		     cr_readb(sdport->base + EMMC_DATA_PAD_DRV),
		     cr_readl(sdport->base + EMMC_CKGEN_CTL),
		     cr_readl(SYS_PLL_EMMC3));
	
	
		
		
#ifdef MMC_DBG
		    sd_reg = cr_readb(sdport->base + SD_CMD0);
		
		
#endif /* 
		    rtkcr_hold_int_dec(sdport->base);
		
		
		
		
		
		    //cmd fire
		    cr_writeb((u8) (cmdcode | START_EN),
			      sdport->base + SD_TRANSFER);
		
		
		
		
		
	
#endif /* 
}



{
	
		
		
			   (unsigned int)sdport->int_waiting);
		
		
		    //sdport->int_waiting = NULL;
		    complete(waiting);
		
		
		
	
	
	else
		




{
	
	
	
	
		
		
		
			break;
		
		
		      *ptr != ' ' && *ptr != '\t' && *ptr != '='
		      && *ptr != '\0'; ptr++) ;
		
		
			
			
				
				
				
				
				     || (*(ptr + 1) != '\0' && *(ptr + 1) != ' '
					 && *(ptr + 1) != '\t')) {
					
					    ("system_parameters error! Check your parameters     .");
					
				
			
				
				
				      *ptr != ' ' && *ptr != '\t'
				      && *ptr != '\0' && *ptr != '"'; ptr++) ;
				
					
					    ("system_parameters error! Check your parameters.");
					
				
			
			
		
		
			
				
				    kmalloc(value_end - value_start + 1,
					    GFP_KERNEL);
				
				    // KWarning: checked ok by alexkh@realtek.com
				    if (ret_str) {
					
						 value_end - value_start);
					
					    '\0';
				
				
			
				
				
				    // KWarning: checked ok by alexkh@realtek.com
				    if (ret_str)
					
				
			
		
	
	



{
	
	
	
	
		
		
		    // KWarning: checked ok by alexkh@realtek.com
		    if ((value >= 0) && (value <= 9))
			
			
			
			
		
		
		    // KWarning: checked ok by alexkh@realtek.com
		    if ((value >= 0) && (value <= 5))
			
			
			
			
			
		
		
		    // KWarning: checked ok by alexkh@realtek.com
		    if ((value >= 0) && (value <= 5))
			
			
			
			
			
	





{
	
	
//TODO : chk
#if 0 
	    if (!verA_magic_num)
		
	
		
	
		
	
	
#else /* 
	    return verA_magic_num;	//0: polling, 1: interrupt
#endif /* 
}



{
	
	
	
	
		
		
		    //clksel_sht = EMMC_CLKSEL_SHT;
	} else if (iobase == CR_BASE_ADDR) {
		
		
		    //clksel_sht = SD_CLKSEL_SHT;
	}
	
		  
		  
		  




/* end of file */ 
    