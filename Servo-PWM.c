#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

// Atualização das constantes...
#define PIN_SERVO 22       // Define o pino do servo
#define PWM_FREQ 50        // Frequência do sinal de PWM em 50 Hz
#define CLK_DIV 100.0f     // Divisor de clock escolhido
#define WRAP_VALUE 24999   // (125.000.000Hz / (100 * 50Hz)) - 1 = 24999

// Função de conversão
uint32_t us_to_level(uint32_t us) {
    // Cada unidade = (20ms / 25000) = 0.8µs
    return (uint32_t)(us * 1.25f); // 1µs = 1.25 unidades
}
// Método principal
int main() {
    set_sys_clock_khz(125000, true);  // Clock em 125 MHz
    stdio_init_all();

    // Altera a função do pino GPIO 22 para PWM
    gpio_set_function(PIN_SERVO, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(PIN_SERVO);
    uint channel = pwm_gpio_to_channel(PIN_SERVO);

    // Configura e inicia o PWM 
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, CLK_DIV);
    pwm_config_set_wrap(&config, WRAP_VALUE);
    pwm_init(slice_num, &config, true);

    // Definindo as posições solicitadas:
    sleep_ms(200);
    pwm_set_chan_level(slice_num, channel, us_to_level(2400)); 
    // 2400µs = 3000 níveis de PWM
    sleep_ms(5000);
        
    pwm_set_chan_level(slice_num, channel, us_to_level(1470)); 
    // 1470µs = 1838 níveis de PWM
    sleep_ms(5000);
        
    pwm_set_chan_level(slice_num, channel, us_to_level(500));  
    // 500µs = 625 níveis de PWM
    sleep_ms(5000);

    int32_t i = 500;

    // Transição suave de 0° a 180°
    uint32_t start_level = us_to_level(500);  // 625 
    uint32_t end_level = us_to_level(2400);   // 3000

    while(true){
    // Loop principal
      for (uint32_t i = start_level; i <= end_level; i+=5) {
        pwm_set_chan_level(slice_num, channel, i);
        sleep_ms(10);  // Suaviza o movimento quando reduzido
      }
      sleep_ms(500);
      for (uint32_t i = end_level; i >= start_level; i-=5) {
        pwm_set_chan_level(slice_num, channel, i);
        sleep_ms(10);  // Suaviza o movimento quando reduzido
      }
      sleep_ms(500);
    }
    
    return 0;
}