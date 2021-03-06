/*
  ==============================================================================

   This file is part of the JUCE 6 technical preview.
   Copyright (c) 2020 - Raw Material Software Limited

   You may use this code under the terms of the GPL v3
   (see www.gnu.org/licenses).

   For this technical preview, this file is not subject to commercial licensing.

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

/**
    This abstract base class is used by some AudioProcessorParameter helper classes.

    @see AudioParameterFloat, AudioParameterInt, AudioParameterBool, AudioParameterChoice

    @tags{Audio}
*/
class JUCE_API RangedAudioParameter   : public AudioProcessorParameterWithID
{
public:
    /** The creation of this object requires providing a name and ID which will be
        constant for its lifetime.
    */
    RangedAudioParameter (const String& parameterID,
                          const String& parameterName,
                          const String& parameterLabel = {},
                          Category parameterCategory = AudioProcessorParameter::genericParameter);

    /** Returns the range of values that the parameter can take. */
    virtual const NormalisableRange<float>& getNormalisableRange() const = 0;

    /** Returns the number of steps for this parameter based on the normalisable range's interval.
        If you are using lambda functions to define the normalisable range's snapping behaviour
        then you should override this function so that it returns the number of snapping points.
    */
    int getNumSteps() const override;

    /** Normalises and snaps a value based on the normalisable range. */
    float convertTo0to1 (float v) const noexcept;

    /** Denormalises and snaps a value based on the normalisable range. */
    float convertFrom0to1 (float v) const noexcept;
};

} // namespace juce
