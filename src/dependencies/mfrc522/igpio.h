// Copyright (C) 2021 twyleg
#pragma once

#include <cstddef>

namespace mfrc522 {

struct IGpio {

	enum class Value {
		low = 0,
		high = 1
	};

	virtual void setValue(Value) = 0;
	virtual Value getValue() = 0;
};

}
