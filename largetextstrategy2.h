//Класс для реализации конкретной стратегии в паттерне Стратегия -
// для вставки большого многострочного текста.
//Представляет собой интерфейс для получения необходимых параметров вставки и текста
//и алгоритм вставки многострочного текста

#ifndef LARGETEXTSTRATEGY2_H
#define LARGETEXTSTRATEGY2_H

#include "textstrategy1.h"

#include <QWidget>
#include <QSlider>
#include <QTextEdit>
#include <QPushButton>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

const string OCVwindName2 = "Adding large text to image";
const int kFonts2 = 8; // Amount of OpenCV fonts

class LargeTextStrategy2 : public QWidget, public TextStrategy1 {

    Q_OBJECT

public:
    LargeTextStrategy2(Mat img, QWidget* parent = 0);
    ~LargeTextStrategy2();

private:
    const string windowName;
    Mat image, textImage;
    Point org; //точка начала вставки текста
    int fontType;
    double fontScale;
    int fontThickness;
    int lineInterval;
    QString teQStr;
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    QSlider* ySlider;
    QSlider* xSlider;
    QSlider* fontSlider;
    QSlider* scaleSlider;
    QSlider* thickSlider;
    QSlider* intervalSlider;

    QTextEdit* te;

    QPushButton* colorButton;
    QPushButton* saveButton;

    void createWidgets();
    void addTextonImage(); //конкретная стратегия вставки многострочного текста

private slots:
    void slotY(int val);
    void slotX(int val);
    void slotFont(int val); //выбор типа шрифта
    void slotScale(int val); //выбор масштаба шрифта
    void slotThick(int val);
    void slotInterval(int val); //выбор межстрочного интервала
    void slotText();
    void slotColor();
    void slotSave();

};

#endif // LARGETEXTSTRATEGY2_H

