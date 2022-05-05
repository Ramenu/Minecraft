#include "minecraft/audio/sounddata.hpp"
#include "minecraft/glerror/glerror.hpp"

/**
 * Initializes the sound from the filepath given by loading 
 * the sound into the buffer and setting the buffer into the audio. 
 */
SoundData::SoundData(const std::string &soundFilePath) noexcept
{
    if (!buffer.loadFromFile(soundFilePath))
        GLError::error_message("Failed to initialize sound data from \"" + soundFilePath + '\"');
    audio.setBuffer(buffer);
}