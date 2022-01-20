/*
  ==============================================================================

    FilterData.cpp
    Created: 19 Jan 2022 4:25:07pm
    Author:  keala

  ==============================================================================
*/

#include "FilterData.h"

void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels)
{
	filter.reset(); // set the filter to base

	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = numChannels;

	filter.prepare(spec); 

	isPrepared = true; // 
}


void FilterData::process(juce::AudioBuffer<float>& buffer)
{
	jassert(isPrepared); // ensures preparetoplay has been called

	juce::dsp::AudioBlock<float> block{buffer};

	filter.process(juce::dsp::ProcessContextReplacing<float> { block }); // replacing the contents of the block with what the filter does
}


void FilterData::updateParams(const int filterType, const float freq, const float res)
{
	switch (filterType)
	{
		case 0:
			filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass); // low pass filter
			break;
		case 1:
			filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass); // band pass filter
			break;
		case 2:
			filter.setType(juce::dsp::StateVariableTPTFilterType::highpass); // high pass filter
			break;
	}

	filter.setCutoffFrequency(freq);
	filter.setResonance(res);
}


void FilterData::reset()
{
	filter.reset();
}
