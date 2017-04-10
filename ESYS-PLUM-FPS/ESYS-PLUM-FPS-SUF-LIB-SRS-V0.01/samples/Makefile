# Compilateur
export CROSS_COMPILE
CC = $(CROSS_COMPILE)gcc

# DEBUG= "no" or "yes"
# DEBUG = yes

# Flags
ifeq ($(DEBUG),yes)
CFLAGS = -Wall -g -Os -fPIC -march=armv7-a -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=/home/banuprakash/plum_project/fsl-release-bsp/build_image/tmp/sysroots/imx6ulevk


else
CFLAGS = -Wall -Os -fPIC -march=armv7-a -mfloat-abi=hard -mfpu=neon -mtune=cortex-a7 --sysroot=/home/banuprakash/plum_project/fsl-release-bsp/build_image/tmp/sysroots/imx6ulevk


endif

# libMSOComm need to be link with libusb
LIB_USB = -lusb
LIB_SDL = -lSDL -lSDL_ttf

# Sagem lib
LIBPATH += -L../lib
LIBPATH += -L/home/banuprakash/plum_project/fsl-release-bsp/build_image/tmp/sysroots/imx6ulevk/usr/lib
LIB_STATIC_SAGEM = ../lib/libMSO.a ../lib/libMSOComm.a
LIB_SAGEM = -lMSO -lMSOComm

# Include directory
SRCINCLUDE += -I../include -I../wsq
SRCINCLUDE += -I/home/banuprakash/plum_project/fsl-release-bsp/build_image/tmp/sysroots/imx6ulevk/usr/include/

# Exec path
EXEC_PATH = bin
EXEC_STATIC = FPS 

FPS_SRC = FPS.c MSO_FPS.c  MSO_errors.c
FPS_OBJ = $(FPS_SRC:.c=.o)

.PHONY: all
all: $(EXEC_STATIC) $(EXEC_SHARED)

%.o: %.c
	$(CC) -c $(CFLAGS) $(SRCINCLUDE) $< -o $@

.PHONY: FPS 
FPS: $(FPS_OBJ)
	$(CC) $(FPS_OBJ) -o $(EXEC_PATH)/FPS $(CFLAGS) $(SRCINCLUDE) $(LIB_STATIC_SAGEM) $(LIB_USB)


.PHONY: clean
clean:
	rm -f $(FPS_OBJ)

.PHONY: cleanall
cleanall:
	rm -f $(FPS_OBJ) 
	cd $(EXEC_PATH) && rm -f $(EXEC_STATIC) $(EXEC_SHARED)

