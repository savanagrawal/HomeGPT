// Copyright (C) 2021 twyleg
#pragma once

#include <mfrc522/igpio.h>
#include <spidevpp/gpio.h>

class SysGpio : public mfrc522::IGpio {

public:
	SysGpio(unsigned int pin, spidevpp::Gpio::Direction direction, spidevpp::Gpio::Value value)
		:  mGpio(pin, direction, value)
	{}

	void setValue(Value value) final {
		mGpio.setValue(static_cast<spidevpp::Gpio::Value>(value));
	}

	Value getValue() final {
		return static_cast<mfrc522::IGpio::Value>(mGpio.getValue());
	}

	spidevpp::Gpio mGpio;

};
