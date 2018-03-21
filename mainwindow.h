#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile.h>
#include <qfiledialog>
#include <QDialog>
#include <files.h>
#include <QFileInfo>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QModelIndex>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString Getdir();

    void Setdir(QString _dir);

    QVector<files> GetVec();

    void SetVec(QVector<files> _fileVec);

    void MakeVec(QString DirName);

    void showView();

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_dirButton_clicked();

    void on_showButton_clicked();

    void on_dirButton_2_clicked();

private:
    QStandardItemModel *model;
    QVector<files> fileVec;
    QString dir;
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
