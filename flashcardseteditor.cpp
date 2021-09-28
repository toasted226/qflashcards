#include "flashcardseteditor.h"
#include "ui_flashcardseteditor.h"
#include "mainwindow.h"

#include <QFile>
#include <QMessageBox>

FlashcardSet* editFlashcardSet;

FlashcardSetEditor::FlashcardSetEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlashcardSetEditor)
{
    ui->setupUi(this);
}

FlashcardSetEditor::~FlashcardSetEditor()
{
    delete ui;
}

void FlashcardSetEditor::ReadFlashcards()
{
    QFile file = QFile(editFlashcardSet->GetFilepath());
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    QTextStream stream = QTextStream(&file);
    while(!stream.atEnd())
    {
        QString line = stream.readLine();
        ui->toBeAddedList->addItem(line);
    }
    qDebug() << "Read flashcard lines to set";
}

void FlashcardSetEditor::setEditFlashcardSet(FlashcardSet* flashcardSet)
{
    //Taking in a pointer to avoid copying

    QString name = flashcardSet->GetName();
    name[0] = name[0].toUpper();

    ui->setTitle->setText(name); //Set display name
    editFlashcardSet = flashcardSet;

    ReadFlashcards();
}

void FlashcardSetEditor::on_addButton_clicked()
{
    //Get inputs
    QString input = ui->inputText->text();
    QString translation = ui->translationText->text();

    //Ensure the input is valid before adding it to the list
    if(!(input.contains(':') || translation.contains(':')))
    {
        QString flashcard = input + ":" + translation;
        ui->toBeAddedList->addItem(flashcard);
    }
}

void FlashcardSetEditor::on_cancelButton_clicked()
{
    //Display a message to let the user know that nothing happened
    QMessageBox msgBox;
    msgBox.setText("Editing cancelled. No changes have been made.");
    msgBox.exec();

    this->close();
}

void FlashcardSetEditor::on_removeButton_clicked()
{
    //Get selected items
    QList<QListWidgetItem*> items = ui->toBeAddedList->selectedItems();

    //Remove each item:
    //Calling the Remove method doesn't actually clear memory or update the list for
    //some reason, so I've resorted to manually getting the item and deleting it.
    foreach(QListWidgetItem* item, items)
    {
        delete ui->toBeAddedList->takeItem(ui->toBeAddedList->row(item));
    }
}

void FlashcardSetEditor::on_finishButton_clicked()
{
    if(ui->toBeAddedList->count() > 0)
    {
        //Open the flashcard set file
        QFile file(editFlashcardSet->GetFilepath());
        if(file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        {
            QTextStream stream = QTextStream(&file); //Create text stream

            //Write each item to the file
            for(int i = 0; i < ui->toBeAddedList->count(); i++)
            {
                stream << ui->toBeAddedList->item(i)->text() << "\n";
            }
            qDebug() << "Wrote items to flashcard set";

            file.close(); //Close the file
        }

        //Display a message to assure the user that the process was successful
        QMessageBox msgBox;
        msgBox.setText("The " + editFlashcardSet->GetName() + " flashcard set has been successfully modified.");
        msgBox.exec();
    }
    else
    {
        //Display a message to let the user know that nothing happened
        QMessageBox msgBox;
        msgBox.setText("No changes have been made.");
        msgBox.exec();
    }

    this->close();
}
