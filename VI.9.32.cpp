//
//  main.cpp
//  VI.9.32
//
//  Created by Egor Denisov on 19.10.2021.
//

#include <iostream>
#include <vector>

using T = double;

T getDividedDifference(std::vector<T>::const_iterator xBegin, std::vector<T>::const_iterator xEnd,
                       std::vector<T>::const_iterator yBegin, std::vector<T>::const_iterator yEnd) {
    if (xEnd - xBegin == 1) {
        return *yBegin;
    }
    
    if (xEnd - xBegin == 2) {
        return (*(yEnd - 1) - *yBegin) / (*(xEnd - 1) - *xBegin);
    }
    
    return (getDividedDifference(xBegin + 1, xEnd, yBegin + 1, yEnd) -
            getDividedDifference(xBegin, xEnd - 1, yBegin, yEnd - 1)) / (*(xEnd - 1) - *xBegin);
}

T useNewtonPolynomial(const std::vector<T>& x, const std::vector<T>& y,
                      const T point) {
    T result = y[0];
    
    T coeff = 1;
    for (int i = 1; i < x.size(); i++) {
        coeff *= (point - x[i - 1]);
        result += coeff * getDividedDifference(x.cbegin(), x.cbegin() + i + 1,
                                               y.cbegin(), y.cbegin() + i + 1);
    }
    
    return result;
}

void readData(int & n, std::vector<T> & x, std::vector<T> & y) {
    std::cout << "Enter number of points:\n";
    std::cin >> n;
    x.resize(n);
    y.resize(n);
    
    std::cout << "\nEnter points x_i, f(x_i):\n";
    for (int i = 0; i < n; i++) {
        std::cin >> x[i] >> y[i];
        assert(std::find(x.begin(), x.begin() + i, x[i]) == x.begin() + i);
    }
}

int main() {
    int n = 0;
    std::vector<T> x, y;
    readData(n, x, y);
    
    double point = 2010;
    std::cout << "Newton's result for "<< point << " year: " << useNewtonPolynomial(x, y, point) << std::endl;
    
    return 0;
}
