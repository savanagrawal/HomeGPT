
#ifndef RFID_H
#define RFID_H

#include "bcm2835.h"
#include "bcm2835_spi_impl.h"
#include "bcm2835_gpio_impl.h"
#include "CppTimer.h"

#include "libmfrc522.h"

#include <iostream>
#include <thread>

class RFID : public CppTimer{
	void timerEvent() {
		// Look for a card
		if (!mfrcptr->PICC_IsNewCardPresent()) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			return;
		}

		if (!mfrcptr->PICC_ReadCardSerial()) {
			return;
		}

		// Print UID
		for (uint8_t i = 0; i < mfrcptr->uid.size; ++i) {
			if (mfrcptr->uid.uidByte[i] < 0x10) {
				printf(" 0");
				printf("%X", mfrcptr->uid.uidByte[i]);
			} else {
				printf(" ");
				printf("%X", mfrcptr->uid.uidByte[i]);
			}
		}
		printf("\n");
	}
	public:
		RFID() {
			BcmSpi spi{};
			BcmGpio resetPin(25);

			mfrc522::MFRC522 mfrc(spi,resetPin);
			mfrc.PCD_Init();
			
			RFID::setMfrc(&mfrc);

			std::cout << "Start read loop!" << std::endl;
		}
		
		void Initialize();
		
		void setMfrc(mfrc522::MFRC522* mfrc) {
			mfrcptr = mfrc;
		}
		
	private:
		mfrc522::MFRC522* mfrcptr = nullptr;
};

#endif
