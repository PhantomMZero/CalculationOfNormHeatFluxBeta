#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <vector>
#include <map>
#include <QString>

class LinearRegression {
    // Dynamic array which is going
    // to contain all (i-th x)
    std::vector<double> x;

    // Dynamic array which is going
    // to contain all (i-th y)
    std::vector<double> y;

    // Store the coefficient/slope in
    // the best fitting line
    double coeff;

    // Store the constant term in
    // the best fitting line
    double constTerm;

    // Contains sum of product of
    // all (i-th x) and (i-th y)
    double sum_xy;

    // Contains sum of all (i-th x)
    double sum_x;

    // Contains sum of all (i-th y)
    double sum_y;

    // Contains sum of square of
    // all (i-th x)
    double sum_x_square;

    // Contains sum of square of
    // all (i-th y)
    double sum_y_square;

public:
    // Constructor to provide the default
    // values to all the terms in the
    // object of class regression
    LinearRegression();


    // Function that calculate the coefficient/
    // slope of the best fitting line
    void calculateCoefficient();


    // Member function that will calculate
    // the constant term of the best
    // fitting line
    void calculateConstantTerm();


    // Function that return the number
    // of entries (xi, yi) in the data set
    int sizeOfData();


    // Function that return the coefficient/
    // slope of the best fitting line
    double coefficient();


    // Function that return the constant
    // term of the best fitting line
    double constant();


    // Function that print the best
    // fitting line
    QString PrintBestFittingLine();


    // Function to take input from the dataset
    void takeInput(std::map<double, double> Data);





    // Function to predict the value
    // corresponding to some input
    double predict(double x);

    // Function that returns overall
    // sum of square of errors
    double errorSquare();


    // Functions that return the error
    // i.e the difference between the
    // actual value and value predicted
    // by our model
    double errorIn(double num);
};


#endif // LINEARREGRESSION_H
