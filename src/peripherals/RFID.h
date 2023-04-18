
#ifndef RFID_H
#define RFID_H

#include "bcm2835.h"
#include "bcm2835/bcm2835_spi_impl.h"
#include "bcm2835/bcm2835_gpio_impl.h"

#include "EventHandler.h"

#include "MFRC522.h"

#include <iostream>
#include <thread>

class RFID {
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

		void start() {
			while(true) {
				EventHandler& eventHandler = EventHandler::getInstance();

				// Look for a card
				if (!mfrcptr->PICC_IsNewCardPresent()) {
					std::this_thread::sleep_for(std::chrono::seconds(1));
					continue;
				}

				if (!mfrcptr->PICC_ReadCardSerial()) {
					continue;
				}

				// Print UID
				std::string UID = "";
				for (uint8_t i = 0; i < mfrcptr->uid.size; ++i) {
					if (mfrcptr->uid.uidByte[i] < 0x10) {
						UID += std::to_string(mfrcptr->uid.uidByte[i]);
					} else {
						UID += std::to_string(mfrcptr->uid.uidByte[i]);
					}
				}

				if(UID == "249240189176") {
					// Emit event.
					printf("Welcome...");
					eventHandler.emit(Event::RfidAuthenticated);
					return;
				} else {
					// Emit fail event.
					printf("Invalid rfid!");
				}
				printf("\n");

			}
		}
		
	private:
		mfrc522::MFRC522* mfrcptr = nullptr;
};

#endif
