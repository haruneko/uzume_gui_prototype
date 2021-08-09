// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENT_DYNAMICS_WIDGET_HPP__
#define __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENT_DYNAMICS_WIDGET_HPP__

#include <QWidget>
#include "domain/entities/WaveformFragments.hpp"

namespace uzume { namespace vocoder {
class Waveform;
} }

class WaveformFragmentDynamicsWidget : public QWidget {
    Q_OBJECT
public:
    WaveformFragmentDynamicsWidget(const WaveformFragment &fragment, const uzume::vocoder::Waveform *waveform, QWidget *parent);

    void paintEvent(QPaintEvent *e) override;

private:
    double msAt(int x) const;

    WaveformFragment fragment;
    const uzume::vocoder::Waveform *waveform;
};

#endif // __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENT_DYNAMICS_WIDGET_HPP__
