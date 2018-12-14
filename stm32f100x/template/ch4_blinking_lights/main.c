
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void Delay(uint32_t nTime);

int main(void){
    GPIO_InitTypeDef GPIO_InitStructure;

    // Enable Peripheral Clocks

    // Configure Pins

    // Configure SysTick Timer

    while(1){
        static int ledval = 0;

        // toggle LED

        Delay(250);     // wait 250ms
    }
}

// Timer code

#ifdef USE_FULL_ASSERT
void assert_failed(utin8_t * file, uint32_t line){
    // infinite loop
    // use GDB to find out why we're here
    while(1);
}
#endif