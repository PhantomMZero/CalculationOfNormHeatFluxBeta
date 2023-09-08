#ifndef CLOSESTELEMENTSINTABLES_H
#define CLOSESTELEMENTSINTABLES_H
#include <map>

class ClosestElementsInTables
{
private:
    std::pair<double,double> Lower;
    double y;

public:

    std::pair<double,double> ClosestLowerDNLowerTEnterKey(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestLowerTBiggerDNEnterKey(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestBiggerTSmallerDNEnterKey(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestSmallerDNEnterKeyIn_6_7Tables(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> BiggerTandSmallerDNInTables6_7(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> BiggerTandBiggerDNInTables6_7(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    double FindExtrapolationForPositiveByT(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    double FindExtrapolationForNegativeByT(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    double FindExtrapolationForPositiveTTableOrNot(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    double FindExtrapolationForNegativeTTableOrNot(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey);

    double FindExtrapolationR(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestLowerDNLowerTEnterKey(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestLowerTBiggerDNEnterKey(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestBiggerTSmallerDNEnterKey(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey);

    std::pair<double,double> ClosestSmallerDNEnterKeyIn_6_7Tables(std::map <const std::pair<int,double>,const int> TableSp, std::pair<double,double> EnterKey);

};

#endif // CLOSESTELEMENTSINTABLES_H

