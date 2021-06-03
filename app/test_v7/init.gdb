set architecture armv7e-m

target remote | openocd -c "gdb_port pipe" -f /interface/stlink-v2-1.cfg -f /target/stm32f4x.cfg

monitor reset halt

load

#b main
iprintf.c:32
c
