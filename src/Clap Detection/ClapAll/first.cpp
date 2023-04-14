// // #include <iostream>
// // #include <vector>
// // #include <cmath>
// // #include <fstream>
// // #include <algorithm>


// // // Define a function to calculate the percentage of match between two audio files
// // double find_per(const std::string& within_file, const std::string& find_file, int window) {
// //     std::ifstream within_fs(within_file, std::ios::binary);
// //     std::ifstream find_fs(find_file, std::ios::binary);

// //     // Get the sample rate of the within_file
// //     uint32_t sr_within;
// //     within_fs.seekg(24);
// //     within_fs.read(reinterpret_cast<char*>(&sr_within), sizeof(sr_within));

// //     // Read the audio data from the within_file and the find_file
// //     std::vector<int16_t> y_within(sr_within * window);
// //     std::vector<int16_t> y_find(sr_within * window);
// //     within_fs.seekg(44);
// //     within_fs.read(reinterpret_cast<char*>(&y_within[0]), y_within.size() * sizeof(y_within[0]));
// //     find_fs.seekg(44);
// //     find_fs.read(reinterpret_cast<char*>(&y_find[0]), y_find.size() * sizeof(y_find[0]));

// //     // Calculate the correlation between the two audio signals
// //     std::vector<double> c(y_within.size() + y_find.size() - 1);
// //     std::cout<< "Hey\n";
// //     std::cout << "The size of the vector is: " << c.size() << std::endl;
// //     for (int i = 0; i < c.size(); i++) {
// //         c[i] = 0;
// //         for (int j = 0; j < y_within.size(); j++) {
// //             if (i - j >= 0 && i - j < y_find.size()) {
// //                 c[i] += y_within[j] * y_find[i - j];
// //             }
// //         }
// //         c[i] = std::abs(c[i]);
// //     }
// //     std::cout << "The size of the vector is: " << c.size() << std::endl;
// //     std::cout<< "Hey\n";
// //     // Square the correlation values
// //     for (int i = 0; i < c.size(); i++) {
// //         c[i] *= c[i];
// //     }

// //     // Find the threshold and count the number of matches
// //     double thres = 0.25 * (*std::max_element(c.begin(), c.end()));
// //     int count = 0;
// //     for (int i = 0; i < c.size(); i++) {
// //         if (c[i] > thres) {
// //             count++;
// //         }
// //     }

// //     // Calculate the percentage of matches
// //     return static_cast<double>(count) / c.size() * 100.0;
// // }

// // // Define the main function
// // // int main(int argc, char** argv) {
// // //     // Parse command line arguments
// // //     int window = 10;
// // //     std::string within_file = "sample.wav";
// // //     std::string find_file = "original.wav";
// // //     if (argc > 1) {
// // //         window = std::stoi(argv[1]);
// // //     }
// // //     if (argc > 2) {
// // //         within_file = argv[2];
// // //     }
// // //     if (argc > 3) {
// // //         find_file = argv[3];
// // //     }

// // //     // Calculate the percentage of matches and print the result
// // //     double per = find_per(within_file, find_file, window);
// // //     if (per <= 0.5) {
// // //         std::cout << "Match Found\n";
// // //     } else {
// // //         std::cout << "Match not found\n";
// // //     }

// // //     return 0;
// // // }

// // int main() {
// //     // Parse command line arguments
// //     int window = 10;
// //     std::string within_file = "sample.wav";
// //     std::string find_file = "original.wav";

// //     // Calculate the percentage of matches and print the result
// //     std::cout<< "Hey\n";
// //     double per = find_per(within_file, find_file, window);
// //     std::cout<< "Hey\n";
// //     if (per <= 0.5) {
// //         std::cout << "Match Found\n";
// //     } else {
// //         std::cout << "Match not found\n";
// //     }

// //     return 0;
// // }







// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <fstream>
// #include <algorithm>

// // Define a function to calculate the percentage of match between two audio files
// double find_per(const std::string& within_file, const std::string& find_file, int window) {
//     std::ifstream within_fs(within_file, std::ios::binary);
//     std::ifstream find_fs(find_file, std::ios::binary);

//     // Get the sample rate of the within_file
//     uint32_t sr_within;
//     within_fs.seekg(24);
//     within_fs.read(reinterpret_cast<char*>(&sr_within), sizeof(sr_within));

//     // Read the audio data from the within_file and the find_file
//     std::vector<int16_t> y_within(sr_within * window);
//     std::vector<int16_t> y_find(sr_within * window);
//     within_fs.seekg(44);
//     within_fs.read(reinterpret_cast<char*>(&y_within[0]), y_within.size() * sizeof(y_within[0]));
//     find_fs.seekg(44);
//     find_fs.read(reinterpret_cast<char*>(&y_find[0]), y_find.size() * sizeof(y_find[0]));

