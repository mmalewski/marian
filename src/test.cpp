#include <iostream>
#include <ctime>

#include "marian.h"

using namespace marian;

Var layer(size_t max, std::vector<Var>& x) {
    Var x0 = 1, x1 = 2, x2 = 3;
    x = { x0, x1, x2 };
    
    Var y = 0.0;
    for(int i = 0; i < max; i++) {
        Var xi = i;
        x.push_back(xi);
        y = y + x0 + log(x2) + x1;
        for(int j = 0; j < i; ++j) {
            y = y + xi;
        }
    }
    
    return y;
}

int main(int argc, char** argv) {
    srand(time(NULL));
        
    std::vector<Var> x1, x2;
    Var y1 = layer(10, x1);
    Var y2 = layer(rand() % 20 + 1, x2);
    
    Var y = y1 + log(y2);
    
    set_zero_all_adjoints();
    y.calc_gradients();
    
    std::cerr << "y1 = " << y1.val() << std::endl;
    std::cerr << "y2 = " << y2.val() << std::endl;
    std::cerr << "y = " << y.val() << std::endl;
    
    std::cerr << "dy/dy1 = " << y1.grad() << std::endl;
    std::cerr << "dy/dy2 = " << y2.grad() << std::endl;
    
    for(size_t i = 0; i < x1.size(); ++i)
        std::cerr << "dy/dx1_" << i << " = " << x1[i].grad() << std::endl;
    for(size_t i = 0; i < x2.size(); ++i)
        std::cerr << "dy/dx2_" << i << " = " << x2[i].grad() << std::endl;
    
}