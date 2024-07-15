#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SeleccionYLikes.h"
#include <QMessageBox>
#include <QStringListModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , database(MovieDatabase::getInstance())
{
    ui->setupUi(this);
    database->loadMovies("mpst_full_data.csv");

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::on_tabWidget_currentChanged);
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
