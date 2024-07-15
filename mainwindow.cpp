#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SeleccionYLikes.h"
#include <QMessageBox>
#include <QStringListModel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(MovieDatabase::getInstance())
{
    ui->setupUi(this);
    database->loadMovies("mpst_full_data.csv");

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);
    connect(ui->resultsListView, &QListView::clicked, this, &MainWindow::handleMovieClick);
    connect(ui->likeBtn, &QPushButton::clicked, this, &MainWindow::handleLikeButtonClick);
    connect(ui->watchLaterBtn, &QPushButton::clicked, this, &MainWindow::handleWatchLaterButtonClick);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete database;
}

void MainWindow::on_searchButton_clicked()
{
    QString keyword = ui->searchLineEdit->text();
    std::vector<Movie> results = database->search(keyword.toStdString());

    if (results.empty()) {
        QMessageBox::information(this, "Resultados", "No se encontraron resultados.");
    } else {
        QStringList resultList;
        for (const auto& movie : results) {
            resultList << QString::fromStdString(movie.title);
        }
        ui->resultsListView->setModel(new QStringListModel(resultList));
    }
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    // Verifica si la pestaña "Liked" está activa
    if (index == ui->tabWidget->indexOf(ui->Liked)) {
        // Cargar y mostrar las películas liked
        std::vector<Movie> likedMovies = database->getLikedMovies();
        QStringList likedList;
        for (const auto& movie : likedMovies) {
            likedList << QString::fromStdString(movie.title);
        }
        ui->likedListView->setModel(new QStringListModel(likedList));
    } else if (index == ui->tabWidget->indexOf(ui->WatchLater)) {
        // Cargar y mostrar las películas watch later
        std::vector<Movie> watchLaterMovies = database->getWatchLaterMovies();
        QStringList watchLaterList;
        for (const auto& movie : watchLaterMovies) {
            watchLaterList << QString::fromStdString(movie.title);
        }
        ui->watchLaterListView->setModel(new QStringListModel(watchLaterList));
    } else {
        // Limpiar los modelos de las listas liked y watch later
        ui->likedListView->setModel(new QStringListModel());
        ui->watchLaterListView->setModel(new QStringListModel());
    }
}

void MainWindow::displayMovieDetails(const Movie& movie) {
    QStringList details;
    details << "IMDB ID: " + QString::fromStdString(movie.imdb_id)
            << "Title: " + QString::fromStdString(movie.title)
            << "Plot Synopsis: " + QString::fromStdString(movie.plot_synopsis)
            << "Tags: " + QString::fromStdString(movie.tags)
            << "Split: " + QString::fromStdString(movie.split)
            << "Synopsis Source: " + QString::fromStdString(movie.synopsis_source);

    ui->infoListView->setModel(new QStringListModel(details));
}

void MainWindow::handleMovieClick(const QModelIndex &index) {
    QString movieTitle = index.data(Qt::DisplayRole).toString();
    currentMovie = database->getMovieByTitle(movieTitle.toStdString());

    if (currentMovie) {
        QStringList movieDetails;
        movieDetails << "IMDB ID: " + QString::fromStdString(currentMovie->imdb_id);
        movieDetails << "Title: " + QString::fromStdString(currentMovie->title);
        movieDetails << "Plot Synopsis: " + QString::fromStdString(currentMovie->plot_synopsis);
        movieDetails << "Tags: " + QString::fromStdString(currentMovie->tags);
        movieDetails << "Split: " + QString::fromStdString(currentMovie->split);
        movieDetails << "Synopsis Source: " + QString::fromStdString(currentMovie->synopsis_source);
        ui->infoListView->setModel(new QStringListModel(movieDetails));
    } else {
        QMessageBox::critical(this, "Error", "No se pudo encontrar la película seleccionada.");
    }
}

void MainWindow::handleLikeButtonClick()
{
    if (currentMovie) {
        database->markAsLiked(currentMovie->imdb_id);
        QMessageBox::information(this, "Liked", "La película ha sido marcada como 'liked'.");
    } else {
        QMessageBox::critical(this, "Error", "No hay ninguna película seleccionada.");
    }
}

void MainWindow::handleWatchLaterButtonClick()
{
    if (currentMovie) {
        database->markAsWatchLater(currentMovie->imdb_id);
        QMessageBox::information(this, "Watch Later", "La película ha sido marcada para 'ver más tarde'.");
    } else {
        QMessageBox::critical(this, "Error", "No hay ninguna película seleccionada.");
    }
}
