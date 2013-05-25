#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <pic18fregs.h>

// Define configuration registers (fuses)
#if defined(pic18f2550) || defined(pic18f2455) || defined(pic18f4550) || defined(pic18f4455)
__code char __at (__CONFIG1L) CONFIG1L = _USBPLL_CLOCK_SRC_FROM_96MHZ_PLL_2_1L
                                       & _CPUDIV__OSC1_OSC2_SRC___1__96MHZ_PLL_SRC___2__1L
                                       & _PLLDIV_DIVIDE_BY_5__20MHZ_INPUT__1L;

__code char __at (__CONFIG1H) CONFIG1H = _IESO_OFF_1H
                                       & _FCMEN_OFF_1H
                                       & _OSC_HS__HS_PLL__USB_HS_1H;

__code char __at (__CONFIG2L) CONFIG2L = _VREGEN_ON_2L
                                       & _PUT_ON_2L
                                       & _BODEN_OFF_2L
                                       & _BODENV_4_5V_2L;

__code char __at (__CONFIG2H) CONFIG2H = _WDT_DISABLED_CONTROLLED_2H
                                       & _WDTPS_1_1_2H;

__code char __at (__CONFIG3H) CONFIG3H = _MCLRE_MCLR_ON_RE3_OFF_3H
                                       & _PBADEN_PORTB_4_0__CONFIGURED_AS_DIGITAL_I_O_ON_RESET_3H
                                       & _CCP2MUX_RC1_3H
                                       & _LPT1OSC_OFF_3H;

__code char __at (__CONFIG4L) CONFIG4L = _STVR_OFF_4L
                                       & _LVP_OFF_4L
                                       & _ENICPORT_OFF_4L
                                       & _ENHCPU_OFF_4L;

__code char __at (__CONFIG5L) CONFIG5L = _CP_0_OFF_5L
                                       & _CP_1_OFF_5L
                                       & _CP_2_OFF_5L
                                       & _CP_3_OFF_5L;

__code char __at (__CONFIG5H) CONFIG5H = _CPD_OFF_5H
                                       & _CPB_OFF_5H;

__code char __at (__CONFIG6L) CONFIG6L = _WRT_0_OFF_6L
                                       & _WRT_1_OFF_6L
                                       & _WRT_2_OFF_6L
                                       & _WRT_3_OFF_6L;

__code char __at (__CONFIG6H) CONFIG6H = _WRTD_OFF_6H
                                       & _WRTB_OFF_6H
                                       & _WRTC_OFF_6H;

__code char __at (__CONFIG7L) CONFIG7L = _EBTR_0_OFF_7L
                                       & _EBTR_1_OFF_7L
                                       & _EBTR_2_OFF_7L
                                       & _EBTR_3_OFF_7L;

__code char __at (__CONFIG7H) CONFIG7H = _EBTRB_OFF_7H;

#endif

#endif // CONFIG_H_INCLUDED


/* Full-Speed USB Clock Source Selection 1L options */
//	_USBPLL_CLOCK_SRC_FROM_96MHZ_PLL_2_1L   	0xFF	/* Clock src from 96MHz PLL/2 */
//	_USBPLL_CLOCK_SRC_FROM_OSC1_OSC2_1L     	0xDF	/* Clock src from OSC1/OSC2 */

/* CPU System Clock Postscaler 1L options */
//	_CPUDIV__OSC1_OSC2_SRC___4__96MHZ_PLL_SRC___6__1L	0xFF	/* [OSC1/OSC2 Src: /4][96MHz PLL Src: /6] */
//	_CPUDIV__OSC1_OSC2_SRC___3__96MHZ_PLL_SRC___4__1L	0xF7	/* [OSC1/OSC2 Src: /3][96MHz PLL Src: /4] */
//	_CPUDIV__OSC1_OSC2_SRC___2__96MHZ_PLL_SRC___3__1L	0xEF	/* [OSC1/OSC2 Src: /2][96MHz PLL Src: /3] */
//	_CPUDIV__OSC1_OSC2_SRC___1__96MHZ_PLL_SRC___2__1L	0xE7	/* [OSC1/OSC2 Src: /1][96MHz PLL Src: /2] */

