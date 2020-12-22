

## How to Build

```{shell}
git clone https://github.com/ucu-cs/UCU_hell_machine
cd UCU_hell_machine/zephyr/blinky_pwm

source ~/zephyrproject/zephyr/zephyr-env.sh # source your local zephyr env
cmake -B build -GNinja -DBOARD=nucleo_h743zi
ninja -C build
ninja flash -C build # flash to board
```
