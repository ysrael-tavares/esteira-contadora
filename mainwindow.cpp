#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(auto& item : QSerialPortInfo::availablePorts())
        ui->boxPortas->addItem(item.portName());

    connect(&serial,
            SIGNAL(readyRead()),
            this,
            SLOT(dadosRecebidos()));

    manager = new QNetworkAccessManager();
    QObject::connect(manager,SIGNAL(finished(QNetworkReply*)),
                     this,
                     SLOT(managerFinished(QNetworkReply*)));

    QString url = "http://esteira-contadora.herokuapp.com/upload";
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSerial_clicked()
{
    serial.setPortName((ui->boxPortas->currentText()));
    serial.setBaudRate(115200);

    if(serial.isOpen()){
        serial.close();
        ui->btnSerial->setText("Conectar");
    }else if(serial.open(QIODevice::ReadWrite)){
        ui->btnSerial->setText("Desconectar");
    }
}

void MainWindow::dadosRecebidos()
{
    auto data = serial.readAll();
    auto dados = QJsonDocument::fromJson(data).object().toVariantMap();

    if(dados.contains("ESTEIRA")){
        atualizaEstadoEsteira(dados["ESTEIRA"].toString());
        ui->estadoEsteira->setChecked(!dados["ESTEIRA"].toBool());
    }

    if(dados.contains("ITENS")){
        atualizaItens(dados["ITENS"].toString());
        ui->qtdItens->setText(dados["ITENS"].toString());
    }




}

void MainWindow::atualizaItens(QString qtditens)
{
    objeto = {{"ITENS",qtditens}};
    manager->post(request,QJsonDocument(objeto).toJson());
}

void MainWindow::atualizaEstadoEsteira(QString estado)
{
    objeto = {{"ESTEIRA",estado}};
    manager->post(request,QJsonDocument(objeto).toJson());
}

void MainWindow::on_butAcao_clicked()
{
    serial.write("{\"ESTEIRA\":1}");
}

void MainWindow::on_btnpause_clicked()
{
    serial.write("{\"ESTEIRA\":0}");
}

void MainWindow::on_pushButton_clicked()
{
    serial.write("{\"RESET\":1}");
}
