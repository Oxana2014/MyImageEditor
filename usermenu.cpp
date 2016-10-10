#include "usermenu.h"
#include "textstrategy1.h"
#include "smalltextstrategy1.h"
#include "largetextstrategy2.h"

#include <string>

#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QDir>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QColor>
#include <QColorDialog>
#include <QSlider>
#include <QLabel>
#include <QMouseEvent>

using namespace cv;


UserMenu::UserMenu(QWidget *parent)
    : QWidget(parent), contrast(0), maxContrast(200), brightness(0), maxBrightness(50)
    , MatContainerMaxSize(20), currPos(0){

    setGeometry(0, 0, 1300, 50);

    setWindowTitle("Menu");
    createWidgets();

    connect(loadButton, SIGNAL(clicked()), this, SLOT(slotLoad()), Qt::UniqueConnection);
    connect(photoButton, SIGNAL(clicked()), this, SLOT(slotPhoto()), Qt::UniqueConnection);
    connect(grayButton, SIGNAL(clicked()), this, SLOT(slotGray()), Qt::UniqueConnection);
    connect(RGBButton, SIGNAL(clicked()), this, SLOT(slotRGB()), Qt::UniqueConnection);
    connect(borderButton, SIGNAL(clicked()), this, SLOT(slotBorder()), Qt::UniqueConnection);
    connect(textButton, SIGNAL(clicked()), this, SLOT(slotText()), Qt::UniqueConnection);
    connect(prevButton, SIGNAL(clicked()), this, SLOT(slotPrev()), Qt::UniqueConnection);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(slotNext()), Qt::UniqueConnection);
    connect(firstButton, SIGNAL(clicked()), this, SLOT(slotFirst()), Qt::UniqueConnection);
    connect(lastButton, SIGNAL(clicked()), this, SLOT(slotLast()), Qt::UniqueConnection);
    connect(smoozeButton, SIGNAL(clicked()), this, SLOT(slotSmooze()), Qt::UniqueConnection);
    connect(sharpenButton, SIGNAL(clicked()), this, SLOT(slotSharpen()), Qt::UniqueConnection);
    connect(resizeButton, SIGNAL(clicked()), this, SLOT(slotResize()), Qt::UniqueConnection);
    connect(edgesButton, SIGNAL(clicked()), this, SLOT(slotEdges()), Qt::UniqueConnection);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(slotSave()), Qt::UniqueConnection);
    connect(contrastSlider, &QSlider::valueChanged, this, &UserMenu::slotContrast);
    connect(brightnessSlider, &QSlider::valueChanged, this, &UserMenu::slotBrightness);
    connect(fixContrastBrightness, SIGNAL(clicked()), this, SLOT(slotFixContrBright()), Qt::UniqueConnection);
    connect(slideShowButton, SIGNAL(clicked()), this, SLOT(slotSlideShow()), Qt::UniqueConnection);


    //Create window opencv
    namedWindow("MyImageEditor", WINDOW_AUTOSIZE | CV_GUI_NORMAL | CV_WINDOW_KEEPRATIO);

    //move window to position and resize
    moveWindow("MyImageEditor", 0, 185);


    //load the start image from file
    QDir currDir;
    QString path =  currDir.currentPath();
    qDebug() << "path: " << path;
    string spath = path.toStdString();
    Mat loadedImage1 = imread(spath + "/Images/start.jpg", IMREAD_COLOR);
    if (!loadedImage1.data)
        qDebug() << "Стартовое изображение не загружено";
    else {
        MatContainer.push_back(loadedImage1);
        currPos = MatContainer.size() - 1;
        imshow("MyImageEditor",MatContainer[currPos]);
    }

}

UserMenu::~UserMenu() {
    destroyWindow("MyImageEditor");
}

