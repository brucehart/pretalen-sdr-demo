#include "mainwindow.h"
#include "ui_mainwindow.h"


DirectionCommand::DirectionCommand(QString dir, uint count, float x, float y) : direction(dir), pulseCount(count), xV(x), yV(y){}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    //setup some default values in the constructor
    //Direction commands from remote -- (text label, number of pulses, x movement, y movement)
    pulseDecode.append(DirectionCommand("UP", 10, 0, -0.5));
    pulseDecode.append(DirectionCommand("DOWN", 40, 0, 1));
    pulseDecode.append(DirectionCommand("LEFT", 58, -1, 0));
    pulseDecode.append(DirectionCommand("RIGHT", 64, 1, 0));
    pulseDecode.append(DirectionCommand("DOWN + LEFT", 52, -0.707, 0.707));
    pulseDecode.append(DirectionCommand("UP + LEFT", 28, -0.707, -0.707));
    pulseDecode.append(DirectionCommand("DOWN + RIGHT", 46, 0.707, 0.707));
    pulseDecode.append(DirectionCommand("UP + RIGHT", 34, 0.707, -0.707));

    //initialize other variables
    currentType = NONE;
    elementCounter = 0;
    pulseCounter = 0;
    pixelRatio = 3.0;

    v1 = 0;
    v2 = 0;

    //initialize UI components
    ui->setupUi(this);

    //set up TCP client and connect to GNU Radio server (note: start GNURadio before program)
    tcpSocket.abort();
    tcpSocket.connectToHost("127.0.0.1",2600);
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//MainWindow::moveIcon(DirectionCommand d) -- Moves the car icon based on the direction specified
void MainWindow::moveIcon(DirectionCommand d)
{
    //scale the movement of the car to a number of pixels
    int moveLeft = d.xV*pixelRatio;
    int moveUp = d.yV*pixelRatio;

    //move the car by moveLeft and moveUp pixels for each command received
    ui->imgCar->move(ui->imgCar->geometry().left() + moveLeft, ui->imgCar->geometry().top() + moveUp);

    //check the bounds and make sure the car stays on the map
    if (ui->imgCar->geometry().left() < 20)
        ui->imgCar->move(20, ui->imgCar->geometry().top());
    else if (ui->imgCar->geometry().left() > 840)
        ui->imgCar->move(840, ui->imgCar->geometry().top());

    if (ui->imgCar->geometry().top() < 40)
        ui->imgCar->move(ui->imgCar->geometry().left(), 40);
    else if (ui->imgCar->geometry().top() > 530)
        ui->imgCar->move(ui->imgCar->geometry().left(), 530);
}

//MainWindow::updateStatus() -- Updates the window using new data that is pending
void MainWindow::updateStatus()
{
    QString str;

    //loop through all of the bytes pending
    while(pendingData.size() > 0)
    {
        //remove the oldest byte
        v1 = pendingData.at(0);
        pendingData.removeFirst();

        //compare it to the previous byte
        //if a match, update a counter
        if (v1 == v2)
            elementCounter++;
        else
        {
            //if not a match, check to see if it was a pulse
            if (v2 > 0)
            {
                //if the pulse was more than 1000 samples --> long pulse
                if (elementCounter > 1000)
                {
                    //if we received a long pulse after a series of short pulses
                    if (currentType == SHORT)
                    {
                        //clear the last measured direction
                        ui->lblDirection->setText("---");

                        //loop through the command and verify the number of short pulses corresponds to a command
                        for(int i=0;i<pulseDecode.size();i++)
                        {
                            //if a match is found, apply the command to the label text and move the car icon
                            if (pulseDecode.at(i).pulseCount == pulseCounter)
                            {
                                ui->lblDirection->setText(pulseDecode.at(i).direction);
                                moveIcon(pulseDecode.at(i));
                                break;
                            }
                        }

                        //reset the counter for consecutive pulses of the same type
                        pulseCounter = 1;
                    }
                    else
                        //if we previously saw a long pulse, then just increment the pulse counter
                        pulseCounter++;

                    //record the last measured pulse type
                    currentType = LONG;
                }
                else
                {
                    //if this is the first short pulse we see in the sequence, reset the pulse counter
                    if (currentType == LONG)
                        pulseCounter = 1;
                    else
                        //otherwise increment the pulse counter
                        pulseCounter++;

                    //update currentType to show the last measured pulse type
                    currentType = SHORT;
                }
            }

            //first sample for this pulse -- reset element counter
            elementCounter = 1;
            //save the current sample for comparison with the next sample
            v2 = v1;
        }
    }
}


//MainWindow::processPendingDatagrams() -- Qt slot for handling incoming data via TCP
void MainWindow::processPendingDatagrams()
{
    QDataStream in(&tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    uint element;

    //keep adding data to the queue when at least one 4 byte sample is available
    while(tcpSocket.bytesAvailable() > 4)
    {
        //push into temporary variable
        in >> element;
        //store variable in QList to be processed later
        pendingData.push_back(element);

        //if more than 1024 samples pending, process these before adding more
        if (pendingData.size() > 1024)
            updateStatus();
    }

    //if any remaining samples are pending, process those before exiting
    //NOTE : Qt will call this slot again when more data is available
    if (pendingData.size() > 0)
        updateStatus();

}
