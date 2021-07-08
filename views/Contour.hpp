// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __UZUME_PROTOTYPE_CONTOUR_HPP__
#define __UZUME_PROTOTYPE_CONTOUR_HPP__

namespace uzume { namespace vocoder { class Spectrogram; } }

class Contour {
public:
    Contour() = default;
    virtual ~Contour() = default;

    virtual double msLength() const = 0;
    virtual double at(double ms) const = 0;
};

class SpectrogramF0Contour final : public Contour {
public:
    SpectrogramF0Contour() = delete;
    explicit SpectrogramF0Contour(const uzume::vocoder::Spectrogram *spectrogram) :
        spectrogram(spectrogram) {
    }

    double msLength() const final;
    double at(double ms) const final;

private:
    const uzume::vocoder::Spectrogram *spectrogram{};
};

#endif // __UZUME_PROTOTYPE_CONTOUR_HPP__
