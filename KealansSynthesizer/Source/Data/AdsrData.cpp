/*
  ==============================================================================

	AdsrData.cpp
	Created: 4 Dec 2021 11:33:05pm
	Author:  keala

  ==============================================================================
*/

#include "AdsrData.h"

// updates the value of the adsr in the process block
void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
	// setting the adsr values
	adsrParams.attack = attack;
	adsrParams.decay = decay;
	adsrParams.sustain = sustain;
	adsrParams.release = release;

	setParameters(adsrParams); // native method called from the adsr class 
}
