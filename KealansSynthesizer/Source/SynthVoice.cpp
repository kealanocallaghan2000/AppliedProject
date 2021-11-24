/*
  ==============================================================================

    SynthVoice.cpp
    Created: 3 Nov 2021 2:55:41pm
    Author:  keala

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) // returns true if object is capable of playing sound
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr; // returns synthesiserSound pointer and makes sure its not null (is loaded)
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) // called to start a new note
{
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber)); // setting the frequency level
	adsr.noteOn(); // starts the attack of the envelopemk

}

void SynthVoice::stopNote(float velocity, bool allowTailOff) // called to stop a note
{
	adsr.noteOff(); // starts the release of the envelope
	if (!allowTailOff || adsr.isActive())
	{
		clearCurrentNote();
	}
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) // called to let the voice object know that controller was moved
{

}

void SynthVoice::renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) // renders the next block of data for this voice
{
	jassert(isPrepared = true); // make sure prepareToPlay is called

	// if we dont have any active voices, leave render block method
	if (!isVoiceActive())
		return;

	synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true); // set the size of the audio buffer to prevent clicking when playing notes
	synthBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };

	// process oscillator through the buffer
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	// osc process runs and audio block contains sine wave info
	// takes values and turns them down
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

	if (startSample != 0)
		jassertfalse;

	for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
	{
		// if theres audio that is already inside of the buffer, add from 0
		outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

		// if our adsr is not active, clear the current note
		if (!adsr.isActive())
		{
			clearCurrentNote();
		}
	}

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	adsr.setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock; // how big our sample size is
	spec.sampleRate = sampleRate; // sample rate of wave
	spec.numChannels = outputChannels; // number of output channels 

	osc.prepare(spec); // pass reference into oscillator

	gain.prepare(spec); // passing gain process spec

	gain.setGainLinear(0.4); // setting the linear gain (between 0 and 1)

	// setting some arbitrary values
	adsrParams.attack = 0.8f;
	adsrParams.decay = 0.8f;
	adsrParams.sustain = 1.0f;
	adsrParams.release = 1.5f;

	adsr.setParameters(adsrParams);


	isPrepared = true; // lets us know that the prepare to play is initialized
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