/* 96MHz PLL Prescaler 1L options */
//	_PLLDIV_DIVIDE_BY_12__48MHZ_INPUT__1L   	0xFF	/* Divide by 12 (48MHz input) */
//	_PLLDIV_DIVIDE_BY_10__40MHZ_INPUT__1L   	0xFE	/* Divide by 10 (40MHz input) */
//	_PLLDIV_DIVIDE_BY_6__24MHZ_INPUT__1L    	0xFD	/* Divide by 6 (24MHz input) */
//	_PLLDIV_DIVIDE_BY_5__20MHZ_INPUT__1L    	0xFC	/* Divide by 5 (20MHz input) */
//	_PLLDIV_DIVIDE_BY_4__16MHZ_INPUT__1L    	0xFB	/* Divide by 4 (16MHz input) */
//	_PLLDIV_DIVIDE_BY_3__12MHZ_INPUT__1L    	0xFA	/* Divide by 3 (12MHz input) */
//	_PLLDIV_DIVIDE_BY_2__8MHZ_INPUT__1L     	0xF9	/* Divide by 2 (8MHz input) */
//	_PLLDIV_NO_DIVIDE__4MHZ_INPUT__1L       	0xF8	/* No Divide (4MHz input) */


/* Oscillator 1H options */
//	_OSC_HS__HS_PLL__USB_HS_1H              	0xFE	/* HS: HS+PLL, USB-HS */
//	_OSC_HS__USB_HS_1H                      	0xFC	/* HS: USB-HS */
//	_OSC_INTOSC__USB_HS_1H                  	0xFB	/* INTOSC: USB-HS */
//	_OSC_INTOSC__USB_XT_1H                  	0xFA	/* INTOSC: USB-XT */
//	_OSC_INTOSC__INTOSC_CLK0_RA6___USB_EC_1H	0xF9	/* INTOSC: INTOSC+CLK0{RA6}, USB-EC */
//	_OSC_INTOSC__INTOSC_RA6__USB_EC_1H      	0xF8	/* INTOSC: INTOSC+RA6, USB-EC */
//	_OSC_EC__EC_PLL__EC_PLL_CLKO_RA6___USB_EC_1H	0xF7	/* EC: EC+PLL, EC+PLL+CLKO{RA6}, USB-EC */
//	_OSC_EC__EC_PLL__EC_PLL_RA6__USB_EC_1H  	0xF6	/* EC: EC+PLL, EC+PLL+RA6, USB-EC */
//	_OSC_EC__EC_CLKO_RA6___USB_EC_1H        	0xF5	/* EC: EC+CLKO{RA6}, USB-EC */
//	_OSC_EC__EC_RA6__USB_EC_1H              	0xF4	/* EC: EC+RA6, USB-EC */
//	_OSC_XT__XT_PLL__USB_XT_1H              	0xF2	/* XT: XT+PLL, USB-XT */
//	_OSC_XT__USB_XT_1H                      	0xF0	/* XT: USB-XT */

/* Fail-Safe Clock Monitor Enable 1H options */
//	_FCMEN_OFF_1H                           	0xBF	/* Disabled */
//	_FCMEN_ON_1H                            	0xFF	/* Enabled */

/* Internal External Switch Over Mode 1H options */
//	_IESO_OFF_1H                            	0x7F	/* Disabled */
//	_IESO_ON_1H                             	0xFF	/* Enabled */


/* USB Voltage Regulator 2L options */
//	_VREGEN_ON_2L                           	0xFF	/* Enabled */
//	_VREGEN_OFF_2L                          	0xDF	/* Disabled */

/* Power Up Timer 2L options */
//	_PUT_OFF_2L                             	0xFF	/* Disabled */
//	_PUT_ON_2L                              	0xFE	/* Enabled */

