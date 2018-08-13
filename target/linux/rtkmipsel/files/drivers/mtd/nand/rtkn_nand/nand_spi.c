
// #include <util.h>
    
#include <nand_spi/ecc_ctrl.h>
#include <nand_spi/nand_spi_ctrl.h>
#include <nand_spi/nand_spi.h>
#include <nand_spi/util.h>
#ifdef __RTK_BOOT__
#include <malloc.h>
#endif /* 
#ifdef __UBOOT__
#include <common.h>
#include <malloc.h>
#endif /* 
#include <asm/io.h>
#include "rtknflash_wrapper.h"
    
//#define VZERO 0
    
#define SECTION_RO
    
#define CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND 1
    

/*Choosing SPI-NAND I/O type
    Definition in nand_spi_ctrl.h

*/ 
    
#ifdef NAND_SPI_USE_SIO
    SECTION_RO cmd_info_t winbond_cmd_info = {

	    SIO_WIDTH, 
	    SIO_WIDTH, 
	    winbond_wait_spi_nand_ready, 

#endif /* 
    
#ifdef NAND_SPI_USE_DIO
    SECTION_RO cmd_info_t winbond_cmd_info = {
	
.w_addr_io = SIO_WIDTH, 
	    WINBOND_FAST_READ_DIO, 
	    DIO_WIDTH, 
	    DIO_WIDTH, 

#endif /* 
    
#ifdef NAND_SPI_USE_DATA_IOx2
    SECTION_RO cmd_info_t winbond_cmd_info = {

	    SIO_WIDTH, 
	    SIO_WIDTH, 
	    winbond_wait_spi_nand_ready, 

#endif /* 
    
#ifdef NAND_SPI_USE_QIO
    SECTION_RO cmd_info_t winbond_cmd_info = {
	
.w_data_io = QIO_WIDTH, 
	    WINBOND_FAST_READ_QIO, 
	    QIO_WIDTH, 
	    QIO_WIDTH, 

#endif /* 
    
#ifdef NAND_SPI_USE_DATA_IOx4 
    SECTION_RO cmd_info_t winbond_cmd_info = {

	    SIO_WIDTH, 
	    WINBOND_FAST_READ_X4, 
	    QIO_WIDTH, 

#endif /* 
    
//MXIC
    SECTION_RO plr_nand_spi_info_t MXIC_MX35LF1GE4AB_info = {

	    
	    1024,.num_chunk_per_block = 
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    

//esmt
    SECTION_RO plr_nand_spi_info_t ESMT_F50L1G41A_info = {

	    
	    1024,.num_chunk_per_block = 
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    

//winbond
    SECTION_RO plr_nand_spi_info_t winbond_W25N01GV_info = {

	    
	    1024,.num_chunk_per_block = 
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    


	    
	    1024,.num_chunk_per_block = 
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    
	    

								 feature_addr
								 
{
	
	
	
	    
	



winbond_set_feature_register(unsigned int feature_addr,
			     unsigned int setting 
{
	
	
		     


#ifdef NAND_SPI_USE_QIO
SECTION_NAND_SPI void 
{
	
	
	
	

#endif /* 

{
	
	
	
	

{
	
	
	
	

{
	
	
	
	

{
	
	
	
		
	



{
	
	
	
	
	    /*
	     * 1-BYTE CMD + 1-BYTE Dummy + 2-BYTE Address 
	     */ 
	    w_io_len = IO_WIDTH_LEN(SIO_WIDTH, SNFCMR_LEN(4));
	
		     
	
	
	    /*
	     * Check Erase Status 
	     */ 
	    efail = 
	
		
			
		
	
	



#if CONF_SPI_NAND_UBOOT_COMMAND
static 
winbond_block_erase_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			  
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbbe <blk_pge_addr>  : SPI-NAND Winbond block erasein hex\r\n");
		
	
	
#endif /* 
	
	    
	
	



	      

#endif /* 

winbond_pio_read_data(void *ram_addr, unsigned int wr_bytes,
		      
/*
 * PIO Read Less than One Chunk (Less than 2112-Byte)
 * Start from the assigned cache register address (CA=col_addr)
 */ 
{
	
#if 1
	    if (wr_bytes > 2112) {
		
		    ("\nFail => PIO Read Less than One Chunk (Less than 2112 (0x840)-Byte) \n");
		
	
	
#endif /* 
	    
	
			     



#if CONF_SPI_NAND_UBOOT_COMMAND
static 
winbond_pio_read_data_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			    
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1]) && (argv[2]) && (argv[3]) && (argv[4])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbpior <ram_addr><wr_bytes><blk_pge_addr><col_addr>  : SPI-NAND Winbond pio read in hex\r\n");
		
	
	
#endif /* 
	    
#if 1
	
	
	    
	
	    
	
	    
	
#endif /* 
	    
	



	      
	      

#endif /* 

winbond_pio_write_data(void *ram_addr, unsigned int wr_bytes,
		       
/*
 * PIO Write Less than One Chunk (Less than 2112-Byte)
 * Start from the assigned cache register address (CA=col_addr)
 */ 
{
	
#if 1
	    if (wr_bytes > 2112) {
		
		    ("\nFail => PIO Write Less than One Chunk  (Less than 2112 (0x840)-Byte) \n");
		
	
	
#endif /* 
	    write_enable();
	
			     
			     
	



#if CONF_SPI_NAND_UBOOT_COMMAND
static 
winbond_pio_write_data_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			     
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1]) && (argv[2]) && (argv[3]) && (argv[4])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbpiow <ram_addr><wr_bytes><blk_pge_addr><col_addr>  : SPI-NAND Winbond pio write in hex\r\n");
		
	
	
#endif /* 
	    
#if 1
	
	
	    
	
	    
	
	    
	
#endif /* 
	    
	



	      
	      

#endif /* 

winbond_dma_read_data(void *dma_addr, unsigned int dma_len,
		      unsigned int blk_pge_addr 
/*
 * Read More or Less than One Chunk (More or less than 2112-Byte)
 * Start from the initial cache register (CA=0x0000)
 */ 
{
	
	    /* cache invalid and writeback */ 
	    dma_cache_wback_inv((unsigned long)dma_addr,
				(unsigned long)dma_len);
	


#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
winbond_dma_read_data_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			    
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1]) && (argv[2]) && (argv[3])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbdmar <dma_addr><dma_len><blk_pge_addr>  : SPI-NAND Winbond DMA read in hex\r\n");
		
	
	
#endif /* 
	    
#if 1
	void *dma_addr = 
	
	    
	
	    
	
#endif /* 
	    
#if 1
	    winbond_dma_read_data(dma_addr, dma_len, blk_pge_addr);
	
#else /* 
	    if (i = 0; i <=; i++) {
		
		
	
	
#endif /* 
	    



	      
	      

#endif /* 

winbond_dma_write_data(void *dma_addr, unsigned int dma_len,
		       unsigned int blk_pge_addr 
/*
 * Write More or Less than One Chunk (More or less than 2112-Byte)
 * Start from the initial cache register (CA=0x0000)
 */ 
{
	
	    /* flush cache */ 
	    dma_cache_wback_inv((unsigned long)dma_addr,
				(unsigned long)dma_len);
	


#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
winbond_dma_write_data_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			     
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1]) && (argv[2]) && (argv[3])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbdmaw <dma_addr><dma_len><blk_pge_addr>  : SPI-NAND Winbond DMA write in hex\r\n");
		
	
	
#endif /* 
	    
#if 1
	void *dma_addr = 
	
	    
	
	    
	
#endif /* 
	    
	    // winbond_dma_write_data(void *dma_addr, unsigned int dma_len,
	    // unsigned int blk_pge_addr);
	    winbond_dma_write_data(dma_addr, dma_len, blk_pge_addr);
	



		
		

#endif /* 

winbond_2KB_chunk_read(void *dma_addr, unsigned int blk_pge_addr 
/*
 * Read One Chunk (2048-Byte SRC Data + 64-Byte Spare Data)
 * Start from the initial cache register (CA=0x0000)
 */ 
{
	
			       


#if 0				// CONF_SPI_NAND_UBOOT_COMMAND
static int 
winbond_2KB_chunk_read_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			     
{
	
#if 0
	unsigned int flash_src_addr =
	    
	
	    
	
	    
	
#else /* 
	void *dma_addr = 
	
	    // unsigned int dma_len= Strtoul((const u8*)(argv[2]), (u8 **)NULL,
	    // 16);
	unsigned int blk_pge_addr =
	    
	
	    // printf("\ndma_addr =0x%x\n",*dma_addr);
	    // printf("\ndma_len =0x%x\n",dma_len);
	    printf("\nblk_pge_addrr =0x%x\n", blk_pge_addr);
	
#endif /* 
	    
	    // winbond_dma_write_data(void *dma_addr, unsigned int dma_len,
	    // unsigned int blk_pge_addr);
	    winbond_2KB_chunk_read(dma_addr, blk_pge_addr);
	



	      
	      

#endif /* 

winbond_2KB_chunk_write(void *dma_addr, unsigned int blk_pge_addr 
/*
 * Write One Chunk (2048-Byte SRC Data + 64-Byte Spare Data)
 * Start from the initial cache register (CA=0x0000)
 */ 
{
	
				


#if 0				// CONF_SPI_NAND_UBOOT_COMMAND
static int 
winbond_2KB_chunk_write_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
			      
{
	
#if 0
	unsigned int flash_src_addr =
	    
	
	    
	
	    
	
#else /* 
	void *dma_addr = 
	
	    // unsigned int dma_len= Strtoul((const u8*)(argv[2]), (u8 **)NULL,
	    // 16);
	unsigned int blk_pge_addr =
	    
	
	    // printf("\ndma_addr =0x%x\n",*dma_addr);
	    // printf("\ndma_len =0x%x\n",dma_len);
	    printf("\nblk_pge_addrr =0x%x\n", blk_pge_addr);
	
#endif /* 
	    
	    // winbond_dma_write_data(void *dma_addr, unsigned int dma_len,
	    // unsigned int blk_pge_addr);
	    winbond_2KB_chunk_write(dma_addr, blk_pge_addr);
	



	      
	      

#endif /* 

winbond_2KB_chunk_write_with_ecc_encode(void *dma_addr,
					
					
{
	
	


#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
winbond_2KB_chunk_write_with_ecc_encode_uboot(cmd_tbl_t * cmdtp, int flag,
					      
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1]) && (argv[2]) && (argv[3])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbwecc <dma_addr><blk_pge_addr><p_eccbuf>  : SPI-NAND Winbond chunk_write with ecc in hex\r\n");
		
	
	
#endif /* 
	    
#if 1
	void *dma_addr = 
	
	    
	
	
#endif /* 
	    
	    // winbond_dma_write_data(void *dma_addr, unsigned int dma_len,
	    // unsigned int blk_pge_addr);
	    winbond_2KB_chunk_write_with_ecc_encode(dma_addr, blk_pge_addr,
						    
	



	      
	      

#endif /* 

winbond_2KB_chunk_read_with_ecc_decode(void *dma_addr,
				       
				       
{
	
	    //int i;
	    //unsigned char* value = (unsigned char*)dma_addr;
	    winbond_2KB_chunk_read(dma_addr, blk_pge_addr);	// whole
	// chunk=2048+64
	// bytes
#if 0
	printf("page_addr = %d\n", blk_pge_addr);
	
		
			
	
	
#endif /* 
	    



#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
winbond_2KB_chunk_read_with_ecc_decode_uboot(cmd_tbl_t * cmdtp, int flag,
					     
{
	
#if CONFIG_AVOID_ERROR_INPUT_HANG_SPI_NAND
	    if ((argv[1]) && (argv[2]) && (argv[3])) {
		
		    /*
		     * Avoid error input format hang 
		     */ 
	} else {
		
		
		    ("Usage:snwbrecc <dma_addr><blk_pge_addr><p_eccbuf>  : SPI-NAND Winbond chunk_read with ecc in hex\r\n");
		
	
	
#endif /* 
	    
#if 1
	void *dma_addr = 
	
	    
	
	
#endif /* 
	    
	    // winbond_dma_write_data(void *dma_addr, unsigned int dma_len,
	    // unsigned int blk_pge_addr);
	    winbond_2KB_chunk_read_with_ecc_decode(dma_addr, blk_pge_addr,
						   
	



	      
	      

#endif /* 

{
	
	


#if 1
SECTION_NAND_SPI unsigned int 
{
	
	
	// length 
	// = 
	// 2byte
	
	// length 
	// = 
	// 3byte
	
	    // #define WINBOND_RDID 0x9f
	unsigned int ret =
	    
	



#endif /* 
    
    
{
	
	
	rdid = winbond_read_id();
	
		
		
		
		
#if 0				//def NAND_SPI_USE_DIO
#error
		    winbond_cmd_info.r_cmd = WINBOND_FAST_READ_DIO;
		
		
		
#endif /* 
		    printf("\nFound recognized ID, rdid=0x%x\n", rdid);
		
	
		
		
		
		
#if 0				//def NAND_SPI_USE_DIO
#error
		    winbond_cmd_info.r_cmd = WINBOND_FAST_READ_DIO;
		
		
		
#endif /* 
		    printf("\nFound recognized ID, rdid=0x%x\n", rdid);
		
	
		
		
		
		
#if 0				//def NAND_SPI_USE_DIO
#error
		    winbond_cmd_info.r_cmd = WINBOND_FAST_READ_DIO;
		
		
		
#endif /* 
		    printf("\nFound recognized ID, rdid=0x%x\n", rdid);
		
	
		
		
		
		
#if 0				//def NAND_SPI_USE_DIO
#error
		    winbond_cmd_info.r_cmd = WINBOND_FAST_READ_DIO;
		
		
		
#endif /* 
		    printf("\nFound recognized ID, rdid=0x%x\n", rdid);
		
	
	
	else {
		
	
	
	
	    // return CMD_RET_SUCCESS;
}


#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
probe_winbond_spi_nand_chip_uboot(cmd_tbl_t * cmdtp, int flag, int argc,
				  
{
	
	    // dram_normal_patterns();
	    
	    /*
	     * Select cs0 or cs1 for user mode , auto mode's setting is
	     * FLASH_SIZE(offset + 0x124) 
	     */ 
#if 0
	    u32 chip_select = 
	
	    // SPI_ChipSelect(chip_select);
	    
#endif /* 
	    
	    // flash_EN4B(&dev); 
	    probe_winbond_spi_nand_chip();
	



		  

#endif /* 
    
#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
SPI_NAND_RDID(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[] 
{
	
	    // dram_normal_patterns();
	
	
	    /*
	     * Select cs0 or cs1 for user mode , auto mode's setting is
	     * FLASH_SIZE(offset + 0x124) 
	     */ 
#if 0
	    u32 chip_select = 
	
	    // SPI_ChipSelect(chip_select);
	    
#endif /* 
	    
#if 0
	    if (argc < 2) {
		
		
		
	
	
#endif /* 
	    
	    // flash_EN4B(&dev); 
	    spi_nand_id = winbond_read_id();
	
	



		  

#endif /* 

{
	
	


#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
SPI_NAND_BBM(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[] 
{
	
	
	
	



		

#endif /* 

{
	
	
	
#define BBT_NUM 20
	
	
	
			       SNF_DONT_CARE, BBT_NUM, buf);
	
		
		
		
		
		
		    //printf("
		    printf("lba=%u,pba=%u\n", lba, pba);
		
	



#if CONF_SPI_NAND_UBOOT_COMMAND
static int 
SPI_NAND_READ_BBM(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[] 
{
	
#define TBL_NUM	20
	
	



		  

#endif /* 
    
// REG_SPI_NAND_PROBE_FUNC(probe_winbond_spi_nand_chip);
    