#ifndef EXPONENTIALFITTING_H
#define EXPONENTIALFITTING_H

#include<cmath>
#include<QString>
#include<map>

class ExponentialFitting
{

    double a,b,c;

    double xsum,x2sum,ysum,xysum;

    double predictedY;





public:
    ExponentialFitting();

    double predict(std::map<double, double> Data, double x);

    QString PrintBestFittingLine();



};

#endif // EXPONENTIALFITTING_H
