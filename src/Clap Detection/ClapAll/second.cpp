// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <fstream>
// #include <algorithm>
// #include "Fir1.h"
// #include <fir1/fir1.hpp>

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

//     // Design a lowpass filter
//     const int N = 31;
//     const double Fc = 0.25;
//     std::vector<double> b = fir1::lowpass(N, Fc, fir1::WINDOW_HANN);

//     // Filter the signals with the designed filter
//     std::vector<double> y_within_flt(y_within.size());
//     std::vector<double> y_find_flt(y_find.size());
//     fir1::filter(b, y_within, y_within_flt);
//     fir1::filter(b, y_find, y_find_flt);

//     // Calculate the correlation between the two audio signals
//     std::vector<double> c(y_within_flt.size() + y_find_flt.size() - 1);
//     for (int i = 0; i < c.size(); i++) {
//         c[i] = 0;
//         for (int j = 0; j < y_within_flt.size(); j++) {
//             if (i - j >= 0 && i - j < y_find_flt.size()) {
//                 c[i] += y_within_flt[j] * y_find_flt[i - j];
//             }
//         }
//         c[i] = std::abs(c[i]);
//     }

//     // Square the correlation values
//     for (int i = 0; i < c.size(); i++) {
//         c[i] *= c[i];
//     }

//     // Find the threshold and count the number of matches
//     double thres = 0.25 * (*std::max_element(c.begin(), c.end()));
//     int count = 0;
//     for (int i = 0; i < c.size(); i++) {
//         if (c[i] > thres) {
//             count++;
//         }
//     }

//     // Calculate the percentage of matches
//     return static_cast<double>(count) / c.size() * 100.0;
// }

// // Define the main function
// int main() {
//     // Parse command line arguments
//     int window = 10;
//     std::string within_file = "sample.wav";
//     std::string find_file = "original.wav";

//     // Calculate the percentage of matches and print the result
//     std::cout << "Hey\n";
//     double per = find_per(within_file, find_file, window);
//     std::cout << "Hey\n";
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

#include <vector>
#include <algorithm>
#include <cmath>


// function to load audio file
std::vector<double> load_audio_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file!");
    }
    
    // read the header
    char header[44];
    file.read(header, 44);
    
    // read data
    std::vector<double> data;
    short sample;
    while (file.read(reinterpret_cast<char*>(&sample), 2)) {
        data.push_back(static_cast<double>(sample) / std::numeric_limits<short>::max());
    }
    
    return data;
}

// Compute the cross-correlation between two signals a and b
std::vector<double> correlate(const std::vector<double>& a, const std::vector<double>& b) {
    std::vector<double> result(a.size() + b.size() - 1);
    std::cout<<result.size()<<std::endl;
    int count = 0;
    for (int i = 0; i < result.size(); i++) {
        double sum = 0.0;
        int j_min = std::max(0, i - static_cast<int>(b.size()) + 1);
        int j_max = std::min(static_cast<int>(a.size()) - 1, i);

        for (int j = j_min; j <= j_max; j++) {
            sum += a[j] * b[i - j];
        }
        count += 1;
        std::cout<<count<<std::endl;
        result[i] = sum;
    }

    return result;
}

// Compute the square of each element in a vector
std::vector<double> square(const std::vector<double>& a) {
    std::vector<double> result(a.size());

    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] * a[i];
    }

    return result;
}

// Find the maximum element in a vector
double max_element(const std::vector<double>& a) {
    double result = a[0];

    for (int i = 1; i < a.size(); i++) {
        if (a[i] > result) {
            result = a[i];
        }
    }

    return result;
}

// Find the percentage of elements in a vector that are greater than a threshold
double percentage_above_threshold(const std::vector<double>& a, double threshold) {
    int count = 0;

    for (double i : a) {
        if (i > threshold) {
            count++;
        }
    }

    return static_cast<double>(count) / static_cast<double>(a.size()) * 100.0;
}

double find_per(const std::string& within_file, const std::string& find_file, int window) {
    double sr_within, sr_find;
    std::vector<double> y_within = load_audio_file(within_file);
    std::vector<double> y_find = load_audio_file(find_file);

    std::cout<<y_within.size()<<std::endl;
    std::cout<<y_find.size()<<std::endl;

    int n_samples_within = static_cast<int>(sr_within * window);
    std::vector<double> y_find_short(y_find.begin(), y_find.begin() + n_samples_within);

    std::vector<double> c = correlate(y_within, y_find);
    c = square(c);

    double thres = max_element(c) / 4.0;
    double count = percentage_above_threshold(c, thres);

    std::cout << y_find[0] << std::endl;

    return count;
}


int main() {
    double per = find_per("whistle.wav", "original.wav", 10);
    if (per <= 0.5) {
        std::cout << "Match Found" << std::endl;
    } else {
        std::cout << "Match not found" << std::endl;
    }
    return 0;
}
