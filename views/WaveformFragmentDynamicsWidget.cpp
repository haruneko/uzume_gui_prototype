// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include "WaveformFragmentDynamicsWidget.hpp"

#include <data/Waveform.hpp>
#include <QPaintEvent>
#include <QPainter>

WaveformFragmentDynamicsWidget::WaveformFragmentDynamicsWidget(
        const WaveformFragment &fragment,
        const uzume::vocoder::Waveform *waveform,
        QWidget *parent)
        : fragment(fragment), waveform(waveform), QWidget(parent) {
}

void WaveformFragmentDynamicsWidget::paintEvent(QPaintEvent *e) {
    QPainter p(this);
    p.setPen(palette().color(QPalette::Shadow));
    for(int x = e->rect().left(); x < e->rect().right(); x++) {
        double msBegin = msAt(x);
        double msEnd = msAt(x + 1);
        double max = waveform->maxAbsoluteValueBetween(msBegin, msEnd);
        int y1 = (int) ((double) height() * (1.0 - max)) / 2;
        int y2 = height() - y1;
        p.drawLine(x, y1, x, y2);
    }

    p.setPen(palette().color(QPalette::Dark));
    for(int x = e->rect().left(); x < e->rect().right(); x++) {
        double msBegin = msAt(x);
        double msEnd = msAt(x + 1);
        double rms = waveform->rootMeanSquareBetween(msBegin, msEnd);
        int y1 = (int)((double)height() * (1.0 - rms)) / 2;
        int y2 = height() - y1;
        p.drawLine(x, y1, x, y2);
    }
}

double WaveformFragmentDynamicsWidget::msAt(int x) const {
    return fragment.msLeft + (double)x / (double)width() * (fragment.msRight - fragment.msLeft);
}
