// Copyright (C) 2021 twyleg
#pragma once

#include "igpio.h"

#include "bcm2835.h"

#include <iostream>

class BcmGpio : public mfrc522::IGpio {

public:
	BcmGpio(unsigned int pin)
		: mPin(pin)
	{
		bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
		bcm2835_gpio_write(pin, 0x00);
	}

	void setValue(Value value) final {
		switch (value) {
		case mfrc522::IGpio::Value::l:
			bcm2835_gpio_write(mPin, 0x00);
			break;
		case mfrc522::IGpio::Value::h:
			bcm2835_gpio_write(mPin, 0x01);
			break;
		}

	}

	Value getValue() final {
		return mfrc522::IGpio::Value::l;
	}

private:

	const unsigned int mPin;

};
