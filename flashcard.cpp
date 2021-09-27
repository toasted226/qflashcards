#include "flashcard.h"

FlashcardSet::FlashcardSet(QString name, QString filepath)
    :m_Name(name), m_Filepath(filepath)
{}

FlashcardSet::FlashcardSet()
    :m_Name(""), m_Filepath("")
{}

QString FlashcardSet::GetName()
{
    return FlashcardSet::m_Name;
}

QString FlashcardSet::GetFilepath()
{
    return FlashcardSet::m_Filepath;
}
