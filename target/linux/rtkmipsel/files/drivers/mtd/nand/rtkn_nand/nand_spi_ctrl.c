#include <nand_spi/util.h>
#include <nand_spi/nand_spi_ctrl.h>
#include <nand_spi/ecc_ctrl.h>	//JSW
#include <nand_spi/soc.h>
#include "rtknflash_wrapper.h"


{
	
	while ((REG32(SNFSR) & 0x1) != 0) ;	//Polling CS# status @REG32(SNFSR) until it is ��0��
}


{
	
	while ((REG32(SNFSR) & 0x1) != 1) ;	//Polling CS# status @REG32(SNFSR) until it is ��1��
}


__spi_nand_pio_cmd(unsigned int opcode, snffcn_ptr sffunc, unsigned int data,
		   unsigned int w_io_len, unsigned int r_io_len,
		   unsigned int wr_bytes, void *wr_buf) 
{
	
	
	
	
	
	
	
	
	
	



snffcn_pio_raw_cmd(unsigned int opcode, unsigned int data,
		   unsigned int w_io_len, unsigned int r_io_len,
		   unsigned int wr_bytes, void *wr_buf) 
{
	
	
	
		
		
			
	
	
	
	
	WAIT_SPI_NAND_CTRLR_RDY();
	
		
		WAIT_SPI_NAND_CTRLR_RDY();
		
	}
	



snffcn_pio_write_data(unsigned int opcode, unsigned int col_addr,
		      unsigned int addr_io, unsigned int data_io,
		      unsigned int wr_bytes, void *wr_buf) 
{
	
	
	
	
	    /* Command: SIO, 1-Byte */ 
	    w_data = opcode;
	
	
	
	
	
	    /* Address: addr_io_len, 2-Byte -Byte */ 
	    w_data = col_addr << 16;
	
	
	
	
	
	    /* Data: data_io_len, wr_len-Byte */ 
	    w_io_len = IO_WIDTH_LEN(data_io, SNFCMR_LEN(1));
	
		
		
			
			
		
			
			
		
		
		    /* The last few bytes may be garbage but won't be written to flash, since its length is explicitly given */ 
		    tmp[0] = *((u8_t *) wr_buf++);
		
		
		
		
		
	



snffcn_pio_read_data(unsigned int opcode, unsigned int col_addr,
		     unsigned int addr_io, unsigned int data_io,
		     unsigned int wr_bytes, void *wr_buf) 
{
	
	
	
	
	
	
	
	
	    /* Command: SIO, 1-Byte */ 
	    w_data = opcode;
	
	
	
	
	
	    /* Address: addr_io_len, 4-Byte */ 
#ifdef NAND_SPI_USE_QIO		
	    /*(Step4) Send 4-Byte Address for QIO , Fast read op(0xeb)need 4T's addr + 4T's dummy */ 
	    w_data = (col_addr << 24) | (dummy << 16);
	
	
#else	/*(Step4) Send 3-Byte Address for SIO/DIO */	
	    w_data = (col_addr << 16) | (dummy << 8);
	
	
#endif /* 
	    
	
	
	WAIT_SPI_NAND_CTRLR_RDY();
	
	    /* Data: data_io_len, wr_len-Byte */ 
	    r_io_len = IO_WIDTH_LEN(data_io, SNFCMR_LEN(1));
	
	
		
			
			
			
			
			
			
			
	
	
		
		
		
	
	



_pio_write(unsigned int w_data, unsigned int w_io_len) 
/* 1. Setting PIO Control Register
  * 2. Trigger it to write
  */ 
{
	
	
	
	WAIT_SPI_NAND_CTRLR_RDY();

{
	
	

program_execute(unsigned int blk_pge_addr, cmd_info_t * snf_cmd_info) 
{
	
	    /* 1-BYTE CMD + 1-BYTE Dummy + 2-BYTE Address */ 
	unsigned int w_io_len = IO_WIDTH_LEN(SIO_WIDTH, SNFCMR_LEN(4));
	
		     SNF_DONT_CARE);
	

page_data_read_to_cache_buf(unsigned int blk_pge_addr,
			    cmd_info_t * snf_cmd_info) 
{
	
	    /* 1-BYTE CMD + 1-BYTE Dummy + 2-BYTE Address */ 
	unsigned int w_io_len = IO_WIDTH_LEN(SIO_WIDTH, SNFCMR_LEN(4));
	
	snf_cmd_info->_wait_spi_nand_ready();

_dma_write_read(unsigned int dma_phy_addr, unsigned int dma_io_len,
		unsigned int wr_dir) 
/* 1. Setting DMA Engine
  * 2. Trigger it to write or read
  */ 
{
	
	
	
	    //printf("\n\n\n_dma_write_read()001\n");
	    
	    //printf("\nREG32(SNFDRSAR,0x%x)dma_phy_addr=0x%x\n",SNFDRSAR,dma_phy_addr);
	    
	
	
	
	    //  printf("\n_dma_write_read()002 ,dma_io_len=0x%x \n",dma_io_len);
	    //  printf("\nREG32(SNFDTR,0x%x)=0x%x\n\n\n",SNFDTR,REG32(SNFDTR) );
	    WAIT_DMA_CTRLR_RDY();


#if 0
SECTION_NAND_SPI void 
dma_write_data(void *dma_addr, unsigned int dma_len, unsigned int blk_pge_addr,
	       cmd_info_t * snf_cmd_info) 
/*
  * Write More or Less than One Chunk (More or less than 2112-Byte)
  * Start from the initial cache register (CA=0x0000)
  */ 
{
	
	
	
		
		    /* (Step1) Enable WEL */ 
		    write_enable();
		
		    /*(Step2) Enable CS */ 
		    WAIT_SPI_NAND_CTRLR_RDY();
		
		
		
		
		    /*(Step3) 1-Byte Command */ 
		    w_data = snf_cmd_info->w_cmd << 24;
		
		
		
		    /*(Step4) 2-Byte Address */ 
		    w_data = column_addr << 16;
		
		    IO_WIDTH_LEN(snf_cmd_info->w_addr_io, SNFCMR_LEN(2));
		
		
		    /*(Step5) DMA Write to cache register from RAM */ 
		    if (dma_len >= MAX_BYTE_PER_DMA) {
			
#if 1
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->w_data_io,
					 MAX_BYTE_PER_DMA);
			
					 DMA_WRITE_DIR);
			
			
			
			    /*(Step6) Write data from cache register to spi nand flash */ 
			    program_execute(blk_pge_addr, snf_cmd_info);
			
#endif /* 
			    
#if 0				//cause Reboot
			    _lplr_basic_io.
			    dcache_writeback_invalidate_range((unsigned int)
							      dma_addr,
							      (unsigned
							       int)(dma_addr +
								    MAX_BYTE_PER_DMA));
			
#else /* 
			    dma_addr += MAX_BYTE_PER_DMA;	//JSW
#endif /* 
			
		
			
#if 1
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->w_data_io, dma_len);
			
					 DMA_WRITE_DIR);
			
			
			
			    /*(Step6) Write data from cache register to spi nand flash */ 
			    program_execute(blk_pge_addr, snf_cmd_info);
			
#endif /* 
			    
#if 0				//cause Reboot
			    _lplr_basic_io.
			    dcache_writeback_invalidate_range((unsigned int)
							      dma_addr,
							      (unsigned
							       int)(dma_addr +
								    dma_len));
			
#else /* 
			    dma_addr += dma_len;	//JSW
#endif /* 
			
		
		
#if 0
		    _dma_write_read(PADDR(dma_addr), dma_io_len, DMA_WRITE_DIR);
		
		
		
		    /*(Step6) Write data from cache register to spi nand flash */ 
		    program_execute(blk_pge_addr, snf_cmd_info);
		
#endif /* 
	}



#else /* 

dma_write_data(void *dma_addr, u32_t dma_len, u32_t blk_pge_addr,
	       cmd_info_t * snf_cmd_info) 
/*
  * Write More or Less than One Chunk (More or less than 2112-Byte)
  * Start from the initial cache register (CA=0x0000)
  */ 
{
	
	
	
		
		    /* (Step1) Enable WEL */ 
		    write_enable();
		
		    /*(Step2) Enable CS */ 
		    WAIT_SPI_NAND_CTRLR_RDY();
		
		
		
		
		    /*(Step3) 1-Byte Command */ 
		    w_data = snf_cmd_info->w_cmd << 24;
		
		
		
		    /*(Step4) 2-Byte Address */ 
		    w_data = column_addr << 16;
		
		    IO_WIDTH_LEN(snf_cmd_info->w_addr_io, SNFCMR_LEN(2));
		
		
		    /*(Step5) DMA Write to cache register from RAM */ 
		    if (dma_len >= MAX_BYTE_PER_DMA) {
			
			    // _lplr_basic_io.dcache_writeback_invalidate_range((u32_t)dma_addr, (u32_t)(dma_addr+MAX_BYTE_PER_DMA));
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->w_data_io,
					 MAX_BYTE_PER_DMA);
			
		
			
			    // _lplr_basic_io.dcache_writeback_invalidate_range((u32_t)dma_addr, (u32_t)(dma_addr+dma_len));
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->w_data_io, dma_len);
			
		
		
		
		
		
		    /*(Step6) Write data from cache register to spi nand flash */ 
		    program_execute(blk_pge_addr, snf_cmd_info);
	



#endif /* 
    
#if 0

dma_read_data(void *dma_addr, unsigned int dma_len, unsigned int blk_pge_addr,
	      cmd_info_t * snf_cmd_info) 
/*
  * Read More or Less than One Chunk (More or less than 2112-Byte)
  * Start from the initial cache register (CA=0x0000)
  */ 
{
	
	
	
	
		
		    /*(Step1) Read data from nand flash to cache register */ 
		    page_data_read_to_cache_buf(blk_pge_addr, snf_cmd_info);
		
		    /*(Step2) Enable CS */ 
		    WAIT_SPI_NAND_CTRLR_RDY();
		
		
		
		
		    /*(Step3) Send 1-Byte Command */ 
		    w_data = snf_cmd_info->r_cmd << 24;
		
		
		
		    /*(Step4) Send 3-Byte Address */ 
		    w_data = (column_addr << 16) | (dummy << 8);
		
		    IO_WIDTH_LEN(snf_cmd_info->r_addr_io, SNFCMR_LEN(3));
		
		
		    /*(Step5) DMA Read from cache register to RAM */ 
		    if (dma_len >= MAX_BYTE_PER_DMA) {
			
#if 1
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->r_data_io,
					 MAX_BYTE_PER_DMA);
			
			
			
					 DMA_READ_DIR);
			
			
			
#endif /* 
#if 0
			    _lplr_basic_io.
			    dcache_writeback_invalidate_range((unsigned int)
							      dma_addr,
							      (unsigned
							       int)(dma_addr +
								    MAX_BYTE_PER_DMA));
			
			
#else /* 
			    dma_addr += MAX_BYTE_PER_DMA;
			
#endif /* 
			    
		
			
#if 1
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->r_data_io, dma_len);
			
			    //  printf("\ndma_io_len=0x%x\n",dma_io_len);   
			    //  printf("\n*dma_addr=0x%x\n",(void*)dma_addr);     
			    _dma_write_read(PADDR(dma_addr), dma_io_len,
					    DMA_READ_DIR);
			
			
			
#endif /* 
			    
#if 0
			    _lplr_basic_io.
			    dcache_writeback_invalidate_range((unsigned int)
							      dma_addr,
							      (unsigned
							       int)(dma_addr +
								    dma_len));
			
#else /* 
			    dma_addr += dma_len;
			
#endif /* 
			    
		
	



#else /* 
SECTION_NAND_SPI void 
dma_read_data(void *dma_addr, u32_t dma_len, u32_t blk_pge_addr,
	      cmd_info_t * snf_cmd_info) 
/*
  * Read More or Less than One Chunk (More or less than 2112-Byte)
  * Start from the initial cache register (CA=0x0000)
  */ 
{
	
	
	
	
		
		    /*(Step1) Read data from nand flash to cache register */ 
		    page_data_read_to_cache_buf(blk_pge_addr, snf_cmd_info);
		
		    /*(Step2) Enable CS */ 
		    WAIT_SPI_NAND_CTRLR_RDY();
		
		
		
		
		    /*(Step3) Send 1-Byte Command */ 
		    w_data = snf_cmd_info->r_cmd << 24;	//r_cmd= 0x03
		w_io_len = IO_WIDTH_LEN(SIO_WIDTH, SNFCMR_LEN(1));
		
		
#ifdef NAND_SPI_USE_QIO	
		    /*(Step4) Send 4-Byte Address for QIO , Fast read op(0xeb)need 4T's addr + 4T's dummy */ 
		    w_data = (column_addr << 24) | (dummy << 16);
		
		    IO_WIDTH_LEN(snf_cmd_info->r_addr_io, SNFCMR_LEN(4));
		
		
#else	/*(Step4) Send 3-Byte Address for SIO/DIO */
		    
		
		    IO_WIDTH_LEN(snf_cmd_info->r_addr_io, SNFCMR_LEN(3));
		
		
#endif /* 
		    
		    /*(Step5) DMA Read from cache register to RAM */ 
		    if (dma_len >= MAX_BYTE_PER_DMA) {
			
			    //_lplr_basic_io.dcache_writeback_invalidate_range((u32_t)dma_addr, (u32_t)(dma_addr+MAX_BYTE_PER_DMA));
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->r_data_io,
					 MAX_BYTE_PER_DMA);
			
		
			
			    // _lplr_basic_io.dcache_writeback_invalidate_range((u32_t)dma_addr, (u32_t)(dma_addr+dma_len));
			    dma_io_len =
			    IO_WIDTH_LEN(snf_cmd_info->r_data_io, dma_len);
			
		
		
		
		    //dma_addr+=MAX_BYTE_PER_DMA;//JSW
		    
		
	



#endif /* 

snffcn_bbm(unsigned int opcode, unsigned int data, unsigned int w_io_len,
	   unsigned int r_io_len, unsigned int wr_bytes, void *wr_buf) 
{
	
	
	
	    /* Command: SIO, 1-Byte */ 
	    w_data = opcode;
	
	
	
	
	
	    /* Address: addr_io_len, 2-Byte -Byte */ 
	    w_data = data;
	
	
	
	
	



snffcn_read_bbm_tbl(unsigned int opcode, unsigned int data,
		    unsigned int addr_io, unsigned int data_io,
		    unsigned int wr_bytes, void *wr_buf) 
{
	
	
	
	
	    //unsigned int wr_bound;
	unsigned int i = 0;
	
	    //unsigned int dummy=0x00;
	    u8_t tmp[4];
	
	    /* Command: SIO, 1-Byte */ 
	    
		
		
			
	
	
	
	
	
	
	
		
		
		
		
		
		
		
		
	


