#
# Este makefile está escrito para una shell bash
#
SHELL = /bin/bash

#
# Paths y nombres de directorios
#

# Ruta al BSP
BSP_ROOT_DIR   = ../../bsp

# Detalles de la plataforma
CODE_BASE 	= 0x20000000
SERIAL_PORT = /dev/ttyACM0
BAUDRATE = 115200

#
# Herramientas y cadena de desarrollo
#

# Herramientas del sistema
MKDIR          = mkdir -p
RM             = rm -rf
# TERMINAL       = gtkterm -s $(BAUDRATE) -p $(SERIAL_PORT)
TERMINAL       = putty -serial -sercfg $(BAUDRATE) $(SERIAL_PORT)

#
# Configuración de las herramientas de desarrollo
#

TOOLS_PATH     = /usr
TOOLS_PREFIX   = arm-none-eabi
CROSS_COMPILE  = $(TOOLS_PATH)/bin/$(TOOLS_PREFIX)-

AS             	= $(CROSS_COMPILE)as
CC             	= $(CROSS_COMPILE)gcc
LD          	= $(CROSS_COMPILE)ld
OBJCOPY			= $(CROSS_COMPILE)objcopy
GDB 			= $(CROSS_COMPILE)/gdb-multiarch
OPENOCD			= $(TOOLS_PATH)/bin/openocd

# Flags
ASFLAGS        = -g -mcpu=cortex-m4 -mimplicit-it=always
CFLAGS         = -c -g -Wall -mcpu=cortex-m4 -mfloat-abi=softfp
LDFLAGS        = -nostartfiles -Map $(MAP)

#
# Fuentes
#

# Aplicación
PROGNAME 	= main
OBJ      	= $(PROGNAME).o
ELF      	= $(PROGNAME).elf
BIN      	= $(PROGNAME).bin
MAP			= $(PROGNAME).map

#
# Incluimos el Makefile público del BSP
#

include $(BSP_ROOT_DIR)/bsp.mk

CFLAGS         += $(BSP_CFLAGS)
LDFLAGS        += $(BSP_LDFLAGS)
LIBS           += $(BSP_LIBS)

#
# Reglas de construcción
#

.PHONY: all
all: $(ELF) bsp $(BIN)

$(ELF) : $(OBJ) $(BSP_ROOT_DIR)/$(BSP_LIB) $(BSP_LINKER_SCRIPT)
	@echo "Enlazando $@ ..."
	$(LD) $(LDFLAGS) $< -o $@ $(LIBS)
	@echo

$(BIN) : $(ELF)
	@echo "Generando $@ ..."
	$(OBJCOPY) -O binary $< $@
	@echo

%.o : %.c
	@echo "Compilando $@ ..."
	$(CC) $(CFLAGS) $< -o $@
	@echo

%.o : %.s
	@echo "Ensamblando $@ ..."
	$(AS) $(ASFLAGS) $< -o $@
	@echo


#
# Reglas para gestionar la plataforma
#

# Ejecución
.PHONY: halt
halt: check-openocd
	@echo "Deteniendo el procesador ..."
	@echo -e "halt" | nc -i 1 localhost 4444 > /dev/null

#.PHONY: bsp
$(BSP_ROOT_DIR)/$(BSP_LIB):
	@make -C $(BSP_ROOT_DIR)

# Ejecución vía OpenOCD
.PHONY: run
run: $(BIN)	check-openocd
	@echo -e "reset halt\n load_image $< $(CODE_BASE)\n reset\n" | nc -i 1 localhost 4444

# Depuración
.PHONY: gdb bsp
gdb: $(ELF)
	gdb-multiarch --command=init.gdb $(ELF)

.PHONY: openocd
openocd:
	@echo "Lanzando openocd ..."
	@xterm -e "$(OPENOCD) -f /interface/stlink-v2-1.cfg -f /target/stm32f4x.cfg" &
	@sleep 1

.PHONY: check-openocd
check-openocd:
	@if [ ! `pgrep openocd` ]; then make -s openocd; fi

.PHONY: openocd-term
openocd-term: check-openocd
	@echo "Abriendo terminal openocd ..."
	@xterm -e "telnet localhost 4444" &

# Terminal serie
.PHONY: term
term:  $(SERIAL_PORT)
	@echo "Abriendo terminal serie ..."
	@$(TERMINAL) &

# Limpieza
.PHONY: clean
clean:
	@echo "Limpiando la aplicación ..."
	@make -C $(BSP_ROOT_DIR) clean
	@$(RM) $(BIN) $(ELF) $(OBJ) *~
