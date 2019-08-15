#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork>
#include <QtDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSerialPort serial;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_btnSerial_clicked();

    void on_butAcao_clicked();

    void on_btnpause_clicked();

    void dadosRecebidos();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString msg;
    void atualizaEstadoEsteira(QString estado);
    void atualizaItens(QString qtditens);
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QJsonObject objeto;

private slots:
    void managerFinished(QNetworkReply *reply);
};

#endif // MAINWINDOW_H
