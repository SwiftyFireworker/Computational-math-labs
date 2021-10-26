//
//  main.cpp
//  4 lab. System of equations
//
//  Created by Egor Denisov on 26.10.2021.
//

#include <iostream>
#include <vector>
#include <cmath>


/*
 x^2 + y^2 = 1
 y = tg(x)
 epsilon = 1e-6
 Using Newton's method
 */

std::vector<double> operator- (const std::vector<double> &lhs,
                               const std::vector<double> &rhs) {
    assert(lhs.size() == rhs.size());
    
    std::vector<double> result(lhs.size());
    for (size_t i = 0; i < lhs.size(); i++) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}


class Task {
private:
    static const double epsilon;
    
    bool isEqual(const double &x, const double &y) {
        return (fabs(x - y) < epsilon);
    }

    bool isEqual(const std::vector<double> &x, const std::vector<double> &y) {
        assert(x.size() == y.size());
        
        for (size_t i = 0; i < x.size(); i++) {
            if (!isEqual(x[i], y[i])) {
                return false;
            }
        }
        return true;
    }
    
    /*
     F - column of system functions, J - jacobian of system
     */
    double determinantJacobian(double x, double y) {
        return (2*x + 2*y / (cos(x)*cos(x)));
    }

    /*
     Funcs of J^(-1) * F:
     */
    double funcFirst(const std::vector<double> &a) {
        double x = a[0], y = a[1];
        return ((x*x - y*y + 2*y*tan(x) - 1) /
                determinantJacobian(x, y));
    }

    double funcSecond(const std::vector<double> &a) {
        double x = a[0], y = a[1];
        return ((2*x*y - 2*x*tan(x) +
                 (x*x + y*y - 1) / (cos(x)*cos(x))) /
                determinantJacobian(x, y));
    }
    
public:
    Task() { }
    
    void use(std::vector<double> &x1) {
        std::vector<double> temp = {funcFirst(x1), funcSecond(x1)};
        std::vector<double> x2 = x1 - temp;
        
        while (!isEqual(x1, x2)) {
            x1 = x2;
            temp = temp = {funcFirst(x1), funcSecond(x1)};
            x2 = x1 - temp;
        }
    }
};

const double Task::epsilon = 1e-6;


int main() {
    std::vector<double> x = {1, 1};
    
    Task task = Task();
    task.use(x);
    
    std::cout << "Result of Newton's method: " << x[0] << ", " << x[1] << std::endl;
    return 0;
}
