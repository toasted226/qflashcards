#include "tester.h"
#include "ui_tester.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFile>

FlashcardSet* testSet;
bool m_Randomised;
bool m_RepeatUntilCorrect;
int m_LanguageOrder;
QList<Flashcard> flashcards;

Flashcard currentFlashcard;
QString correctAnswer;
QList<Flashcard> incorrect;

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
    //Set FlashcardSet for testing
    testSet = flashcardSet;
}

void Tester::getTestSettings(bool randomised, bool repeatUntilCorrect, int languageOrder)
{
    //Apply all settings
    m_Randomised = randomised;
    m_RepeatUntilCorrect = repeatUntilCorrect;
    m_LanguageOrder = languageOrder;

    if(testSet != nullptr)
    {
        //Change the text in the Window Title
        this->setWindowTitle(testSet->GetName() + " Test");
    }

    //Start the test
    StartTest();
}

void Tester::StartTest()
{
    //Initialise correct answer text
    ui->correctAnswer->setText("");

    if(testSet != nullptr)
    {
        flashcards = GetFlashcards(*testSet); //Read flashcards from set

        if(flashcards.count() == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("There are no flashcards in this set. Please add flashcards"
                           " to the set by going to Edit > Edit Flashcard Set.");
            msgBox.exec();
            this->close();
        }
        else
        {
            currentFlashcard = GetNextFlashcard(); //Get values for first flashcard

            SetValues(currentFlashcard); //Set display values for flashcard
        }
    }
}

QList<Flashcard> Tester::GetFlashcards(FlashcardSet flashcardSet)
{
    QList<Flashcard> flashcards;

    QFile file(flashcardSet.GetFilepath());
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream = QTextStream(&file);
        while(!stream.atEnd())
        {
            //Read line to std::string, so we can use the std find function
            std::string line = stream.readLine().toStdString();

            //Get the base word(s) as a QString
            QString base = QString::fromStdString(line.substr(0, line.find(':')));
            //Get the translation as a QString
            QString translation = QString::fromStdString(line.substr(line.find(':') + 1, line.length()));

            //Add the Flashcard to the flashcards list
            flashcards.append(Flashcard(base, translation));
        }
    }

    return flashcards;
}

Flashcard Tester::GetNextFlashcard()
{
    Flashcard flashcard;

    //Check if the user chose the randomised option
    if(m_Randomised)
    {
        //Choose a random flashcard to use
        int c = QRandomGenerator::global()->bounded(0, flashcards.length());
        flashcard = flashcards[c];
        flashcards.removeAt(c); //Remove it from the list of flashcards
    }
    else
    {
        //Use the first flashcard and remove it from the list
        flashcard = flashcards[0];
        flashcards.removeFirst();
    }

    ui->answerBox->setText(""); //Clear the answer box

    return flashcard;
}

void Tester::SetValues(Flashcard flashcard)
{
    QString question;
    QString answer;

    if(m_LanguageOrder == 0) //Randomised (Either from or to the language the user chose)
    {
        int c = QRandomGenerator::global()->bounded(0, 2);
        if(c == 0) //To
        {
            question = flashcard.GetBase();
            answer = flashcard.GetTranslation();
        }
        else //From
        {
            question = flashcard.GetTranslation();
            answer = flashcard.GetBase();
        }
    }
    else if(m_LanguageOrder == 1) //From the language the user chose
    {
        question = flashcard.GetTranslation();
        answer = flashcard.GetBase();
    }
    else //To the language the user chose
    {
        question = flashcard.GetBase();
        answer = flashcard.GetTranslation();
    }

    //Display the question
    ui->question->setText(question);
    correctAnswer = answer; //Set the correct answer that the user must attempt to get
}

void Tester::on_nextButton_clicked()
{
    if(!CheckAnswer()) //Check if the user got the question wrong
    {
        //Inform the user that they got the question wrong, then show the correct answer
        QMessageBox msgBox;
        msgBox.setText("Incorrect. The correct translation is " + correctAnswer);
        msgBox.exec();

        //Add this flashcard to the list of flashcards the user got wrong
        incorrect.append(currentFlashcard);
    }

    if(flashcards.length() > 0) //The user is not at the last card
    {
        //Set up the next flashcard
        currentFlashcard = GetNextFlashcard();
        SetValues(currentFlashcard);
    }
    else //The user is on the last card
    {
        if(incorrect.length() > 0) //Check if the user got anything wrong
        {
            if(m_RepeatUntilCorrect) //Check if the user wants to retry flashcards they got wrong
            {
                //Add the flashcards the user got wrong to the list of flashcards to answer
                //so that the user can retry
                qDebug() << "Repeating incorrect questions";
                flashcards = incorrect;
                incorrect.clear();

                //Set up the next flashcard
                currentFlashcard = GetNextFlashcard();
                SetValues(currentFlashcard);
            }
            else
            {
                //Inform the user that they have finished testing
                QMessageBox msgBox;
                msgBox.setText("Testing finished!");
                msgBox.exec();
                this->close();
            }
        }
        else
        {
            //Inform the user that they have finished testing
            QMessageBox msgBox;
            msgBox.setText("Testing finished!");
            msgBox.exec();
            this->close();
        }
    }
}

void Tester::on_checkButton_clicked()
{
    if(CheckAnswer()) //The user got the question correct
    {
        //Display green text to inform the user that they're correct
        ui->correctAnswer->setText("Correct!");
    }
    else
    {
        //Inform the user that they got the question wrong, then show the correct answer
        QMessageBox msgBox;
        msgBox.setText("Incorrect. The correct translation is \"" + correctAnswer + "\".");
        msgBox.exec();
    }
}

bool Tester::CheckAnswer()
{
    //Get answer the user entered
    QString answer = ui->answerBox->text();

    //Check if the user's answer matches the given correct answer
    if(answer.toLower() == correctAnswer.toLower())
    {
        return true;
    }
    else
    {
        return false;
    }
}
