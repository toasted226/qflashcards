#include "flashcard.h"
#include <QDebug>

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

Flashcard::Flashcard(QString base, QString translation)
    :m_Base(base), m_Translation(translation)
{}

Flashcard::Flashcard()
    :m_Base(""), m_Translation("")
{}

QString Flashcard::GetBase()
{
    return Flashcard::m_Base;
}

QString Flashcard::GetTranslation()
{
    return Flashcard::m_Translation;
}
