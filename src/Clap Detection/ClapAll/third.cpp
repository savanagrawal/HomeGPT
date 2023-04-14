#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <complex>
#include <bits/stdc++.h>


void fft(std::vector<std::complex<double>>& a, std::vector<std::complex<double>>& b, bool inverse) {
    int n = a.size();
    if (n == 1) {
        b[0] = a[0];
        return;
    }
    std::vector<std::complex<double>> a0(n / 2), a1(n / 2), b0(n / 2), b1(n / 2);
    for (int i = 0; i < n / 2; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, b0, inverse);
    fft(a1, b1, inverse);
    std::complex<double> w(1, 0), wn(std::cos(2 * M_PI / n), std::sin(2 * M_PI / n));
    if (inverse) {
        wn = std::conj(wn);
    }
    for (int i = 0; i < n / 2; i++) {
        b[i] = b0[i] + w * b1[i];
        b[i + n / 2] = b0[i] - w * b1[i];
        w *= wn;
    }
    if (inverse) {
        for (int i = 0; i < n; i++) {
            b[i] /= n;
        }
    }
}



std::vector<double> correlate(const std::vector<double>& a, const std::vector<double>& b) {
    // Pad the input vectors with zeros to make them of equal length, which is a power of 2
    int n = 1;
    while (n < a.size() + b.size() - 1) {
        n <<= 1;
    }
    std::vector<std::complex<double>> pa(n), pb(n);
    for (int i = 0; i < a.size(); i++) {
        pa[i] = a[i];
    }
    for (int i = 0; i < b.size(); i++) {
        pb[i] = b[i];
    }
    std::cout<<pb[0]<<std::endl;
    // Compute the FFT of both padded vectors
    std::vector<std::complex<double>> fa(n), fb(n);
    fft(pa, fa, false);
    fft(pb, fb, false);
    std::cout<<fa[0]<<std::endl;
    // Multiply the FFTs element-wise
    std::vector<std::complex<double>> fc(n);
    for (int i = 0; i < n; i++) {
        fc[i] = fa[i] * fb[i];
    }
    std::cout<<fb[0]<<std::endl;
    // Compute the inverse FFT of the product
    std::vector<std::complex<double>> fd(n);
    fft(fc, fd, true);
    std::cout<<fd[0]<<std::endl;
    // Extract the real part of the inverse FFT to get the correlation result
    std::vector<double> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = fd[i].real();
    }
    result.resize(a.size() + b.size() - 1);
    return result;
}


// // Compute the FFT of a vector
// void fft(std::vector<std::complex<double>>& a, bool inverse) {
//     int n = a.size();
//     if (n == 1) {
//         return;
//     }
//     std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
//     for (int i = 0; i < n / 2; i++) {
//         a0[i] = a[2 * i];
//         a1[i] = a[2 * i + 1];
//     }
//     fft(a0, inverse);
//     fft(a1, inverse);
//     std::complex<double> w(1, 0), wn(std::cos(2 * M_PI / n), std::sin(2 * M_PI / n));
//     if (inverse) {
//         wn = std::conj(wn);
//     }
//     for (int i = 0; i < n / 2; i++) {
//         std::complex<double> t = w * a1[i];
//         a[i] = a0[i] + t;
//         a[i + n / 2] = a0[i] - t;
//         w *= wn;
//         if (inverse) {
//             a[i] /= 2;
//             a[i + n / 2] /= 2;
//         }
//     }
// }

// // Compute the circular convolution of two vectors using the DFT
// std::vector<double> convolve(const std::vector<double>& a, const std::vector<double>& b) {
//     int n = a.size();
//     int m = b.size();
//     int l = n + m - 1;
//     int p = 1;
//     while (p < l) {
//         p <<= 1;
//     }
//     std::vector<std::complex<double>> pa(p), pb(p), pc(p), pd(p);
//     for (int i = 0; i < n; i++) {
//         pa[i] = a[i];
//     }
//     for (int i = 0; i < m; i++) {
//         pb[i] = b[i];
//     }
//     fft(pa, false);
//     fft(pb, false);
//     for (int i = 0; i < p; i++) {
//         pc[i] = pa[i] * pb[i];
//     }
//     fft(pc, true);
//     std::vector<double> result(l);
//     for (int i = 0; i < l; i++) {
//         result[i] = pc[i].real();
//         result[i] *= result[i];
//     }
//     return result;
// }

// void fft(std::vector<std::complex<double>>& a, bool inverse) {
//     int n = a.size();
//     if (n == 1) {
//         return;
//     }
//     std::vector<std::complex<double>> a0(n / 2), a1(n / 2);
//     for (int i = 0; i < n / 2; i++) {
//         a0[i] = a[2 * i];
//         a1[i] = a[2 * i + 1];
//     }
//     fft(a0, inverse);
//     fft(a1, inverse);
//     std::complex<double> wn(std::cos(2 * M_PI / n), std::sin(2 * M_PI / n));
//     if (inverse) {
//         wn = std::conj(wn);
//     }
//     std::complex<double> w(1, 0);
//     for (int i = 0; i < n / 2; i++) {
//         std::complex<double> t = w * a1[i];
//         a[i] = a0[i] + t;
//         a[i + n / 2] = a0[i] - t;
//         w *= wn;
//         if (inverse) {
//             a[i] /= 2;
//             a[i + n / 2] /= 2;
//         }
//     }
// }


