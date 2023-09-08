#include "Functions.h"
#include "SourceData.h"
#include "closestelementsintables.h"
#include <math.h>



double DIzulN1ForSurface(double LambdaIz,double tOutside,double tInside, double KCoefficient, int qCoefficient, double RCoefficient){//Переделать Ккоэф
    return LambdaIz*((KCoefficient*(tInside-tOutside)*qCoefficient)-RCoefficient);
}

double BForPipelinesFormula(double LambdaIz,double tOutside,double tInside, double KCoefficient, double qCoefficient, double RCoefficient){ //Переделать Ккоэф

    if(KCoefficient!=0 && qCoefficient!=0 && RCoefficient!=0){
        double B=2*3.1416*LambdaIz*((KCoefficient*(tInside-tOutside))/qCoefficient-RCoefficient);//e^2*3.1416*LambdaIz*((KCoefficient*(tInside-tOutside))/qCoefficient-RCoefficient)
    return B;
    }
    else{
    return 0;
    }
}


double DIzulN1ForPipelines(double B, double DiameterPipeline){ //Переделать Ккоэф
    return (DiameterPipeline*(exp(B)-1)/2);
}


double K1Take(int NTypeofPillars, double DN){
    double KCoef=0;
    switch (NTypeofPillars){

    case 0:
        KCoef=KCoefficientExtraLoss[0];
        break;

    case 1:
        if (DN<150){
        KCoef=KCoefficientExtraLoss[1];
        break;
        }
        else{
        KCoef=KCoefficientExtraLoss[2];
        break;
        }

    case 3:
        KCoef=KCoefficientExtraLoss[3];
        break;

    case 4:
        KCoef=KCoefficientExtraLoss[4];
        break;

    case 5:
        KCoef=KCoefficientExtraLoss[5];
        break;
    default:
        break;
    }
    return KCoef;
}


double K2Take(int DistrictIndex,int LocationIndex){
    return KCoefficientConstruct [DistrictIndex][LocationIndex];
}

double K3Take(int MaterialIndex,int WetIndex){
    if (MaterialIndex!=0&&WetIndex!=0){
    return KCoefficientWetting [MaterialIndex-1][WetIndex-1];
    }
    else return 0;
}




