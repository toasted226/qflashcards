#ifndef FLASHCARDSETEDITOR_H
#define FLASHCARDSETEDITOR_H

#include <QDialog>
#include "flashcard.h"

namespace Ui {
class FlashcardSetEditor;
}

class FlashcardSetEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FlashcardSetEditor(QWidget *parent = nullptr);
    ~FlashcardSetEditor();

    void ReadFlashcards();

public slots:
    void setEditFlashcardSet(FlashcardSet* flashcardSet);

private slots:
    void on_addButton_clicked();

    void on_cancelButton_clicked();

    void on_removeButton_clicked();

    void on_finishButton_clicked();

private:
    Ui::FlashcardSetEditor *ui;
};

#endif // FLASHCARDSETEDITOR_H
