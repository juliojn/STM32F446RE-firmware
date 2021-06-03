#
# Makefile del BSP para la placa STM32F446RE
#

# Este makefile está escrito para una shell bash
SHELL = /bin/bash

#
# Paths y nombres de directorios
#

# Ruta al BSP
BSP_ROOT_DIR   = .

# Directorio para almacenar los ficheros objeto
OBJ_DIR        = $(BSP_ROOT_DIR)/obj

# Directorio de la toolchain de GNU
# Toolchain de los repositorios
TOOLS_PATH     = /usr

#
# Herramientas y cadena de desarrollo
#

# Herramientas del sistema
MKDIR          = mkdir -p
RM             = rm -rf

# Cadena de desarrollo
# Toolchain de los repositorios
TOOLS_PREFIX   = arm-none-eabi
# Toolchain construida a partir de las fuentes
#TOOLS_PREFIX   = arm-econotag-eabi

CROSS_COMPILE  = $(TOOLS_PATH)/bin/$(TOOLS_PREFIX)-
AS             = $(CROSS_COMPILE)as
CC             = $(CROSS_COMPILE)gcc
AR             = $(CROSS_COMPILE)ar

# Flags
ASFLAGS        = -g -mcpu=cortex-m4 -mimplicit-it=always
CFLAGS         = -c -g -Wall -mcpu=cortex-m4
ARFLAGS        = -src

#
# Fuentes
#

# Todos los ficheros C del BSP
C_SRCS     = $(shell find $(BSP_ROOT_DIR) -name '*.c' -print)

# Todos los ficheros en ensamblador del BSP
ASM_SRCS   = $(shell find $(BSP_ROOT_DIR) -name '*.s' -print)

# Todos los ficheros cabecera del BSP
INCLUDES   = $(shell find $(BSP_ROOT_DIR) -name '*.h' -print)

#
# Lista de ficheros objeto
#

OBJS		= $(addprefix $(OBJ_DIR)/, $(ASM_SRCS:.s=.o) $(C_SRCS:.c=.o))

#
# Makefile público del BSP
#

include bsp.mk

ASFLAGS        += $(BSP_ASFLAGS)
CFLAGS         += $(BSP_CFLAGS)

#
# Reglas de construcción
#

.PHONY: all
all: $(BSP_LIB)

.PHONY: all
all: $(BSP_LIB)

$(BSP_LIB): $(OBJS)
	@echo "Generando la biblioteca del bsp ..."
	$(AR) $(ARFLAGS) $@ $^
	@echo

$(OBJ_DIR)/%.o : %.s $(BSP_LINKER_SCRIPT) $(INCLUDES)
	@echo "Ensamblando $< ..."
	@$(MKDIR) $(@D)
	$(AS) $(ASFLAGS) $< -o $@
	@echo

$(OBJ_DIR)/%.o : %.c $(INCLUDES)
	@echo "Compilando $< ..."
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $< -o $@
	@echo

.PHONY: clean
clean:
	@echo "Limpiando el BSP ..."
	@$(RM) $(BSP_LIB) $(OBJ_DIR) $(DIST_DIR) $(shell find $(BSP_ROOT_DIR) -name '*~' -print)
