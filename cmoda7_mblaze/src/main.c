#include "xparameters.h"
#include "xil_printf.h"
#include "xgpio.h"
#include "xil_types.h"
#include "sleep.h"

// Get device IDs from xparameters.h
#define BTN_ID XPAR_AXI_GPIO_BUTTONS_DEVICE_ID
#define LED_ID XPAR_AXI_GPIO_LED_DEVICE_ID
#define BTN_CHANNEL 1
#define LED_CHANNEL 1
#define BTN_MASK 0b1
#define LED_MASK 0b11

int main() {
	XGpio_Config *cfg_ptr;
	XGpio led_device, btn_device;
	u32 data;

	xil_printf("BTN0 has been pressed\r\n");

	// Initialize LED Device
	cfg_ptr = XGpio_LookupConfig(LED_ID);
	XGpio_CfgInitialize(&led_device, cfg_ptr, cfg_ptr->BaseAddress);

	// Initialize Button Device
	cfg_ptr = XGpio_LookupConfig(BTN_ID);
	XGpio_CfgInitialize(&btn_device, cfg_ptr, cfg_ptr->BaseAddress);

	// Set Button Tristate
	XGpio_SetDataDirection(&btn_device, BTN_CHANNEL, BTN_MASK);

	// Set Led Tristate
	XGpio_SetDataDirection(&led_device, LED_CHANNEL, 0);

	while (1) {
		data = XGpio_DiscreteRead(&btn_device, BTN_CHANNEL);
		data &= BTN_MASK;
		if (data != 0) {
			data = LED_MASK;
			usleep(150000);
			xil_printf("BTN1 has been pressed\r\n");
		}
		else {
			data = 0;
		}
		XGpio_DiscreteWrite(&led_device, LED_CHANNEL, data);
	}
}

