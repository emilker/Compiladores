#include "audiogenerator.hpp"
#include <unordered_map>
#include <iostream>
#include <string>

AudioGenerator::AudioGenerator()  
{
    settings = new_fluid_settings();
    fluid_settings_setnum(settings, "synth.gain", 5);
    synth = new_fluid_synth(settings);
    fluid_synth_sfload(synth, "./SoundFont/MuseScore_General.sf2", 1);

    sfinfo = {0, 44100, 2, SF_FORMAT_WAV | SF_FORMAT_PCM_16};
    outfile = nullptr;

    is_recording = false;
}

AudioGenerator::~AudioGenerator() 
{
    stop_recording();

    delete_fluid_synth(synth);

    delete_fluid_settings(settings);
}

void AudioGenerator::start_recording(const std::string& output_file) 
{
    if (is_recording) return;

    outfile = sf_open(output_file.c_str(), SFM_WRITE, &sfinfo);
    is_recording = true;
}

void AudioGenerator::stop_recording() 
{
    if (!is_recording) return;

    sf_close(outfile);
    is_recording = false;
}

void AudioGenerator::play_note(int midi_note, float duration_seconds, int velocity) 
{
    if (!is_recording) return;
    
    int frames_totales = sfinfo.samplerate * duration_seconds;
    int frames_procesados = 0;
    
    if (midi_note != -1) 
    {
        fluid_synth_noteon(synth, 0, midi_note, velocity);

        while (frames_procesados < frames_totales) 
        {
            int frames = std::min(buffer_size, frames_totales - frames_procesados);
            fluid_synth_write_s16(synth, frames, audio_buffer, 0, 2, audio_buffer, 1, 2);
            sf_writef_short(outfile, audio_buffer, frames);
            frames_procesados += frames;
        }

        fluid_synth_noteoff(synth, 0, midi_note);

    } else 
    {
        fluid_synth_all_notes_off(synth, 0);
        std::fill_n(audio_buffer, buffer_size * 2, 0);
        while (frames_procesados < frames_totales) 
        {
            int frames = std::min(buffer_size, frames_totales - frames_procesados);
            sf_writef_short(outfile, audio_buffer, frames);
            frames_procesados += frames;
        }
    }
}

int AudioGenerator::convert_to_midi(std::string nota)
{
    std::unordered_map<std::string, int> KeyToMidi = {
        // Octava 1 (C1-B1)
        {"C1", 24}, {"C#1", 25}, {"Db1", 25}, {"D1", 26}, {"D#1", 27}, {"Eb1", 27}, {"E1", 28},
        {"F1", 29}, {"F#1", 30}, {"Gb1", 30}, {"G1", 31}, {"G#1", 32}, {"Ab1", 32}, {"A1", 33},
        {"A#1", 34}, {"Bb1", 34}, {"B1", 35},
    
        // Octava 2 (C2-B2)
        {"C2", 36}, {"C#2", 37}, {"Db2", 37}, {"D2", 38}, {"D#2", 39}, {"Eb2", 39}, {"E2", 40},
        {"F2", 41}, {"F#2", 42}, {"Gb2", 42}, {"G2", 43}, {"G#2", 44}, {"Ab2", 44}, {"A2", 45},
        {"A#2", 46}, {"Bb2", 46}, {"B2", 47},
    
        // Octava 3 (C3-B3)
        {"C3", 48}, {"C#3", 49}, {"Db3", 49}, {"D3", 50}, {"D#3", 51}, {"Eb3", 51}, {"E3", 52},
        {"F3", 53}, {"F#3", 54}, {"Gb3", 54}, {"G3", 55}, {"G#3", 56}, {"Ab3", 56}, {"A3", 57},
        {"A#3", 58}, {"Bb3", 58}, {"B3", 59},
    
        // Octava 4 (C4-B4) - Do central
        {"C4", 60}, {"C#4", 61}, {"Db4", 61}, {"D4", 62}, {"D#4", 63}, {"Eb4", 63}, {"E4", 64},
        {"F4", 65}, {"F#4", 66}, {"Gb4", 66}, {"G4", 67}, {"G#4", 68}, {"Ab4", 68}, {"A4", 69},
        {"A#4", 70}, {"Bb4", 70}, {"B4", 71},
    
        // Octava 5 (C5-B5)
        {"C5", 72}, {"C#5", 73}, {"Db5", 73}, {"D5", 74}, {"D#5", 75}, {"Eb5", 75}, {"E5", 76},
        {"F5", 77}, {"F#5", 78}, {"Gb5", 78}, {"G5", 79}, {"G#5", 80}, {"Ab5", 80}, {"A5", 81},
        {"A#5", 82}, {"Bb5", 82}, {"B5", 83},
    
        // Octava 6 (C6-B6)
        {"C6", 84}, {"C#6", 85}, {"Db6", 85}, {"D6", 86}, {"D#6", 87}, {"Eb6", 87}, {"E6", 88},
        {"F6", 89}, {"F#6", 90}, {"Gb6", 90}, {"G6", 91}, {"G#6", 92}, {"Ab6", 92}, {"A6", 93},
        {"A#6", 94}, {"Bb6", 94}, {"B6", 95},
    
        // Octava 7 (C7-B7)
        {"C7", 96}, {"C#7", 97}, {"Db7", 97}, {"D7", 98}, {"D#7", 99}, {"Eb7", 99}, {"E7", 100},
        {"F7", 101}, {"F#7", 102}, {"Gb7", 102}, {"G7", 103}, {"G#7", 104}, {"Ab7", 104}, {"A7", 105},
        {"A#7", 106}, {"Bb7", 106}, {"B7", 107},
    
        // Octava 8 (solo C8 en pianos estándar)
        {"C8", 108},

        // Silencio
        {"-", -1}
    };

    auto it = KeyToMidi.find(nota);
    return it->second;
}
