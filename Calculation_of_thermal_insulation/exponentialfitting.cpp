#include "exponentialfitting.h"


ExponentialFitting::ExponentialFitting(){
    a=0,b=0,c=0;

    xsum=0,x2sum=0,ysum=0,xysum=0;

    predictedY=0;
}


double ExponentialFitting::predict(std::map<double,double> Data, double x)
{
    double* lny=new double[Data.size()];
    int i=0;
    for (auto it=Data.begin();it!=Data.end();it++,i++){                        //Calculate the values of ln(yi)
        lny[i]=log(it->first);
    }
                   //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    i=0;

    for (auto it=Data.begin();it!=Data.end();it++,i++)
    {
        xsum=xsum+it->second;                        //calculate sigma(xi)
        ysum=ysum+lny[i];                        //calculate sigma(yi)
        x2sum=x2sum+pow(it->second,2);                //calculate sigma(x^2i)
        xysum=xysum+it->second*lny[i];                    //calculate sigma(xi*yi)
    }
    a=(i*xysum-xsum*ysum)/(i*x2sum-xsum*xsum);            //calculate slope(or the the power of exp)
    b=(x2sum*ysum-xsum*xysum)/(x2sum*i-xsum*xsum);            //calculate intercept
    c=pow(2.71828,b);                        //since b=ln(c)

    double predictedY=c*pow(2.71828,a*x);                    //to calculate y(fitted) at given x points

    delete [] lny;


    return predictedY;
}



QString ExponentialFitting::PrintBestFittingLine()
{

    QString result="The best fitting line is y= "+ QString::number(c) + "e^" + QString::number(a);
    return result;

}