void UserMenu::createWidgets() {

    qDebug() << "createWidgets function";
    QGridLayout* menuLayout = new QGridLayout;
    setLayout(menuLayout);

    loadButton = new QPushButton("Load");
    photoButton = new QPushButton("My photo");
    grayButton = new QPushButton("toGray");
    RGBButton = new QPushButton("toRGB");
    borderButton = new QPushButton("add Border");
    textButton = new QPushButton("add Text");
    prevButton = new QPushButton("prev");
    nextButton = new QPushButton("next");
    firstButton = new QPushButton("first");
    lastButton = new QPushButton("last");
    smoozeButton = new QPushButton("smooze");
    sharpenButton = new QPushButton("sharpen");
    resizeButton = new QPushButton("resize");
    edgesButton = new QPushButton("show edges");
    saveButton = new QPushButton("save");
    slideShowButton = new QPushButton("slide show");

    loadButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    photoButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    grayButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    RGBButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    borderButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    textButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    prevButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    nextButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    firstButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    lastButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    smoozeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sharpenButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    resizeButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    edgesButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    saveButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    slideShowButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    contrastSlider = new QSlider(Qt::Horizontal, this);
    brightnessSlider = new QSlider(Qt::Horizontal, this);

    contrastSlider->setMinimum(0);
    contrastSlider->setMaximum(maxContrast);
    brightnessSlider->setMinimum(0);
    brightnessSlider->setMaximum(maxBrightness);

    QLabel* contrastLabel = new QLabel("Contrast");
    QLabel* brightnessLabel = new QLabel("Brightness");

    fixContrastBrightness = new QPushButton("FixContrBright");
    fixContrastBrightness->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    menuLayout->addWidget(loadButton, 0, 0);
    menuLayout->addWidget(photoButton, 1, 0);
    menuLayout->addWidget(grayButton, 0, 1);
    menuLayout->addWidget(RGBButton, 1, 1);
    menuLayout->addWidget(borderButton, 0, 2);
    menuLayout->addWidget(textButton, 1, 2);
    menuLayout->addWidget(prevButton, 0, 3);
    menuLayout->addWidget(firstButton, 1, 3);
    menuLayout->addWidget(nextButton, 0, 4);
    menuLayout->addWidget(lastButton, 1, 4);
    menuLayout->addWidget(smoozeButton, 0, 5);
    menuLayout->addWidget(sharpenButton, 1, 5);
    menuLayout->addWidget(resizeButton, 0, 6);
    menuLayout->addWidget(edgesButton, 1, 6);
    menuLayout->addWidget(saveButton, 0, 7);
    menuLayout->addWidget(slideShowButton, 1, 7);
    menuLayout->addWidget(contrastSlider, 2, 0, 1, 4 );
    menuLayout->addWidget(brightnessSlider, 3, 0, 1, 4 );
    menuLayout->addWidget(contrastLabel, 2, 4);
    menuLayout->addWidget(brightnessLabel, 3, 4);
    menuLayout->addWidget(fixContrastBrightness, 2, 5, 2, 2);

qDebug() <<"End of createWidgets function";
}



void UserMenu::slotLoad(){
    qDebug() << "slotLoad";

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

        if (!fileName.isEmpty()) {
            qDebug() << fileName;
            string sFileName = fileName.toStdString();
            Mat loadedImage;
            loadedImage = imread(sFileName, 1);
            if (loadedImage.data) {
                while(MatContainer.size() > MatContainerMaxSize) {
                    MatContainer.erase(MatContainer.begin());
                }
                MatContainer.push_back(loadedImage);
                currPos = MatContainer.size()-1;

                imshow("MyImageEditor", MatContainer[currPos]);
            }
        }
        else
            qDebug() << "file is not found";

}


void UserMenu::slotPhoto(){
    qDebug() << "slotPhoto";

//Применение паттерна Декоратор в классе CameraWrapper.
    CameraWrapper* camObject = new CameraWrapper(0);
    camObject->show();

}

void UserMenu::slotGray(){
    qDebug() << "slotGray";
    Mat gray;
    cvtColor(MatContainer[currPos], gray, CV_BGR2GRAY);

    while(MatContainer.size() > MatContainerMaxSize) {
        MatContainer.erase(MatContainer.begin());
    }
    MatContainer.push_back(gray);
    currPos = MatContainer.size()-1;
    imshow("MyImageEditor", MatContainer[currPos]);
}

