#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "main.h"

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void recvOK();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;



private slots:
    void on_pushButton_openFile_clicked();

    void on_pushButton_openPort_clicked();

    void read_COM();



    void on_pushButton_StartSending_clicked();



    void sendOnce();



    void on_pushButton_refreashCOM_clicked();

private:
    void refreshPortName(); //刷新可用串口列表


    QByteArray file_array;    //文件数据buf
    int file_length;         //文件字节长度
    QSerialPort mySerial;   //串口对象

    int sendedBytes = 0;//已发送字节
    int unSendedBytes = 0;  //未发送字节
    int terminal_recv_OK = 0;
    int receive_finish_Flag = 0;
    int currentLen = 0;

};

#endif // MAINWINDOW_H










