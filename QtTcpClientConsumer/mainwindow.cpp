#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <vector>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT (tcpConnect()));
  connect(ui->pushButtonDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT (tcpDisconnect()));

  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(getData()));

  connect(ui->pushButtonUpdate,
          SIGNAL(clicked(bool)),
          this,
          SLOT(upgrade()));
  connect(ui->listWidgetDeIPs,
          SIGNAL(itemClicked(QListWidgetItem*)),
          this,
          SLOT(Item(QListWidgetItem*)));
  connect(ui->horizontalSliderTime,
          SIGNAL(valueChanged(int)),
          this,
          SLOT(setTimings(int)));
  /*connect(ui->pushButtonGet,
          SIGNAL(clicked(bool)),
          this,
          SLOT(maiorValor));*/

startTimer(timing*1000);
}
int timerID1=0;
void MainWindow::tcpConnect(){
  socket->connectToHost(ui->lineEditIPdoServidor->text(),1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
    listData();
    if(tempo.size()!=0){
        tempo.clear();
    }

  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();
}


void MainWindow::Item(QListWidgetItem *item)
 {
    itemDaLista=item->text();

}

void MainWindow::getData(){
  QString str;
  QByteArray array;
  QStringList list;
  int thetime;
  int value;


  qDebug() << "to get data...";
  if(socket->state() == QAbstractSocket::ConnectedState){
    if(socket->isOpen()){
      qDebug() << "reading...";
      str="get "+itemDaLista+" 10\r\n";
      socket->write(str.toStdString().c_str());
      socket->waitForBytesWritten();
      socket->waitForReadyRead();
      qDebug() << socket->bytesAvailable();
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        if(list.size() == 2){
          bool ok;
          str = list.at(0);
          thetime = (int)str.toLongLong(&ok);
          tempo.push_back(thetime);
          str = list.at(1);
          value=str.toInt(&ok);
          valores.push_back(value);
          qDebug() << thetime << ": " << str;
           }
        }
      }
    }
  }


void MainWindow::listData()
{
    QString str;
    QByteArray array;
    QStringList list;

    qDebug() << "to list data...";
    if(socket->state() == QAbstractSocket::ConnectedState){
      if(socket->isOpen()){
        qDebug() << "reading...";
        socket->write("list\r\n");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        qDebug() << socket->bytesAvailable();
        while(socket->bytesAvailable()){
          str = socket->readLine().replace("\n","").replace("\r","");
          ui->listWidgetDeIPs->addItem(str);

        }
      }
    }
}

void MainWindow::timerEvents(QTimerEvent *event)
{
    getData();
    timerID1=event->timerId();

}

/*int MainWindow::maiorValor()
{
    int maior=valores[0];
    for(int i=0;i<=9;i++){
        if(maior<valores[i+1]){
            maior=valores[i+1];
            qDebug();
        }
    }
    return maior;
}*/
void MainWindow::upgrade()
{
    ui->listWidgetDeIPs->clear();
    listData();
    if(tempo.size()!=0){
    tempo.clear();
    }

}

void MainWindow::setTimings(int _timing)
{
    timing=_timing;
}

void MainWindow::stopGetData()
{
    killTimer(timerID1);
}

/*void MainWindow::timeStamp()
{
   double soma=0;
    double div=0;

    for(int i=1;i<10;i++){
        soma=tempo[i]-tempo[0];
     //qDebug()<<"Soma = "<<soma;
        div=(soma/1000);
      //qDebug()<<"Div = "<<div;
        tempo[i]= rint(div);
        //qDebug()<<tempo[i];
    }
/*    tempo[0]=0;
    for(int i=0;i<10;i++){
      qDebug()<<tempo[i];
    }
}*/

MainWindow::~MainWindow()
{
  delete socket;
    delete ui;
}