//Только для труб, для таблиц 2,3,4,5
//Условия с часами работы в normheatfluxdensity
double LinearInterpolationForPipesPosTemp (std::map <const std::pair<int,int>,const int> TableSp, double EnterDn, double EnterTInside, int LocBox){
    if (EnterDn>1400){
    EnterDn=1500; //Костыль для тех кто больше 1400
    }

    auto it = TableSp.find(std::make_pair(EnterDn, EnterTInside));
    //Нахождение табличного значения
    if (it != TableSp.end()) {
    return it->second;
    }

    //Нахождение значения через линейную интерполяцию, где EnterDn>=15&&EnterDn<=1400&&EnterTInside>=20&&EnterTInside<=600
    if(EnterDn>=15&&EnterDn<=1400&&EnterTInside>=20&&EnterTInside<=600){
    auto itlb=TableSp.lower_bound(std::make_pair(EnterDn, EnterTInside));
    std::pair<int,int> itlbpair=itlb->first;
    auto itlb2=TableSp.lower_bound(std::make_pair(itlbpair.first, EnterTInside));//Поиск точного значения, от найденного большего Dn


        //Интерполяция где DN табличный
        if (itlb2 != TableSp.end() && EnterDn==itlb2->first.first && EnterTInside!=itlb2->first.second){
        double x2=itlb2->first.second;
        double y2=itlb2->second;

        ClosestElementsInTables ForDnTable;
        auto itless=TableSp.find(ForDnTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

        double x1=itless->first.second;
        double y1=itless->second;
        double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
        return y;
        }


        //Интерполяция где t табличная
        if (itlb2 != TableSp.end() && EnterTInside==itlb2->first.second && EnterDn!=itlb2->first.first){
        double x2=itlb2->first.first;
        double y2=itlb2->second;

        ClosestElementsInTables ForTTable;

        auto itless=TableSp.find(ForTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

        double x1=itless->first.first;
        double y1=itless->second;
        double y=y1+((EnterDn-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
        return y;
        }


        //Интерполяция где нет табличных значений, Сначала интерполируем по DN, потом по температуре
        if (itlb2 != TableSp.end() && EnterDn!=itlb2->first.first  && EnterTInside!=itlb2->first.second){


        ClosestElementsInTables ForNoDnTTable;
        auto itDN1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, EnterTInside)));
        auto itDN2=TableSp.find(ForNoDnTTable.ClosestLowerTBiggerDNEnterKey(TableSp,std::make_pair(EnterDn, EnterTInside)));
        auto itT1=TableSp.find(ForNoDnTTable.ClosestBiggerTSmallerDNEnterKey(TableSp,std::make_pair(EnterDn, EnterTInside)));
        auto itT2=itlb2;

            if (itDN1 != TableSp.end() && itDN2 != TableSp.end() && itT1 != TableSp.end() && itT2 != TableSp.end()){

            /*Найти интерполяцию
            y11             y13
            y21     y22     y23
            y31             y33
                найти y22
    */

            double x11=itDN1->first.first;
            double y11=itDN1->second;
            double x31=itDN2->first.first;
            double y31=itDN2->second;


            double y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            double x13=itT1->first.first;
            double y13=itT1->second;
            double x33=itT2->first.first;
            double y33=itT2->second;


            double y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            double x21=itDN1->first.second;
            double x23=itT2->first.second;
            double y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));

            return y22;
            }
        }
    }


    //Интерполяция где DN > 1400
    if(EnterDn>1400&&EnterTInside>=20&&EnterTInside<=600){

        auto itlb=TableSp.lower_bound(std::make_pair(EnterDn, EnterTInside));

        if (itlb != TableSp.end() && EnterDn==itlb->first.first && EnterTInside!=itlb->first.second){
        double x2=itlb->first.second;
        double y2=itlb->second;

        ClosestElementsInTables ForDnTable;
        auto itless=TableSp.find(ForDnTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

        double x1=itless->first.second;
        double y1=itless->second;
        double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
        return y;
        }

    }

    //Интерполяция где 0<t<20, Открытый воздух, для 2,3 таблиц
    //Изза хардкода страдает оптимизация, но времени мало
    if (EnterTInside>0 && EnterTInside<20 && (TableSp==Table2Sp || TableSp==Table3Sp)){

    std::map <const std::pair<int,int>,const int> TableSpMinus;

        if (LocBox==0){//Условие для выбора таблицы с отрицательными температурами
        TableSpMinus=Table6Sp;
        }
        else {
        TableSpMinus=Table7Sp;
        }

    auto itlb=TableSp.lower_bound(std::make_pair(EnterDn, EnterTInside));
    std::pair<int,int> itlbpair=itlb->first;
    auto itlb2=TableSp.lower_bound(std::make_pair(itlbpair.first, EnterTInside));//Нахождение элемента больше чем ключ



    auto itlbminus=TableSpMinus.lower_bound(std::make_pair(EnterDn, 0));
    std::pair<int,int> itlbminuspair=itlbminus->first;
    auto itlbminus2=TableSpMinus.lower_bound(std::make_pair(itlbminuspair.first, 0));
    //Нахождение элемента больше чем ключ

        if (EnterDn>500){
        itlbminuspair.first=600;
        itlbminuspair.second=0;
        itlbminus2=TableSpMinus.find(itlbminuspair);
        }

        //Интерполяция где DN совпадает с таблицами
        if (itlb2 != TableSp.end() && itlbminus2!=TableSpMinus.end() && EnterDn == itlb2->first.first && (EnterDn==itlbminus2->first.first||itlbminus2->first.first==600)){
        double x2=itlb2->first.second;
        double y2=itlb2->second;
        double x1=itlbminus2->first.second;
        double y1=itlbminus2->second;
        double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
        return y;
        }


//          Конструкция добавлена в If
//        ClosestElementsInTables ForNoDnTTable;
//        auto itDN1=TableSpMinus.find(ForNoDnTTable.ClosestSmallerDNEnterKeyIn_6_7Tables(TableSpMinus,std::make_pair(EnterDn, 0)));
//        auto itT1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, 20)));



        //Интерполяция где DN не совпадает с таблицами или частично совпадает, DN>20
        if (itlb2 != TableSp.end() && (EnterDn != itlb2->first.first || EnterDn != itlbminus2->first.first) && EnterDn>20){

        ClosestElementsInTables ForNoDnTTable;
        auto itDN1=TableSpMinus.find(ForNoDnTTable.ClosestSmallerDNEnterKeyIn_6_7Tables(TableSpMinus,std::make_pair(EnterDn, 0)));
        auto itT1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, 20)));

        double y11;
        double y21;
        double y31;
        double y13;
        double y23;
        double y33;
        double y22;
        double x11;
        double x21;
        double x31;
        double x13;
        double x23;
        double x33;


        /*Найти интерполяцию
        y11(itDN1)             y13(itT1)
        y21             y22    y23
        y31(itlbminus2)        y33 (itlb2)
                    найти y22
        */


        if (EnterDn==itlbminus2->first.first||EnterDn>500){
                y21=itlbminus2->second; //Только для DN>20
                x13=itT1->first.first;
                y13=itT1->second;
                x33=itlb2->first.first;
                y33=itlb2->second;


                y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                x21=itlbminus2->first.second;
                x23=itlb2->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }



        if (EnterDn==itlb2->first.first){
                y23=itlb2->second; //Только для DN>20
                x11=itDN1->first.first;
                y11=itDN1->second;
                x31=itlbminus2->first.first;
                y31=itlbminus2->second;


                y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                x21=itlbminus2->first.second;
                x23=itlb2->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }



        x11=itDN1->first.first;
        y11=itDN1->second;
        x31=itlbminus2->first.first;
        y31=itlbminus2->second;


        y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


        x13=itT1->first.first;
        y13=itT1->second;
        x33=itlb2->first.first;
        y33=itlb2->second;


        y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


        x21=itlbminus2->first.second;
        x23=itlb2->first.second;
        y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));

        return y22;

        }

        //Интерполяция и экстраполяция где DN не совпадает с таблицами или частично совпадает, DN<20
        if (itlb2 != TableSp.end() && (EnterDn != itlb2->first.first || EnterDn != itlbminus2->first.first) && EnterDn<20){

            double y11;
            double y21;
            double y31;
            double y13;
            double y23;
            double y33;
            double y22;
            double x11;
            double x21;
            double x31;
            double x13;
            double x23;
            double x33;




            /*Найти интерполяцию
            y11(itDN1)             y13(itT1)
            y21             y22    y23
            y31(itlbminus2)        y33 (itlb2)
                        найти y22
            */

                if (EnterDn>=15){//Случай если Dn==15 или больше 15

                ClosestElementsInTables ForNoDnTTable;
                auto itDN1=TableSpMinus.find(ForNoDnTTable.ClosestSmallerDNEnterKeyIn_6_7Tables(TableSpMinus,std::make_pair(EnterDn, 0)));
                auto itT1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, 20)));


                /*Найти интерполяцию и экстраполяцию
                Экстраполяция          Интерполяция
                y11(itDN1)             y13(itT1)
                y21             y22    y23
                y31(itlbminus2)        y33 (itlb2)
                            найти y22
                */

                if (EnterDn == itlb2->first.first && TableSpMinus == Table6Sp){


                y23=itlb2->second; //Только для DN>20


                x11=20;
                y11=3;
                x31=25;
                y31=3;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)


                x21=0;
                x23=itlb2->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
                return y22;
                }






            //Захардкодить экстраполяцию
                if(EnterDn>15 && TableSpMinus == Table6Sp){
                x13=itT1->first.first;
                y13=itT1->second;
                x33=itlb2->first.first;
                y33=itlb2->second;
                y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)

                x11=20;
                y11=3;
                x31=25;
                y31=3;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x21=0;
                x23=itlb->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;

                }



            }



            //Экстраполяция когда меньше 15
            if (EnterDn<15 && TableSp == Table2Sp && TableSpMinus == Table6Sp){

                x11=20;
                y11=3;
                x31=25;
                y31=3;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x13=15;
                y13=4;
                x33=20;
                y33=4;
                y23=y13+((EnterDn-x13)/(x33-x13)*(y33-y13));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x21=0;
                x23=20;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }

            if (EnterDn<15 && TableSp == Table3Sp && TableSpMinus == Table6Sp){

                x11=20;
                y11=3;
                x31=25;
                y31=3;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x13=15;
                y13=4;
                x33=20;
                y33=5;
                y23=y13+((EnterDn-x13)/(x33-x13)*(y33-y13));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x21=0;
                x23=20;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }



        }


    }



    //Интерполяция где 0<t<50, Помещение, для 4,5 таблиц
    //Изза хардкода страдает оптимизация, но времени мало
    if (EnterTInside>0 && EnterTInside<50 && (TableSp==Table4Sp || TableSp==Table5Sp)){

        std::map <const std::pair<int,int>,const int> TableSpMinus;

        if (LocBox==0){//Условие для выбора таблицы с отрицательными температурами
            TableSpMinus=Table6Sp;
        }
        else {
            TableSpMinus=Table7Sp;
        }

        auto itlb=TableSp.lower_bound(std::make_pair(EnterDn, EnterTInside));
        std::pair<int,int> itlbpair=itlb->first;
        auto itlb2=TableSp.lower_bound(std::make_pair(itlbpair.first, EnterTInside));//Нахождение элемента больше чем ключ



        auto itlbminus=TableSpMinus.lower_bound(std::make_pair(EnterDn, 0));
        std::pair<int,int> itlbminuspair=itlbminus->first;
        auto itlbminus2=TableSpMinus.lower_bound(std::make_pair(itlbminuspair.first, 0));
        //Нахождение элемента больше чем ключ

        if (EnterDn>500){
            itlbminuspair.first=600;
            itlbminuspair.second=0;
            itlbminus2=TableSpMinus.find(itlbminuspair);
        }

        //Интерполяция где DN совпадает с таблицами
        if (itlb2 != TableSp.end() && itlbminus2!=TableSpMinus.end() && EnterDn == itlb2->first.first && (EnterDn==itlbminus2->first.first||itlbminus2->first.first==600)){
            double x2=itlb2->first.second;
            double y2=itlb2->second;
            double x1=itlbminus2->first.second;
            double y1=itlbminus2->second;
            double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            return y;
        }


        //          Конструкция добавлена в If
        //        ClosestElementsInTables ForNoDnTTable;
        //        auto itDN1=TableSpMinus.find(ForNoDnTTable.ClosestSmallerDNEnterKeyIn_6_7Tables(TableSpMinus,std::make_pair(EnterDn, 0)));
        //        auto itT1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, 20)));



        //Интерполяция где DN не совпадает с таблицами или частично совпадает, DN>20
        if (itlb2 != TableSp.end() && (EnterDn != itlb2->first.first || EnterDn != itlbminus2->first.first) && EnterDn>20){

            ClosestElementsInTables ForNoDnTTable;
            auto itDN1=TableSpMinus.find(ForNoDnTTable.ClosestSmallerDNEnterKeyIn_6_7Tables(TableSpMinus,std::make_pair(EnterDn, 0)));
            auto itT1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, 50)));

            double y11;
            double y21;
            double y31;
            double y13;
            double y23;
            double y33;
            double y22;
            double x11;
            double x21;
            double x31;
            double x13;
            double x23;
            double x33;


            /*Найти интерполяцию
        y11(itDN1)             y13(itT1)
        y21             y22    y23
        y31(itlbminus2)        y33 (itlb2)
                    найти y22
        */


            if (EnterDn==itlbminus2->first.first||EnterDn>500){
                y21=itlbminus2->second; //Только для DN>20
                x13=itT1->first.first;
                y13=itT1->second;
                x33=itlb2->first.first;
                y33=itlb2->second;


                y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                x21=itlbminus2->first.second;
                x23=itlb2->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }



            if (EnterDn==itlb2->first.first){
                y23=itlb2->second; //Только для DN>20
                x11=itDN1->first.first;
                y11=itDN1->second;
                x31=itlbminus2->first.first;
                y31=itlbminus2->second;


                y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                x21=itlbminus2->first.second;
                x23=itlb2->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }



            x11=itDN1->first.first;
            y11=itDN1->second;
            x31=itlbminus2->first.first;
            y31=itlbminus2->second;


            y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x13=itT1->first.first;
            y13=itT1->second;
            x33=itlb2->first.first;
            y33=itlb2->second;


            y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x21=itlbminus2->first.second;
            x23=itlb2->first.second;
            y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));

            return y22;

        }

        //Интерполяция и экстраполяция где DN не совпадает с таблицами или частично совпадает, DN<20
        if (itlb2 != TableSp.end() && (EnterDn != itlb2->first.first || EnterDn != itlbminus2->first.first) && EnterDn<20){

            double y11;
            double y21;
            double y31;
            double y13;
            double y23;
            double y33;
            double y22;
            double x11;
            double x21;
            double x31;
            double x13;
            double x23;
            double x33;




            /*Найти интерполяцию
            y11(itDN1)             y13(itT1)
            y21             y22    y23
            y31(itlbminus2)        y33 (itlb2)
                        найти y22
            */

            if (EnterDn>=15){//Случай если Dn==15 или больше 15

                ClosestElementsInTables ForNoDnTTable;
                auto itT1=TableSp.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(TableSp,std::make_pair(EnterDn, 50)));


                /*Найти интерполяцию и экстраполяцию
                Экстраполяция          Интерполяция
                y11(itDN1)             y13(itT1)
                y21             y22    y23
                y31(itlbminus2)        y33 (itlb2)
                            найти y22
                */



                if (EnterDn == itlb2->first.first && TableSpMinus == Table7Sp){


                y23=itlb2->second; //Только для DN>20


                x11=20;
                y11=5;
                x31=25;
                y31=6;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)


                x21=0;
                x23=itlb2->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
                return y22;
                }



                //Захардкодить экстраполяцию
                if(EnterDn>15 && TableSpMinus == Table7Sp){
                x13=itT1->first.first;
                y13=itT1->second;
                x33=itlb2->first.first;
                y33=itlb2->second;
                y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)

                x11=20;
                y11=5;
                x31=25;
                y31=6;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x21=0;
                x23=itlb->first.second;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
                }

            }



            if (EnterDn<15 && TableSp == Table4Sp && TableSpMinus == Table7Sp){

                x11=20;
                y11=5;
                x31=25;
                y31=6;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x13=15;
                y13=6;
                x33=20;
                y33=7;
                y23=y13+((EnterDn-x13)/(x33-x13)*(y33-y13));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x21=0;
                x23=50;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }




            if (EnterDn<15 && TableSp == Table5Sp && TableSpMinus == Table7Sp){

                x11=20;
                y11=5;
                x31=25;
                y31=6;
                y21=y11+((EnterDn-x11)/(x31-x11)*(y31-y11));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x13=15;
                y13=6;
                x33=20;
                y33=7;
                y23=y13+((EnterDn-x13)/(x33-x13)*(y33-y13));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                x21=0;
                x23=50;
                y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));
                return y22;
            }
        }
    }

    if(EnterDn<15 && EnterTInside>=20 && EnterTInside<=600 && (TableSp==Table2Sp||TableSp==Table3Sp)){
        ClosestElementsInTables ExtraPol;
        return ExtraPol.FindExtrapolationForPositiveTTableOrNot(TableSp,std::make_pair(EnterDn,EnterTInside));
    }

    if(EnterDn<15 && EnterTInside>=50 && EnterTInside<=600 && (TableSp==Table4Sp||TableSp==Table5Sp)){
        ClosestElementsInTables ExtraPol;
        return ExtraPol.FindExtrapolationForPositiveTTableOrNot(TableSp,std::make_pair(EnterDn,EnterTInside));
    }

    //Для таблиц 2,3,4,5 экстраполяция
    if(EnterTInside>600){

        //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
        ClosestElementsInTables ExtraPol;
        return ExtraPol.FindExtrapolationForPositiveByT(TableSp,std::make_pair(EnterDn,EnterTInside));

    }
    return 0;
};



