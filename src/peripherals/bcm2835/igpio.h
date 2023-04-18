// Copyright (C) 2021 twyleg
#pragma once

#include <cstddef>
#include <cstdint>

namespace mfrc522 {

	struct IGpio {

		enum class Value {
			l = 0,
			h = 1
		};

		virtual void setValue(Value) = 0;
		virtual Value getValue() = 0;
	};

}
