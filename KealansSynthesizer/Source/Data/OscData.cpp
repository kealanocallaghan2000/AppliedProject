/*
  ==============================================================================

    OscData.cpp
    Created: 7 Dec 2021 4:30:41pm
    Author:  keala

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
	prepare(spec);
}

// oscillator choice
void OscData::setWaveType(const int choice)
{
	// switch statement for choice of oscillator wave type
	switch (choice)
	{
		case 0:
			initialise([](float x) { return std::sin(x); }); // sine wave
			break;
			
		case 1:
			initialise([](float x) { return x / juce::MathConstants<float>::pi; }); // saw wave
			break;

		case 2:
			initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); // square wave
			break;

		default:
			jassertfalse; // if we get to this point, none of the waves worked and something went wrong
			break;
	}
}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)); // setting the frequency level
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	// process oscillator through the buffer
	process(juce::dsp::ProcessContextReplacing<float>(block));
}