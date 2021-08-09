// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#ifndef __UZUME_GUI_PROTOTYPE_EDIT_VOICE_HPP__
#define __UZUME_GUI_PROTOTYPE_EDIT_VOICE_HPP__

#include <QObject>

class WaveformFragments;

namespace uzume { namespace vocoder {
class WaveformSpectrogram;
class Waveform;
}}

class EditVoice : public QObject {
    Q_OBJECT
public:
    EditVoice(QObject *parent);
    ~EditVoice();

    bool initWith(const char *filepath);
    bool synthesize(const char *filepath);

    const uzume::vocoder::Waveform *waveform() const;
    const uzume::vocoder::WaveformSpectrogram *waveformSpectrogram() const;
    const WaveformFragments *waveformFragments() const;

signals:
    void fragmentChanged(const WaveformFragments *fragments);

public slots:
    void divideAt(double ms);
    void extend(int index, double ms);
    void mergeToPrevious(int index);

private:
    uzume::vocoder::Waveform *_waveform;
    WaveformFragments *fragments;
    uzume::vocoder::WaveformSpectrogram *spectrogram;
};

#endif // __UZUME_GUI_PROTOTYPE_EDIT_VOICE_HPP__
