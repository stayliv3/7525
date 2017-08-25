PWD := $(shell pwd)
ifeq ($(DSP),viking)
GDI_DIR := $(PWD)/gdi
endif
ifeq ($(DSP),mtk)
GDI_DIR := $(PWD)/gdi_mtk
endif
ADAM_DIR := $(PWD)/adam
EVCOM_DIR := $(PWD)/evcom
LOADER_DIR := $(PWD)/loader
SPI_TEST_DIR := $(PWD)/spi_test


All: gdi adam evcom loader spi_test

clean: gdi_clean adam_clean evcom_clean loader_clean spi_test_clean
	rm -rf $(PWD)/bin/*

	

gdi:gdi_clean
	if test -f $(GDI_DIR)/Makefile; \
	then echo "Build GDI!"; \
	$(MAKE) -C $(GDI_DIR); \
	fi
ifeq ($(DSP),viking)
	if test -e $(GDI_DIR)/libgdi_viking.a; \
	then echo "Compile gdi success"; \
	else echo "Compile gdi error!"; exit 1; \
	fi
	cp  $(GDI_DIR)/libgdi_viking.a  $(PWD)/bin/
endif
ifeq ($(DSP),mtk)

ifneq ($(strip $(DYNAMIC_LIB_SUPPORT)),)
	if test -e $(GDI_DIR)/libgdi_mtk.so; \
	then echo "Compile gdi so success"; \
	else echo "Compile gdi so error!"; exit 1; \
	fi
	cp  $(GDI_DIR)/libgdi_mtk.so  $(PWD)/bin/
else
	if test -e $(GDI_DIR)/libgdi_mtk.a; \
	then echo "Compile gdi success"; \
	else echo "Compile gdi error!"; exit 1; \
	fi
	cp  $(GDI_DIR)/libgdi_mtk.a  $(PWD)/bin/
endif

endif

gdi_clean:
	if test -f $(GDI_DIR)/Makefile; \
	then echo "Clean GDI!"; \
	$(MAKE) -C $(GDI_DIR) clean; \
	else echo "Clean GDI! do noting!"; \
	fi
	
adam:adam_clean
	echo "Build ADAM!"
	$(MAKE) -C $(ADAM_DIR)
	
	
ifneq ($(strip $(DYNAMIC_LIB_SUPPORT)),)
	if test -e $(ADAM_DIR)/libadam.so; \
	then echo "Compile adam so success"; \
	else echo "Compile adam so error!"; exit 1; \
	fi
	cp  $(ADAM_DIR)/libadam.so  $(PWD)/bin/
else
	if test -e $(ADAM_DIR)/libadam.a; \
	then echo "Compile adam success"; \
	else echo "Compile adam error!"; exit 1; \
	fi
	cp  $(ADAM_DIR)/libadam.a  $(PWD)/bin/	
endif
	
adam_clean:
	echo "Clean ADAM!"
	$(MAKE) -C $(ADAM_DIR) clean
	
evcom:evcom_clean
	echo "Build EVCOM!"
	$(MAKE) -C $(EVCOM_DIR)
	if test -e $(EVCOM_DIR)/evcom; \
	then echo "Compile evcom success"; \
	else echo "Compile evcom error!"; exit 1; \
	fi
	cp  $(EVCOM_DIR)/evcom $(PWD)/bin/	
evcom_clean:
	echo "Clean EVCOM!"
	$(MAKE) -C $(EVCOM_DIR) clean

loader:loader_clean
	echo "Build loader!"
	$(MAKE) -C $(LOADER_DIR)
	if test -e $(LOADER_DIR)/voip_loader; \
	then echo "Compile loader success"; \
	else echo "Compile loader error!"; exit 1; \
	fi
	cp $(LOADER_DIR)/voip_loader $(PWD)/bin/

loader_clean:
	echo "Clean Loader!"
	$(MAKE) -C $(LOADER_DIR) clean

spi_test:spi_test_clean
	echo "Build spi test!"
	$(MAKE) -C $(SPI_TEST_DIR)
	if test -e $(SPI_TEST_DIR)/spi_test; \
	then echo "Compile spi test success"; \
	else echo "Compile spi test error!"; exit 1; \
	fi
	cp $(SPI_TEST_DIR)/spi_test $(PWD)/bin/

spi_test_clean:
	echo "Clean spi test!"
	$(MAKE) -C $(SPI_TEST_DIR) clean
