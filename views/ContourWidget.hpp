// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __CONTOUR_WIDGET_HPP__
#define __CONTOUR_WIDGET_HPP__

#include <QWidget>

class Contour;

class ContourWidgetStyle final {
public:
    enum ValueType {
        LINEAR,
        LOGARITHMIC
    };

    ContourWidgetStyle(const double topValue,
                       const double bottomValue,
                       const double leftTime,
                       const double rightTime,
                       const ValueType valueType,
                       const QColor &color = QColorConstants::Black,
                       const QColor &bgColor = QColorConstants::White) :
        topValue(topValue),
        bottomValue(bottomValue),
        leftTime(leftTime),
        rightTime(rightTime),
        valueType(valueType),
        color(color),
        bgColor(bgColor) {
    }
    ContourWidgetStyle(const ContourWidgetStyle &other) = default;

    const double topValue;
    const double bottomValue;
    const double leftTime;
    const double rightTime;
    const ValueType valueType;
    const QColor color;
    const QColor bgColor;
};

class ContourWidget : public QWidget {
    Q_OBJECT
public:
    ContourWidget() = delete;
    ContourWidget(const Contour *contour, const ContourWidgetStyle &contourWidgetStyle, QWidget *parent);
    ~ContourWidget() noexcept;

public slots:
    void update(Contour const *contour, const ContourWidgetStyle &contourWidgetStyle);

signals:
    void onUpdated(Contour const *contour, const ContourWidgetStyle &contourWidgetStyle);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Contour const *contour;
    ContourWidgetStyle const *contourWidgetStyle;

    double secondsAt(int x) const;
    double yAt(double value) const;
};

#endif // __CONTOUR_WIDGET_HPP__
