//
//  main.cpp
//  IV.12.8 b
//
//  Created by Egor Denisov on 19.10.2021.
//

#include <iostream>
#include <cmath>

/*
 f(x) = x * exp(-x^2), x >= 0
 epsilon = 1e-3
 */

double getFuncValue(double x) {
    const double e = 2.71828;
    double result = x * pow(e, -x * x);
    return result;
}

int main() {
    /*
     Working segment [0; 2]
     On [0; 2] f'(x) <= 1, then Delta F ~ Delta X
     */
    const double step = 1e-3 / 4;
    
    double currentX = 0;
    double edge = 2;
    
    double xHeight = 0;
    double height = getFuncValue(xHeight);
    
    while (currentX < edge) {
        double currentValue = getFuncValue(currentX);
        
        if (currentValue > height) {
            height = currentValue;
            xHeight = currentX;
        }
        currentX += step;
    }
    
    double x1 = xHeight, x2 = xHeight;
    while (getFuncValue(x1) > height / 2) {
        x1 -= step;
    }
    
    while (getFuncValue(x2) > height / 2) {
        x2 += step;
    }
    
    std::cout << "Width: " << x2 - x1 << std::endl;
    
    return 0;
}
