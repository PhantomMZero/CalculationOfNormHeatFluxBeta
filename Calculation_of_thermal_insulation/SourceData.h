#ifndef SOURCEDATA_H
#define SOURCEDATA_H
#include <map>

extern const double KCoefficientConstruct [6][4]; //Коэффициент района строительства


extern const double KCoefficientExtraLoss [6]; //Коэффициент дополнительных потерь


extern const int aCoefficient [2][5]; //Коэффициент альфа, коэффициент теплоотдачи


extern const double KCoefficientWetting [3][3]; //Коэффициент увлажнения


extern const std::map<const std::pair<int,int>,const int> Table2Sp;    /*Инициализация Таблицы 2 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это плотность теплового потока
    нормы плотности теплового потока оборудования и трубопроводов с
    положительными температурами при расположении на открытом воздухе и
    числе часов работы более 5000*/

extern const std::map<const std::pair<int,int>,const int> Table3Sp;    /*Инициализация Таблицы 3 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это плотность теплового потока
    Нормы плотности теплового потока оборудования и трубопроводов с
    положительными температурами при расположении на открытом воздухе и
    числе часов работы 5000 и менее*/



extern const std::map<const std::pair<int,int>,const int> Table4Sp;    /*Инициализация Таблицы 4 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это плотность теплового потока
    Нормы плотности теплового потока оборудования и трубопроводов с
    положительными температурами при расположении в помещении и
    числе часов работы более 5000*/



extern const std::map<const std::pair<int,int>,const int> Table5Sp;    /*Инициализация Таблицы 5 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это плотность теплового потока
    Нормы плотности теплового потока оборудования и трубопроводов с
    положительными температурами при расположении в помещении и
    числе часов работы 5000 и менее*/



extern const std::map<const std::pair<int,int>,const int> Table6Sp;    /*Инициализация Таблицы 6 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это плотность теплового потока
    Нормы плотности теплового потока оборудования и трубопроводов с
    отрицательными температурами при расположении на открытом воздухе*/




extern const std::map<const std::pair<int,int>,const int> Table7Sp;    /*Инициализация Таблицы 7 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это плотность теплового потока
    Нормы плотности теплового потока оборудования и трубопроводов с
    отрицательными температурами при расположении в помещении*/


extern const std::map<const std::pair<int,int>,const double> RInsideLowCoef;    /*Инициализация Таблицы В3 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это RнL
    Внутри помещения для малых коэффициентов излучения*/



extern const std::map<const std::pair<int,int>,const double> RInsideHighCoef;    /*Инициализация Таблицы В3 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это RнL
    Внутри помещения для высоких коэффициентов излучения*/



extern const std::map<const std::pair<int,int>,const double> ROutside;    /*Инициализация Таблицы В3 из СП pair отвечает за DN(первый эл)
    и за температуру(Второй эл) int это RнL
    На открытом воздухе*/

#endif // SOURCEDATA_H
