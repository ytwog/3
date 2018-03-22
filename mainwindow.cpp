 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dir = "";
    fileVec.resize(0);
    model = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::Getdir()
{
    return dir;
}

void MainWindow::Setdir(QString _dir)
{
    dir = _dir;
}

void MainWindow::on_dirButton_clicked()
{
    Setdir(QFileDialog::getExistingDirectory(0, "Выберите директорию"));
    ui->dirBrowser->setText(dir);
}

void MainWindow::on_showButton_clicked()
{
    MakeVec(dir);
    if(fileVec.isEmpty())
    {
        ui->errBrowser->setText("Файлы в директории\nне обнаружены");
    }
    else
    {
        showView();
    }
}

void MainWindow::showView()
{
    if(model)
    {
        delete model;
        model = NULL;
    }
    if(fileVec.isEmpty())
    {
        return;
    }
    else
    {
        model = new QStandardItemModel(fileVec.length(), 4);
        ui->tableView->setModel(model);
        model->setHeaderData(0, Qt::Horizontal, "Название");
        model->setHeaderData(1, Qt::Horizontal, "Дата изменения");
        model->setHeaderData(2, Qt::Horizontal, "Размер");
        model->setHeaderData(3, Qt::Horizontal, "Атрибуты");



        ui->tableView->setColumnWidth(0, (ui->tableView->width() - ui->tableView->verticalHeader()->size().width() - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 3);
        ui->tableView->setColumnWidth(1, (ui->tableView->width() - ui->tableView->verticalHeader()->size().width() - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 3);
        ui->tableView->setColumnWidth(2, (ui->tableView->width() - ui->tableView->verticalHeader()->size().width() - qApp->style()->pixelMetric(QStyle::PM_ScrollBarExtent)) / 6);
        ui->tableView->horizontalHeader()->setStretchLastSection(true);
        int i = 0;
        for(QVector<files>::iterator it = fileVec.begin(); it != fileVec.end(); it++, i++)
        {
            for(int col = 0; col < 4; col++)
            {
                if(col == 0)
                {
                    model->setData(model->index(i, col), it->getname());
                }
                else if(col == 1)
                {
                    model->setData(model->index(i, col), it->getdate());
                }
                else if(col == 2)
                {
                    model->setData(model->index(i, col), it->getsize());
                }
                else
                {
                    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
                    model->setData(model->index(i, col), it->getattr());
                    QString attr = "";
                    int res = it->getattr();

                    if(res > 7)
                    {
                        attr += "E ";
                        res -= 8;
                    }
                    else if(res > 3)
                    {
                        attr += "D ";
                        res -= 4;
                    }
                    if(res > 1)
                    {
                        attr += "H";
                        res -= 2;
                    }
                    if(res > 0)
                    {
                        attr += "R";
                    }
                    if(attr == "")
                    {
                        attr = "N";
                    }
                    // = 0   | No attributes
                    // += 1  | Read-only
                    // += 2  | Hidden
                    // += 4  | Directory
                    // += 8  | Executable
                    model->setData(model->index(i, col), attr);
                }
            }
        }
        ui->tableView->setModel(model);
    }
}


qint64 getSize(QDir Dir, QString DirName)
{
    qint64 res = 0;

    QDir NextDir = QDir(Dir.absoluteFilePath(DirName));
    NextDir.setFilter(QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    QStringList Nextlist = NextDir.entryList();

    foreach (QString _name, Nextlist)
    {
        QFileInfo file = NextDir.absoluteFilePath(_name);
        if(file.isDir())
        {
            res += getSize(NextDir, _name);
        }
        else
        {
            res += file.size();
        }
    }
    return res;
}


void MainWindow::MakeVec(QString DirName)
{
    fileVec.resize(0);
    QApplication::processEvents();
    if(DirName == "")
    {
        return;
    }
    QDir Dir = QDir(DirName);
    Dir.setFilter(QDir::AllEntries | QDir::Hidden | QDir::System | QDir::NoDotAndDotDot);
    QStringList listFiles = QDir(Dir).entryList();
    QVector<files> tempVec = GetVec();
    foreach (QString _name, listFiles)
    {
        QFileInfo file = Dir.absoluteFilePath(_name);
        qint64 _size;
        if(file.isDir())
        {
           _size = getSize(Dir, _name);
        }
        else
        {
           _size = file.size();
        }
        QDateTime _date = file.lastModified();
        short _attributes = 0;
        if((file.isReadable()) && (!file.isWritable()))
        {
            _attributes += 1;
        }
        if(file.isHidden())
        {
            _attributes += 2;
        }
        if(file.isDir())
        {
            _attributes += 4;
        }
        else if(file.isExecutable())
        {
            _attributes += 8;
        }

        files *Obj = new files(_name, _size,  _date,  _attributes);
        addToVec(tempVec, Obj);
    }
    SetVec(tempVec);
}




QVector<files> MainWindow::GetVec()
{
    return fileVec;
}

void MainWindow::SetVec(QVector<files> _fileVec)
{
    fileVec = _fileVec;
}

void MainWindow::on_dirButton_2_clicked()
{
    Setdir("C:/Abc/qt/projects/3\0");
    ui->dirBrowser->setText(dir);
}
