#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "flashcardseteditor.h"
#include <QStandardPaths>
#include <QDir>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

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

void MainWindow::on_actionAdd_Flashcards_triggered()
{
    //Allocate space for Flashcard Set Editor on the heap
    FlashcardSetEditor* flashcardSetEditor = new FlashcardSetEditor();

    //Connect signals and slots
    connect(this, &MainWindow::setEditFlashcardSet,
            flashcardSetEditor, &FlashcardSetEditor::setEditFlashcardSet);

    //Emit signal to pass pointer to the selected FlashcardSet to the Flashcart Set Editor
    int index = ui->flashcardSetsList->currentRow();
    emit setEditFlashcardSet(&flashcardSets[index]);

    //Change modality of the new window, this prevents the parent from being interactable
    flashcardSetEditor->setWindowModality(Qt::ApplicationModal);

    //Open up the Flashcart Set Editor
    flashcardSetEditor->show();

    //The allocated memory will be cleared when the window is closed
}


void MainWindow::on_actionNew_Flashcard_Set_triggered()
{
    //Get config location that we've set up in main.cpp
    QDir directory(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation));
    QString filePath = directory.absolutePath();

    //Open an input dialog to prompt user to save a new flashcard set
    bool ok;
    QString filename = QInputDialog::getText(this, tr("Flashcard Set Creator"),
                                             tr("Flashcard Set Name:"), QLineEdit::Normal,
                                             "Example: Spanish", &ok);
    if(ok)
    {
        //Ensure the filename is valid
        if(!(filename == "" || filename.contains(QRegularExpression("^[.,/\()]")) || filename.toLower() == "con"))
        {
            QFile file(filePath + "/" + filename + ".txt");
            if(file.open(QIODevice::WriteOnly | QIODevice::Text)) //Create/Open file
            {
                file.close();
                qDebug() << "Successfully wrote flashcard set to " << filePath;
            }
        }
        else
        {
            if(filename.toLower() != "con")
            {
                //Tell the user that the entry contains invalid characters
                QMessageBox msgBox;
                msgBox.setText("Flashcard Set name cannot be empty or contain .,/\()");
                msgBox.exec();
            }
            else
            {
                //Tell the user that the file cannot be named CON, because Windows doesn't allow it

                //Linux and Mac users are able to do this, so this should be changed to disallow the
                //user only if they're on Windows

                QMessageBox msgBox;
                msgBox.setText("For Windows reasons, the Flashcard Set cannot be named CON.");
                msgBox.exec();
            }
        }
    }

    //Refresh
    RefreshFlashcardSetList();
}

void MainWindow::on_actionRemove_Flashcard_Set_triggered()
{
    int index = ui->flashcardSetsList->currentRow(); //Get selected flashcard set
    QString filepath = flashcardSets[index].GetFilepath(); //Get filepath of set

    //Ask user for confirmation to delete the file
    QMessageBox::StandardButton confirmation;
    confirmation = QMessageBox::question(this, "Flashcard Set",
                                  "Remove " + flashcardSets[index].GetName() + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if(confirmation == QMessageBox::Yes)
    {
        QFile file = QFile(filepath);
        if(!file.remove()) //Delete file
        {
            qDebug() << "Failed to delete file at " + filepath;
        }

        //Let user know that the file has been deleted
        QMessageBox msgBox;
        msgBox.setText(flashcardSets[index].GetName() + " has been deleted.");
        msgBox.exec();
    }

    //Refresh
    RefreshFlashcardSetList();
}
