// Copyright (C) 2021 twyleg
#pragma once

#include <mfrc522/ispi.h>
#include <spidevpp/spi.h>

class Spidev : public mfrc522::ISpi {

public:
	Spidev(const std::string& device)
		:  mSpi(device)
	{}

	void write(char* pData, size_t len) final {
		mSpi.write(pData, len);
	}

	void read(char* pData, size_t len) final {
		mSpi.read(pData, len);
	}

	void writeRead(char* pData, size_t len) final {
		mSpi.writeRead(pData, len);
	}

	char writeRead(char data) final {
		return mSpi.writeRead(data);
	}

	spidevpp::Spi mSpi;

};