void UserMenu::slotRGB(){
    qDebug() << "slotRGB";

    const int channels = MatContainer[currPos].channels();
    switch (channels) {
    case 1:
        qDebug() << "Your image is grayscale\n";
        break;
    case 3:
        uchar nullTable[256];
        for (int i = 0; i < 256; i++)
            nullTable[i] = (uchar)0;
        Mat blue = MatContainer[currPos].clone();
        Mat red = MatContainer[currPos].clone();
        Mat green = MatContainer[currPos].clone();
        CV_Assert(blue.depth() == CV_8U);

        MatIterator_<Vec3b> it, end;
        for(it = blue.begin<Vec3b>(), end = blue.end<Vec3b>(); it != end; ++it) {
            (*it)[1] = nullTable[(*it)[1]];
            (*it)[2] = nullTable[(*it)[2]];
        }
        for(it = green.begin<Vec3b>(), end = green.end<Vec3b>(); it != end; ++it) {
            (*it)[0] = nullTable[(*it)[0]];
            (*it)[2] = nullTable[(*it)[2]];
        }
        for(it = red.begin<Vec3b>(), end = red.end<Vec3b>(); it != end; ++it) {
            (*it)[0] = nullTable[(*it)[0]];
            (*it)[1] = nullTable[(*it)[1]];
        }

        while(MatContainer.size() > MatContainerMaxSize) {
            MatContainer.erase(MatContainer.begin());
        }
        MatContainer.push_back(red);
        currPos = MatContainer.size()-1;
        imshow("MyImageEditor", MatContainer[currPos]);
        waitKey(1000);

        while(MatContainer.size() > MatContainerMaxSize) {
            MatContainer.erase(MatContainer.begin());
        }
        MatContainer.push_back(green);
        currPos = MatContainer.size()-1;
        imshow("MyImageEditor", MatContainer[currPos]);
        waitKey(1000);

        while(MatContainer.size() > MatContainerMaxSize) {
            MatContainer.erase(MatContainer.begin());
        }
        MatContainer.push_back(blue);
        currPos = MatContainer.size()-1;
        imshow("MyImageEditor", MatContainer[currPos]);
        waitKey(1000);

        break;

    }


}

void UserMenu::slotBorder(){
    qDebug() << "slotBorder";
    int bordertype;
    bool ok;
    Scalar value = Scalar(0, 0, 0);
        int btype = QInputDialog::getInt(this, tr("Выбор варианта рамки"),
                                     tr("Выберите: 0 для цветной рамки или 1 для реплики"), 0, 0, 1, 1, &ok);
        if (ok) {
            if (btype)
                bordertype = BORDER_REPLICATE;
            else {
                bordertype = BORDER_CONSTANT;
                QColor color =  QColorDialog::getColor(Qt::green, this, "Select Color");

                if (color.isValid()) {
                    qDebug() << "color.name(): " << color.name();
                value = Scalar(color.blue(), color.green(), color.red());
            }
        }

        Mat dst;
        int top, bottom, left1, right1;

        //Initialize arguments for the filter
        top = (int) (0.05 * MatContainer[currPos].rows);
        bottom = (int)(0.05 * MatContainer[currPos].rows);
        left1 = (int)(0.05 * MatContainer[currPos].cols);
        right1 = (int)(0.05 * MatContainer[currPos].cols);
        dst = MatContainer[currPos];

        copyMakeBorder(MatContainer[currPos], dst, top, bottom, left1, right1, bordertype, value);
        MatContainer.push_back(dst);
        currPos = MatContainer.size()-1;
        imshow("MyImageEditor", MatContainer[currPos]);
        }

        else
            qDebug() << "Вариант рамки не выбран";

}

void UserMenu::slotText(){
    qDebug() << "slotText";


//применение паттерна Стратегия - выбор конкретной стратегии в зависимости от размера  вставляемого текста.
    bool ok;
    int strategy = QInputDialog::getInt(this, tr("Выбор размера текста для вставки"),
                                 tr("Выберите: 0 для короткого текста или 1 для многострочного текста"), 0, 0, 1, 1, &ok);
    if (ok) {
        if (strategy) {
            TextStrategy1* textStrategy1 = new LargeTextStrategy2(MatContainer[currPos]);

        }
        else {
            TextStrategy1* textStrategy1 = new SmallTextStrategy1( MatContainer[currPos],0);

        }
    }

}

