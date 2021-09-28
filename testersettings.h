#ifndef TESTERSETTINGS_H
#define TESTERSETTINGS_H

#include <QDialog>
#include "flashcard.h"

namespace Ui {
class TesterSettings;
}

class TesterSettings : public QDialog
{
    Q_OBJECT

public:
    explicit TesterSettings(QWidget *parent = nullptr);
    ~TesterSettings();

private:
    Ui::TesterSettings *ui;

public slots:
    void getFlashcardSet(FlashcardSet* flashcardSet);
private slots:
    void on_startTest_clicked();

signals:
    void setFlashcardSet(FlashcardSet* flashcardSet);
    void setTestSettings(bool randomised, bool repeatUntilCorrect, int languageOrder);
};

#endif // TESTERSETTINGS_H
