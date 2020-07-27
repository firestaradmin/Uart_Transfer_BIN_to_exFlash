#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    refreshPortName();
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

    ui->pushButton_StartSending->setEnabled(false);
    ui->progressBar->setEnabled(false);
    connect(this, &MainWindow::recvOK, this, &MainWindow::sendOnce);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_openFile_clicked()
{

    QString fileName=QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("bin file"),qApp->applicationDirPath(),
                                                  QString::fromLocal8Bit("bin File(*.bin)"));//新建文件打开窗口
    if (fileName.isEmpty()){//如果未选择文件便确认，即返回
        ui->textEdit_Log->append("请选择一个二进制文件【.BIN】");
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        ui->textEdit_Log->append(file.errorString());//文件打开错误显示错误信息

    file_array=file.readAll();//读取文件
    ui->textEdit_Log->append("打开文件：");
    ui->textEdit_Log->append(fileName);
    file_length=file_array.size();//计算长度
    ui->textEdit_Log->append(QString("字库大小：%1 Bytes").arg(file_length));
    sendedBytes = 0;
    unSendedBytes = file_length;
    ui->label_sendedBytes->setNum(sendedBytes);
    ui->label_unSendedBytes->setNum(unSendedBytes);
    ui->progressBar->setValue(static_cast<int>((static_cast<float>(sendedBytes) / static_cast<float>(file_length)) * 100));

    file.close();

    ui->pushButton_StartSending->setEnabled(true);

}

void MainWindow::on_pushButton_openPort_clicked()
{
    if(ui->comboBox_PortChoice->isEnabled())
    {
        ui->pushButton_openPort->setText("ClosePort"); //按下打开串口后显示为"关闭串口"
        ui->comboBox_PortChoice->setDisabled(true); //禁止修改串口
        mySerial.setPortName(ui->comboBox_PortChoice->currentText()); //设置串口号
        mySerial.setBaudRate(ui->comboBox_BaudRate->currentText().toInt()); //设置波特率
        mySerial.setDataBits(QSerialPort::Data8); //数据位
        mySerial.setFlowControl(QSerialPort::NoFlowControl);
        mySerial.setParity(QSerialPort::NoParity);
        mySerial.setStopBits(QSerialPort::OneStop);
        mySerial.close();
        if(mySerial.open(QIODevice::ReadWrite))
        {
            //将串口的 readyread 信号绑定到 read_com 这个槽函数上
            connect(&mySerial,SIGNAL(readyRead()),this,SLOT(read_COM()));
            ui->textEdit_Log->append(QString("串口%1连接成功").arg(ui->comboBox_PortChoice->currentText()));
        }
    }
    else
    {
        ui->pushButton_openPort->setText("OpenPort");
        ui->comboBox_PortChoice->setEnabled(true);
        mySerial.close();
        ui->textEdit_Log->append(QString("串口%1断开连接").arg(ui->comboBox_PortChoice->currentText()));
    }

}


void MainWindow::refreshPortName()
{
    QStringList strList_port;
    for(int i = 0; i < QSerialPortInfo::availablePorts().size(); i++ ){
        strList_port.append(QSerialPortInfo::availablePorts().at(i).portName());
    }
    ui->comboBox_PortChoice->clear();
    ui->comboBox_PortChoice->addItems(strList_port);
}


void MainWindow::read_COM()
{
    QByteArray mytemp = mySerial.readAll();
    uint16_t length ;
    char bcc = 0;
    int err = 0;
    if(!mytemp.isEmpty())
    {
        qDebug() << mytemp.toHex();
        if((mytemp.at(0) & 0xff) != 0xC5)
            err = 1;
        if((mytemp.at(1) & 0xff) != 0x5C)
            err = 1;
        length = (mytemp.at(3) & 0xff) * 0xFF + (mytemp.at(4) & 0xff);
        for(int i = 2; i < 5 + length; i ++){
            bcc ^= (mytemp.at(i) & 0xff);
        }

        if(bcc != (mytemp.at(5 + length) & 0xff))
            err = 2;	//bcc校验码错误

        if((mytemp.at(6 + length) & 0xff) != 0x5C)
            err = 3;	//帧尾错误
        if((mytemp.at(7 + length) & 0xff) != 0xC5)
            err = 3;	//帧尾错误
        if(err != 0){
            ui->pushButton_StartSending->setEnabled(true);
            ui->textEdit_Log->append("FrameVerify ERROR!");
            ui->textEdit_Log->append(QString("ERROR:%1").arg(err));
            transfer_Started_flag = 0;
            return  ;

        }

        switch((mytemp.at(2) & 0xff)){  //CMD字节
        case 0x00:  //数据传输命令ACK
            if(((mytemp.at(length + 4) & 0xff) == 0x00) && transfer_Started_flag == 1 ){
                ui->textEdit_Log->append("send Data OK!");
                sendedBytes += currentLen;
                unSendedBytes = file_length - sendedBytes;
                if(unSendedBytes < 0)
                    unSendedBytes = 0;
                ui->label_sendedBytes->setNum(sendedBytes);
                ui->label_unSendedBytes->setNum(unSendedBytes);
                ui->progressBar->setValue(static_cast<int>((static_cast<float>(sendedBytes) / static_cast<float>(file_length)) * 100));
                if(unSendedBytes > 0){
                    emit(recvOK());
                }else {
                    ui->textEdit_Log->append("all data send over!");
                    ui->pushButton_StartSending->setEnabled(true);
                    transfer_Started_flag = 0;
                }

            }
            else {
                ui->pushButton_StartSending->setEnabled(true);
                ui->textEdit_Log->append("send Data failed!");
                ui->textEdit_Log->append(QString("ERROR:%1").arg(mytemp.at(5) & 0xff));
            }
            break;
        case 0x01:  //数据传输开始ACK
            if(((mytemp.at(5) & 0xff) == 0x00)){
                ui->textEdit_Log->append("start transfer data!");
                emit(recvOK());
                transfer_Started_flag = 1;
            }
            else {
                ui->pushButton_StartSending->setEnabled(true);
                ui->textEdit_Log->append("send Data failed!");
                ui->textEdit_Log->append(QString("ERROR:%1").arg(mytemp.at(5) & 0xff));
            }
            break;
        case 0x02:  //数据传输结束ACK

            break;
        default:
            //TODO
            ;
        };

        //mytemp.clear();
    }
}







