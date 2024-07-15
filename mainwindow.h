#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MovieDatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();
    void on_tabWidget_currentChanged(int index);
    void handleMovieClick(const QModelIndex &index);
    void displayMovieDetails(const Movie& movie);
    void handleLikeButtonClick();
    void handleWatchLaterButtonClick();

private:
    Ui::MainWindow *ui;
    MovieDatabase* database;
    std::optional<Movie> currentMovie;
};

#endif // MAINWINDOW_H