//     // Calculate the correlation between the two audio signals
//     std::vector<double> c(y_within.size() + y_find.size() - 1);
//     std::cout << "The size of the vector is: " << c.size() << std::endl;
//     for (int i = 0; i < y_within.size(); i++) {
//         for (int j = 0; j < y_find.size(); j++) {
//             c[i + j] += y_within[i] * y_find[j];
//         }
//     }
//     std::cout << "The size of the vector is: " << c.size() << std::endl;
//     // Square the correlation values
//     std::for_each(c.begin(), c.end(), [](double& x){ x *= x; });

//     // Find the threshold and count the number of matches
//     double thres = 0.25 * (*std::max_element(c.begin(), c.end()));
//     int count = std::count_if(c.begin(), c.end(), [thres](double x){ return x > thres; });

//     // Calculate the percentage of matches
//     return static_cast<double>(count) / c.size() * 100.0;
// }

// int main() {
//     // Parse command line arguments
//     int window = 10;
//     std::string within_file = "sample.wav";
//     std::string find_file = "original.wav";

//     // Calculate the percentage of matches and print the result
//     std::cout<< "Hey\n";
//     double per = find_per(within_file, find_file, window);
//     std::cout<< "Hey\n";
//     if (per <= 0.5) {
//         std::cout << "Match Found\n";
//     } else {
//         std::cout << "Match not found\n";
//     }

//     return 0;
// }






#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <cstdint> // for uint32_t

// Define a function to calculate the percentage of match between two audio files
double find_per(const std::string& within_file, const std::string& find_file, int window) {
    std::ifstream within_fs(within_file, std::ios::binary);
    std::ifstream find_fs(find_file, std::ios::binary);

    // Get the sample rate of the within_file
    uint32_t sr_within;
    within_fs.seekg(24);
    within_fs.read(reinterpret_cast<char*>(&sr_within), sizeof(sr_within));

    // Read the audio data from the within_file and the find_file
    std::vector<int16_t> y_within(sr_within * window);
    std::vector<int16_t> y_find(sr_within * window);
    within_fs.seekg(44);
    within_fs.read(reinterpret_cast<char*>(&y_within[0]), y_within.size() * sizeof(y_within[0]));
    find_fs.seekg(44);
    find_fs.read(reinterpret_cast<char*>(&y_find[0]), y_find.size() * sizeof(y_find[0]));

    // Calculate the correlation between the two audio signals
    std::vector<double> c(y_within.size() + y_find.size() - 1);
    std::cout<< "Hey\n";
    std::cout << "The size of the vector is: " << c.size() << std::endl;
    // for (int i = 0; i < c.size(); i++) {
    //     c[i] = 0;
    //     for (int j = 0; j < y_within.size(); j++) {
    //         if (i - j >= 0 && i - j < y_find.size()) {
    //             c[i] += y_within[j] * y_find[i - j];
    //         }
    //     }
    //     c[i] = std::abs(c[i]);
    // }

    for (int i = 0; i < c.size(); i++) {
        c[i] = 0;
        int j_start = std::max(0, i - (int)y_within.size() + 1);
        int j_end = std::min((int)y_find.size() - 1, i);
        for (int j = j_start; j <= j_end; j++) {
            c[i] += y_within[i - j] * y_find[j];
        }
        c[i] = std::abs(c[i]);
    }

    std::cout << "The size of the vector is: " << c.size() << std::endl;
    std::cout<< "Hey\n";
    // Square the correlation values
    for (int i = 0; i < c.size(); i++) {
        c[i] *= c[i];
    }

    // Find the threshold and count the number of matches
    double thres = 0.25 * (*std::max_element(c.begin(), c.end()));
    int count = 0;
    for (int i = 0; i < c.size(); i++) {
        if (c[i] > thres) {
            count++;
        }
    }

    // Calculate the percentage of matches
    return static_cast<double>(count) / c.size() * 100.0;
}

// Define the main function
int main(int argc, char** argv) {
    // Parse command line arguments
    int window = 10;
    std::string within_file = "sample.wav";
    std::string find_file = "original.wav";
    if (argc > 1) {
        window = std::stoi(argv[1]);
    }
    if (argc > 2) {
        within_file = argv[2];
    }
    if (argc > 3) {
        find_file = argv[3];
    }

    // Calculate the percentage of matches and print the result
    double per = find_per(within_file, find_file, window);
    if (per <= 0.5) {
        std::cout << "Match Found\n";
    } else {
        std::cout << "Match not found\n";
    }

    return 0;
}