/* Brown Out Detect 2L options */
//	_BODEN_ON_2L                            	0xFF	/* Enabled in hardware, SBOREN disabled */
//	_BODEN_ON_WHILE_ACTIVE_2L               	0xFD	/* Enabled while active,disabled in SLEEP,SBOREN disabled */
//	_BODEN_CONTROLLED_WITH_SBOREN_BIT_2L    	0xFB	/* Controlled with SBOREN bit */
//	_BODEN_OFF_2L                           	0xF9	/* Disabled in hardware, SBOREN disabled */

/* Brown Out Voltage 2L options */
//	_BODENV_2_0V_2L                         	0xFF	/* 2.0V */
//	_BODENV_2_7V_2L                         	0xF7	/* 2.7V */
//	_BODENV_4_2V_2L                         	0xEF	/* 4.2V */
//	_BODENV_4_5V_2L                         	0xE7	/* 4.5V */


/* Watchdog Timer 2H options */
//	_WDT_ON_2H                              	0xFF	/* Enabled */
//	_WDT_DISABLED_CONTROLLED_2H             	0xFE	/* Disabled-Controlled by SWDTEN bit */

/* Watchdog Postscaler 2H options */
//	_WDTPS_1_32768_2H                       	0xFF	/* 1:32768 */
//	_WDTPS_1_16384_2H                       	0xFD	/* 1:16384 */
//	_WDTPS_1_8192_2H                        	0xFB	/* 1:8192 */
//	_WDTPS_1_4096_2H                        	0xF9	/* 1:4096 */
//	_WDTPS_1_2048_2H                        	0xF7	/* 1:2048 */
//	_WDTPS_1_1024_2H                        	0xF5	/* 1:1024 */
//	_WDTPS_1_512_2H                         	0xF3	/* 1:512 */
//	_WDTPS_1_256_2H                         	0xF1	/* 1:256 */
//	_WDTPS_1_128_2H                         	0xEF	/* 1:128 */
//	_WDTPS_1_64_2H                          	0xED	/* 1:64 */
//	_WDTPS_1_32_2H                          	0xEB	/* 1:32 */
//	_WDTPS_1_16_2H                          	0xE9	/* 1:16 */
//	_WDTPS_1_8_2H                           	0xE7	/* 1:8 */
//	_WDTPS_1_4_2H                           	0xE5	/* 1:4 */
//	_WDTPS_1_2_2H                           	0xE3	/* 1:2 */
//	_WDTPS_1_1_2H                           	0xE1	/* 1:1 */


/* CCP2 Mux 3H options */
//	_CCP2MUX_RC1_3H                         	0xFF	/* RC1 */
//	_CCP2MUX_RB3_3H                         	0xFE	/* RB3 */

/* PortB A/D Enable 3H options */
//	_PBADEN_PORTB_4_0__CONFIGURED_AS_ANALOG_INPUTS_ON_RESET_3H	0xFF	/* PORTB<4:0> configured as analog inputs on RESET */
//	_PBADEN_PORTB_4_0__CONFIGURED_AS_DIGITAL_I_O_ON_RESET_3H	0xFD	/* PORTB<4:0> configured as digital I/O on RESET */

/* Low Power Timer1 Osc enable 3H options */
//	_LPT1OSC_ON_3H                          	0xFF	/* Enabled */
//	_LPT1OSC_OFF_3H                         	0xFB	/* Disabled */

/* Master Clear Enable 3H options */
//	_MCLRE_MCLR_ON_RE3_OFF_3H               	0xFF	/* MCLR Enabled,RE3 Disabled */
//	_MCLRE_MCLR_OFF_RE3_ON_3H               	0x7F	/* MCLR Disabled,RE3 Enabled */


/* Stack Overflow Reset 4L options */
//	_STVR_ON_4L                                        	0xFF	/* Enabled */
//	_STVR_OFF_4L                            	0xFE	/* Disabled */

/* Low Voltage Program 4L options */
//	_LVP_ON_4L                              	0xFF	/* Enabled */
//	_LVP_OFF_4L                             	0xFB	/* Disabled */

/* Dedicated In-Circuit Port {ICD/ICSP} 4L options */
//	_ENICPORT_OFF_4L                        	0xDF	/* Disabled */

