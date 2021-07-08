// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <Spectrogram.hpp>

#include "Contour.hpp"

double SpectrogramF0Contour::msLength() const {
    return this->spectrogram->msLength();
}

double SpectrogramF0Contour::at(double ms) const {
    return this->spectrogram->f0At(ms);
}