// std::vector<double> convolve(const std::vector<double>& a, const std::vector<double>& b) {
//     int n = a.size();
//     int m = b.size();
//     int l = n + m - 1;
//     int p = 1;
//     while (p < l) {
//         p <<= 1;
//     }
//     std::vector<std::complex<double>> pa(p), pb(p);
//     for (int i = 0; i < n; i++) {
//         pa[i] = a[i];
//     }
//     for (int i = 0; i < m; i++) {
//         pb[i] = b[i];
//     }
//     fft(pa, false);
//     fft(pb, false);
//     for (int i = 0; i < p; i++) {
//         pa[i] *= pb[i];
//     }
//     fft(pa, true);
//     std::vector<double> result(l);
//     for (int i = 0; i < l; i++) {
//         result[i] = pa[i].real();
//         result[i] *= result[i];
//     }
//     return result;
// }

// Compute the FFT of a vector
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
    std::complex<double> w(1, 0), wn(std::cos(2 * M_PI / n), std::sin(2 * M_PI / n));
    if (inverse) {
        wn = std::conj(wn);
    }
    for (int i = 0; i < n / 2; i++) {
        std::complex<double> t = w * a1[i];
        a[i] = a0[i] + t;
        a[i + n / 2] = a0[i] - t;
        w *= wn;
        if (inverse) {
            a[i] /= 2.0;
            a[i + n / 2] /= 2.0;
        }
    }
}



// Compute the circular convolution of two vectors using the DFT
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
    // for (int i = 0; i < p; i++) {
    //     pc[i] = pa[i] * pb[i];
    // }

    std::transform(pa.begin(), pa.end(), pb.begin(), pc.begin(),
               [](const std::complex<double>& a, const std::complex<double>& b) { return a * b; });
    fft(pc, true);

    std::vector<double> result(l);
    // for (int i = 0; i < l; i++) {
    //     // result[i] = std::real(pc[i]) / static_cast<double>(p);
    //     result[i] = std::real(pc[i]);
    // }


    // Use std::transform to compute the real part of each complex number
    std::transform(pc.begin(), pc.begin() + l, result.begin(),
               [](const std::complex<double>& cplx) { return std::real(cplx) * std::real(cplx); });

    return result;
}








// // function to load audio file
// std::vector<double> load_audio_file(const std::string& filename) {
//     std::ifstream file(filename, std::ios::binary);
//     if (!file) {
//         throw std::runtime_error("Unable to open file!");
//     }
    
//     // read the header
//     char header[44];
//     file.read(header, 44);
    
//     // read data
//     std::vector<double> data;
//     short sample;
//     while (file.read(reinterpret_cast<char*>(&sample), 2)) {
//         data.push_back(static_cast<double>(sample) / std::numeric_limits<short>::max());
//     }
    
//     return data;
// }

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
    double c = 1.0e-120;
    for (int i = 0; i < a.size(); i++) {
        result[i] = a[i] * a[i];
        // result[i] /= c;
    }

    return result;
}

// // Find the maximum element in a vector
// double max_element(const std::vector<double>& a) {
//     double result = a[0];

//     for (int i = 1; i < a.size(); i++) {
//         if (a[i] > result) {
//             result = a[i];
//         }
//     }

//     return result;
// }

// // Find the percentage of elements in a vector that are greater than a threshold
// double percentage_above_threshold(const std::vector<double>& a, double threshold) {
//     int count = 0;

//     for (double i : a) {
//         if (i > threshold) {
//             count++;
//         }
//     }
//     std::cout<<count<<std::endl;
//     return static_cast<double>(count) / static_cast<double>(a.size()) * 100.0;
// }

double percentage_above_threshold(const std::vector<double>& a, double threshold) {
    const int count = std::count_if(a.begin(), a.end(), [threshold](double i) { return i > threshold; });
    return static_cast<double>(count) / static_cast<double>(a.size()) * 100.0;
}


double find_per(const std::string& within_file, const std::string& find_file, int window) {
    double sr_within, sr_find;
    std::vector<double> y_within = load_audio_file(within_file);
    std::vector<double> y_find = load_audio_file(find_file);

    std::cout<<y_within.size()<<std::endl;
    std::cout<<y_find.size()<<std::endl;

    // std::vector<double> c = correlate(y_within, y_find);
    std::vector<double> c = convolve(y_within, y_find);
    // c = square(c);
    
    double thres = *std::max_element(c.begin(), c.end()) / 10.0;
    double count = percentage_above_threshold(c, thres);

    std::cout << *std::max_element(c.begin(), c.end()) << std::endl;
    std::cout << count << std::endl;

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
    double per = find_per("cat.wav", "sample.wav", 10);
    result(per, 0.5);
}

int main() {
    ClapDetection();
    return 0;
}


// thres = 2
//sample = 0.022515
//sample2 = 0.0134687
//sample3 = 0.00717657
//whistle = 0.00323406
//cat = 0.613182

// thres = 1.2
//sample = 0.00274992
//sample2 = 0.000380472
//sample3 = 0.000326208
//whistle = 0.000421834
//cat = 0.00733471