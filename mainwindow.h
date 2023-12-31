#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket> //para protocolo udp
#include <QHostAddress>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void onQUdpSocket1Rx(void);



    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QUdpSocket *QUdpSocket1;

    QHostAddress remoteHostIP;

    quint16 remotePort;



};
#endif // MAINWINDOW_H
