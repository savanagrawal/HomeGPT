#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <complex>
#include <bits/stdc++.h>

void fft(std::vector<std::complex<double>>& a, bool inverse) {
    int n = a.size();
    if (n == 1) {
        return;
    }
    std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, inverse);
    fft(a1, inverse);
    std::complex<double> wn(std::cos(2 * M_PI / n), std::sin(2 * M_PI / n));
    if (inverse) {
        wn = std::conj(wn);
    }
    std::complex<double> w(1, 0);
    for (int i = 0; i < n / 2; i++) {
        std::complex<double> t = w * a1[i];
        a[i] = a0[i] + t;
        a[i + n / 2] = a0[i] - t;
        w *= wn;
        if (inverse) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
    }
}


//Compute the circular convolution of two vectors using the DFT
std::vector<double> convolve(const std::vector<double>& a, const std::vector<double>& b) {
    int n = a.size();
    int m = b.size();
    int l = n + m - 1;
    int p = 1;
    while (p < l) {
        p <<= 1;
    }
    std::vector<std::complex<double>> pa(p), pb(p), pc(p);
    std::copy(a.begin(), a.end(), pa.begin());
    std::copy(b.begin(), b.end(), pb.begin());
    fft(pa, false);
    fft(pb, false);
    std::transform(pa.begin(), pa.end(), pb.begin(), pc.begin(),
               [](const std::complex<double>& a, const std::complex<double>& b) { return a * b; });
    fft(pc, true);
    std::vector<double> result(l);
    // Use std::transform to compute the real part of each complex number
    std::transform(pc.begin(), pc.begin() + l, result.begin(),
               [](const std::complex<double>& cplx) { return std::real(cplx) * std::real(cplx); });

    return result;
}



std::vector<double> load_audio_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Unable to open file!");
    }
    
    // read the header
    char header[44];
    file.read(header, 44);
    
    // read data
    const int BUFFER_SIZE = 4096; // arbitrary buffer size
    std::vector<double> data;
    short buffer[BUFFER_SIZE];
    while (file.read(reinterpret_cast<char*>(&buffer[0]), BUFFER_SIZE * sizeof(short))) {
        for (int i = 0; i < BUFFER_SIZE; i++) {
            data.push_back(static_cast<double>(buffer[i]) / std::numeric_limits<short>::max());
        }
    }
    
    return data;
}



// Compute the square of each element in a vector
std::vector<double> square(const std::vector<double>& a) {
    std::vector<double> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] * a[i];
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

    std::vector<double> c = convolve(y_within, y_find);
    
    double thres = *std::max_element(c.begin(), c.end()) / 10.0;
    double count = percentage_above_threshold(c, thres);

    std::fstream file;
    file.open("vector_file.txt",std::ios_base::out);
 
    for(int i=0;i<c.size();i++)
    {
        file<<c[i]<<std::endl;
    }
 
    file.close();

    return count;
}

void result(double per, double check){
    if (per <= check) {
        std::cout << "Match Found" << std::endl;
    } else {
        std::cout << "Match not found" << std::endl;
    }
}

void ClapDetection() {
    std::cout << "Correlating the two sounds..." << std::endl;
    double per = find_per("sample2.wav", "original.wav", 10);
    result(per, 0.5);
}

int main() {
    ClapDetection();
    return 0;
}
