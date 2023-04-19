// Copyright (C) 2021 twyleg
#pragma once

#include <cstddef>

namespace mfrc522 {

struct ISpi {
	virtual void write(char* pData, size_t len) = 0;
	virtual void read(char* pData, size_t len) = 0;
	virtual void writeRead(char* pData, size_t len) = 0;
	virtual char writeRead(char data) = 0;
};

}
