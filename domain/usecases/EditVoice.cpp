// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include <data/Waveform.hpp>
#include <data/LinearTimeAxisMap.hpp>
#include <spectrogram/ArraySpectrogramAggregator.hpp>
#include <spectrogram/StretchedPartialSpectrogram.hpp>
#include <spectrogram/WaveformSpectrogram.hpp>
#include <world/SynthesizeWaveformWithWORLD.hpp>
#include <vector>

#include "domain/entities/WaveformFragments.hpp"
#include "EditVoice.hpp"

using namespace uzume::vocoder;
using namespace uzume::vocoder::world;

EditVoice::EditVoice(QObject *parent)
        : QObject(parent), _waveform(nullptr), fragments(nullptr), spectrogram(nullptr) {
}

EditVoice::~EditVoice() {
    delete _waveform;
    delete fragments;
    delete spectrogram;
}

const Waveform *EditVoice::waveform() const {
    return _waveform;
}

const WaveformSpectrogram *EditVoice::waveformSpectrogram() const {
    return spectrogram;
}

const WaveformFragments *EditVoice::waveformFragments() const {
    return fragments;
}

bool EditVoice::initWith(const char *filepath) {
    uzume::vocoder::Waveform *w = uzume::vocoder::Waveform::read(filepath);
    if(w == nullptr) {
        return false;
    }
    if(w->length == 0 || w->samplingFrequency != 44100) {
        delete w;
        return false;
    }
    delete _waveform;
    _waveform = w;
    delete fragments;
    fragments = new WaveformFragments(w->msLength());
    delete spectrogram;
    spectrogram = new WaveformSpectrogram(_waveform);
    emit this->fragmentChanged(fragments);
    return true;
}

bool EditVoice::synthesize(const char *filepath) {
    if(!_waveform || ! fragments) {
        return false;
    }

    unsigned int samplingFrequency = 44100;
    auto length = (unsigned int)(fragments->msLength() / 1000.0 * (double)samplingFrequency);

    const auto fs = fragments->data();
    std::vector<LinearTimeAxisMap *> tams;
    std::vector<const Spectrogram *> specs;
    for(const auto &f: fs) {
        auto *tam = new LinearTimeAxisMap(f.msLeft, f.msRight, f.msLength);
        auto *s = new StretchedPartialSpectrogram(spectrogram, tam);
        tams.emplace_back(tam);
        specs.emplace_back(s);
    }

    auto *output = new Waveform(length, _waveform->samplingFrequency);
    auto *spec = ArraySpectrogramAggregator::from(specs);

    SynthesizeWaveformWithWORLD synthesize;
    bool result = true;

    result &= synthesize(output, spec);
    result &= output->save(filepath);

    delete spec;
    delete output;

    for(auto t: tams) {
        delete t;
    }
    for(auto s: specs) {
        delete s;
    }

    return result;
}

void EditVoice::divideAt(double ms) {
    if(this->fragments == nullptr) {
        return;
    }
    if(this->fragments->divideAt(ms)) {
        emit this->fragmentChanged(fragments);
    }
}

void EditVoice::extend(int index, double ms) {
    if(this->fragments == nullptr) {
        return;
    }
    if(this->fragments->setLength(index, ms)) {
        emit this->fragmentChanged(fragments);
    }
}

void EditVoice::mergeToPrevious(int index) {
    if(this->fragments == nullptr) {
        return;
    }
    if(this->fragments->mergeToPrevious(index)) {
        emit fragmentChanged(fragments);
    }
}
