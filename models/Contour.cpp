// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <Spectrogram.hpp>
#include <data/Waveform.hpp>

#include "Contour.hpp"

double SpectrogramF0Contour::msLength() const {
    return this->spectrogram->msLength();
}

double SpectrogramF0Contour::at(double ms) const {
    return this->spectrogram->f0At(ms);
}

double WaveformDynamicsContour::msLength() const {
    return this->waveform->msLength();
}

double WaveformDynamicsContour::at(double ms) const {
    int beginIndex = (int)((ms - msFramePeriod / 2.0) / 1000.0 * waveform->samplingFrequency);
    int endIndex = (int)((ms - msFramePeriod / 2.0) / 1000.0 * waveform->samplingFrequency);
    beginIndex = beginIndex < 0 ? 0 : beginIndex;
    endIndex = endIndex >= waveform->length - 1 ? waveform->length - 1 : endIndex;
    double ret = 0.0;
    int length = endIndex - beginIndex;
    for(int i = beginIndex; i < endIndex; i++) {
        double v = waveform->data[i];
        ret += v * v;
    }
    return ret / (length == 0 ? 1.0 : (double)length);
}
