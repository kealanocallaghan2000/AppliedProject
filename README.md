# G00373834 Final Year Project - Kealan O'Callaghan
My repository for my final year project.

## Audio Synthesis with C++ in the Juce framework


### Github Log of Progress
#### 22/10/2021
* Project Created with Juce
* Modules added
* Classes added with boiler plate code
* Hello world window working
* Simple sine wav playing on build with raw oscillator

#### 03/11/2021
* Started basic scaffolding for the Synth class
* set up for loops for updating when changes are made
* Set up SynthVoice and SynthSounc classes / header files
* Added just one voice to the synth

#### 06/11/2021
* Finished setup of PrepareToPlay
* Finished setup of RenderNextBlock
* Set up attack/decay/sustain/release methods
* Made frequency to be changed by midi input in the audio workstation (not hardcoded)
* Done full build of project and ran in Ableton - successfullyp plays a simple sine wave

#### 16/11/2021
* Set up main class to accept paremeters

#### 17/11/2021
* Connected ADSR from front end to back end
* Error in PluginProcessor.cpp to do with constructor

#### 23/11/2021 
* Attempted to fix clicking noise when playing notes by creating an audio buffer
* Didnt work

#### 24/11/2021
* Fixed clicking noises with audio buffer
* Fixed attachment error
* Connected audio attachments to UI
* Sliders only half working