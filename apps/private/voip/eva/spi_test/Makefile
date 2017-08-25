PWD := $(shell pwd)

SPI_TEST_DIR := $(PWD)
SPI_TEST_SRC := spi_test.c 
SPI_TEST_OBJ := $(subst .c,.o,$(SPI_TEST_SRC))


INCLUDE = 
CFLAGS += -O2 -Wall -lpthread -lm $(INCLUDE)

TARGET = spi_test

%.o:%.c
	$(CC) $(CFLAGS) -c $<

	
.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SPI_TEST_OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(SPI_TEST_OBJ) 
	@cp $(SPI_TEST_DIR)/$(TARGET) $(SPI_TEST_DIR)/bin/.
	@cp $(SPI_TEST_DIR)/$(TARGET) $(SPI_TEST_DIR)/../bin/.

	
clean:
	rm -rf *.o $(TARGET) $(SPI_TEST_OBJ)
	
