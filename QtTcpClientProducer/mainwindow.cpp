#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QTimer>

//#include
int timerID=0;
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow){
  ui->setupUi(this);
  socket = new QTcpSocket(this);


  connect(ui->pushButtonConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));

  connect(ui->pushButtonDisconect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));
  connect(ui->horizontalSliderMin,
          SIGNAL(valueChanged(int)),
                 this,
                 SLOT(setMinimo(int)));
  connect (ui->horizontalSliderMax,
           SIGNAL(valueChanged(int)),
                  this,
                  SLOT (setMaximo(int)));
  connect (ui->horizontalSliderTiming,
           SIGNAL(valueChanged(int)),
           this,
           SLOT(setTiming(int)));
  connect(ui->pushButtonStart,
          SIGNAL(clicked(bool)),
                 this,
                 SLOT (start()));
  connect(ui->pushButtonStop,
          SIGNAL(clicked(bool)),
                 this,
                 SLOT (stopTransmissao()));

startTimer(timing*1000);//aciona o temporizador em segundos
}
void MainWindow::tcpConnect(){
    socket->connectToHost(ui->lineEdit_IP->text(),1234);//conecta o ip da maquina digitado
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{  
    qDebug() << "Disconnected";
  }
}

void MainWindow::tcpDisconnect()
{
    socket->disconnectFromHost();//desconecta o socket
    qDebug()<<"Disconnected";
}

void MainWindow::setMinimo(int _minimo)
{
    minimo=_minimo;//recebe o valor minimo
}

void MainWindow::setMaximo(int _maximo)
{
    maximo=_maximo;//recebe o valor máximo
}

void MainWindow::setTiming(int _timing)
{
    timing=_timing;
}

void MainWindow::stopTransmissao()
{
    killTimer(timerID);
}

void MainWindow::start(){
  QDateTime datetime;
  QString str;
  qint64 msecdate;


  if(socket->state()== QAbstractSocket::ConnectedState){

    msecdate = QDateTime::currentDateTime().toMSecsSinceEpoch();//transformma a data em milisegundos

    str = "set "+ QString::number(msecdate) + " " + QString::number(minimo+(rand()%(maximo-minimo+1)))+"\r\n";
            //retorna um string com o tempo e o numero da faixa de valores

    ui->listWidget->addItem(str);//add na lista
    //qDebug() << str;
          qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";

      }

  }
}

void MainWindow::timerEvent(QTimerEvent *event)
{

    start();
    //recebe o indentificador do timer para matar o timer
    timerID=event->timerId();

}

MainWindow::~MainWindow(){
  delete socket;
    delete ui;
}

