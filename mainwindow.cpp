#include <QFileDialog>
#include <data/Waveform.hpp>
#include <spectrogram/WaveformSpectrogram.hpp>
#include <views/ContourWidget.hpp>
#include <views/Contour.hpp>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , waveformSpectrogram(nullptr)
{
    ui->setupUi(this);
    connect(this->ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete waveformSpectrogram;
}

void MainWindow::openFile()
{
    // ファイル名取ってくるロジックをストラテジで読み込んだほうが良いがサボってこう書いちゃう。
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open wave file."), QString(), tr("Wave file (*.wav)"));
    if(fileName.isNull()) {
        return;
    }
    this->setWindowTitle(fileName);

    // 直接 Waveform 作ってしまうとテストできないので本当は良くないがファクトリ用意するのをサボってこう書いちゃう。
    auto waveform = uzume::vocoder::Waveform::read(fileName.toLocal8Bit().data());
    if(waveform->length == 0) {
        delete waveform;
        return;
    }
    delete waveformSpectrogram;
    waveformSpectrogram = new uzume::vocoder::WaveformSpectrogram(waveform);

    delete this->ui->centralwidget;
    this->ui->centralwidget = new ContourWidget(
            new SpectrogramF0Contour(waveformSpectrogram),
            ContourWidgetStyle(660, 220, 0, waveformSpectrogram->msLength() /1000.0, ContourWidgetStyle::ValueType::LOGARITHMIC),
            this);
    this->setCentralWidget(this->ui->centralwidget);
}
