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

public slots:
    void getFlashcardSet(FlashcardSet* flashcardSet);
    void getTestSettings(bool randomised, bool repeatUntilCorrect, int languageOrder);

private:
    Ui::Tester *ui;
};

#endif // TESTER_H
