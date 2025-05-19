#include <fluidsynth.h>
#include <sndfile.h>
#include <string>
#include <memory>

class AudioGenerator {
public:
    AudioGenerator();
    ~AudioGenerator();
    
    void start_recording(const std::string& output_file);
    void stop_recording();
    void play_note(int midi_note, float duration_seconds, int velocity);
    int convert_to_midi(std::string nota);
    
private:
    fluid_settings_t* settings;
    fluid_synth_t* synth;

    SNDFILE* outfile;
    SF_INFO sfinfo;
    bool is_recording;

    int buffer_size = 1024;
    short audio_buffer[1024 * 2]; 
};