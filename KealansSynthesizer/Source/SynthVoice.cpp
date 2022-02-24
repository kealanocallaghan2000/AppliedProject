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
	osc.setWaveFrequency(midiNoteNumber);
	adsr.noteOn(); // starts the attack of the envelopemk
	modAdsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) // called to stop a note
{
	adsr.noteOff(); // starts the release of the envelope
	modAdsr.noteOff();
	if (!allowTailOff || ! adsr.isActive())
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
	modAdsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples); // activates the adsr without affecting buffer
	synthBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
	osc.getNextAudioBlock(audioBlock);
	adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
	filter.process(synthBuffer);

	// osc process runs and audio block contains sine wave info
	// takes values and turns them down
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));


	

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

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
	float modulator = modAdsr.getNextSample();
	filter.updateParams(filterType, cutoff, resonance, modulator);
}

// updates the value of the adsr in the process block
void SynthVoice::updateAdsr (const float attack, const float decay, const float sustain, const float release)
{
	adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock; // how big our sample size is
	spec.sampleRate = sampleRate; // sample rate of wave
	spec.numChannels = outputChannels; // number of output channels 

	osc.prepareToPlay(spec);
	adsr.setSampleRate(sampleRate);
	filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
	modAdsr.setSampleRate(sampleRate);
	gain.prepare(spec); // passing gain process spec

	gain.setGainLinear(0.4); // setting the linear gain (between 0 and 1)

	isPrepared = true; // lets us know that the prepare to play is initialized
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::updateModAdsr(const float attack, const float decay, const float sustain, const float release)
{
	modAdsr.updateADSR(attack, decay, sustain, release);
}

