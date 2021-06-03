set architecture armv7e-m

target remote | openocd -c "gdb_port pipe" -f /interface/stlink-v2-1.cfg -f /target/stm32f4x.cfg

monitor reset halt

load

c
#b *0x20000004
#b *0x200000ba
