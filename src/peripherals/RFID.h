
#ifndef RFID_H
#define RFID_H

#include "EventHandler.h"

#include "spi/spidev_impl.h"
#include "spi/sys_gpio_impl.h"

#include <mfrc522/mfrc522.h>
#include <spidevpp/gpio.h>

#include <iostream>
#include <thread>

class RFID {
	public:
		RFID() : spi("/dev/spidev0.0") {
			spi.mSpi.setBitsPerWord(8);
			spi.mSpi.setSpeed(488000);
			spi.mSpi.setMode(0);

			std::cout << spi.mSpi << std::endl;

			SysGpio resetPin(25, spidevpp::Gpio::Direction::OUTPUT, spidevpp::Gpio::Value::low);

			mfrc522::MFRC522 mfrc(spi, resetPin);
			mfrc.PCD_Init();
			
			std::cout << "Start read loop!" << std::endl;
			
			while(true) {
				EventHandler& eventHandler = EventHandler::getInstance();
				
				// Look for a card
				if (!mfrc.PICC_IsNewCardPresent()) {
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
					continue;
				}

				if (!mfrc.PICC_ReadCardSerial()) {
					continue;
				}
				
				// Print UID
				std::string UID = "";
				for (uint8_t i = 0; i < mfrc.uid.size; ++i) {
					UID += std::to_string(mfrc.uid.uidByte[i]);
				}

				if(UID == "249240189176") {
					// Emit event.
					printf("Welcome...\n");
					eventHandler.emit(Event::RfidAuthenticated);
					std::this_thread::sleep_for(std::chrono::seconds(3));
					return;
				} else {
					// Emit fail event.
					printf("Invalid rfid! Try again in few seconds...\n");
					std::this_thread::sleep_for(std::chrono::seconds(3));
				}

			}
		}
		
		void Initialize();
		
		void setMfrc(mfrc522::MFRC522* mfrc) {
			mfrcptr = mfrc;
		}

		void start() {
			return;
			std::cout << "Start read loop!" << std::endl;
			// return;
			while(true) {
				EventHandler& eventHandler = EventHandler::getInstance();
				
				std::cout << std::to_string(mfrcptr->PICC_IsNewCardPresent()) << std::endl;
				return;
				
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
					UID += std::to_string(mfrcptr->uid.uidByte[i]);
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
		mfrc522::MFRC522* mfrcptr;
		Spidev spi;
};

#endif
