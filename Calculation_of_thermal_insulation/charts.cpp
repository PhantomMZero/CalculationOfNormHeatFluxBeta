#include "charts.h"
#include "ui_charts.h"

//Была ошибка в UI соответственно в ui findlambda слева температура, справа ламбда
//В DataCharts first это лямбда, second это температура

Charts::Charts(std::map<double, double> DataForCharts, double tInside, double predictedLambda, QString Formula, int TypeOfCalc, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Charts)
{
    ui->setupUi(this);

    if (TypeOfCalc==0){
    QChart* chart=new QChart();
    QScatterSeries* series = new QScatterSeries();
    series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    series->setMarkerSize(15.0);


    QScatterSeries* predictedLSeries = new QScatterSeries();
    predictedLSeries->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    predictedLSeries->setMarkerSize(15.0);
    predictedLSeries->append(tInside, predictedLambda);

    DataForCharts.insert({predictedLambda, tInside});

    for (auto it=DataForCharts.begin();it!=DataForCharts.end();++it){
        series->append(it->second, it->first);
    }


    chart->setTitle(Formula);
    chart->addSeries(series);
    chart->addSeries(predictedLSeries);



    //Возможно весь чарт в условие закинуть

    QSplineSeries* ExponentTrendSeries = new QSplineSeries();


    ExponentialFitting EFit;


    //Добавление предсказуемой точки в линию тренда

    /*!!!!!!!!!!!!!! Для поиска меньшего значения в map!!!!!!!!!!!!!!*/

    typedef std::pair<double, double> mypairtype;
    struct comparesecond
    {
        bool operator()(const mypairtype& left, const mypairtype& right) const
        {
            return left.second < right.second;
        }
    };

    std::pair<double, double> min
        = *min_element(DataForCharts.begin(), DataForCharts.end(), comparesecond());


    /*-------------------------------------------------------------------------------*/


    std::map<double,double>::reverse_iterator rightit=DataForCharts.rbegin();
    double x=min.second;

    for ( ;x<=rightit->second; ){

        ExponentTrendSeries->append(x, EFit.predict(DataForCharts,x));
        x+=0.01;

    }

    //Удаление предсказуемой точки изи данных таблицы


    chart->addSeries(ExponentTrendSeries);

    chart->createDefaultAxes();
    double leftx=0;
    double rightx=rightit->second+5;
    chart->axes(Qt::Horizontal).first()->setRange(leftx, rightx);
    chart->axes(Qt::Vertical).first()->setRange(leftx, rightit->first+5);
    DataForCharts.erase(predictedLambda);


    chart->legend()->attachToChart();
//    QValueAxis* axisX = new QValueAxis;
//    double leftx=x-5;
//    double rightx=rightit->second+5;
//    axisX->setRange(leftx, rightx);
//    chart->addAxis(axisX, Qt::AlignBottom);
//    ExponentTrendSeries->attachAxis(axisX);
//    predictedLSeries->attachAxis(axisX);
//    series->attachAxis(axisX);



//    QValueAxis* axisY = new QValueAxis;
//    chart->addAxis(axisY, Qt::AlignLeft);
//    ExponentTrendSeries->attachAxis(axisY);
//    predictedLSeries->attachAxis(axisY);
//    series->attachAxis(axisY);


    QChartView* chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    ui->chartLayout->addWidget(chartView); // add the chart to the UI layout
    }

}

Charts::~Charts()
{
    delete ui;
}
