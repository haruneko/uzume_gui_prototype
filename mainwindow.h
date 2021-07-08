#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace uzume { namespace vocoder { class WaveformSpectrogram; } }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public Q_SLOT:
    void openFile();

private:
    Ui::MainWindow *ui;
    uzume::vocoder::WaveformSpectrogram *waveformSpectrogram;
};
#endif // MAINWINDOW_H