double LinearInterpolationForPipesNegTemp (std::map <const std::pair<int,int>,const int> TableSp, double EnterDn, double EnterTInside, int LocBox){
    if (EnterDn>500){
        EnterDn=600; //Костыль для тех кто больше 500
    }

    auto it = TableSp.find(std::make_pair(EnterDn, EnterTInside));
    //Нахождение табличного значения
    if (it != TableSp.end()) {
        return it->second;
    }

    //Нахождение значения через линейную интерполяцию, где EnterDn>=20&&EnterDn<=500&&EnterTInside>=-180&&EnterTInside<=0
    if(EnterDn>=20&&EnterDn<=500&&EnterTInside>=-180&&EnterTInside<=0){
        auto itlb=TableSp.lower_bound(std::make_pair(EnterDn, EnterTInside));
        std::pair<int,int> itlbpair=itlb->first;
        auto itlb2=TableSp.lower_bound(std::make_pair(itlbpair.first, EnterTInside));//Поиск точного значения, от найденного большего Dn


        //Интерполяция где DN табличный
        if (itlb2 != TableSp.end() && EnterDn==itlb2->first.first && EnterTInside!=itlb2->first.second){
            double x2=itlb2->first.second;
            double y2=itlb2->second;
/*
            xy1(itlb2)      xy2(itless)
 */

            ClosestElementsInTables ForDnTable;
            auto itless=TableSp.find(ForDnTable.BiggerTandSmallerDNInTables6_7(TableSp,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

            double x1=itless->first.second;
            double y1=itless->second;
            double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            return y;
        }


        //Интерполяция где t табличная
        if (itlb2 != TableSp.end() && EnterTInside==itlb2->first.second && EnterDn!=itlb2->first.first){
            double x2=itlb2->first.first;
            double y2=itlb2->second;

            ClosestElementsInTables ForTTable;
/*
 *          xy1(itless)
 *
 *          y
 *
 *          xy2(itless)
 *
 */
            auto itless=TableSp.find(ForTTable.BiggerTandSmallerDNInTables6_7(TableSp,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

            double x1=itless->first.first;
            double y1=itless->second;
            double y=y1+((EnterDn-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            return y;
        }

        /*Найти интерполяцию
            y11(itxy11)             y13(itxy13)
            y21             y22     y23
            y31(itxy31)             y33 (itxy33)
                        найти y22
            */
        //Интерполяция где нет табличных значений, Сначала интерполируем по DN, потом по температуре
        if (itlb2 != TableSp.end() && EnterDn!=itlb2->first.first  && EnterTInside!=itlb2->first.second){


            ClosestElementsInTables ForNoDnTTable;
            //itdn1 переделать
            auto itxy11=TableSp.find(ForNoDnTTable.ClosestBiggerTSmallerDNEnterKey(TableSp,std::make_pair(EnterDn, EnterTInside)));
            //itDN2 переделать
            auto itxy31=itlb2;
            //оба дают меньше таргета
            auto itxy13=TableSp.find(ForNoDnTTable.BiggerTandSmallerDNInTables6_7(TableSp,std::make_pair(EnterDn, EnterTInside)));


            auto itxy33=TableSp.find(ForNoDnTTable.BiggerTandBiggerDNInTables6_7(TableSp,std::make_pair(EnterDn, EnterTInside)));

            if (itxy11 != TableSp.end() && itxy31 != TableSp.end() && itxy13 != TableSp.end() && itxy33 != TableSp.end()){

                /*Найти интерполяцию
            y11             y13
            y21     y22     y23
            y31             y33
                найти y22
    */

                double x11=itxy11->first.first;
                double y11=itxy11->second;
                double x31=itxy31->first.first;
                double y31=itxy31->second;


                double y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                double x13=itxy13->first.first;
                double y13=itxy13->second;
                double x33=itxy33->first.first;
                double y33=itxy33->second;


                double y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                double x21=itxy11->first.second;
                double x23=itxy13->first.second;
                double y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));

                return y22;
            }
        }
    }


    //Интерполяция где DN > 500
    if(EnterDn>500&&EnterTInside<=0&&EnterTInside>=-180){

        auto itlb=TableSp.lower_bound(std::make_pair(EnterDn, EnterTInside));

        if (itlb != TableSp.end() && EnterDn==itlb->first.first && EnterTInside!=itlb->first.second){
            double x2=itlb->first.second;
            double y2=itlb->second;

            ClosestElementsInTables ForDnTable;
            auto itless=TableSp.find(ForDnTable.BiggerTandSmallerDNInTables6_7(TableSp,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

            double x1=itless->first.second;
            double y1=itless->second;
            double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            return y;
        }

    }



    //Для таблиц 6,7 экстраполяция
    if(EnterDn<20 && EnterTInside<=0 && EnterTInside>=-180){
        ClosestElementsInTables ExtraPol;
        return ExtraPol.FindExtrapolationForNegativeTTableOrNot(TableSp,std::make_pair(EnterDn,EnterTInside));
    }



    //Для таблиц 6,7 экстраполяция
    if(EnterTInside<-180){

        //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
        ClosestElementsInTables ExtraPol;
        return ExtraPol.FindExtrapolationForNegativeByT(TableSp,std::make_pair(EnterDn,EnterTInside));

    }
    return 0;
}



//Функция получения R
double GetR (std::map <const std::pair<int,int>,const double> RTable, double EnterDn, double EnterTInside){
   if (EnterTInside<100){
        EnterTInside=100;
    }


    auto it = RTable.find(std::make_pair(EnterDn, EnterTInside));
    //Нахождение табличного значения
    if (it != RTable.end()) {
        return it->second;
    }

    //Нахождение значения через линейную интерполяцию
    if(EnterDn>=32&&EnterDn<=2000&&EnterTInside<=500){
        auto itlb=RTable.lower_bound(std::make_pair(EnterDn, EnterTInside));
        std::pair<int,int> itlbpair=itlb->first;
        auto itlb2=RTable.lower_bound(std::make_pair(itlbpair.first, EnterTInside));//Поиск точного значения, от найденного большего Dn


        //Интерполяция где DN табличный
        if (itlb2 != RTable.end() && EnterDn==itlb2->first.first && EnterTInside!=itlb2->first.second){
            double x2=itlb2->first.second;
            double y2=itlb2->second;

            ClosestElementsInTables ForDnTable;
            auto itless=RTable.find(ForDnTable.ClosestLowerDNLowerTEnterKey(RTable,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

            double x1=itless->first.second;
            double y1=itless->second;
            double y=y1+((EnterTInside-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            return y;
        }


        //Интерполяция где t табличная
        if (itlb2 != RTable.end() && EnterTInside==itlb2->first.second && EnterDn!=itlb2->first.first){
            double x2=itlb2->first.first;
            double y2=itlb2->second;

            ClosestElementsInTables ForTTable;

            auto itless=RTable.find(ForTTable.ClosestLowerDNLowerTEnterKey(RTable,std::make_pair(EnterDn,EnterTInside)));//Поиск значения меньше чем заданные

            double x1=itless->first.first;
            double y1=itless->second;
            double y=y1+((EnterDn-x1)*(y2-y1)/(x2-x1)); //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            return y;
        }


        //Интерполяция где нет табличных значений, Сначала интерполируем по DN, потом по температуре
        if (itlb2 != RTable.end() && EnterDn!=itlb2->first.first  && EnterTInside!=itlb2->first.second){


            ClosestElementsInTables ForNoDnTTable;
            auto itDN1=RTable.find(ForNoDnTTable.ClosestLowerDNLowerTEnterKey(RTable,std::make_pair(EnterDn, EnterTInside)));
            auto itDN2=RTable.find(ForNoDnTTable.ClosestLowerTBiggerDNEnterKey(RTable,std::make_pair(EnterDn, EnterTInside)));
            auto itT1=RTable.find(ForNoDnTTable.ClosestBiggerTSmallerDNEnterKey(RTable,std::make_pair(EnterDn, EnterTInside)));
            auto itT2=itlb2;

            if (itDN1 != RTable.end() && itDN2 != RTable.end() && itT1 != RTable.end() && itT2 != RTable.end()){

                /*Найти интерполяцию
            y11             y13
            y21     y22     y23
            y31             y33
                найти y22
    */

                double x11=itDN1->first.first;
                double y11=itDN1->second;
                double x31=itDN2->first.first;
                double y31=itDN2->second;


                double y21=y11+((EnterDn-x11)*(y31-y11)/(x31-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                double x13=itT1->first.first;
                double y13=itT1->second;
                double x33=itT2->first.first;
                double y33=itT2->second;


                double y23=y13+((EnterDn-x13)*(y33-y13)/(x33-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


                double x21=itDN1->first.second;
                double x23=itT2->first.second;
                double y22=y21+((EnterTInside-x21)*(y23-y21)/(x23-x21));

                return y22;
            }
        }
    }



        //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
    ClosestElementsInTables ExtraPol;
    return ExtraPol.FindExtrapolationR(RTable,std::make_pair(EnterDn,EnterTInside));
}



int acceptedDiz(double CalculatedDIz){

    double x=0;
    int y=0;

    if (CalculatedDIz>0 && CalculatedDIz<=20){
    return 20;
    }

    if (CalculatedDIz>20){
    x = CalculatedDIz + 0.5 - (CalculatedDIz<0);
    y = (int)x;
    if (y % 10 <= 3) {
            return (y/10)*10;
        }
    if (y % 10 >3){
            return ((y/10)*10)+10;
        }
    }

    return 0;

}



