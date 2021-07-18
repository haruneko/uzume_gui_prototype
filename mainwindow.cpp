#include <QFileDialog>
#include <QMessageBox>
#include <data/Waveform.hpp>
#include <spectrogram/WaveformSpectrogram.hpp>

#include "domain/usecases/EditVoice.hpp"
#include "models/Contour.hpp"
#include "views/ContourWidget.hpp"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , editor(new EditVoice())
{
    ui->setupUi(this);
    connect(this->ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(this->ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete editor;
}

void MainWindow::openFile()
{
    // ファイル名取ってくるロジックをストラテジで読み込んだほうが良いがサボってこう書いちゃう。
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open wave file."), QString(), tr("Wave file (*.wav)"));
    if(fileName.isNull()) {
        return;
    }

    if(!editor->initWith(fileName.toLocal8Bit())) {
        QMessageBox::critical(this, tr("Error"), tr("Could not read wave file."));
        return;
    }

    delete this->ui->centralwidget;
    this->ui->centralwidget = new ContourWidget(
            new SpectrogramF0Contour(editor->waveformSpectrogram()),
            ContourWidgetStyle(660, 220, 0, editor->waveformSpectrogram()->msLength() /1000.0, ContourWidgetStyle::ValueType::LOGARITHMIC),
            this);
    this->setCentralWidget(this->ui->centralwidget);
    this->setWindowTitle(fileName);
}

void MainWindow::saveFile() {
    // ファイル名取ってくるロジックをストラテジで読み込んだほうが良いがサボってこう書いちゃう。
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save wave file."), QString(), tr("Wave file (*.wav)"));
    if(fileName.isNull()) {
        return;
    }

    if(!editor->synthesize(fileName.toLocal8Bit())) {
        QMessageBox::critical(this, tr("Error"), tr("Could not synthesize wave file."));
        return;
    }
}
