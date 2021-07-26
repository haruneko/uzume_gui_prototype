#include <QColor>
#include <QFileDialog>
#include <QMessageBox>
#include <data/Waveform.hpp>
#include <spectrogram/WaveformSpectrogram.hpp>

#include "domain/entities/WaveformFragments.hpp"
#include "domain/usecases/EditVoice.hpp"
#include "views/WaveformFragmentsWidget.hpp"

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , editor(new EditVoice(this))
{
    ui->setupUi(this);
    connect(this->ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(this->ui->actionSave, &QAction::triggered, this, &MainWindow::saveFile);
    this->ui->centralwidget->show();
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

    if(this->ui->centralwidget->widget() != nullptr) {
        this->ui->centralwidget->widget()->deleteLater();
    }

    auto wfw = new WaveformFragmentsWidget(editor->waveformFragments()->msLength(), this);
    wfw->setMinimumWidth(640);
    auto p = wfw->palette();
    p.setColor(QPalette::Window, QColor(0, 30, 30));
    wfw->setPalette(p);
    this->ui->centralwidget->setWidget(wfw);

    connect(wfw, &WaveformFragmentsWidget::waveformFragmentsDividedAt, editor, &EditVoice::divideAt);
    connect(wfw, &WaveformFragmentsWidget::waveformFragmentExtended, editor, &EditVoice::extend);
    connect(wfw, &WaveformFragmentsWidget::waveformFragmentMergedToPrevious, editor, &EditVoice::mergeToPrevious);
    connect(editor, &EditVoice::fragmentChanged, wfw, &WaveformFragmentsWidget::onWaveformFragmentsUpdated);

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
