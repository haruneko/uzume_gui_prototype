// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __UZUME_GUI_PROTOTYPE_EDIT_VOICE_HPP__
#define __UZUME_GUI_PROTOTYPE_EDIT_VOICE_HPP__

class WaveformFragments;

namespace uzume { namespace vocoder {
class WaveformSpectrogram;
class Waveform;
}}

class EditVoice {
public:
    EditVoice();
    ~EditVoice();

    bool initWith(const char *filepath);
    bool synthesize(const char *filepath);

    const uzume::vocoder::WaveformSpectrogram *waveformSpectrogram() const;
private:
    uzume::vocoder::Waveform *waveform;
    WaveformFragments *fragments;
    uzume::vocoder::WaveformSpectrogram *spectrogram;
};

#endif // __UZUME_GUI_PROTOTYPE_EDIT_VOICE_HPP__
