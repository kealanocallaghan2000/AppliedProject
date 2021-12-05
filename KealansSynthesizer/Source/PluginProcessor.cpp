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
                       ), apvts (*this, nullptr, "Parameters", createParams())
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
	synth.setCurrentPlaybackSampleRate(sampleRate);

	for (int i = 0; i < synth.getNumVoices(); i++)
	{
		if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) // turning each of our synthVoices into a synthesiserVoice pointer
		{
			// if we set the pointer successfully, we can call prepare to play
			voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
		}

	}

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

	// makes sure that if the user changes any parameters that it gets updated
	for (int i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
		{
			// osc controls
			// adsr
			// LFO

			auto& attack = *apvts.getRawParameterValue("ATTACK");
			auto& decay = *apvts.getRawParameterValue("DECAY");
			auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
			auto& release = *apvts.getRawParameterValue("RELEASE");

			voice->update(attack.load(), decay.load(), sustain.load(), release.load()); // .load() means its an atomic float
		}
	}

	// calling the render on each of our voices
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

// states which kind of parameters we'd like the user to be able to control
juce::AudioProcessorValueTreeState::ParameterLayout KealansSynthesizerAudioProcessor::createParams()
{
	// Oscillator wave select
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
	params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

	// ADSR Params
	params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f)); // Attack defaulted to 0.1
	params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f)); // Decay defaulted to 0.1
	params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f)); // velocity stays consistent for sustain
	params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f)); // Release defaulted to 0.1, max release time 3 seconds

	return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new KealansSynthesizerAudioProcessor();
}


