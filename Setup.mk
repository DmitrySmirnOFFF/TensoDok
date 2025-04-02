
include FromCubeMX.mk

# Build path
BUILD_DIR = build

######################################
# Modules
######################################
MODBUS_MODULE_SRC = \
# PWM/PWM.c			\


MODBUS_MODULE_INC = \
# -IPWM				\



#$(patsubst %,-I%,$(include_paths))

# C_STANDARD = -std=c11 #-std=c99
# CPP_STANDARD = -std=c++11

# compile gcc flags
#----------------------------------------ASM
ASM_FLAGS = $(MCU) $(AS_DEFS) $(ALL_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

# ifeq ($(DEBUG), 1)
# ASM_FLAGS += -g -gdwarf-2  #Добавление отладочной информации в объекты (тест)
# endif

#----------------------------------------C
C_FLAGS += $(MCU) $(C_DEFS) $(ALL_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections -DARM_MATH_CM4
ifeq ($(DEBUG), 1)
C_FLAGS += -g -gdwarf-2  #Добавление отладочной информации в объекты
endif

# Generate dependency information
C_FLAGS += -MMD -MP -MF"$(@:%.o=%.d)"
C_FLAGS += $(C_STANDARD)


# libraries
# -l:libarm_cortexM4lf_math.a
LIBS = --specs=rdimon.specs#-specs=rdimon.specs  -lc -lm -lnosys 
LIBDIR = #-LArmMath
LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections


# Использовать библиотеку C-runtime,
# оптимизированную для применения в микроконтроллерах
# USE_NANO = -specs=nano.specs
# # Использовать "заглушки" для некоторых
# # функций C-runtime, неиспользуемых в микроконтроллерах
# USE_SEMIHOST = -specs=rdimon.specs

# Флаги линкера
# LDFLAGS = $(MCU)
# LDFLAGS += -mthumb
# LDFLAGS += -Wl,-Map="$(BUILD_DIR)/$(TARGET).map",--cref
# LDFLAGS += -Wl,--gc-sections
# LDFLAGS += -T$(LD_SCRIPT)
# LDFLAGS        += $(USE_NANO)
# LDFLAGS        += $(USE_SEMIHOST)
# Для использования в проекте функций, обращающихся к C- C++-runtime
# после -lrdimon добавить -lc и/или -lstdc++
# LDFLAGS        += -Wl,--start-group -lrdimon -Wl,--end-group