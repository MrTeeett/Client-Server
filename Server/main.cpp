#include <QCoreApplication>
#include <iostream>
#include <string>
#include <cmath>
#include <QDebug>
#include "server.h"

double aFunction(double x) {
    return cos(x) * 2 - 1.5;
}

double integrate(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (aFunction(a) + aFunction(b)) / 2.0;

    for (int i = 1; i < n; ++i) {
        double x = a + i * h;
        sum += aFunction(x);
    }

    return h * sum;
}

void square(){
    double start = 0.0;  // Начальная точка интегрирования
    double end = 10.0; // Конечная точка интегрирования
    int count = 10000;   // Количество разбиений

    double targetArea = 0.0;
    double previousArea = 0.0;
    double tolerance = 1e-6;

    do {
        previousArea = targetArea;
        targetArea = integrate(start, end, count);
        count *= 2; // Увеличиваем количество разбиений вдвое
    } while (std::abs(targetArea - previousArea) > tolerance);

    std::cout << "Площадь фигуры при y < 0: " << targetArea << std::endl;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
    return a.exec();
}
