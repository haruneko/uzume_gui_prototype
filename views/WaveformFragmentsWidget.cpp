// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <QCursor>
#include <QLayout>
#include <QMouseEvent>

#include "../domain/entities/WaveformFragments.hpp"
#include "WaveformFragmentsWidget.hpp"

WaveformFragmentsWidget::WaveformFragmentsWidget(double msLength, QWidget *parent)
        : QSplitter(parent), msLength(msLength) {
}

void WaveformFragmentsWidget::onWaveformFragmentsUpdated(const WaveformFragments *fragments) {
    if(fragments == nullptr) {
        return;
    }
    for(int i = 0; i < this->count(); i++) {
        this->widget(i)->deleteLater();
    }

    int index = 0;
    int previousX = 0;
    double currentMs = 0.0;
    for(auto d: fragments->data()) {
        currentMs += d.msLength;
        int x = xAt(currentMs);
        auto w = new QWidget(this);
        w->setMinimumWidth(x - previousX);
        w->setMinimumHeight(32);
        w->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        QPalette pBackground = this->palette();
        pBackground.setColor(QPalette::Window, QColor(index * 30, 0, 0));
        w->setPalette(pBackground);
        w->setAutoFillBackground(true);
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
