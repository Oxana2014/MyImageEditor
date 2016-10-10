#include "largetextstrategy2.h"

#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QColorDialog>
#include <QStringList>
#include <QChar>

QString quote = QString("Imagination\n is more important\n than knowledge");

LargeTextStrategy2::LargeTextStrategy2(Mat img, QWidget *parent)
    : QWidget(parent), windowName(OCVwindName2), image(img), org(Point(0,img.rows/2)), fontType(0), fontScale(1)
    , fontThickness(3), lineInterval(10), teQStr(quote), red(0), green(0), blue(0) {
    qDebug() << "Largetextstrategy constructor";

    setGeometry(600, 300, 700, 400);
    setWindowTitle("Adding Large Text");

    createWidgets();

    connect(ySlider, &QSlider::valueChanged, this, &LargeTextStrategy2::slotY);
    connect(xSlider, &QSlider::valueChanged, this, &LargeTextStrategy2::slotX);
    connect(fontSlider, &QSlider::valueChanged, this, &LargeTextStrategy2::slotFont);
    connect(scaleSlider, &QSlider::valueChanged, this, &LargeTextStrategy2::slotScale);
    connect(thickSlider, &QSlider::valueChanged, this, &LargeTextStrategy2::slotThick);
    connect(intervalSlider, &QSlider::valueChanged, this, &LargeTextStrategy2::slotInterval);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(slotColor()), Qt::UniqueConnection);
    connect(saveButton, SIGNAL(clicked()), this, SLOT(slotSave()), Qt::UniqueConnection);
    connect(te, &QTextEdit::textChanged, this, &LargeTextStrategy2::slotText);

    show();

    //Create window opencv
    namedWindow(windowName, WINDOW_AUTOSIZE | CV_GUI_NORMAL | CV_WINDOW_KEEPRATIO);

    //move window to position and resize
    moveWindow(windowName, 50, 185);

    imshow(windowName, image);
}

LargeTextStrategy2::~LargeTextStrategy2() {
    destroyWindow(windowName);
}

void LargeTextStrategy2::createWidgets() {
    qDebug() << "Largestrategy2 createWidgets function";
    QGridLayout* textLayout = new QGridLayout;
    setLayout(textLayout);

    ySlider = new QSlider(Qt::Vertical, this);
    xSlider = new QSlider(Qt::Horizontal, this);
    fontSlider = new QSlider(Qt::Horizontal, this);
    scaleSlider = new QSlider(Qt::Horizontal, this);
    thickSlider = new QSlider(Qt::Horizontal, this);
    intervalSlider = new QSlider(Qt::Horizontal, this);

    ySlider->setMinimum(0);
    ySlider->setMaximum(image.rows);
    xSlider->setMinimum(0);
    xSlider->setMaximum(image.cols);
    ySlider->setValue(image.rows/2);
    fontSlider->setMinimum(0);
    fontSlider->setMaximum(kFonts2 - 1); //кол-во шрифтов от 0 до kFonts-1.
    scaleSlider->setMinimum(0);
    scaleSlider->setMaximum(50);
    scaleSlider->setValue(10);
    thickSlider->setMinimum(1);
    thickSlider->setMaximum(10);
    thickSlider->setValue(3);
    intervalSlider->setMinimum(0);
    intervalSlider->setMaximum(100);
    intervalSlider->setValue(10);


    QLabel* yLabel = new QLabel("Y");
    QLabel* xLabel = new QLabel("X - coordinate");
    QLabel* fontLabel = new QLabel("Font type");
    QLabel* scaleLabel = new QLabel("Font Scale");
    QLabel* thickLabel = new QLabel("Thickness");
    QLabel* intervalLabel = new QLabel("Line Interval");

    te = new QTextEdit(this);
    te->setText(quote);

    colorButton  = new QPushButton("Color");
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
    textLayout->addWidget(intervalSlider, 8, 1, 1, 5);
    textLayout->addWidget(intervalLabel, 9, 2, 1, 3);
    textLayout->addWidget(te, 0, 6, 5, 2);
    textLayout->addWidget(colorButton, 6, 7, 1, 2);
    textLayout->addWidget(saveButton, 8, 7, 1, 2);
}

void LargeTextStrategy2::slotY(int val) {
    org.y = ySlider->maximum() - val;
    qDebug() << "org.y: " << org.y;
    addTextonImage();
}

void LargeTextStrategy2::slotX(int val) {
    org.x = val;
    qDebug() << "org.x: " << org.x;
    addTextonImage();
}

void LargeTextStrategy2::slotFont(int val) {
    fontType = val;
    qDebug() << "fontType: " << fontType;
    addTextonImage();
}

void LargeTextStrategy2::slotScale(int val) {
    fontScale = val * 0.1;
    qDebug() << "font Scale: " << fontScale;
    addTextonImage();
}

void LargeTextStrategy2::slotThick(int val) {
    fontThickness = val;
    qDebug() << "font thickness: " << fontThickness;
    addTextonImage();
}

void LargeTextStrategy2::slotInterval(int val) {
    lineInterval = val;
    qDebug() << "line Interval: " << lineInterval;
    addTextonImage();
}

void LargeTextStrategy2::slotText() {
    qDebug() << "slot text";
    teQStr = te->toPlainText();
    qDebug() << "teQStr: " << teQStr;
    addTextonImage();
}

void LargeTextStrategy2::slotColor() {
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

void LargeTextStrategy2::slotSave() {

    imwrite("Images/textImage.jpg", textImage);

}

void LargeTextStrategy2::addTextonImage() {
    qDebug() << "AddText in Large strategy";
    textImage = image.clone();


    if (!teQStr.isEmpty()) {
        QStringList* lineList = new QStringList();
        *lineList = teQStr.split(QChar('\n'));

        QStringList::const_iterator it = (*lineList).begin();
        for(int counter = 0; it != (*lineList).end(); it++, counter++) {
            qDebug() << *it;
            QString s = *it;
            putText(textImage, s.toStdString(), Point(org.x, org.y + counter * lineInterval)
                    , fontType, fontScale, Scalar(blue, green, red), fontThickness);
        }
    }
    imshow(windowName, textImage);
}
