/**************************************************************************//**
 * @file     system_rda5981.c
 ******************************************************************************/


#include <stdint.h>
#include "rda5981.h"

/** @addtogroup RDA5981_System
 * @{
 */

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- Clock Configuration ----------------------------------
//
// <e> Clock Configuration
//   <h> Clock Gating Control 0 Register (CLKGATE0)
//     <o1.0>       DEEPSLEEP: Deep sleep mode enable
//     <o1.15>      EXIF: EXIF clock gating enable
//   </h>
//
//   <h> Clock Gating Control 1 Register (CLKGATE1)
//     <o2.0>       GPIO: GPIO clock gating enable
//     <o2.1>       I2S: I2S clock gating enable
//     <o2.2>       PWM: PWM clock gating enable
//     <o2.3>       TIMER: APB Timer clock gating enable
//     <o2.4>       PSRAM_PCLK: PSRAM PCLK clock gating enable
//     <o2.5>       SDMMC: SDMMC clock gating enable
//     <o2.6>       I2C: I2C clock gating enable
//     <o2.4>       PSRAM_HCLK: PSRAM HCLK clock gating enable
//   </h>
//
//   <h> Clock Gating Control 2 Register (CLKGATE2)
//     <o3.16>      I2SIN: I2SIN clock gating enable
//     <o3.17>      I2SOUT: I2SOUT clock gating enable
//     <o3.18>      GSPI: General SPI clock gating enable
//     <o3.19>      RFSPI: RF SPI clock gating enable
//     <o3.31>      SLOWFLASH: Slow flash clock gating enable
//   </h>
//
//   <h> Clock Gating Control 3 Register (CLKGATE3)
//     <o4.30>      DOZEMODE: Doze mode enable
//     <o4.31>      CLKMODE: Clock mode enable
//   </h>
//
//   <h> Clock Core Configure Register (CORECFG)
//     <o5.11>      HCLK: HCLK config
//     <o5.12..13>  CPUCLK: CPU Clock config
//   </h>
//
// </e>
*/



/** @addtogroup RDA5981_System_Defines  RDA5981 System Defines
  @{
 */

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  DEFINES
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define RDA_SYS_CLK_FREQUENCY_40M                            ( 40000000UL)
#define RDA_SYS_CLK_FREQUENCY_80M                            ( 80000000UL)
#define RDA_SYS_CLK_FREQUENCY_160M                           (160000000UL)
#define RDA_BUS_CLK_FREQUENCY_40M                            ( 40000000UL)
#define RDA_BUS_CLK_FREQUENCY_80M                            ( 80000000UL)


/**
 * @}
 */


/** @addtogroup RDA5981_System_Public_Variables  RDA5981 System Public Variables
  @{
 */
/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
//uint32_t SystemCoreClock = RDA_SYS_CLK_FREQUENCY_160M; /*!< System Clock Frequency (Core Clock)*/
//uint32_t AHBBusClock     = RDA_BUS_CLK_FREQUENCY_80M; /*!< AHB Bus Clock Frequency (Bus Clock)*/
uint32_t SystemCoreClock = RDA_SYS_CLK_FREQUENCY_40M; /*!< System Clock Frequency (Core Clock)*/
uint32_t AHBBusClock     = RDA_BUS_CLK_FREQUENCY_40M; /*!< AHB Bus Clock Frequency (Bus Clock)*/

/**
 * @}
 */


/** @addtogroup RDA5981_System_Public_Functions  RDA5981 System Public Functions
  @{
 */

/**
 * Update SystemCoreClock variable
 *
 * @param  none
 * @return none
 *
 * @brief  Updates the SystemCoreClock with current core Clock
 *         retrieved from cpu registers.
 */
void SystemCoreClockUpdate (void)            /* Get Core/Bus Clock Frequency     */
{
    uint32_t val = RDA_SCU->CORECFG;
    /* Determine clock frequency according to SCU core config register values    */
    switch ((val >> 12) & 0x03UL) {
      case 0:
        SystemCoreClock = RDA_SYS_CLK_FREQUENCY_40M;
        break;
      case 1:
        SystemCoreClock = RDA_SYS_CLK_FREQUENCY_80M;
        break;
      case 2:
      case 3:
        SystemCoreClock = RDA_SYS_CLK_FREQUENCY_160M;
        break;
    }

    /* Determine clock frequency according to SCU core config register values    */
    switch ((val >> 11) & 0x01UL) {
      case 0:
        AHBBusClock = RDA_BUS_CLK_FREQUENCY_40M;
        break;
      case 1:
        AHBBusClock = RDA_BUS_CLK_FREQUENCY_80M;
        break;
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
    SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */
    SCB->VTOR  = RDA_CODE_BASE;                       /* vector table in flash      */
    NVIC_SetPriorityGrouping(0x06);                   /* 1 bit for pre-emption pri  */
    __enable_irq();
}

/**
 * @}
 */

/**
 * @}
 */
