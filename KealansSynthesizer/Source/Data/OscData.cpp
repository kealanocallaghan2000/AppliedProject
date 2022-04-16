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
	fmOscillator.prepare(spec); // pass it process spec
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
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod); // setting the frequency level
	// add fm mod to change the final frequency ^
	lastMidiNote = midiNoteNumber; // keeps trackc of what the last note was
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	// get the waveform of the fm at any given time - sample by sample processing
	for (int channel = 0; channel < block.getNumChannels(); ++channel)
	{
		for (int sample = 0; sample < block.getNumSamples(); ++sample)
		{
			fmMod = fmOscillator.processSample(block.getSample(channel, sample)) * fmDepth;
		};
	}

	// process oscillator through the buffer 
	process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setFmParams(const float frequency, const float depth)
{
	fmOscillator.setFrequency(frequency);
	fmDepth = depth;
	auto currentFrequency = juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod; // updates the fm mod so you dont have to change note to hear the difference
	setFrequency(currentFrequency >= 0 ? currentFrequency : currentFrequency * -1.0); // if current frequency is greater than 0 then fine, if not flip it
}