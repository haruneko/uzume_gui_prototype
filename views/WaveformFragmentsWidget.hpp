// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENTS_WIDGET_HPP__
#define __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENTS_WIDGET_HPP__

#include <QSplitter>

class WaveformFragment;
class WaveformFragments;

class WaveformFragmentWidget final : public QWidget {
    Q_OBJECT
public:
    WaveformFragmentWidget() = delete;
    explicit WaveformFragmentWidget(const WaveformFragment *fragment, QWidget *parent) : QWidget(parent) { }
};

class WaveformFragmentsWidget : public QSplitter {
    Q_OBJECT
public:
    WaveformFragmentsWidget() = delete;
    explicit WaveformFragmentsWidget(double msLength, QWidget *parent);
    ~WaveformFragmentsWidget() noexcept override = default;
public slots:
    void onWaveformFragmentsUpdated(const WaveformFragments *fragments);

signals:
    void waveformFragmentsDividedAt(double ms);
    void waveformFragmentExtended(int index, double ms);
    void waveformFragmentMergedToPrevious(int index);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    double msAt(int x) const;
    int xAt(double ms) const;

    double msLength;
};

#endif // __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENTS_WIDGET_HPP__