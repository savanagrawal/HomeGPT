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

int main(int argc, const char* argv[]){

	/* Initialize thread objects */
	ControllerThread controllerThread;

	std::cout << argc << std::endl;

	/* Check if there's any agruments worth storing. */
	if(argc > 1) {
		std::vector<std::string> args(argc);
		
		for(int i = 0; i < argc; i++){
			args[i] = argv[i];
		}

		std::cout << args[1];

		controllerThread.setArgs(argc, args);
	}


	/* Run Controller Thread */ 
	controllerThread.start();
  
	/* Join to the thread */
	controllerThread.join();
  
	return 0;
}