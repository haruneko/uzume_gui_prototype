// Copyright 2021 Hal@shurabaP.  All rights reserved.
// Use of this source code is governed by a MIT style
// license that can be found in the LICENSE file.
#include "WaveformFragments.hpp"

WaveformFragments::WaveformFragments(double msLength) {
    flush(msLength);
}

void WaveformFragments::flush(double msLength) {
    fragments.clear();
    fragments.emplace_back(0.0, msLength, msLength);
}

int WaveformFragments::indexAt(double ms) const {
    if(ms < 0.0) {
        return -1;
    }
    double currentMs = 0.0;
    int i = 0;
    for(auto iterator = fragments.begin(); iterator != fragments.end(); iterator++, i++) {
        currentMs += iterator->msLength;
        if(ms <= currentMs) {
            return i;
        }
    }
    return -1;
}

bool WaveformFragments::setLength(int indexAt, double msLength) {
    if(indexAt < 0 || fragments.size() <= indexAt) {
        return false;
    }
    int i = 0;
    for(auto iterator = fragments.begin(); iterator != fragments.end(); iterator++, i++) {
        if(i == indexAt) {
            (*iterator).msLength = msLength;
            if((*iterator).msLength < 0.0) {
                (*iterator).msLength = 0.0;
            }
            return true;
        }
    }
    return false;
}

bool WaveformFragments::mergeToPrevious(int index) {
    if(index < 0 || fragments.size() <= index) {
        return false;
    }
    int i = 0;
    for(auto iterator = fragments.begin(); iterator != fragments.end(); iterator++, i++) {
        if(i == index) {
            fragments.erase(iterator);
            return true;
        }
    }
    return false;
}

bool WaveformFragments::divideAt(double ms) {
    if(ms < 0.0) {
        return false;
    }
    double currentMs = 0.0;
    double previousMs = 0.0;
    auto iterator = fragments.begin();
    while(iterator != fragments.end()) {
        previousMs = currentMs;
        currentMs += iterator->msLength;
        if(ms <= currentMs) {
            break;
        }
        iterator++;
    }
    if(iterator == fragments.end()) {
        return false;
    }
    double dividedRelativePosition = iterator->msLeft +
                                     (iterator->msRight - iterator->msLeft) * (ms - previousMs) / iterator->msLength;
    WaveformFragment next(dividedRelativePosition, iterator->msRight, currentMs - ms);
    iterator->msLength = ms - previousMs;
    iterator->msRight = dividedRelativePosition;
    fragments.insert(++iterator, next);
    return true;
}

double WaveformFragments::msLength() const {
    double result = 0.0;
    for(const auto &f: fragments) {
        result += f.msLength;
    }
    return result;
}