/* Extended CPU Enable 4L options */
//	_ENHCPU_ON_4L                           	0xFF	/* Enabled */
//	_ENHCPU_OFF_4L                          	0xBF	/* Disabled */

/* Background Debug 4L options */
//	_BACKBUG_OFF_4L                         	0xFF	/* Disabled */
//	_BACKBUG_ON_4L                          	0x7F	/* Enabled */


/* Code Protect 00800-01FFF 5L options */
//	_CP_0_OFF_5L                            	0xFF	/* Disabled */
//	_CP_0_ON_5L                             	0xFE	/* Enabled */

/* Code Protect 02000-03FFF 5L options */
//	_CP_1_OFF_5L                            	0xFF	/* Disabled */
//	_CP_1_ON_5L                             	0xFD	/* Enabled */

/* Code Protect 04000-05FFF 5L options */
//	_CP_2_OFF_5L                            	0xFF	/* Disabled */
//	_CP_2_ON_5L                             	0xFB	/* Enabled */

/* Code Protect 06000-07FFF 5L options */
//	_CP_3_OFF_5L                            	0xFF	/* Disabled */
//	_CP_3_ON_5L                             	0xF7	/* Enabled */


/* Data EE Read Protect 5H options */
//	_CPD_OFF_5H                             	0xFF	/* Disabled */
//	_CPD_ON_5H                              	0x7F	/* Enabled */

/* Code Protect Boot 5H options */
//	_CPB_OFF_5H                             	0xFF	/* Disabled */
//	_CPB_ON_5H                              	0xBF	/* Enabled */


/* Table Write Protect 00800-01FFF 6L options */
//	_WRT_0_OFF_6L                           	0xFF	/* Disabled */
//	_WRT_0_ON_6L                            	0xFE	/* Enabled */

/* Table Write Protect 02000-03FFF 6L options */
//	_WRT_1_OFF_6L                           	0xFF	/* Disabled */
//	_WRT_1_ON_6L                            	0xFD	/* Enabled */

/* Table Write Protect 04000-05FFF 6L options */
//	_WRT_2_OFF_6L                           	0xFF	/* Disabled */
//	_WRT_2_ON_6L                            	0xFB	/* Enabled */

/* Table Write Protect 06000-07FFF 6L options */
//	_WRT_3_OFF_6L                           	0xFF	/* Disabled */
//	_WRT_3_ON_6L                            	0xF7	/* Enabled */


/* Data EE Write Protect 6H options */
//	_WRTD_OFF_6H                            	0xFF	/* Disabled */
//	_WRTD_ON_6H                             	0x7F	/* Enabled */

/* Table Write Protect Boot 6H options */
//	_WRTB_OFF_6H                            	0xFF	/* Disabled */
//	_WRTB_ON_6H                             	0xBF	/* Enabled */

/* Config. Write Protect 6H options */
//	_WRTC_OFF_6H                            	0xFF	/* Disabled */
//	_WRTC_ON_6H                             	0xDF	/* Enabled */


/* Table Read Protect 00800-01FFF 7L options */
//	_EBTR_0_OFF_7L                          	0xFF	/* Disabled */
//	_EBTR_0_ON_7L                           	0xFE	/* Enabled */

/* Table Read Protect 02000-03FFF 7L options */
//	_EBTR_1_OFF_7L                          	0xFF	/* Disabled */
//	_EBTR_1_ON_7L                           	0xFD	/* Enabled */

/* Table Read Protect 04000-05FFF 7L options */
//	_EBTR_2_OFF_7L                          	0xFF	/* Disabled */
//	_EBTR_2_ON_7L                           	0xFB	/* Enabled */

/* Table Read Protect 06000-07FFF 7L options */
//	_EBTR_3_OFF_7L                          	0xFF	/* Disabled */
//	_EBTR_3_ON_7L                           	0xF7	/* Enabled */


/* Table Read Protect Boot 7H options */
//	_EBTRB_OFF_7H                           	0xFF	/* Disabled */
//	_EBTRB_ON_7H                            	0xBF	/* Enabled */
