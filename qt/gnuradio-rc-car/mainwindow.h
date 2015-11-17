#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QList>

#define BOUND_LEFT      20
#define BOUND_RIGHT     840
#define BOUND_TOP       40
#define BOUND_BOTTOM    530

namespace Ui {
class MainWindow;
}

class DirectionCommand
{
public:
    DirectionCommand(QString dir, uint count, float x, float y);
    QString direction;
    uint pulseCount;
    float xV;
    float yV;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateStatus();
    void moveIcon(DirectionCommand d);

private slots:
    void processPendingDatagrams();

private:
    Ui::MainWindow *ui;
    QTcpSocket tcpSocket;
    QList<uint> pendingData;

    enum pulseType {NONE, SHORT, LONG};
    pulseType currentType;

    uint elementCounter;
    uint pulseCounter;

    uint v1;
    uint v2;
    QList<DirectionCommand> pulseDecode;

    float pixelRatio;
};



#endif // MAINWINDOW_H