void UserMenu::slotPrev(){
    qDebug() << "slotPrev";
    if (currPos != 0) {
        --currPos;
        imshow("MyImageEditor", MatContainer[currPos]);
        qDebug() << "currPos : " << currPos << ", size: " << MatContainer.size();
        contrastSlider->setValue(0);
        brightnessSlider->setValue(0);
    }
    else {
        qDebug() << "Current image is the first\n";
    }
}

void UserMenu::slotNext(){
    qDebug() << "slotNext";
    if (currPos != MatContainer.size()-1)  {
        currPos++;
        imshow("MyImageEditor", MatContainer[currPos]);
        contrastSlider->setValue(0);
        brightnessSlider->setValue(0);
        qDebug() << "currPos : " << currPos << ", size: " << MatContainer.size();
    }
    else {
        qDebug() << "Current image is the last\n";
    }

}

void UserMenu::slotFirst(){
    qDebug() << "slotFirst";
    if(currPos != 0) {
        currPos = 0;
        imshow("MyImageEditor", MatContainer[currPos]);
        contrastSlider->setValue(0);
        brightnessSlider->setValue(0);
        qDebug() << "currPos : " << currPos << ", size: " << MatContainer.size();
    }
    else {
        qDebug() << "Current image is the first\n";
    }
}

void UserMenu::slotLast(){
    qDebug() << "slotLast";
    if (currPos != MatContainer.size()-1)  {
        currPos = MatContainer.size()-1;
        imshow("MyImageEditor", MatContainer[currPos]);
        contrastSlider->setValue(0);
        brightnessSlider->setValue(0);
        qDebug() << "currPos : " << currPos << ", size: " << MatContainer.size();
    }
    else {
        qDebug() << "Current image is the last\n";
    }
}

void UserMenu::slotSmooze(){
    qDebug() << "slotSmooze";
    Mat dst = MatContainer[currPos].clone();
    bilateralFilter(MatContainer[currPos], dst, 5, 160, 160);
    while(MatContainer.size() > MatContainerMaxSize) {
        MatContainer.erase(MatContainer.begin());
    }
    MatContainer.push_back(dst);
    currPos = MatContainer.size()-1;
    imshow("MyImageEditor", MatContainer[currPos]);
}

void UserMenu::slotSharpen(){
    qDebug() << "slotSharpen";
    Mat kern = (Mat_<char>(3, 3) << 0, -1, 0,
                                   -1, 5, -1,
                                    0, -1, 0);
    Mat resSharp;

    filter2D(MatContainer[currPos], resSharp, MatContainer[currPos].depth(), kern);

    while(MatContainer.size() > MatContainerMaxSize) {
        MatContainer.erase(MatContainer.begin());
    }
    MatContainer.push_back(resSharp);
    currPos = MatContainer.size()-1;
    imshow("MyImageEditor", MatContainer[currPos]);
}

void UserMenu::slotResize(){
    qDebug() << "slotResize";
    int userHeight = 0, newHeight;
    bool ok;

    int newWidth = QInputDialog::getInt(this, tr("Width"),tr("Изображение имеет ширину %1 пикселей и\n "
                                                                 "Высоту %2 пикселей.\n Выберите новую ширину: ")
                                        .arg(MatContainer[currPos].cols)
                                        .arg(MatContainer[currPos].rows)
                                        ,0, 0, 10000, 1, &ok);

    if (ok && newWidth) {
        userHeight = QInputDialog::getInt(this, tr("Height"),
                                                tr("По умолчанию новое изображение сохранит соотношение сторон.\n"
                                                   "Если вы хотите изменить соотношение,\n"
                                                   " Выберите новую высоту: "), 0, 0, 10000, 1, &ok);
        qDebug() << "Userheight: " << userHeight;
        if (ok) {
            if(!userHeight){
                qDebug() << "newwidth: " << newWidth;
                qDebug() << "MatContainer[currPos].cols: " << MatContainer[currPos].cols;
                qDebug() << "MatContainer[currPos].rows: " << MatContainer[currPos].rows;
                newHeight = static_cast <int> (newWidth * 1.0 / MatContainer[currPos].cols * MatContainer[currPos].rows);
                 qDebug() << "newHeight: " << newHeight;
            }
                else
                newHeight = userHeight;
        }
        else
            newHeight = static_cast <int> (newWidth * 1.0 / MatContainer[currPos].cols * MatContainer[currPos].rows);

        Mat res;
        cv::resize(MatContainer[currPos], res, Size(newWidth, newHeight));

        while(MatContainer.size() > MatContainerMaxSize) {
            MatContainer.erase(MatContainer.begin());
        }
        MatContainer.push_back(res);
        currPos = MatContainer.size()-1;

        QMessageBox::information(this, tr("Параметры нового изображения"), tr(" Ширина: %1 пикселей, Высота: %2 пикселей")
                                 .arg(MatContainer[currPos].cols)
                                 .arg(MatContainer[currPos].rows));

        imshow("MyImageEditor", MatContainer[currPos]);

    }


}

