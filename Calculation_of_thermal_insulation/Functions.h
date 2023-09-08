#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <map>



//Функция подсчета толщины теплоизоляции  по нормированной плотности теплового потока для поверхностей 1,4м и более

extern double DIzulN1ForSurface(double LambdaIz,double tOutside,double tInside, double KCoefficient, int qCoefficient, double RCoefficient);

extern double BForPipelinesFormula(double LambdaIz, double tOutside, double tInside, double KCoefficient, double qCoefficient, double RCoefficient); //Переделать Ккоэф

//Функция подсчета толщины теплоизоляции  по нормированной плотности теплового потока для однослойных цилиндрических поверхностей менее 1,4м
extern double DIzulN1ForPipelines(double B, double DiameterPipeline);

extern double K1Take(int NTypeofPillars, double DN);//Функция для поиска нужного коэффициента из массива

extern double K2Take(int DistrictIndex,int LocationIndex);//Функция для поиска нужного коэффициента из массива

extern double K3Take(int MaterialIndex,int WetIndex);//Функция для поиска нужного коэффициента из массива

extern double LinearInterpolationForPipesPosTemp (std::map <const std::pair<int,int>,const int> TableSp, double EnterDn, double EnterTInside, int LocBox);

extern double LinearInterpolationForPipesNegTemp (std::map <const std::pair<int,int>,const int> TableSp, double EnterDn, double EnterTInside, int LocBox);

extern double GetR (std::map<const std::pair<int, int>, const double> RTable, double EnterDn, double EnterTInside);

extern int acceptedDiz(double CalculatedDIz);



#endif // FUNCTIONS_H
