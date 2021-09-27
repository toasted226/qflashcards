#include "flashcard.h"

FlashcardSet::FlashcardSet(QString name, QString filepath)
    :m_Name(name), m_Filepath(filepath)
{}

QString FlashcardSet::GetName()
{
    return FlashcardSet::m_Name;
}

QString FlashcardSet::GetFilepath()
{
    return FlashcardSet::m_Filepath;
}


