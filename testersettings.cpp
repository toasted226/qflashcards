#include "testersettings.h"
#include "ui_testersettings.h"
#include "tester.h"

FlashcardSet* settingsFlashcardSet;

TesterSettings::TesterSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TesterSettings)
{
    ui->setupUi(this);
}

TesterSettings::~TesterSettings()
{
    delete ui;
}

void TesterSettings::getFlashcardSet(FlashcardSet* flashcardSet)
{
    //Set up translationRule dropdown
    ui->translationRule->setItemText(0, "Randomised");
    ui->translationRule->setItemText(1, "From " + flashcardSet->GetName());
    ui->translationRule->setItemText(2, "To " + flashcardSet->GetName());

    settingsFlashcardSet = flashcardSet;
}

void TesterSettings::on_startTest_clicked()
{
    Tester* tester = new Tester(); //Heap allocation of Tester

    //Connect signals and slots
    connect(this, &TesterSettings::setFlashcardSet, tester, &Tester::getFlashcardSet);
    connect(this, &TesterSettings::setTestSettings, tester, &Tester::getTestSettings);

    //Pass FlashcardSet pointer to Tester
    emit setFlashcardSet(settingsFlashcardSet);
    //Pass settings to Tester
    emit setTestSettings(ui->randomised->isChecked(),
                         ui->repeatUntilCorrect->isChecked(),
                         ui->translationRule->currentIndex());

    //Set window modality, disallowing interactability on parent
    tester->setWindowModality(Qt::ApplicationModal);

    tester->show(); //Open up Tester, memory freed on window close
    this->close(); //Close this window
}
