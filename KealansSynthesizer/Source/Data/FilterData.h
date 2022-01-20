/*
  ==============================================================================

    FilterData.h
    Created: 19 Jan 2022 4:25:07pm
    Author:  keala

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class FilterData
{
public:
	void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels); // always need a preparetoplay to pass the sample rate to algorithm
	void process(juce::AudioBuffer<float>& buffer);
	void updateParams(const int filterType, const float freq, const float res);
	void reset();

private:
	juce::dsp::StateVariableTPTFilter<float> filter;
	bool isPrepared{ false };

};