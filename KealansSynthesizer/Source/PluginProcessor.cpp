/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
KealansSynthesizerAudioProcessor::KealansSynthesizerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	synth.addSound(new SynthSound());
	synth.addVoice(new SynthVoice());
}

KealansSynthesizerAudioProcessor::~KealansSynthesizerAudioProcessor()
{


}

//==============================================================================
const juce::String KealansSynthesizerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool KealansSynthesizerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool KealansSynthesizerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool KealansSynthesizerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double KealansSynthesizerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int KealansSynthesizerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int KealansSynthesizerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void KealansSynthesizerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String KealansSynthesizerAudioProcessor::getProgramName (int index)
{
    return {};
}

void KealansSynthesizerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void KealansSynthesizerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock; // how big our sample size is
	spec.sampleRate = sampleRate; // sample rate of wave
	spec.numChannels = getTotalNumInputChannels(); // number of output channels 

	osc.prepare(spec); // pass reference into oscillator

	gain.prepare(spec); // passing gain process spec

	osc.setFrequency(350.0f); // setting the frequency level
	gain.setGainLinear(0.02); // setting the linear gain (between 0 and 1)

	synth.setCurrentPlaybackSampleRate(sampleRate); // sets the current sample playback rate
}

void KealansSynthesizerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool KealansSynthesizerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// where the actual audio processing happens
void KealansSynthesizerAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
	juce::ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();


	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	juce::dsp::AudioBlock<float> audioBlock{ buffer };

	// process oscillator through the buffer
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	// osc process runs and audio block contains sine wave info
	// takes values and turns them down
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	// makes sure that if the user changes any parameters that it gets updated
	for (int i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto voice = dynamic_cast<juce::SynthesiserVoice*>(synth.getVoice(i)))
		{
			// osc controls
			// adsr
			// LFO
		}
	}


	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples()); // output audio buffer, input midi = midi messages, start sample = 0, buffer = get number of samples 
}

//==============================================================================
bool KealansSynthesizerAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* KealansSynthesizerAudioProcessor::createEditor()
{
    return new KealansSynthesizerAudioProcessorEditor (*this);
}

//==============================================================================
void KealansSynthesizerAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void KealansSynthesizerAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KealansSynthesizerAudioProcessor();
}