void MainWindow::sendOnce(){
    QByteArray sendBuf, dataBuf;

    char file_length0,file_length1;
    QString str;
    char bcc = 0x00;

    if(unSendedBytes >= ui->lineEdit_ByteNum->text().toInt()){
        dataBuf = file_array.mid(sendedBytes, ui->lineEdit_ByteNum->text().toInt());
        currentLen = ui->lineEdit_ByteNum->text().toInt();
     }
    else {
        dataBuf = file_array.mid(sendedBytes, unSendedBytes);
        currentLen = unSendedBytes;
    }
    //qDebug() << dataBuf.size();
    sendBuf.clear();
    sendBuf.append("\xC5\x5C");
    sendBuf.append(static_cast<char>(0));
    file_length0 = static_cast<char>(currentLen / 0xFF);
    file_length1 = static_cast<char>(currentLen % 0xFF);
    sendBuf.append(file_length0);
    sendBuf.append(file_length1);
    //qDebug() << sendBuf.toHex().toUpper();

    sendBuf.append(dataBuf);
    //qDebug() << sendBuf.toHex().toUpper();

    for(int i = 2; i < sendBuf.size(); i++){
        //str.append((QString("%1  ").arg(file_array.at(i) & 0xff, 2, 16, QLatin1Char('0')).toUpper()));
        bcc ^= sendBuf.at(i) & 0xff;
    }
    sendBuf.append(bcc);
    sendBuf.append("\x5C\xC5");
    //qDebug() << sendBuf.toHex().toUpper();

    for(int i = 5; i < sendBuf.size() - 3; i++){
        str.append((QString("%1  ").arg(sendBuf.at(i) & 0xff, 2, 16, QLatin1Char('0')).toUpper()));
    }
    ui->textEdit_Status->append("---------------------------------------");
    ui->textEdit_Status->append(QString("地址[ %1 ] to [ %2 ] 的数据：").arg(sendedBytes).arg(sendedBytes + currentLen - 1));
    ui->textEdit_Status->append(str);
    ui->textEdit_Status->append(QString("---  BCC校验码: %1  ---").arg(bcc & 0xff, 2, 16, QLatin1Char('0')).toUpper());

    ui->textEdit_Log->append(QString("send [ %1 ] to [ %2 ] Data ...").arg(sendedBytes).arg(sendedBytes + currentLen - 1));
    mySerial.write(sendBuf);


}

void MainWindow::on_pushButton_StartSending_clicked()
{
    QByteArray sendBuf;
    QString str;
    char bcc = 0x00;
    uint32_t address = static_cast<uint32_t>(ui->lineEdit_AddressOffSet->text().toInt());
    unSendedBytes = file_length;
    sendedBytes = 0;
    ui->label_sendedBytes->setNum(sendedBytes);
    ui->label_unSendedBytes->setNum(unSendedBytes);
    ui->progressBar->setValue(static_cast<int>((static_cast<float>(sendedBytes) / static_cast<float>(file_length)) * 100));

    ui->progressBar->setEnabled(true);

    //emit(recvOK());

    sendBuf.append("\xC5\x5C");
    sendBuf.append(static_cast<char>(1));
    sendBuf.append(static_cast<char>(0));
    sendBuf.append(static_cast<char>(4));

    sendBuf.append(static_cast<char>(address / 0xFFFFFF));  //0xffffffff
    sendBuf.append(static_cast<char>((address % 0x1000000) / 0xFFFF));
    sendBuf.append(static_cast<char>((address % 0x10000) / 0xFF));
    sendBuf.append(static_cast<char>(address % 0x100));

    for(int i = 2; i < sendBuf.size(); i++){
        bcc ^= sendBuf.at(i) & 0xff;
    }
    sendBuf.append(bcc);
    sendBuf.append("\x5C\xC5");

    //qDebug() << sendBuf.toHex();

    mySerial.write(sendBuf);
    ui->pushButton_StartSending->setEnabled(false);

}






void MainWindow::on_pushButton_refreashCOM_clicked()
{
    refreshPortName();
}
