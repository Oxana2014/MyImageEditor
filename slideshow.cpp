#include "slideshow.h"

#include <QDebug>
#include <QString>
#include <QStringList>


using namespace std;
using namespace cv;

SlideShow::SlideShow(QString dir) : workDir(dir), dirPath(dir) {
    qDebug() << "constructor SlideShow";
    QStringList filters;
    filters << "*.img" <<"*.IMG" << "*.jpg" << "*.JPG" << "*.png" <<  "*.PNG";
    workDir.setNameFilters(filters);

    //Создаем агрегатор
    QStringList* imageFiles = new QStringList(workDir.entryList());
    qDebug() << "QStringList: " << *imageFiles;
    if(!(*imageFiles).empty()) {
        namedWindow("Slide Show");
        moveWindow("Slide Show",50, 200);

        //Создаем итератор
        QStringList::const_iterator constIterator;
        for(constIterator = (*imageFiles).begin(); constIterator != (*imageFiles).end(); constIterator++) {
            QString imagePath = dirPath + "/" + (*constIterator);
            qDebug() << "imagePath: " << imagePath;

            //Используем созданный итератор
            Mat image = imread(imagePath.toStdString(), 1);
            imshow("Slide Show", image);
            waitKey(1000);
        }
        destroyWindow("Slide Show");
    }
    delete imageFiles;
}

SlideShow::~SlideShow() {

}
