#ifndef RandomPickPlayers_H
#define RandomPickPlayers_H

#include <QMainWindow>
#include <vector>
#include <QTimer>
namespace Ui {
class QTShowPic;
}

class QTShowPic : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTShowPic(QWidget *parent = 0);
    ~QTShowPic();

private slots:

    void on_pushButton_Start_clicked();

    void on_pushButton_Reset_clicked();
    //定时器
    void TimeOut();
private:
    Ui::QTShowPic *ui;
    int m_iIndex;
    int m_iPlayerNum;
    int m_iCurrentNum;
    int m_iPlayerNeed;
    int m_iPlayerIndex;
    std::vector<QString> m_vecPlayerNameAll;
    std::vector<QString> m_vecPlayerNameBackup;
    std::vector<QString> m_vecPlayerNamePatt;
    QTimer *m_pTime;
    bool m_bStart;
};

#endif // RandomPickPlayers_H
