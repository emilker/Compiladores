#include "audiogenerator.hpp"
#include <fluidsynth.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <thread>
#include <chrono>

AudioGenerator::AudioGenerator(int sample_rate)
    : sample_rate(sample_rate), synth(nullptr), settings(nullptr)
{
    settings = new_fluid_settings();
    fluid_settings_setnum(settings, "synth.sample-rate", sample_rate);
    synth = new_fluid_synth(settings);

    // Intenta cargar un SoundFont por defecto
    if (fluid_synth_sfload(synth, "./SoundFont/GeneralUser-GS.sf2", 1) == FLUID_FAILED) 
    {
        std::cerr << "⚠️  Error al cargar SoundFont './SoundFont/GeneralUser-GS.sf2'\n";
    }
}

AudioGenerator::~AudioGenerator()
{
    if (synth) delete_fluid_synth(synth);
    if (settings) delete_fluid_settings(settings);
}

bool AudioGenerator::load_soundfont(const std::string& path)
{
    return fluid_synth_sfload(synth, path.c_str(), 1) != FLUID_FAILED;
}

void AudioGenerator::set_tempo(double bpm)
{
    this->bpm = bpm;
}

void AudioGenerator::start_recording(const std::string& wav_filename)
{
    notes.clear();
    output_path = wav_filename;
}

void AudioGenerator::play_note(const std::vector<std::string>& note_names, double beats)
{
    notes.push_back({note_names, beats});
}

void AudioGenerator::stop_recording()
{
    double seconds_per_beat = 60.0 / bpm;
    double total_seconds = 0.0;

    // Calcular duración total para reservar buffer
    for (const auto& note_event : notes)
    {
        total_seconds += note_event.beats * seconds_per_beat;
    }

    int total_frames = static_cast<int>(sample_rate * total_seconds);
    std::vector<short> buffer(total_frames * 2, 0); // estéreo

    int frame_index = 0;
    int channel = 0;
    int velocity = 100;

    for (const auto& note_event : notes)
    {
        int frames_for_event = static_cast<int>(note_event.beats * seconds_per_beat * sample_rate);

        // Encender todas las notas del acorde simultáneamente
        std::vector<int> midi_notes;
        for (const std::string& note_name : note_event.note_names)
        {
            int midi_note = convert_to_midi(note_name);
            if (midi_note != -1)
            {
                midi_notes.push_back(midi_note);
                fluid_synth_noteon(synth, channel, midi_note, velocity);
            }
            else
            {
                std::cerr << "⚠️ Nota desconocida: " << note_name << "\n";
            }
        }

        // Escribir audio para el evento (acorde o nota simple)
        fluid_synth_write_s16(
            synth, frames_for_event,
            &buffer[frame_index * 2], 0, 2,
            &buffer[frame_index * 2], 1, 2);

        // Apagar notas
        for (int midi_note : midi_notes)
        {
            fluid_synth_noteoff(synth, channel, midi_note);
        }

        frame_index += frames_for_event;
    }

    write_wav(output_path, buffer, sample_rate);
    std::cout << "✅ Audio generado en '" << output_path << "' (" << bpm << " BPM)\n";
}

