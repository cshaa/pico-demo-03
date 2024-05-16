#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/vreg.h"
#include "st7789.h"

const uint32_t CPU_FREQ_KHZ = 133000;
const uint32_t SPI_FREQ_HZ = 50 * 1000 * 1000;
const enum vreg_voltage CPU_VOLTAGE = VREG_VOLTAGE_1_10;

#ifdef PICO_W
const uint LED_PIN = CYW43_WL_GPIO_LED_PIN;
#else
const uint LED_PIN = PICO_DEFAULT_LED_PIN;
#endif

uint32_t time_ms()
{
    return (time_us_32() / 1000);
}

#ifdef PICO_W
void led_setup()
{
    cyw43_arch_init();
}
void led_on()
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
}
void led_off()
{
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
}
#else
void led_setup()
{
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
}
void led_on()
{
    gpio_put(PICO_DEFAULT_LED_PIN, true);
}
void led_off()
{
    gpio_put(PICO_DEFAULT_LED_PIN, false);
}
#endif

int main()
{
    vreg_set_voltage(CPU_VOLTAGE);
    set_sys_clock_khz(CPU_FREQ_KHZ, true);

    stdio_init_all();

    led_setup();

    const struct st7789_config lcd_config = {
        .spi = PICO_DEFAULT_SPI_INSTANCE,
        .freq_hz = SPI_FREQ_HZ,
        .gpio_din = PICO_DEFAULT_SPI_TX_PIN,
        .gpio_clk = PICO_DEFAULT_SPI_SCK_PIN,
        .gpio_cs = -1,
        .gpio_dc = 20,
        .gpio_rst = 21,
        .gpio_bl = 22,
    };
    st7789_init(&lcd_config, 240, 240);

    while (true)
    {
        printf("Screen ahoy! (%i)\n", time_ms() / 1000);
        led_on();
        st7789_fill(0x0000);
        sleep_ms(200);
        st7789_fill(0xf000);
        sleep_ms(200);
        st7789_fill(0x0f00);
        sleep_ms(200);
        led_off();
        st7789_fill(0x00ff);
        sleep_ms(200);
        st7789_fill(0xffff);
        sleep_ms(200);
    }
}