void UserMenu::slotEdges(){
    qDebug() << "slotEdges";

    Mat blur, gray, grad;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;

    //reduce noise
    GaussianBlur(MatContainer[currPos], blur, Size(3, 3), 0, 0, BORDER_DEFAULT);

    //convert to gray
    cvtColor(blur, gray, CV_BGR2GRAY);

    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    //Gradient X
    Sobel(gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_x, abs_grad_x);

    //Gradient Y
    Sobel(gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT);
    convertScaleAbs(grad_y, abs_grad_y);

    //Total gradient
    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    while(MatContainer.size() > MatContainerMaxSize) {
        MatContainer.erase(MatContainer.begin());
    }
    MatContainer.push_back(grad);
    currPos = MatContainer.size()-1;

    imshow("MyImageEditor", MatContainer[currPos]);

}

void UserMenu::slotSave(){
    static int counter = 0;
    qDebug() << "slotSave";
    counter++;

    QDir currDir;
    QString path =  currDir.currentPath();
    qDebug() << "path: " << path;
    string spath = path.toStdString();


    char fileToSave[512];
    sprintf(fileToSave, "/Images/Image%d.jpg", counter);

    imwrite(string(spath + fileToSave), MatContainer[currPos]);

    qDebug() << "Изображение сохранено в папку Images\n";
}

void UserMenu::slotSlideShow() {
    qDebug() << "slotSlideShow";
    QString dir = QFileDialog::getExistingDirectory(0, tr("\nВыберите каталог с изображениями для просмотра\n "),
                                                    "/home", QFileDialog::DontResolveSymlinks);
    qDebug() << "dir: " << dir;

//Применение паттерна Итератор в классе SlideShow.
    SlideShow* pShow = new SlideShow(dir);
    delete pShow;
}


void UserMenu::slotContrast(int val) {
    contrast = val;
    qDebug() << "contrast: " << contrast;
    contrastImage = Mat::zeros(MatContainer[currPos].size(), MatContainer[currPos].type());
    MatContainer[currPos].convertTo(contrastImage, -1, 1.0 * (contrast + 100)/100, brightness);

    imshow("MyImageEditor", contrastImage);
}

void UserMenu::slotBrightness(int val) {
    brightness = val;
    qDebug() << "brightness: " << brightness;
    contrastImage = Mat::zeros(MatContainer[currPos].size(), MatContainer[currPos].type());
    MatContainer[currPos].convertTo(contrastImage, -1, 1.0 * (contrast + 100)/100, brightness);

    imshow("MyImageEditor", contrastImage);
}

void UserMenu::slotFixContrBright() {
    qDebug() << "slotContrBright" ;
    imwrite("Images/contrBright.jpg", contrastImage);
    Mat temp;
    temp = imread("Images/contrBright.jpg", 1);
    while(MatContainer.size() > MatContainerMaxSize) {
        MatContainer.erase(MatContainer.begin());
    }
    MatContainer.push_back(temp);
    currPos = MatContainer.size()-1;
    imshow("MyImageEditor", MatContainer[currPos]);
    contrastSlider->setValue(0);
    brightnessSlider->setValue(0);
}
