#pragma once
#include <string>
#include <vector>
#include <fluidsynth.h>
#include <sndfile.h>
#include <unordered_map>
struct SoundFrequencies 
{
    std::string name;
    double beats;
};

class AudioGenerator
{
public:
    AudioGenerator(int sample_rate = 44100);
    ~AudioGenerator();

    bool load_soundfont(const std::string& path);
    void start_recording(const std::string& wav_filename);
    void stop_recording();
    void play_note(const std::string& name, double beats);
    void set_tempo(double bpm);
    void write_wav(const std::string& filename, const std::vector<short>& buffer, int sample_rate);    
    int convert_to_midi(const std::string& nota) const;

private:
    static const std::unordered_map<std::string, int> KeyToMidi;
    std::vector<SoundFrequencies> notes;
    std::string output_path;
    double bpm = 160.0; // default
    int sample_rate;

    fluid_settings_t* settings;
    fluid_synth_t* synth;
};