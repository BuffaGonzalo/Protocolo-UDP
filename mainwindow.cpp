#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QUdpSocket1 = new QUdpSocket(this);

    connect(QUdpSocket1, &QUdpSocket::readyRead,this, &MainWindow::onQUdpSocket1Rx);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    uint16_t port;
    bool ok;

    if(QUdpSocket1->isOpen()){
        QUdpSocket1 ->abort(); //abortamos para cortar cualquier tarea antes de cerrarlo
        QUdpSocket1 ->close();
        ui->pushButton->setText("OPEN");
    } else{
        port = ui->lineEdit->text().toInt(&ok, 10);

        if(ok){
            QUdpSocket1->bind(port); //parte del sistema que gestiona los protocolos
            if(QUdpSocket1->open(QUdpSocket::ReadWrite)){
                ui->pushButton->setText("CLOSE");
            }
        }


    }
    port = ui->lineEdit->text().toInt(&ok, 10);



}

void MainWindow::onQUdpSocket1Rx(void)
{
    int count;
    char *buffer;

    count = QUdpSocket1->bytesAvailable();

    if(count <= 0)
        return;

    //datagram - paquete completo Udp

    while(QUdpSocket1 -> hasPendingDatagrams()){
        count = QUdpSocket1->pendingDatagramSize();
        buffer = new char[count];

        QUdpSocket1->readDatagram(buffer,count,&remoteHostIP, &remotePort);


        ui->lineEdit_2->setText(remoteHostIP.toString());
        ui->lineEdit_4->setText(QString().number((remotePort)));

        ui->plainTextEdit->appendPlainText(buffer);


        delete [] buffer;
    }

}



void MainWindow::on_pushButton_2_clicked()
{
    if(QUdpSocket1->isOpen()){
        remoteHostIP.setAddress(ui->lineEdit_2->text());
        remotePort =ui->lineEdit_4->text().toUShort();
        QUdpSocket1->writeDatagram(ui->lineEdit_3->text().toUtf8().data(),ui->lineEdit_3->text().length(),remoteHostIP,remotePort);
    }
}

