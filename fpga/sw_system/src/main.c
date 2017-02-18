
/* Standard C Includes */
#include <stdio.h>

/* BSP & Xilinx Includes */
#include "xparameters.h"
#include "xgpio.h"

/* Project includes */
#include "platform.h"
#include "wifi_esp8266.h"
#include "scheduler.h"
#include "http_client.h"
#include "sd_spi.h"

XGpio Gpio1;

int main() {
    xil_printf("\r\n--- CMOD_A7_35T_1 Running %s %s ---\r\n\r\n", __DATE__, __TIME__);

    /* Init platform */
    init_platform();
    scheduler_init();
    wifi_esp8266_init();
    http_client_init ();
    sd_spi_init();

    /* Enable Interrupts (after all initialization calls) */
    platform_enable_interrupts();

    (void) XGpio_Initialize(&Gpio1, XPAR_AXI_GPIO_0_DEVICE_ID);

    sd_spi_send_command (SD_SPI_CMD0_GO_IDLE_STATE);

    while (TRUE) {
        wifi_esp8266_task();
        http_client_task();

        if (XGpio_DiscreteRead(&Gpio1, 2) != 0){
            xil_printf("> SPI SD CMD0\r\n");
            while(XGpio_DiscreteRead(&Gpio1, 2) != 0)
                sd_spi_send_command(SD_SPI_CMD0_GO_IDLE_STATE);

        }

    }

    /* End */
    return (int) NULL;
}
