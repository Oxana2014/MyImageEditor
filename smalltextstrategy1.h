//Класс для реализации конкретной стратегии в паттерне Стратегия -
// для вставки с маленького однострочного текста.
//Представляет собой интерфейс для получения необходимых параметров вставки и текста
//и алгоритм вставки маленького текста

#ifndef SMALLTEXTSTRATEGY1_H
#define SMALLTEXTSTRATEGY1_H

#include "textstrategy1.h"

#include <string>

#include <QWidget>
#include <QSlider>
#include <QLineEdit>
#include <QString>
#include <QPushButton>
#include <QColor>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

const string OCVwindName = "Adding text to image";
const int kFonts = 8; //amount of OpenCV fonts

class SmallTextStrategy1 : public QWidget, public TextStrategy1 {

    Q_OBJECT

public:
    SmallTextStrategy1( Mat img, QWidget* parent = 0);
    ~SmallTextStrategy1();



private:
    const string windowName;
    Mat image, textImage;
    Point org; //точка начала вставки текста
    int fontType;
    double fontScale;
    int fontThickness;
    QString leQStr;
    unsigned int red;
    unsigned int green;
    unsigned int blue;

    QSlider* ySlider;
    QSlider* xSlider;
    QSlider* fontSlider;
    QSlider* scaleSlider;
    QSlider* thickSlider;
    QLineEdit* le;

    QPushButton* colorButton;
    QPushButton* saveButton;

    void createWidgets();
    void addTextonImage(); //конкретная стратегия вставки маленького текста

private slots:
    void slotY(int val);
    void slotX(int val);
    void slotFont(int val); //выбор типа шрифта
    void slotScale(int val); //выбор масштаба шрифта
    void slotThick(int val);
    void slotLE(); //line edit
    void slotColor();
    void slotSave();

};

#endif // SMALLTEXTSTRATEGY1_H

