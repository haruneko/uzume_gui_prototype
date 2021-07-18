// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <cmath>

#include <QPainter>
#include <QPaintEvent>

#include "domain/usecases/EditVoice.hpp"
#include "models/Contour.hpp"
#include "ContourWidget.hpp"

ContourWidget::ContourWidget(const Contour *contour, const ContourWidgetStyle &contourWidgetStyle, QWidget *parent)
    : contour(nullptr), contourWidgetStyle(nullptr), QWidget(parent) {
    update(contour, contourWidgetStyle);
    this->show();
}

ContourWidget::~ContourWidget() noexcept {
    delete this->contourWidgetStyle;
}

void ContourWidget::update(const Contour *contour, const ContourWidgetStyle &contourWidgetStyle) {
    delete this->contourWidgetStyle;
    this->contour = contour;
    this->contourWidgetStyle = new ContourWidgetStyle(contourWidgetStyle);
    emit onUpdated(this->contour, contourWidgetStyle);
}

void ContourWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    painter.fillRect(event->rect(), this->contourWidgetStyle->bgColor);
    painter.setBrush(this->contourWidgetStyle->color);
    for(int x = event->rect().left(); x <= event->rect().right(); x++) {
        double t1 = secondsAt(x);
        double t2 = secondsAt(x + 1);
        double y1 = yAt(contour->at(t1 * 1000.0));
        double y2 = yAt(contour->at(t2 * 1000.0));
        painter.drawLine(x, y1, x, y2);
    }
}

double ContourWidget::secondsAt(int x) const {
    return (double)x / (double)width() * (contourWidgetStyle->rightTime - contourWidgetStyle->leftTime) + contourWidgetStyle->leftTime;
}

double ContourWidget::yAt(double value) const {
    switch(contourWidgetStyle->valueType) {
        case ContourWidgetStyle::ValueType::LOGARITHMIC:
            {
                double top = log2(contourWidgetStyle->topValue);
                double bottom = log2(contourWidgetStyle->bottomValue);
                double logValue = log2(value + 0.00000001);
                return height() - (logValue - bottom) / (top - bottom) * height();
            }
        case ContourWidgetStyle::ValueType::LINEAR:
        default:
            return height() - (value - contourWidgetStyle->bottomValue) / (contourWidgetStyle->topValue - contourWidgetStyle->bottomValue) * height();
    }
}
