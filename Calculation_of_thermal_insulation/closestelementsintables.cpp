#include "closestelementsintables.h"


        //Значение DN и t меньше ключа
    std::pair<double,double> ClosestElementsInTables::ClosestLowerDNLowerTEnterKey(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const int>::iterator it;
        Lower.first=0;
        Lower.second=0;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }


    //Значение t меньше ключа, DN больше
    std::pair<double,double> ClosestElementsInTables::ClosestLowerTBiggerDNEnterKey(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){
        std::map<const std::pair<int,int>,const int>::iterator it;
        Lower.first=1500;
        Lower.second=0;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (EnterKey.first<=it->first.first && it->first.first<=Lower.first){
                Lower.first=it->first.first;
            }

            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }

    //Значение DN меньше ключа, t больше
    std::pair<double,double> ClosestElementsInTables::ClosestBiggerTSmallerDNEnterKey(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){
        std::map<const std::pair<int,int>,const int>::iterator it;
        Lower.first=0;
        Lower.second=600;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (EnterKey.second<=it->first.second && it->first.second<=Lower.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }



    //Для нахождения меньшего значения по температуре 0 в таблицах 6,7
    std::pair<double,double> ClosestElementsInTables::ClosestSmallerDNEnterKeyIn_6_7Tables(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const int>::iterator it;
        Lower.first=0;
        Lower.second=0;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }




    std::pair<double,double> ClosestElementsInTables::BiggerTandSmallerDNInTables6_7(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){
        std::map<const std::pair<int,int>,const int>::iterator it;
        Lower.first=0;
        Lower.second=-999999;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }

    std::pair<double,double> ClosestElementsInTables::BiggerTandBiggerDNInTables6_7(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){
        std::map<const std::pair<int,int>,const int>::iterator it;
        Lower.first=600;
        Lower.second=-999999;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (EnterKey.first<=it->first.first && it->first.first<=Lower.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }



    //Нахождение экстраполяции >большее значение
    double ClosestElementsInTables::FindExtrapolationForPositiveByT(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const int>::iterator it;
        double FirstT=0;
        double SecondT=0;
        double TableDn=0;
        double x1;
        double y1;
        double x2;
        double y2;
        double x11;
        double x13;
        double x21;
        double x23;
        double y11;
        double y13;
        double y21;
        double y23;


        std::pair<double,double> PairXY11;
        std::pair<double,double> PairXY13;
        std::pair<double,double> PairXY21;
        std::pair<double,double> PairXY23;
        //Для поиска температуры в таблицах для эсктраполяции по температуре
        if (EnterKey.second<=600){
            for (it=TableSp.begin(); it!=TableSp.end();it++){

                if (it->first.second<EnterKey.second && it->first.second!=EnterKey.second && it->first.second>=FirstT){
                    FirstT=it->first.second;
                }

            }
            //Условие для нахождения значения больше чем таргет
            for (it=TableSp.begin(); it!=TableSp.end();it++){

                if (it->first.second>EnterKey.second && it->first.second!=EnterKey.second && it->first.second<=SecondT){
                    SecondT=it->first.second;
                }

            }
        }
        else{
            FirstT=550;
            SecondT=600;
        }

        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (it->first.first==EnterKey.first){
                TableDn=it->first.first;
            }

        }
        // Экстраполяция где DN табличный
        if (TableDn!=0){
            auto itxy1=TableSp.find(std::make_pair(TableDn, FirstT));
            auto itxy2=TableSp.find(std::make_pair(TableDn, SecondT));

            if (itxy1 != TableSp.end() && itxy2 != TableSp.end()) {
                x1=FirstT;
                y1=itxy1->second;
                x2=SecondT;
                y2=itxy2->second;
                y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                return y;
            }
        }

        if (TableDn==0 && EnterKey.first>=15){
            auto itXY2123=TableSp.lower_bound(std::make_pair(EnterKey.first,FirstT));
            PairXY21.first=itXY2123->first.first;
            PairXY23.first=itXY2123->first.first;

            for (it=TableSp.begin(); it!=TableSp.end();it++){
                //Проверить
                if (PairXY11.first<=it->first.first && it->first.first<=EnterKey.first){
                    PairXY11.first=it->first.first;
                    PairXY13.first=it->first.first;
                }

            }
            PairXY11.second=FirstT;
            PairXY21.second=FirstT;
            PairXY13.second=SecondT;
            PairXY23.second=SecondT;

            auto itxy11=TableSp.find(PairXY11);
            auto itxy13=TableSp.find(PairXY13);
            auto itxy21=TableSp.find(PairXY21);
            auto itxy23=TableSp.find(PairXY23);

            x11=itxy11->first.first;
            y11=itxy11->second;
            x21=itxy21->first.first;
            y21=itxy21->second;

            y1=y11+((EnterKey.first-x11)*(y21-y11)/(x21-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x13=itxy13->first.first;
            y13=itxy13->second;
            x23=itxy23->first.first;
            y23=itxy23->second;

            y2=y13+((EnterKey.first-x13)*(y23-y13)/(x23-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x1=FirstT;
            x2=SecondT;
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            return y;
        }

        if (TableDn==0 && EnterKey.first<15){
            auto itXY1121=TableSp.lower_bound(std::make_pair(EnterKey.first,FirstT));

            /* Везде экстраполяция
             xy1     xy2    y
             xy11   xy21
             xy13   xy23
            */
            PairXY11.first=itXY1121->first.first;
            PairXY21.first=itXY1121->first.first;
            auto itXY1323=TableSp.lower_bound(std::make_pair(PairXY11.first+1,FirstT));
            PairXY13.first=itXY1323->first.first;
            PairXY23.first=itXY1323->first.first;


            PairXY11.second=FirstT;
            PairXY21.second=SecondT;
            PairXY13.second=FirstT;
            PairXY23.second=SecondT;

            auto itxy11=TableSp.find(PairXY11);
            auto itxy13=TableSp.find(PairXY13);
            auto itxy21=TableSp.find(PairXY21);
            auto itxy23=TableSp.find(PairXY23);



            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy13->first.first;
            y13=itxy13->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));


            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy23->first.first;
            y23=itxy23->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            return y;
        }
        return 0;
    }


    double ClosestElementsInTables::FindExtrapolationForNegativeByT(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const int>::iterator it;
        double FirstT=0;
        double SecondT=-9999999999;
        double TableDn=0;
        double x1;
        double y1;
        double x2;
        double y2;
        double x11;
        double x13;
        double x21;
        double x23;
        double y11;
        double y13;
        double y21;
        double y23;


        std::pair<double,double> PairXY11;
        std::pair<double,double> PairXY13;
        std::pair<double,double> PairXY21;
        std::pair<double,double> PairXY23;
        //Для поиска температуры в таблицах для эсктраполяции по температуре
        if (EnterKey.second>=-180){
            for (it=TableSp.begin(); it!=TableSp.end();it++){
                if (it->first.second>EnterKey.second && it->first.second!=EnterKey.second && it->first.second<=FirstT){
                    FirstT=it->first.second;
                }

            }
            //Условие для нахождения значения больше чем таргет
            for (it=TableSp.begin(); it!=TableSp.end();it++){
                if (it->first.second<EnterKey.second && it->first.second!=EnterKey.second && it->first.second>=SecondT){
                    SecondT=it->first.second;
                }

            }
        }
        else{
            FirstT=-160;
            SecondT=-180;
        }

        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (it->first.first==EnterKey.first){
                TableDn=it->first.first;
            }

        }
        // Экстраполяция где DN табличный
        if (TableDn!=0){
            auto itxy1=TableSp.find(std::make_pair(TableDn, FirstT));
            auto itxy2=TableSp.find(std::make_pair(TableDn, SecondT));

            if (itxy1 != TableSp.end() && itxy2 != TableSp.end()) {
                x1=FirstT;
                y1=itxy1->second;
                x2=SecondT;
                y2=itxy2->second;
                y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                return y;
            }
        }

        if (TableDn==0 && EnterKey.first>=20){
            auto itXY2123=TableSp.lower_bound(std::make_pair(EnterKey.first,FirstT));
            PairXY21.first=itXY2123->first.first;
            PairXY23.first=itXY2123->first.first;

            for (it=TableSp.begin(); it!=TableSp.end();it++){
                //Проверить
                if (PairXY11.first<=it->first.first && it->first.first<=EnterKey.first){
                    PairXY11.first=it->first.first;
                    PairXY13.first=it->first.first;
                }

            }
            PairXY11.second=FirstT;
            PairXY21.second=FirstT;
            PairXY13.second=SecondT;
            PairXY23.second=SecondT;

            auto itxy11=TableSp.find(PairXY11);
            auto itxy13=TableSp.find(PairXY13);
            auto itxy21=TableSp.find(PairXY21);
            auto itxy23=TableSp.find(PairXY23);

            x11=itxy11->first.first;
            y11=itxy11->second;
            x21=itxy21->first.first;
            y21=itxy21->second;

            y1=y11+((EnterKey.first-x11)*(y21-y11)/(x21-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x13=itxy13->first.first;
            y13=itxy13->second;
            x23=itxy23->first.first;
            y23=itxy23->second;

            y2=y13+((EnterKey.first-x13)*(y23-y13)/(x23-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x1=FirstT;
            x2=SecondT;
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            return y;
        }

        if (TableDn==0 && EnterKey.first<20){
            auto itXY1121=TableSp.lower_bound(std::make_pair(EnterKey.first,FirstT));

            /* Везде экстраполяция
             xy1     xy2    y
             xy11   xy21
             xy13   xy23
            */
            PairXY11.first=itXY1121->first.first;
            PairXY21.first=itXY1121->first.first;
            auto itXY1323=TableSp.lower_bound(std::make_pair(PairXY11.first+1,FirstT));
            PairXY13.first=itXY1323->first.first;
            PairXY23.first=itXY1323->first.first;


            PairXY11.second=FirstT;
            PairXY21.second=SecondT;
            PairXY13.second=FirstT;
            PairXY23.second=SecondT;

            auto itxy11=TableSp.find(PairXY11);
            auto itxy13=TableSp.find(PairXY13);
            auto itxy21=TableSp.find(PairXY21);
            auto itxy23=TableSp.find(PairXY23);



            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy13->first.first;
            y13=itxy13->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));


            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy23->first.first;
            y23=itxy23->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            return y;
        }
        return 0;
    }

    //Для DN<15 2,3,4,5 таблицы
    double ClosestElementsInTables::FindExtrapolationForPositiveTTableOrNot(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const int>::iterator it;
        double FirstT=0;
        double SecondT=9999999999;
        double TargetT=0;
        double TableDn=0;
        double x1;
        double y1;
        double x2;
        double y2;
        double x11;
        double x13;
        double x21;
        double x23;
        double y11;
        double y13;
        double y21;
        double y23;





        std::pair<double,double> PairXY11;
        std::pair<double,double> PairXY13;
        std::pair<double,double> PairXY21;
        std::pair<double,double> PairXY23;


        //Для поиска температуры в таблицах для эсктраполяции по температуре
        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (EnterKey.second==it->first.second){
                TargetT=it->first.second;
            }

        }


        if (EnterKey.second==TargetT){
            auto itXYa1=TableSp.lower_bound(std::make_pair(EnterKey.first,TargetT));
            auto itXY1=TableSp.lower_bound(std::make_pair(itXYa1->first.first,TargetT));
            auto itXYa2=TableSp.lower_bound(std::make_pair(itXYa1->first.first+1,TargetT));
            auto itXY2=TableSp.lower_bound(std::make_pair(itXYa2->first.first,TargetT));


            x1=itXY1->first.first;
            x2=itXY2->first.first;
            y1=itXY1->second;
            y2=itXY2->second;
            y=y1+((EnterKey.first-x1)/(x2-x1)*(y2-y1));
            return y;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
        }

        //Условие для нахождения значения меньше чем таргет
        if (EnterKey.second<=600){
            for (it=TableSp.begin(); it!=TableSp.end();it++){

                if (it->first.second<EnterKey.second && it->first.second!=EnterKey.second && it->first.second>=FirstT){
                    FirstT=it->first.second;
                }

            }
            //Условие для нахождения значения больше чем таргет
            for (it=TableSp.begin(); it!=TableSp.end();it++){

                if (it->first.second>EnterKey.second && it->first.second!=EnterKey.second && it->first.second<=SecondT){
                    SecondT=it->first.second;
                }

            }
        }
        else{
            FirstT=550;
            SecondT=600;
        }

        if (EnterKey.first<15){
            auto itxy11=TableSp.find(std::make_pair(15,FirstT));
            auto itxy12=TableSp.find(std::make_pair(20,FirstT));
            auto itxy21=TableSp.find(std::make_pair(15,SecondT));
            auto itxy22=TableSp.find(std::make_pair(20,SecondT));

            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy12->first.first;
            y13=itxy12->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));

            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy22->first.first;
            y23=itxy22->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            y=y1+((EnterKey.second-x1)*(y2-y1)/(x2-x1));
            return y;
        }


        return 0;
    }



    double ClosestElementsInTables::FindExtrapolationForNegativeTTableOrNot(std::map <const std::pair<int,int>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const int>::iterator it;
        double FirstT=0;
        double SecondT=-9999999999;
        double TargetT=0;
        double TableDn=0;
        double x1;
        double y1;
        double x2;
        double y2;
        double x11;
        double x13;
        double x21;
        double x23;
        double y11;
        double y13;
        double y21;
        double y23;





        std::pair<double,double> PairXY11;
        std::pair<double,double> PairXY13;
        std::pair<double,double> PairXY21;
        std::pair<double,double> PairXY23;


        //Для поиска температуры в таблицах для эсктраполяции по температуре
        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (EnterKey.second==it->first.second){
                TargetT=it->first.second;
            }

        }


        if (EnterKey.second==TargetT){
            auto itXYa1=TableSp.lower_bound(std::make_pair(EnterKey.first,TargetT));
            auto itXY1=TableSp.lower_bound(std::make_pair(itXYa1->first.first,TargetT));
            auto itXYa2=TableSp.lower_bound(std::make_pair(itXYa1->first.first+1,TargetT));
            auto itXY2=TableSp.lower_bound(std::make_pair(itXYa2->first.first,TargetT));


            x1=itXY1->first.first;
            x2=itXY2->first.first;
            y1=itXY1->second;
            y2=itXY2->second;
            y=y1+((EnterKey.first-x1)/(x2-x1)*(y2-y1));
            return y;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
        }

        //Условие для нахождения значения меньше чем таргет
        if (EnterKey.second>=-180){
            for (it=TableSp.begin(); it!=TableSp.end();it++){
                if (it->first.second>EnterKey.second && it->first.second!=EnterKey.second && it->first.second<=FirstT){
                    FirstT=it->first.second;
                }

            }
            //Условие для нахождения значения больше чем таргет
            for (it=TableSp.begin(); it!=TableSp.end();it++){
                if (it->first.second<EnterKey.second && it->first.second!=EnterKey.second && it->first.second>=SecondT){
                    SecondT=it->first.second;
                }

            }
        }
        else{
            FirstT=-160;
            SecondT=-180;
        }

        if (EnterKey.first<20){
            auto itxy11=TableSp.find(std::make_pair(20,FirstT));
            auto itxy12=TableSp.find(std::make_pair(25,FirstT));
            auto itxy21=TableSp.find(std::make_pair(20,SecondT));
            auto itxy22=TableSp.find(std::make_pair(25,SecondT));

            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy12->first.first;
            y13=itxy12->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));

            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy22->first.first;
            y23=itxy22->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            y=y1+((EnterKey.second-x1)*(y2-y1)/(x2-x1));
            return y;
        }


        return 0;
    }


    //const double для R
    double ClosestElementsInTables::FindExtrapolationR(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey){    // Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const double>::iterator it;
        double FirstT=0;
        double SecondT=9999999999;
        double TargetT=0;
        double TableDn=0;
        double x1;
        double y1;
        double x2;
        double y2;
        double x11;
        double x13;
        double x21;
        double x23;
        double y11;
        double y13;
        double y21;
        double y23;


        std::pair<double,double> PairXY11;
        std::pair<double,double> PairXY13;
        std::pair<double,double> PairXY21;
        std::pair<double,double> PairXY23;
        //Для поиска температуры в таблицах для эсктраполяции по температуре
        if (EnterKey.second<=500){
            for (it=TableSp.begin(); it!=TableSp.end();it++){

                if (it->first.second<EnterKey.second && it->first.second!=EnterKey.second && it->first.second>=FirstT){
                    FirstT=it->first.second;
                }

            }
            //Условие для нахождения значения больше чем таргет
            for (it=TableSp.begin(); it!=TableSp.end();it++){

                if (it->first.second>EnterKey.second && it->first.second!=EnterKey.second && it->first.second<=SecondT){
                    SecondT=it->first.second;
                }

            }

        }

        else{


            FirstT=300;
            SecondT=500;
        }

        // Экстраполяция где DN табличный
        if (TableDn!=0 && EnterKey.second>500){
            auto itxy1=TableSp.find(std::make_pair(TableDn, FirstT));
            auto itxy2=TableSp.find(std::make_pair(TableDn, SecondT));

            if (itxy1 != TableSp.end() && itxy2 != TableSp.end()) {
                x1=FirstT;
                y1=itxy1->second;
                x2=SecondT;
                y2=itxy2->second;
                y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));//Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)

                return y;
            }
        }

        if (TableDn==0 && EnterKey.first>=32 && EnterKey.first<=2000 && EnterKey.second>500){
            auto itXY2123=TableSp.lower_bound(std::make_pair(EnterKey.first,FirstT));
            PairXY21.first=itXY2123->first.first;
            PairXY23.first=itXY2123->first.first;

            for (it=TableSp.begin(); it!=TableSp.end();it++){
                //Проверить
                if (PairXY11.first<=it->first.first && it->first.first<=EnterKey.first){
                    PairXY11.first=it->first.first;
                    PairXY13.first=it->first.first;
                }

            }
            PairXY11.second=FirstT;
            PairXY21.second=FirstT;
            PairXY13.second=SecondT;
            PairXY23.second=SecondT;

            auto itxy11=TableSp.find(PairXY11);
            auto itxy13=TableSp.find(PairXY13);
            auto itxy21=TableSp.find(PairXY21);
            auto itxy23=TableSp.find(PairXY23);

            x11=itxy11->first.first;
            y11=itxy11->second;
            x21=itxy21->first.first;
            y21=itxy21->second;

            y1=y11+((EnterKey.first-x11)*(y21-y11)/(x21-x11));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x13=itxy13->first.first;
            y13=itxy13->second;
            x23=itxy23->first.first;
            y23=itxy23->second;

            y2=y13+((EnterKey.first-x13)*(y23-y13)/(x23-x13));//Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)


            x1=FirstT;
            x2=SecondT;
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            return y;
        }



        if (TableDn==0 && EnterKey.first<32 && EnterKey.second>500){
            auto itXY1=TableSp.lower_bound(std::make_pair(EnterKey.first,FirstT));
            auto itXY1121=TableSp.lower_bound(std::make_pair(itXY1->first.first,FirstT));
            /* Везде экстраполяция
                 xy1     xy2    y
                 xy11   xy21
                 xy13   xy23
                */
            PairXY11.first=itXY1121->first.first;
            PairXY21.first=itXY1121->first.first;
            auto itXY2=TableSp.lower_bound(std::make_pair(PairXY11.first+1,FirstT));
            auto itXY1323=TableSp.lower_bound(std::make_pair(itXY2->first.first,FirstT));
            PairXY13.first=itXY1323->first.first;
            PairXY23.first=itXY1323->first.first;


            PairXY11.second=FirstT;
            PairXY21.second=SecondT;
            PairXY13.second=FirstT;
            PairXY23.second=SecondT;

            auto itxy11=TableSp.find(PairXY11);
            auto itxy13=TableSp.find(PairXY13);
            auto itxy21=TableSp.find(PairXY21);
            auto itxy23=TableSp.find(PairXY23);



            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy13->first.first;
            y13=itxy13->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));


            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy23->first.first;
            y23=itxy23->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            return y;
        }




        if (TableDn==0 && EnterKey.first>2000 && EnterKey.second>500){
            auto itxy11=TableSp.find(std::make_pair(1000,FirstT));
            auto itxy12=TableSp.find(std::make_pair(2000,FirstT));
            auto itxy21=TableSp.find(std::make_pair(1000,SecondT));
            auto itxy22=TableSp.find(std::make_pair(2000,SecondT));

            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy12->first.first;
            y13=itxy12->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));

            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy22->first.first;
            y23=itxy22->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            return y;
        }

        //Для поиска температуры в таблицах для эсктраполяции по температуре
        //Не готово
        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (EnterKey.second==it->first.second){
                TargetT=it->first.second;
            }

        }

        if (EnterKey.second==TargetT && EnterKey.first<32){
            auto itXYa1=TableSp.lower_bound(std::make_pair(EnterKey.first,TargetT));
            auto itXY1=TableSp.lower_bound(std::make_pair(itXYa1->first.first,TargetT));
            auto itXYa2=TableSp.lower_bound(std::make_pair(itXYa1->first.first+1,TargetT));
            auto itXY2=TableSp.lower_bound(std::make_pair(itXYa2->first.first,TargetT));


            x1=itXY1->first.first;
            x2=itXY2->first.first;
            y1=itXY1->second;
            y2=itXY2->second;
            y=y1+((EnterKey.first-x1)/(x2-x1)*(y2-y1));
            return y;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
        }

        if (EnterKey.second==TargetT && EnterKey.first>2000){
            auto itXY1=TableSp.lower_bound(std::make_pair(1000,TargetT));
            auto itXY2=TableSp.lower_bound(std::make_pair(2000,TargetT));


            x1=itXY1->first.first;
            x2=itXY2->first.first;
            y1=itXY1->second;
            y2=itXY2->second;
            y=y1+((EnterKey.first-x1)/(x2-x1)*(y2-y1));
            return y;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
        }

        //Условие для нахождения значения меньше чем таргет
        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (it->first.second<EnterKey.second && it->first.second!=EnterKey.second && it->first.second>=FirstT){
                FirstT=it->first.second;
            }

        }
        //Условие для нахождения значения больше чем таргет
        for (it=TableSp.begin(); it!=TableSp.end();it++){

            if (it->first.second>EnterKey.second && it->first.second!=EnterKey.second && it->first.second<=SecondT){
                SecondT=it->first.second;
            }

        }


        if (EnterKey.first<32 && EnterKey.second<500){
            auto itxy11=TableSp.find(std::make_pair(32,FirstT));
            auto itxy12=TableSp.find(std::make_pair(40,FirstT));
            auto itxy21=TableSp.find(std::make_pair(32,SecondT));
            auto itxy22=TableSp.find(std::make_pair(40,SecondT));

            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy12->first.first;
            y13=itxy12->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));

            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy22->first.first;
            y23=itxy22->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Interpolation (y) = y1 + [(x-x1) × (y2-y1)]/ (x2-x1)
            y=y1+((EnterKey.second-x1)*(y2-y1)/(x2-x1));
            return y;
        }


        //Не готово
        if (EnterKey.first>2000 && EnterKey.second<500){
            auto itxy11=TableSp.find(std::make_pair(1000,FirstT));
            auto itxy12=TableSp.find(std::make_pair(2000,FirstT));
            auto itxy21=TableSp.find(std::make_pair(1000,SecondT));
            auto itxy22=TableSp.find(std::make_pair(2000,SecondT));

            x11=itxy11->first.first;
            y11=itxy11->second;
            x13=itxy12->first.first;
            y13=itxy12->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y1=y11+((EnterKey.first-x11)/(x13-x11)*(y13-y11));

            x21=itxy21->first.first;
            y21=itxy21->second;
            x23=itxy22->first.first;
            y23=itxy22->second;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y2=y21+((EnterKey.first-x21)/(x23-x21)*(y23-y21));


            x1=FirstT;
            x2=SecondT;
            //Linear Extrapolation y=y1+((x-x1)/(x2-x1))*(y2-y1)
            y=y1+((EnterKey.second-x1)/(x2-x1)*(y2-y1));
            return y;
        }
        return 0;
    }
    //Const double
    //Значение DN и t меньше ключа
    std::pair<double,double> ClosestElementsInTables::ClosestLowerDNLowerTEnterKey(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,int>,const double>::iterator it;
        Lower.first=0;
        Lower.second=0;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }


    //Значение t меньше ключа, DN больше
    std::pair<double,double> ClosestElementsInTables::ClosestLowerTBiggerDNEnterKey(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey){
        std::map<const std::pair<int,int>,const double>::iterator it;
        Lower.first=1500;
        Lower.second=0;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (EnterKey.first<=it->first.first && it->first.first<=Lower.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }

    //Значение DN меньше ключа, t больше
    std::pair<double,double> ClosestElementsInTables::ClosestBiggerTSmallerDNEnterKey(std::map <const std::pair<int,int>,const double> TableSp, std::pair<double,double> EnterKey){
        std::map<const std::pair<int,int>,const double>::iterator it;
        Lower.first=0;
        Lower.second=600;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (EnterKey.second<=it->first.second && it->first.second<=Lower.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }



    //Для нахождения меньшего значения по температуре 0 в таблицах 6,7
    std::pair<double,double> ClosestElementsInTables::ClosestSmallerDNEnterKeyIn_6_7Tables(std::map <const std::pair<int,double>,const int> TableSp, std::pair<double,double> EnterKey){// Поиск значения меньше заданного, применимо только в 2 случаях
        std::map<const std::pair<int,double>,const int>::iterator it;
        Lower.first=0;
        Lower.second=0;
        for (it=TableSp.begin(); it!=TableSp.end();it++){
            if (Lower.first<=it->first.first && it->first.first<=EnterKey.first){
                Lower.first=it->first.first;
            }
            if (Lower.second<=it->first.second && it->first.second<=EnterKey.second){
                Lower.second=it->first.second;
            }
        }
        return Lower;
    }



