#ifndef TESTER_H
#define TESTER_H

#include <QDialog>
#include "flashcard.h"

namespace Ui {
class Tester;
}

class Tester : public QDialog
{
    Q_OBJECT

public:
    explicit Tester(QWidget *parent = nullptr);
    ~Tester();

    void StartTest();
    Flashcard GetNextFlashcard();
    void SetValues(Flashcard flashcard);
    bool CheckAnswer();
    QList<Flashcard> GetFlashcards(FlashcardSet flashcardSet);

public slots:
    void getFlashcardSet(FlashcardSet* flashcardSet);
    void getTestSettings(bool randomised, bool repeatUntilCorrect, int languageOrder);

private slots:
    void on_nextButton_clicked();

    void on_checkButton_clicked();

private:
    Ui::Tester *ui;
};

#endif // TESTER_H
