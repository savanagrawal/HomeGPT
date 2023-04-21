/**
* @file main.cpp
* @author Chinmay Nagrale
* @version 0.1
*
* 
* This is main entry for the program.
*
* 
*/
#include "ControllerThread.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem.hpp>
#include <pigpio.h>

int main(int argc, const char* argv[]){
	
	if (gpioInitialise() < 0) {
		std::cerr << "Error initializing pigpio" << std::endl;
		return 1;
	}

	/* Initialize thread objects */
	ControllerThread controllerThread;

	/* Check if there's any agruments worth storing. */
	if(argc > 1) {
		std::vector<std::string> args(argc);
		
		for(int i = 0; i < argc; i++){
			args[i] = argv[i];
		}
		
		controllerThread.setArgs(argc, args);
	}


	/* Run Controller Thread */ 
	controllerThread.start();
  
	/* Join to the thread */
	controllerThread.join();
	
	gpioTerminate();
  
	return 0;
}
