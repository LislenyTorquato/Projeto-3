#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QListWidgetItem>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
    std::vector <int> tempo;
    std::vector <int> valores;
    int timing=1;
    QString itemDaLista;
   //void timeStamp();
    void listData();
    void timerEvents(QTimerEvent *event);
    //int maiorValor();
public slots:

   void Item(QListWidgetItem *item);
   void getData();
   void tcpConnect();
   void tcpDisconnect();
   void upgrade();
  void setTimings(int _timing);
  void stopGetData();
   // void timeStamp();
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;

};

#endif // MAINWINDOW_H
