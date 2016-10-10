#include "smalltextstrategy1.h"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QColorDialog>

QString name = QString("Albert Einstein");
SmallTextStrategy1::SmallTextStrategy1(Mat img, QWidget* parent)
    : QWidget(parent), windowName(OCVwindName), image(img), org(Point(0,img.rows/2)), fontType(0), fontScale(1),
      fontThickness(3), leQStr(name), red(0), green(0), blue(0) {
    qDebug() << "SmallTextStrategy1 constructor";


    setGeometry(600, 300, 700, 400);
    setWindowTitle("Adding Small Text");

    createWidgets();

    connect(ySlider, &QSlider::valueChanged, this, &SmallTextStrategy1::slotY);
    connect(xSlider, &QSlider::valueChanged, this, &SmallTextStrategy1::slotX);
    connect(fontSlider, &QSlider::valueChanged, this, &SmallTextStrategy1::slotFont);
    connect(scaleSlider, &QSlider::valueChanged, this, &SmallTextStrategy1::slotScale);
    connect(thickSlider, &QSlider::valueChanged, this, &SmallTextStrategy1::slotThick);
    connect(le, &QLineEdit::textChanged, this, &SmallTextStrategy1::slotLE);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(slotColor()), Qt::UniqueConnection);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(slotSave()), Qt::UniqueConnection);

    show();

    //Create window opencv
    namedWindow(windowName, WINDOW_AUTOSIZE | CV_GUI_NORMAL | CV_WINDOW_KEEPRATIO);

    //move window to position and resize
    moveWindow(windowName, 50, 185);

    imshow(windowName, image);
}

SmallTextStrategy1::~SmallTextStrategy1() {
    destroyWindow(windowName);
}


void SmallTextStrategy1::createWidgets() {
    qDebug() << "createWidgets function";
    QGridLayout* textLayout = new QGridLayout;
    setLayout(textLayout);

    ySlider = new QSlider(Qt::Vertical, this);
    xSlider = new QSlider(Qt::Horizontal, this);
    fontSlider = new QSlider(Qt::Horizontal, this);
    scaleSlider = new QSlider(Qt::Horizontal, this);
    thickSlider = new QSlider(Qt::Horizontal, this);

    ySlider->setMinimum(0);
    ySlider->setMaximum(image.rows);
    xSlider->setMinimum(0);
    xSlider->setMaximum(image.cols);
    ySlider->setValue(image.rows/2);
    fontSlider->setMinimum(0);
    fontSlider->setMaximum(kFonts - 1); //кол-во шрифтов от 0 до kFonts-1
    scaleSlider->setMinimum(0);
    scaleSlider->setMaximum(50);
    scaleSlider->setValue(10);
    thickSlider->setMinimum(1);
    thickSlider->setMaximum(10);
    thickSlider->setValue(3);

    QLabel* yLabel = new QLabel("Y");
    QLabel* xLabel = new QLabel("X - coordinate");
    QLabel* fontLabel = new QLabel("Font type");
    QLabel* scaleLabel = new QLabel("Font Scale");
    QLabel* thickLabel = new QLabel("Thickness");

    le = new QLineEdit(this);
    le->setText(name);

    colorButton = new QPushButton("Color");
    saveButton = new QPushButton("Save");

    textLayout->addWidget(ySlider, 0, 0, 5, 1);
    textLayout->addWidget(xSlider, 0, 1, 1, 5);
    textLayout->addWidget(yLabel, 5, 0, 1, 1);
    textLayout->addWidget(xLabel, 1, 2, 1, 4);
    textLayout->addWidget(fontSlider, 2, 1, 1, 5);
    textLayout->addWidget(fontLabel, 3, 2, 1, 3);
    textLayout->addWidget(scaleSlider, 4, 1, 1, 5);
    textLayout->addWidget(scaleLabel, 5, 2, 1, 3);
    textLayout->addWidget(thickSlider, 6, 1, 1, 5);
    textLayout->addWidget(thickLabel, 7, 2, 1, 3);
    textLayout->addWidget(le, 0, 6, 1, 2);
    textLayout->addWidget(colorButton, 2, 6, 1, 2);
    textLayout->addWidget(saveButton, 4, 6, 1, 2);
}

void SmallTextStrategy1::slotY(int val) {
    org.y = ySlider->maximum() - val;
    qDebug() << "org.y: " << org.y;
    addTextonImage();
}

void SmallTextStrategy1::slotX(int val) {
    org.x = val;
    qDebug() << "org.x: " << org.x;
    addTextonImage();
}

void SmallTextStrategy1::slotFont(int val) {
    fontType = val;
    qDebug() << "fontType: " << fontType;
    addTextonImage();
}

void SmallTextStrategy1::slotScale(int val) {
    fontScale = val * 0.1;
    qDebug() << "font Scale: " << fontScale;
    addTextonImage();
}

void SmallTextStrategy1::slotThick(int val) {
    fontThickness = val;
    qDebug() << "font thickness: " << fontThickness;
    addTextonImage();
}

void SmallTextStrategy1::slotLE() {
    leQStr = le->text();
    qDebug() << "leQStr: " << leQStr;
    addTextonImage();
}

void SmallTextStrategy1::slotColor() {
    QColor askColor = QColorDialog::getColor(Qt::green, this, "Select color");
    if (askColor.isValid()) {
        qDebug() << "color.name(): " << askColor.name();
        red = askColor.red();
        green = askColor.green();
        blue = askColor.blue();
        qDebug() << red << green << blue;
        addTextonImage();
    }
    else
        qDebug() << "Color is not valid";

}

void SmallTextStrategy1::slotSave() {

    imwrite("Images/textImage.jpg", textImage);

}

void SmallTextStrategy1::addTextonImage() {
    textImage = image.clone();
    putText(textImage, leQStr.toStdString(), org, fontType, fontScale, Scalar(blue, green, red), fontThickness);
    imshow(windowName, textImage);
}
