#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
    int minimo=1, maximo=1,timing=1;
public:
  explicit MainWindow(QWidget *parent = 0);
void timerEvent(QTimerEvent *event);
  ~MainWindow();
  

public slots:
void tcpConnect();
void tcpDisconnect();
 void start();
  void setMinimo(int _minimo);
  void setMaximo(int _maximo);
  void setTiming(int _timing);
  void stopTransmissao();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