const std::unordered_map<std::string, int> AudioGenerator::KeyToMidi = 
{
    {"C1", 24}, {"C#1", 25}, {"Db1", 25}, {"D1", 26}, {"D#1", 27}, {"Eb1", 27}, {"E1", 28},
    {"F1", 29}, {"F#1", 30}, {"Gb1", 30}, {"G1", 31}, {"G#1", 32}, {"Ab1", 32}, {"A1", 33},
    {"A#1", 34}, {"Bb1", 34}, {"B1", 35},

    {"C2", 36}, {"C#2", 37}, {"Db2", 37}, {"D2", 38}, {"D#2", 39}, {"Eb2", 39}, {"E2", 40},
    {"F2", 41}, {"F#2", 42}, {"Gb2", 42}, {"G2", 43}, {"G#2", 44}, {"Ab2", 44}, {"A2", 45},
    {"A#2", 46}, {"Bb2", 46}, {"B2", 47},

    {"C3", 48}, {"C#3", 49}, {"Db3", 49}, {"D3", 50}, {"D#3", 51}, {"Eb3", 51}, {"E3", 52},
    {"F3", 53}, {"F#3", 54}, {"Gb3", 54}, {"G3", 55}, {"G#3", 56}, {"Ab3", 56}, {"A3", 57},
    {"A#3", 58}, {"Bb3", 58}, {"B3", 59},

    {"C4", 60}, {"C#4", 61}, {"Db4", 61}, {"D4", 62}, {"D#4", 63}, {"Eb4", 63}, {"E4", 64},
    {"F4", 65}, {"F#4", 66}, {"Gb4", 66}, {"G4", 67}, {"G#4", 68}, {"Ab4", 68}, {"A4", 69},
    {"A#4", 70}, {"Bb4", 70}, {"B4", 71},

    {"C5", 72}, {"C#5", 73}, {"Db5", 73}, {"D5", 74}, {"D#5", 75}, {"Eb5", 75}, {"E5", 76},
    {"F5", 77}, {"F#5", 78}, {"Gb5", 78}, {"G5", 79}, {"G#5", 80}, {"Ab5", 80}, {"A5", 81},
    {"A#5", 82}, {"Bb5", 82}, {"B5", 83},

    {"C6", 84}, {"C#6", 85}, {"Db6", 85}, {"D6", 86}, {"D#6", 87}, {"Eb6", 87}, {"E6", 88},
    {"F6", 89}, {"F#6", 90}, {"Gb6", 90}, {"G6", 91}, {"G#6", 92}, {"Ab6", 92}, {"A6", 93},
    {"A#6", 94}, {"Bb6", 94}, {"B6", 95},

    {"C7", 96}, {"C#7", 97}, {"Db7", 97}, {"D7", 98}, {"D#7", 99}, {"Eb7", 99}, {"E7", 100},
    {"F7", 101}, {"F#7", 102}, {"Gb7", 102}, {"G7", 103}, {"G#7", 104}, {"Ab7", 104}, {"A7", 105},
    {"A#7", 106}, {"Bb7", 106}, {"B7", 107},

    {"C8", 108},

    {"-", -1} // silencio
};

int AudioGenerator::convert_to_midi(const std::string& nota) const
{
    auto it = KeyToMidi.find(nota);
    if (it != KeyToMidi.end())
        return it->second;
    else
        return -1; // Nota no encontrada
}


void AudioGenerator::write_wav(const std::string& filename, const std::vector<short>& buffer, int sample_rate)
{
    std::ofstream out(filename, std::ios::binary);
    int data_size = buffer.size() * sizeof(short);
    int byte_rate = sample_rate * 2 * sizeof(short);
    int file_size = 36 + data_size;
    short block_align = 2 * sizeof(short);
    short bits_per_sample = 16;
    short audio_format = 1;
    short num_channels = 2;

    out.write("RIFF", 4);
    out.write(reinterpret_cast<char*>(&file_size), 4);
    out.write("WAVE", 4);
    out.write("fmt ", 4);
    int subchunk1_size = 16;
    out.write(reinterpret_cast<char*>(&subchunk1_size), 4);
    out.write(reinterpret_cast<char*>(&audio_format), 2);
    out.write(reinterpret_cast<char*>(&num_channels), 2);
    out.write(reinterpret_cast<char*>(&sample_rate), 4);
    out.write(reinterpret_cast<char*>(&byte_rate), 4);
    out.write(reinterpret_cast<char*>(&block_align), 2);
    out.write(reinterpret_cast<char*>(&bits_per_sample), 2);
    out.write("data", 4);
    out.write(reinterpret_cast<char*>(&data_size), 4);
    out.write(reinterpret_cast<const char*>(buffer.data()), data_size);
    out.close();
}