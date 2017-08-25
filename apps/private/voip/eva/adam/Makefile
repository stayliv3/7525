PWD := $(shell pwd)
ADAM_SRC := adam.c
ADAM_OBJ := $(subst .c,.o,$(ADAM_SRC))

ifneq ($(strip $(DYNAMIC_LIB_SUPPORT)),)
	TARGET := $(PWD)/libadam.so
else
TARGET := $(PWD)/libadam.a
endif


INCLUDE = -I$(SYSROOT)/usr/include/ -I$(PWD)/../common

ifneq ($(strip $(DYNAMIC_LIB_SUPPORT)),)
	CFLAGS+= -O2 -Wall -fPIC $(INCLUDE)
else
CFLAGS+= -O2 -Wall $(INCLUDE) 
endif

ifeq ($(DSP),viking)
GDI_LIB_DIR := $(PWD)/../bin
GDI_LIB_LINK := -L$(GDI_LIB_DIR)/ -lgdi_viking 
GDI_LIB := $(GDI_LIB_DIR)/libgdi_viking.a
GDI_INCLUDE = -I$(PWD)/../gdi
CFLAGS += -D OSAL_PTHREADS -D DSPID_VIKING 
endif

ifeq ($(DSP),mtk)
GDI_LIB_DIR := $(PWD)/../bin

GDI_LIB_LINK := -L$(GDI_LIB_DIR)/ -lgdi_mtk 
ifneq ($(strip $(DYNAMIC_LIB_SUPPORT)),)
	GDI_LIB := $(GDI_LIB_DIR)/libgdi_mtk.so
else
GDI_LIB := $(GDI_LIB_DIR)/libgdi_mtk.a 
endif
GDI_INCLUDE = -I$(PWD)/../gdi_mtk
CFLAGS += -D DSPID_MTK
endif

CFLAGS += $(GDI_INCLUDE)  

%.o:%.c
	$(CC) $(CFLAGS) $(GDI_LIB_LINK) -c $< -o $@

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(ADAM_OBJ)
	$(CC) $(CFLAGS) -c $(ADAM_SRC)
ifneq ($(strip $(DYNAMIC_LIB_SUPPORT)),)
	$(LD) -shared -o $(TARGET) $(ADAM_OBJ) $(GDI_LIB)
else
	$(AR) rcs $(TARGET) $(ADAM_OBJ) $(GDI_LIB)
endif

clean:
	rm -rf *.o $(TARGET) $(ADAM_OBJ)