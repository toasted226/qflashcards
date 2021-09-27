#ifndef FLASHCARD_H
#define FLASHCARD_H

#include <QMainWindow>

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
