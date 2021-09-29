#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <QMainWindow>

class Flashcard
{
private:
    QString m_Base;
    QString m_Translation;

public:
    Flashcard(QString base, QString translation);
    Flashcard();

    QString GetBase();
    QString GetTranslation();
};

class FlashcardSet
{
private:
    QString m_Name;
    QString m_Filepath;

public:
    FlashcardSet(QString name, QString filepath);
    FlashcardSet();

    QString GetName();
    QString GetFilepath();
};

#endif // FLASHCARD_H
