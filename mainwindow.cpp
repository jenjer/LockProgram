#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QLineEdit>
#include <QtX11Extras/QX11Info>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include <QScreen>
#include <X11/keysym.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetLockScreen();
}

void MainWindow::SetLockScreen()
{
    setWindowState(Qt::WindowFullScreen);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    this->setStyleSheet("background-color: ;");
    QLabel *label = new QLabel("Hello, world!", this);
    label->setAlignment(Qt::AlignCenter);
    resize(400,300);
    label->setStyleSheet("color: white; font-size:24px;");
    label->show();
    setAttribute(Qt::WA_X11DoNotAcceptFocus, false);

    QLineEdit *lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("여기에 입력하세요..."); // 입력 힌트
     lineEdit->setStyleSheet("color: white; font-size: 18px; background-color: gray; border-radius: 5px; padding: 5px;");
    lineEdit->show();

    installEventFilter(this);

    //setupUI();
    setupX11Grab();
}

void MainWindow::setupX11Grab()
{
    Display *display = QX11Info::display();
    Window root = XDefaultRootWindow(display);
        // root 권한 필요 and if not root than doesn't work
    //system("sudo chmod 700 /dev/tty[1-6]");
    XGrabKeyboard(display, root, True, GrabModeAsync, GrabModeAsync, CurrentTime);
    XGrabPointer(display, root, True, ButtonPressMask | ButtonReleaseMask | PointerMotionMask, GrabModeAsync, GrabModeAsync, root, None, CurrentTime);
}



MainWindow::~MainWindow()
{
    delete ui;
}

