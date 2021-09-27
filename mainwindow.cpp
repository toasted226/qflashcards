#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>

#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    OnLoad();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnLoad()
{
    RefreshFlashcardSetList();
}

void MainWindow::RefreshFlashcardSetList()
{
    //Get config directory
    QDir directory(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));

    //Get list of text files
    QStringList files = directory.entryList(QStringList() << "*.txt" << "*.TXT", QDir::Files);

    flashcardSets.clear();
    flashcardSets.reserve(files.capacity());

    foreach(QString filename, files)
    {
        QFileInfo fileinfo = QFileInfo(QFile(filename));

        flashcardSets.emplace_back(fileinfo.baseName(), fileinfo.absoluteFilePath());
        ui->flashcardSetsList->addItem(fileinfo.baseName());
    }
}

void MainWindow::on_actionFlashcard_Set_triggered()
{
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir directory(configPath);

    qDebug() << configPath;

    QString defaultDir = directory.absolutePath() + "/flashcardset.txt";

    QString filePath = QFileDialog::getSaveFileName(
                this, tr("Save File"), defaultDir, tr("Text Files (*.txt)"));

    if(filePath != "")
    {
        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.close();
            qDebug() << "Wrote flashcard set to " << filePath;
        }
    }

    RefreshFlashcardSetList();
}









