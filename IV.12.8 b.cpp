//
//  main.cpp
//  IV.12.8 b
//
//  Created by Egor Denisov on 19.10.2021.
//

#include <iostream>
#include <vector>
#include <cmath>

/*
 IV.12.8
 f(x) = x * exp(-x^2), x >= 0
 error <= 1e-3
 Width on half of height - ?
 */

class Task {
private:
    static const double halfHeight;
    
    std::vector<double> roots = {};
    
public:
    Task() { }
    
    static double fiFirst(const double &x) {
        return (exp(x * x) * halfHeight);
    }
    
    static double fiSecond(const double &x) {
        return sqrt(log(x / halfHeight));
    }
    
    double getDifferenceWithHalfHeight(double x) {
        return (x * exp(-x * x) - halfHeight);
    }
    
    void localizeRoots() {
        double currentX = 0;
        double edge = 2;
        const double step = 1e-1;
        
        for( ; currentX < edge; currentX += step) {
            if (getDifferenceWithHalfHeight(currentX) *
                getDifferenceWithHalfHeight(currentX + step) <= 0) {
                roots.push_back(currentX);
            }
        }
    }
    
    double & getRootRef(const int i) {
        return roots[i];
    }
    
    double getWidth() {
        return roots[1] - roots[0];
    }
};

const double Task::halfHeight = 1 / (2 * sqrt(2 * M_E));


bool useSimpleIterationMethod(double &x, double (*fi)(const double &)) {
    const double epsilon = 1e-3;
    while (fabs(fi(x) - x) > epsilon / 2) {
        x = fi(x);
    }
    return true;
}


int main() {
    Task task = Task();
    
    task.localizeRoots();
    
    useSimpleIterationMethod(task.getRootRef(0), Task::fiFirst);
    useSimpleIterationMethod(task.getRootRef(1), Task::fiSecond);
    
    std::cout << "Width: " << task.getWidth() << std::endl;
    
    return 0;
}
