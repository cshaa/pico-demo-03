# Raspberry Pi Pico – Demo Project

Blinks the built-in LED and a connected 240x240 ST7789 display, and print "Screen ahoy (elapsed time)" to the USB tty.

```sh
make build
# or
make build CFLAGS="-DPICO_W=ON" # for Pico W
make build CFLAGS="-DPICO_W=OFF" # for Pico
# then
make flash
```

If you uncomment [line 61](https://github.com/m93a/pico-st7789-bug/blob/main/main.c#L61), re-build and re-flash, the Pico will hang.
