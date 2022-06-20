#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    memset(records, 0, sizeof records);
    ui->lineEdit->setText("C:\\Users\\tiroxwater\\Desktop\\Project\\stock_china.csv");
     show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::readData()
{
    QFile* mainFilePtr = new QFile(ui->lineEdit->text());
    if(!mainFilePtr->exists()) {QMessageBox::critical(this, "Error", "File not exist.") ;return -1;}
    mainFilePtr->open(QFile::OpenModeFlag::ReadOnly);
    int iter;
    //C:\Users\tiroxwater\Desktop\Project\stock_china.csv
    QString headLine = mainFilePtr->readLine(); //移除第一行的
    for(iter = 117; false; iter++) {
        bool finished = false;
        int i;
        for(i=0;i<100000;i++) {
            QString lineData = mainFilePtr->readLine();
            if(lineData == "") {
                finished = true;
                break;
            }
            if(records[i] == nullptr) records[i] = new StockRecord(lineData);
            else *(records[i]) = StockRecord(lineData);
        }
        std::sort(records, records+i, [](const StockRecord *a, const StockRecord *b) -> bool {
            return (*a) < (*b);
        });
        qDebug() << "Data Sort" << iter << ": Success";

        string filename = "C:\\Users\\tiroxwater\\Desktop\\Project\\lol\\build-project-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\\tmp\\rec_" + std::to_string(iter) + ".csv"; // name of the small files

        QFile* out = new QFile(QString::fromStdString(filename));
        out->open(QFile::OpenModeFlag::WriteOnly);
        for(int j=0;j<i;j++) {
            DateType date = records[j]->getDate();
            out->write((date.toQString() + ",").toStdString().c_str());
            out->write((records[j]->getName() + ",").toStdString().c_str());
            out->write(records[j]->getPrice().toQString().toStdString().c_str());
            out->write("\n");
        }
        qDebug() << "Data Write: Success";
        out->close();
        delete out;
        if(finished) break;
    }
    mainFilePtr->close();
    delete mainFilePtr;

    typedef std::pair<StockRecord, int> Pair;
    std::priority_queue<Pair> Q;
    QFile *files[200] = {};
    //初始化最小堆
    for(int i = 0; i<=iter; ++i) {
        files[i] = new QFile(("tmp/rec_" + std::to_string(iter) + ".csv").c_str());
        files[i]->open(QFile::OpenModeFlag::ReadOnly);
        QString data = files[i]->readLine();
        if(records[i] == nullptr) records[i] = new StockRecord(data);
        else *(records[i]) = StockRecord(data);
        Q.push(Pair(*records[i], i));
    }

    QFile *outputPtr = new QFile("..\\output.txt");
    outputPtr->open(QFile::OpenModeFlag::ReadWrite);
    outputPtr->write(headLine.toStdString().c_str());

    while(!Q.empty()) {
        Pair p = Q.top(); Q.pop();

        StockRecord rec = p.first; int source = p.second;
        outputPtr->write(rec.getName().toStdString().c_str());
        outputPtr->write(",");
        outputPtr->write(rec.getDate().toQString().toStdString().c_str());
        outputPtr->write(",");
        outputPtr->write(rec.getPrice().toQString().toStdString().c_str());
        outputPtr->write("\n");

        QString buffer = files[source]->readLine(1000);
        if(buffer == "") {continue; qDebug() << source << "ended.";}
        if(records[source] == nullptr) records[source] = new StockRecord(buffer);
        else *(records[source]) = StockRecord(buffer);
        Q.push(Pair(*records[source], source));

        //TODO: output p.first to output.txt, and read a new StockRecord from files[p.second] (if possible).
    }

    outputPtr->close();
    delete outputPtr;
    qDebug() << "2333";
    for(int i = 0; i<=iter; ++i) {files[i]->close(); delete files[i];}
    for(int i = 0; i<100000; ++i) {
        if(records[i] != nullptr) delete records[i];
        records[i] = nullptr;
    }
    return 1;
}
