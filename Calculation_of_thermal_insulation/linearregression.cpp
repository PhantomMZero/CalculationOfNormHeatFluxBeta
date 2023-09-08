#include "linearregression.h"
#include <QDebug>


LinearRegression::LinearRegression()
    {
        coeff = 0;
        constTerm = 0;
        sum_y = 0;
        sum_y_square = 0;
        sum_x_square = 0;
        sum_x = 0;
        sum_xy = 0;
    }

    // Function that calculate the coefficient/
    // slope of the best fitting line
    void LinearRegression::calculateCoefficient()
    {
        double N = x.size();
        double numerator
            = (N * sum_xy - sum_x * sum_y);
        double denominator
            = (N * sum_x_square - sum_x * sum_x);
        coeff = numerator / denominator;
    }

    // Member function that will calculate
    // the constant term of the best
    // fitting line
    void LinearRegression::calculateConstantTerm()
    {
        double N = x.size();
        double numerator
            = (sum_y * sum_x_square - sum_x * sum_xy);
        double denominator
            = (N * sum_x_square - sum_x * sum_x);
        constTerm = numerator / denominator;
    }

    // Function that return the number
    // of entries (xi, yi) in the data set
    int LinearRegression::sizeOfData()
    {
        return x.size();
    }

    // Function that return the coefficient/
    // slope of the best fitting line
    double LinearRegression::coefficient()
    {
        if (coeff == 0)
            calculateCoefficient();
        return coeff;
    }

    // Function that return the constant
    // term of the best fitting line
    double LinearRegression::constant()
    {
        if (constTerm == 0)
            calculateConstantTerm();
        return constTerm;
    }

    // Function that print the best
    // fitting line
    QString LinearRegression::PrintBestFittingLine()
    {
        if (coeff == 0 && constTerm == 0) {
            calculateCoefficient();
            calculateConstantTerm();
        }
        QString result="The best fitting line is y= "+ QString::number(coeff) + "x + " + QString::number(constTerm);
        return result;
    }

    // Function to take input from the dataset
    void LinearRegression::takeInput(std::map<double, double> Data)
    {
        auto it=Data.begin();

        while(it!=Data.end()){
            double xi=it->first;
            double yi=it->second;
            sum_xy += xi * yi;
            sum_x += xi;
            sum_y += yi;
            sum_x_square += xi * xi;
            sum_y_square += yi * yi;
            x.push_back(xi);
            y.push_back(yi);
            ++it;
        }
    }




    // Function to predict the value
    // corresponding to some input
    double LinearRegression::predict(double x)
    {
        if (coeff == 0 && constTerm == 0) {
            calculateCoefficient();
            calculateConstantTerm();
        }
        return coeff * x + constTerm;
    }

    // Function that returns overall
    // sum of square of errors
    double LinearRegression::errorSquare()
    {
        double ans = 0;
        for (int i = 0;
             i < x.size(); i++) {
            ans += ((predict(x[i]) - y[i])
                    * (predict(x[i]) - y[i]));
        }
        return ans;
    }

    // Functions that return the error
    // i.e the difference between the
    // actual value and value predicted
    // by our model
    double LinearRegression::errorIn(double num)
    {
        for (int i = 0;
             i < x.size(); i++) {
            if (num == x[i]) {
                return (y[i] - predict(x[i]));
            }
        }
        return 0;
    }


