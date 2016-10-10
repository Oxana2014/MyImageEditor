#ifndef USERMENU_H
#define USERMENU_H

#include "camerawrapper.h"
#include "slideshow.h"

#include <vector>
#include <cstddef>

#include <QWidget>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class QPushButton;
class QSlider;

class UserMenu : public QWidget
{
    Q_OBJECT

public:
    UserMenu(QWidget *parent = 0);
    ~UserMenu();

private:
    void createWidgets();

    QPushButton* loadButton;
    QPushButton* photoButton;
    QPushButton* grayButton;
    QPushButton* RGBButton;
    QPushButton* borderButton;
    QPushButton* textButton;
    QPushButton* prevButton;
    QPushButton* nextButton;
    QPushButton* firstButton;
    QPushButton* lastButton;
    QPushButton* smoozeButton;
    QPushButton* sharpenButton;
    QPushButton* resizeButton;
    QPushButton* edgesButton;
    QPushButton* saveButton;
    QPushButton* slideShowButton;

    QSlider* contrastSlider;
    QSlider* brightnessSlider;

    QPushButton* fixContrastBrightness;

    Mat contrastImage;

    int contrast;
    int maxContrast;
    int brightness;
    int maxBrightness;

    size_t MatContainerMaxSize;
    size_t currPos;
    vector<Mat> MatContainer;//контейнер для хранения матриц используемых изображений

private slots:
    void slotLoad(); //загрузить изображение
    void slotPhoto(); //сделать фото штатной камерой
    void slotGray(); //сделать изображение черно-белым
    void slotRGB(); //получить RGB - разложение
    void slotBorder(); //добавить рамку
    void slotText(); //добавить текст
    void slotPrev(); //загрузить предыдущую матрицу
    void slotNext(); //загрузить следующую матрицу
    void slotFirst(); //загрузить первую матрицу
    void slotLast(); //загрузить последнюю матрицу
    void slotSmooze(); // сглаживание, удаление шумов
    void slotSharpen(); // увеличить резкость
    void slotResize(); //изменить размер
    void slotEdges(); //показать контуры
    void slotSave(); //сохранить в файл
    void slotContrast(int); //регулировка контраста
    void slotBrightness(int); //регулировка яркости
    void slotFixContrBright(); //зафиксировать матрицу с полученными регулировками контраста и яркости
    void slotSlideShow(); //слайд - шоу
};


#endif // USERMENU_H

