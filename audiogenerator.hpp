#pragma once
#include <string>
#include <vector>
#include <fluidsynth.h>
#include <sndfile.h>
#include <unordered_map>
struct MusicalNotes 
{
    std::vector<std::string> note_names; 
    double beats;
};

class AudioGenerator
{
public:
    AudioGenerator(int sample_rate = 44100);
    ~AudioGenerator();

    void prepare_output(const std::string& wav_filename);
    void render_audio();
    void play_note(const std::vector<std::string>& notes, double beats);
    void set_tempo(double bpm);
    void write_wav(const std::string& filename, const std::vector<short>& buffer, int sample_rate);    
    int convert_to_midi(const std::string& nota) const;    

private:
    static const std::unordered_map<std::string, int> KeyToMidi;
    std::vector<MusicalNotes> notes;
    std::string output_path;
    double bpm = 120.0; // default
    int sample_rate;


    fluid_settings_t* settings;
    fluid_synth_t* synth;
};