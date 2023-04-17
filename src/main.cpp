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
#include <unistd.h>
#define GetCurrentDir getcwd

int main(int argc, const char* argv[] ){

	/* Initialize thread objects */ 
	ControllerThread controllerThread;

	// char buff[FILENAME_MAX];
	// GetCurrentDir( buff, FILENAME_MAX );
	// std::string current_working_dir(buff);

	// // std::string path = realpath();
  	// char* curr_working_dir = get_current_dir_name();

	// std::cout << current_working_dir << std::endl;
	
	// boost::filesystem::path path = boost::filesystem::current_path();

	// std::cout << path;

	// std::fstream my_file;
	// my_file.open(path.string(), std::ios::in);
	// if (!my_file) {
	// 	std::cout << "No such file";
	// }
	// else {
	// 	char ch;

	// 	while (1) {
	// 		my_file >> ch;
	// 		if (my_file.eof())
	// 			break;

	// 		std::cout << ch;
	// 	}

	// }
	// my_file.close();

	// printf(""+path);

	// return 0;
	/* Run Controller Thread */ 
	controllerThread.start();
  
	/* Join to the thread */
	controllerThread.join();
  
	return 0;
}