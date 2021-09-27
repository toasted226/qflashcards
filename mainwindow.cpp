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

    ui->flashcardSetsList->clear(); //Clear UI flashcard set listview
    flashcardSets.clear(); //Clear internal flashcard set vector
    flashcardSets.reserve(files.capacity()); //Reserve the correct amount of memory

    //Foreach file in config directory, add the text files to each flashcard set list
    foreach(QString filename, files)
    {
        QFileInfo fileinfo = QFileInfo(QFile(filename));

        //Fill in the values for the spots reserved on memory, avoids copy operations
        flashcardSets.emplace_back(fileinfo.baseName(), fileinfo.absoluteFilePath());
        //Add flashcard lists to the listview in UI
        ui->flashcardSetsList->addItem(fileinfo.baseName());
    }
}

void MainWindow::on_actionFlashcard_Set_triggered()
{
    //Get config location that we've set up in main.cpp
    QDir directory(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QString defaultDir = directory.absolutePath() + "/flashcardset.txt"; //Default dir with filename

    //Open file dialog to prompt user to save a new flashcard set
    QString filePath = QFileDialog::getSaveFileName(
                this, tr("Save File"), defaultDir, tr("Text Files (*.txt)"));

    if(filePath != "")
    {
        QFile file(filePath);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //Create/Open file
        {
            //Will probably add default text for these files
            file.close();
            qDebug() << "Successfully wrote flashcard set to " << filePath;
        }
    }

    //Refresh
    RefreshFlashcardSetList();
}









