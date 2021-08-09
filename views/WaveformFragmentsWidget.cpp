// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <QCursor>
#include <QLayout>
#include <QMouseEvent>
#include <data/Waveform.hpp>

#include "../domain/entities/WaveformFragments.hpp"
#include "WaveformFragmentsWidget.hpp"
#include "WaveformFragmentDynamicsWidget.hpp"

WaveformFragmentsWidget::WaveformFragmentsWidget(const uzume::vocoder::Waveform *waveform,
                                                 double msLength,
                                                 QWidget *parent)
        : QSplitter(parent), waveform(waveform), msLength(msLength) {
}

void WaveformFragmentsWidget::onWaveformFragmentsUpdated(const WaveformFragments *fragments) {
    if(fragments == nullptr) {
        return;
    }
    for(int i = 0; i < this->count(); i++) {
        this->widget(i)->deleteLater();
    }
    msLength = fragments->msLength();

    int index = 0;
    int previousX = 0;
    double currentMs = 0.0;
    for(auto d: fragments->data()) {
        currentMs += d.msLength;
        int x = xAt(currentMs);
        auto w = new WaveformFragmentDynamicsWidget(d, waveform, this);
        w->setMinimumWidth(x - previousX);
        w->setMinimumHeight(32);
        w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        this->addWidget(w);

        previousX = x;
        index++;
    }
}

void WaveformFragmentsWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    emit(this->waveformFragmentsDividedAt(msAt(event->x())));
}

double WaveformFragmentsWidget::msAt(int x) const {
    return (double)x / (double)this->width() * msLength;
}

int WaveformFragmentsWidget::xAt(double ms) const {
    return (int)(ms / msLength * this->width());
}
