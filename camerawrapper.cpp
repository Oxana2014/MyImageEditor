#include "camerawrapper.h"

#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QDir>
#include <QLabel>

CameraWrapper::CameraWrapper(QWidget *parent) : QWidget(parent) {

    setGeometry(700, 300, 230, 80);

    setWindowTitle("CameraMenu");

    QLabel* camInstruction = new QLabel(this);
    camInstruction->setText("\nДля закрытия окна КАМЕРЫ щелкните по нему мышкой и нажмите 'ESC'\n");
    QPushButton* cameraOnBtn = new QPushButton("CameraOn", this);
    QPushButton* saveFromCameraBtn = new QPushButton("SaveFrame", this);
    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(cameraOnBtn, 0, 0);
    grid->addWidget(saveFromCameraBtn, 1, 0);
    grid->addWidget(camInstruction, 2, 0);

    setLayout(grid);

    connect(cameraOnBtn, SIGNAL(clicked()), this, SLOT(initCamera()), Qt::UniqueConnection);
    connect(saveFromCameraBtn, SIGNAL(clicked()), this, SLOT(saveCameraView()), Qt::UniqueConnection);

}

CameraWrapper::~CameraWrapper() {}


void CameraWrapper::initCamera() {
    qDebug() << "slot initCamera";

    VideoCapture camera(0); //open the default camera
    if (!camera.isOpened()) {
        QMessageBox::information(this, tr("Работа со встроенной камерой"),"Some problems with your camera\n");

    }
    else {
        namedWindow("Make your photo", 1);
        moveWindow("Make your photo",100, 240);
        while(true) {

             camera >> frame;
             imshow("Make your photo", frame);

             char c = waitKey(33);
             if(c == 27) {
                 //нажата Esc.

                 destroyWindow("Make your photo");
                 break;

            }
        }
    }

}



void CameraWrapper::saveCameraView() {
    qDebug() << "saveCameraView";
    static int counter = 0;

    QDir currDir;
    QString path =  currDir.currentPath();
    qDebug() << "path: " << path;
    string spath = path.toStdString();

    //сохраняем кадр в файл
    char fileToSave[512];
    sprintf(fileToSave, "/Images/FromCamera%d.jpg", counter);

    imwrite(string(spath + fileToSave), frame);
    counter++;
}

