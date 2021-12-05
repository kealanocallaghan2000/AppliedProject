/*
  ==============================================================================

    AdsrData.h
    Created: 4 Dec 2021 11:33:05pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
	void updateADSR(const float attack, const float decay, const float sustain, const float release);


private:
	juce::ADSR::Parameters adsrParams;

};


