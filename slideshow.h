//Применение паттерна Итератор для итерации по каталогу
//и подачи файлов с изображениями на загрузку в рабочее окно OpenCV.

#ifndef SLIDESHOW_H
#define SLIDESHOW_H

#include <QString>
#include <QDir>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;


class SlideShow {
public:
    SlideShow(QString dir);
    ~SlideShow();

private:
    QDir workDir;
    QString dirPath;
};

#endif // SLIDESHOW_H

