// Copyright (C) 2021 twyleg
#pragma once

#include "./ispi.h"

#include "bcm2835.h"

class BcmSpi : public mfrc522::ISpi{

public:
	BcmSpi() {
		bcm2835_spi_begin();
		bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
		bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
		bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64);    // ~ 4 MHz
		bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
		bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0x00);      // the default
	}

	void write(char* pData, size_t len) final {
		bcm2835_spi_writenb(pData, len);
	}

	void read(char* pData, size_t len) final {
		bcm2835_spi_transfern(pData, len);
	}

	void writeRead(char* pData, size_t len) final {
		bcm2835_spi_transfern(pData, len);
	}

	char writeRead(char data) final {
		return bcm2835_spi_transfer(data);
	}

};
