//применение паттерна Декоратор:
//CameraWrapper - Wrapper, OpenCV Window - Component without any buttons.


#ifndef CAMERAWRAPPER_H
#define CAMERAWRAPPER_H

#include <QWidget>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class CameraWrapper : public QWidget {
    Q_OBJECT

public:
    CameraWrapper(QWidget* parent);
    ~CameraWrapper();

private:
    Mat frame;

private slots:
    void initCamera(); //включить камеру
    void saveCameraView(); //сохранить показываемое с камеры в данный момент изображение в файл

};

#endif // CAMERAWRAPPER_H

