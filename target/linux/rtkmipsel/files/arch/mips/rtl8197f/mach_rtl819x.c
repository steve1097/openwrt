/*
 *  Buffalo WZR-HP-AG300H board support
 *
 *  Copyright (C) 2011 Felix Fietkau <nbd@openwrt.org>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License version 2 as published
 *  by the Free Software Foundation.
 */  
    
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/leds.h>
#ifndef CONFIG_WRT_BARRIER_BREAKER
#include <linux/autoconf.h>
#else /* 
#include <generated/autoconf.h>
#endif /* 
#include <asm/mach-rtl8197f/bspchip.h>
    
#include "dev_leds_gpio.h"
#include "dev-gpio-buttons.h"
    
#define RTL819X_BUTTONS_POLL_INTERVAL   100	// orignal is 20 , fine-tune to 100
#define RTL819X_BUTTONS_DEBOUNCE_INTERVAL   3*RTL819X_BUTTONS_POLL_INTERVAL
extern void rtl819x_gpio_pin_enable(u32 pin);


#if defined(CONFIG_RTL_8367R_SUPPORT)
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_G6
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_H0
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_H1
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_H1
#define BSP_8367R_RST_PIN		BSP_GPIO_PIN_H2
#define BSP_8367R_I2C_PIN1		BSP_GPIO_PIN_C2
#define BSP_8367R_I2C_PIN2		BSP_GPIO_PIN_C3
#else /* 
#define BSP_RESET_BTN_PIN		BSP_GPIO_PIN_C3
#define BSP_WPS_BTN_PIN			BSP_GPIO_PIN_C1
#define BSP_RESET_LED_PIN		BSP_GPIO_PIN_B7
#define BSP_WPS_LED_PIN			BSP_GPIO_PIN_B7
#endif /* 

	    {
	     BSP_WPS_LED_PIN, 
};


	    {
	     KEY_RESTART, 
	     RTL819X_BUTTONS_DEBOUNCE_INTERVAL, 
	     //.threshold    = 3,
	     .gpio = BSP_RESET_BTN_PIN, 
    {
     KEY_WPS_BUTTON, 
     //.threshold    = 3,
     .gpio = BSP_WPS_BTN_PIN, 
};


{
	
	
#ifdef CONFIG_LEDS_GPIO
	    rtl819x_register_leds_gpio(-1, ARRAY_SIZE(rtl819x_leds_gpio),
				       
	
		
	
	
#endif /* 
	    for (i = 0; i < ARRAY_SIZE(rtl819x_buttons); i++) {
		
	
	
					 
					 
	
	    //###customized gpio###
	    //enable your customized gpio here
	    //for example ,
	    //rtl819x_gpio_pin_enable(BSP_GPIO_PIN_A6);
#if 0	
#ifdef CONFIG_SERIAL_RTL_UART1
	    rtl819x_gpio_pin_enable(BSP_UART1_PIN);
	
#endif /* 
#ifdef CONFIG_SERIAL_RTL_UART2
	    rtl819x_gpio_pin_enable(BSP_UART2_PIN);
	
#endif /* 
#endif /* 




{
	
	
		
		
	
	
	    /* Button gpio */ 
	    for (i = 0; i < ARRAY_SIZE(rtl819x_buttons); i++) {
		
	
	
	    //###customized gpio### 
	    //export your customized gpio here
	    //for example ,
	    //gpio_export(BSP_GPIO_PIN_A6,1);
}


