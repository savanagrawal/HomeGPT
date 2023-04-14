#include <iostream>
#include <vector>
#include "gnuplot_i.hpp"

int main()
{
    std::vector<double> myVector {1, 2, 3, 4, 5};
    
    Gnuplot plot;
    plot.plot_x(myVector, "My Vector");
    
    return 0;
}
