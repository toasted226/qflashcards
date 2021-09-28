#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flashcard.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    std::vector<FlashcardSet> flashcardSets; //Our internal list of flashcard sets, stores names and paths

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void OnLoad();
    void RefreshFlashcardSetList();

private slots:
    void on_actionAdd_Flashcards_triggered();

    void on_actionNew_Flashcard_Set_triggered();

    void on_actionRemove_Flashcard_Set_triggered();

signals:
    void setEditFlashcardSet(FlashcardSet* flashcardSet);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
