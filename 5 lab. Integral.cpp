//
//  main.cpp
//  5 lab. Integral
//
//  Created by Egor Denisov on 25.10.2021.
//

#include <iostream>
#include <cmath>
#include <vector>

/*
 Integral [0; 3] f(x) dx
 f(x) = sin(100 * x) * exp(-x^2) * cos(2 * x)
 */


class SimpsonMethod {
private:
    double lowerLimit;
    double upperLimit;
    int N;
    
    double h;
    std::vector<double> points = {};
    
public:
    SimpsonMethod(double lowerLimit, double upperLimit, int n)
        : lowerLimit(lowerLimit), upperLimit(upperLimit), N(2 * n)
    {
        h = (upperLimit - lowerLimit) / double(N);
        for(int i = 0; i < N + 1; i++) {
            points.push_back(lowerLimit + i * h);
        }
    }
    
    double use(double (*f)(double)) {
        double result = 0;
        result += f(points[0]) + f(points[N]);
        
        for(int i = 1; i < N; i++) {
            double coeff = (i % 2 == 0) ? 2 : 4;
            result += coeff * f(points[i]);
        }
        result *= h / 3;
        return result;
    }
    
};


double func(double x) {
    return (sin(100 * x) * exp(-x * x) * cos(2 * x));
}


int main() {
    SimpsonMethod simpsonMethod(0, 3, 10000);
    std::cout << "Result of Simpson's method " << simpsonMethod.use(func) << std::endl;
    return 0;
}
