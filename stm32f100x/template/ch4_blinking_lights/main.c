
#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

/* 
 * The fundamental steps to initialize any STM32 peripheral are: 
 * 1. Enable clocks to the peripheral
 * 2. Configure pins required by the peripheral
 * 3. Configure peripheral hardware * 
 */

void Delay(uint32_t nTime);

int main(void){
    GPIO_InitTypeDef GPIO_InitStructure_LEDS;
    GPIO_InitTypeDef GPIO_InitStructure_pushButton;

    // Enable Peripheral Clocks for GPIOC (for LEDs) and GPIOA (for push-button)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOA, ENABLE);

    // Configure Pins for both LEDs
    GPIO_StructInit(&GPIO_InitStructure_LEDS);
    GPIO_InitStructure_LEDS.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_8;  // for green and blue LEDs
    GPIO_InitStructure_LEDS.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure_LEDS.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure_LEDS);

    // Configure Pins for the push-button
    GPIO_StructInit(&GPIO_InitStructure_pushButton);
    GPIO_InitStructure_pushButton.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure_pushButton.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure_pushButton.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure_pushButton);
    
    // Configure SysTick Timer
    if(SysTick_Config(SystemCoreClock / 1000)){
        while(1);
    }

    while(1){
        static int ledval = 0;

        // toggle the green LED
        GPIO_WriteBit(GPIOC, GPIO_Pin_9, (ledval) ? Bit_SET : Bit_RESET);
        ledval = 1 - ledval;

        // if the button is pushed, turn the blue LED on, otherwise turn it off 
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_RESET){
            GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_SET);
        }else{
            GPIO_WriteBit(GPIOC, GPIO_Pin_8, Bit_RESET);
        }

        Delay(250);     // wait 250ms
    }
}

// Timer code
static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime){
    TimingDelay = nTime;
    while(TimingDelay != 0);
}

void SysTick_Handler(void){
    if(TimingDelay != 0x00){
        TimingDelay--;
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t * file, uint32_t line){
    // infinite loop
    // use GDB to find out why we're here
    while(1);
}
#endif