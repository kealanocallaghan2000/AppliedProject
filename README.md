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

#### 28/11/2021
* Sliders still not fully working but just have to be tweaked

#### 05/12/2021
* Began tidying Adsr into encapsulated classes
* Created encapsulations for the Adsr UI and the data
* Changed ADSR sliders sizes
* More object oriented approach from now on

#### 06/12/2021
* Created encapsulations for oscillator class
* Moved code around slightly

#### 07/12/2021
* Moved all osc code into their own classes
* created front end for oscillator
* Front end attached to noise now
* Three different wave types now working

#### 14/12/2021
* Started to add fm modulation
* Could only display frequency
* Set upattachments and backend

#### 15/12/2021
* Had trouble displaying sound
* voice line for fm modulation broke output audio
* fm modulation with freq and depth working, optimised