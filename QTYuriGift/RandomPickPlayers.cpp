#include "RandomPickPlayers.h"
#include "ui_RandomPickPlayers.h"
#include <QDir>
#include <QFileDialog>
#include <QSettings>
#pragma execution_character_set("utf-8")
QTShowPic::QTShowPic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTShowPic)
{
    ui->setupUi(this);
    m_iIndex = 0;
    m_bStart = false;
    ui->label_Change->setAlignment(Qt::AlignCenter);

    ui->label_Change->setStyleSheet("background-color: rgb(255, 255, 255);color:red");

    //初始化画面号
    QSettings *configIniRead = new QSettings("./YuriTeam.ini", QSettings::IniFormat);
    configIniRead->setIniCodec("GB2312"); ;//添上这句就不会出现乱码了
    m_iCurrentNum = m_iPlayerNum = configIniRead->value("/Player/PlayerNum").toInt();
    m_iPlayerNeed = configIniRead->value("/Player/PlayerNeed").toInt();
    for(int i=0;i<m_iPlayerNum;i++)
    {

        m_vecPlayerNameBackup.push_back(configIniRead->value(QString("/Name/Player%1").arg(i)).toString());
    }
    for(int i=0;i<m_iCurrentNum;i++)
    {

        ui->plainTextEdit_all->appendPlainText(m_vecPlayerNameBackup.at(i));
    }
    m_iPlayerIndex = m_iPlayerNeed;
    m_vecPlayerNameAll = m_vecPlayerNameBackup;
    if(configIniRead != nullptr)
    {
        delete configIniRead;
        configIniRead = nullptr;
    }
    ui->statusBar->showMessage(QString("还需要抽 %1 人").arg(m_iPlayerIndex),5000);

    //定时器
    m_pTime = new QTimer(this);
    connect(m_pTime,&QTimer::timeout,this,&QTShowPic::TimeOut);
}

QTShowPic::~QTShowPic()
{
    delete ui;
}

void QTShowPic::TimeOut()
{
    if(m_iIndex==m_iCurrentNum)
    {
        m_iIndex=0;
    }
    ui->label_Change->setText(m_vecPlayerNameAll.at(m_iIndex));
    m_iIndex++;
    ui->statusBar->showMessage(QString("还需要抽 %1 人").arg(m_iPlayerIndex),5000);
}

void QTShowPic::on_pushButton_Start_clicked()
{
    if(m_bStart)
    {
        m_pTime->stop();
        m_bStart = false;
        ui->pushButton_Start->setText("开始抽奖");
        if(m_iIndex>m_iCurrentNum-1)
        {
            m_iIndex=m_iCurrentNum-1;
        }
        ui->plainTextEdit_part->appendPlainText(m_vecPlayerNameAll.at(m_iIndex));
        ui->label_Change->setText(m_vecPlayerNameAll.at(m_iIndex));
        auto it = m_vecPlayerNameAll.begin()+m_iIndex;
        m_vecPlayerNameAll.erase(it);
        m_iIndex=0;
        m_iCurrentNum--;
        m_iPlayerIndex--;
        ui->statusBar->showMessage(QString("还需要抽 %1 人").arg(m_iPlayerIndex),5000);
        ui->plainTextEdit_all->clear();
        for(int i=0;i<m_iCurrentNum;i++)
        {

            ui->plainTextEdit_all->appendPlainText(m_vecPlayerNameAll.at(i));
        }

    }
    else
    {
        m_bStart = true;
        ui->pushButton_Start->setText("停止抽奖");
        m_pTime->start(10);

    }
    if(m_iPlayerIndex==0)
    {
        ui->pushButton_Reset->setEnabled(true);
        ui->pushButton_Start->setEnabled(false);
        ui->statusBar->showMessage("请重新开始抽奖",5000);
    }
}

void QTShowPic::on_pushButton_Reset_clicked()
{
    ui->pushButton_Reset->setEnabled(false);
    ui->pushButton_Start->setEnabled(true);
    m_iCurrentNum = m_iPlayerNum;
    m_iPlayerIndex = m_iPlayerNeed;
    m_vecPlayerNameAll = m_vecPlayerNameBackup;
    ui->plainTextEdit_part->clear();
    ui->plainTextEdit_all->clear();
    for(int i=0;i<m_iCurrentNum;i++)
    {

        ui->plainTextEdit_all->appendPlainText(m_vecPlayerNameBackup.at(i));
    }
    ui->label_Change->setText("请开始抽取选手");
    ui->statusBar->showMessage(QString("还需要抽 %1 人").arg(m_iPlayerIndex),5000);
}
