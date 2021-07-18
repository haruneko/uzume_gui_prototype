// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENTS_HPP__
#define __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENTS_HPP__

#include <list>

class WaveformFragment final {
public:
    WaveformFragment() = default;
    WaveformFragment(double msLeft, double msRight, double msLength) :
            msLeft(msLeft), msRight(msRight), msLength(msLength) {
    }

    double msLeft;
    double msRight;
    double msLength;
};

class WaveformFragments final {
public:
    WaveformFragments(double msLength);

    int indexAt(double ms) const;

    bool extend(int index, double ms);
    bool divideAt(double ms);
    bool mergeToPrevious(int index);

    void flush(double msLength);
    double msLength() const;

    const std::list<WaveformFragment> &data() const { return fragments; }
private:
    std::list<WaveformFragment> fragments;
};

#endif // __UZUME_GUI_PROTOTYPE_WAVEFORM_FRAGMENTS_HPP__
