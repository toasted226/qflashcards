#include "tester.h"
#include "ui_tester.h"

FlashcardSet* testSet;
bool m_Randomised;
bool m_RepeatUntilCorrect;
int m_LanguageOrder;

Tester::Tester(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tester)
{
    ui->setupUi(this);
}

Tester::~Tester()
{
    delete ui;
}

void Tester::getFlashcardSet(FlashcardSet* flashcardSet)
{
    testSet = flashcardSet;
}

void Tester::getTestSettings(bool randomised, bool repeatUntilCorrect, int languageOrder)
{
    m_Randomised = randomised;
    m_RepeatUntilCorrect = repeatUntilCorrect;
    m_LanguageOrder = languageOrder;
}
