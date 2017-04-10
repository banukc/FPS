# Library Version
MSO_LIB_VERSION = 1.2

# Library Name
MSO_LIB_NAME = libMSO

# flag debug: yes or no
# DEBUG = yes
export CROSS_COMPILE
######################################################################################

TARGET_SHARED =  $(MSO_LIB_NAME).so.$(MSO_LIB_VERSION)
TARGET_STATIC = $(MSO_LIB_NAME).a

# Path to the lib
MSO_LIB_PATH = ../lib

# Compilateur
CC = $(CROSS_COMPILE)gcc

# Flags
ifeq ($(DEBUG),yes)
CFLAGS = -Wall -g -O4 -fPIC -g -O4 -fpic -march=armv7-a -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=/home/banuprakash/plum_project/fsl-release-bsp/build_image/tmp/sysroots/imx6ulevk

else
CFLAGS = -Wall -O4 -fPIC -g -O4 -fpic -march=armv7-a -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=/home/banuprakash/plum_project/fsl-release-bsp/build_image/tmp/sysroots/imx6ulevk

endif

# Include
SRCINCLUDE = -I../include -I../driver/RS232 -I../driver/USB

libMSO_SRCS = \
       		Ilv.c \
       		MSO_Bio_Verify.c \
       		MSO_Bio_VerifyMatch.c \
       		MSO_BioDB_GetBaseConfig.c \
       		MSO_BioDB_GetPublicListData.c \
       		MSO_BioDB_AddBaseRecord.c \
       		MSO_SetPk.c \
       		MSO_SetTkb.c \
       		MSO_SetIsoPk.c \
       		MSO_SECU_GetSerialNumber.c \
       		MSO_Cancel.c \
       		MSO_ConfigUart.c \
       		MSO_GET_DESCRIPTOR.c \
       		MSO100.c
	
libMSO_OBJS = $(libMSO_SRCS:.c=.o)
              
.PHONY: all
all: $(TARGET_STATIC) $(TARGET_SHARED) 

.PHONY: $(TARGET_STATIC) 
$(TARGET_STATIC): $(libMSO_OBJS)
	ar ruv $(MSO_LIB_PATH)/$(TARGET_STATIC) $(libMSO_OBJS)
	ranlib $(MSO_LIB_PATH)/$(TARGET_STATIC)
    
%.o: %.c 
	$(CC) -c $(CFLAGS) $(SRCINCLUDE) $< -o $@

.PHONY: $(TARGET_SHARED)
$(TARGET_SHARED): $(libMSO_OBJS)
	$(CC) -o $(MSO_LIB_PATH)/$@ -shared $(libMSO_OBJS) $(CFLAGS) $(SRCINCLUDE)
	cd $(MSO_LIB_PATH) && ln -sf `ls $(MSO_LIB_NAME).so.*.*` $(MSO_LIB_NAME).so
    
.PHONY: clean
clean:
	rm -f $(libMSO_OBJS)

.PHONY: cleanall
cleanall:
	rm -f $(MSO_LIB_PATH)/$(TARGET_STATIC) 
	rm -f $(MSO_LIB_PATH)/$(TARGET_SHARED) 
	rm -f $(MSO_LIB_PATH)/$(MSO_LIB_NAME).so
	rm -f $(libMSO_OBJS)
   
