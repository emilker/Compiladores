#include "statement.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "symbol_table.hpp"
#include "audiogenerator.hpp"

using namespace std::literals;

Statement::~Statement()
{
}

StatementSequence::StatementSequence(Statement* f, Statement* n) noexcept
    : first(f), next(n)
{
}

void StatementSequence::destroy() noexcept
{
    if (first)
    {
        first->destroy();
        delete first;
        first = nullptr;
    }

    if (next)
    {
        next->destroy();
        delete next;
        next = nullptr;
    }
}

float StatementSequence::pulse() noexcept
{
    float first_ = 0.0f;
    float next_ = 0.0f;

    if (first) first_ = first->pulse();
    
    if (next) next_ = next->pulse();

    std::cout << "first: " << first_;
    std::cout << " next: " << next_ << std::endl;

    if (first_ == 1000) return next_;

    if (first_ != 1000 && next_ != 1000)
    {
        if (first_ != next_) return 0.0f;
    }

    return first_;
}


bool StatementSequence::semantic_analysis() noexcept
{
    bool result = true;

    if (first)
    {
        result =  first->semantic_analysis();
        if (!result)
        {
            return false;
        }
    } 

    if (next) 
    {
        result = next->semantic_analysis();
        if (!result)
        {
            return false;
        }
    }

    return true;
}

bool  StatementSequence::resolve_name(SymbolTable &symbol_table) noexcept
{
    bool result = true;

    if (first)
    {
        result = first->resolve_name(symbol_table);
        if (!result)
        {
            return false;
        }
    } 

    if (next) 
    {
        result = next->resolve_name(symbol_table);
        if (!result)
        {
            return false;
        }
    }

    return true;
}

void StatementSequence::generate_sound(AudioGenerator &audio_gen) noexcept
{
    if (first) first->generate_sound(audio_gen);
    if (next) next->generate_sound(audio_gen);
}

Measures::Measures(Statement* c1, Statement* c2, bool time_)
    : left_Sequence(c1), right_Sequence(c2), left_pulse(0.0f), right_pulse(0.0f), time(time_)
{
}

void Measures::destroy() noexcept
{
    if (left_Sequence)
    {
        left_Sequence->destroy();
        delete left_Sequence;
        left_Sequence = nullptr;
    }
    if (right_Sequence)
    {
        right_Sequence->destroy();
        delete right_Sequence;
        right_Sequence = nullptr;
    }
}

float MeasureSequence::pulse() noexcept
{
    if (left_Sequence) left_pulse = left_Sequence->pulse();
    if (right_Sequence) right_pulse = right_Sequence->pulse();  

    if (left_pulse == right_pulse)
    {
        return left_pulse;
    }
    else
    {
        return 0.0f; 
    }
}

void MeasureSequence::destroy() noexcept
{
    if (left_Sequence)
    {
        left_Sequence->destroy();
        delete left_Sequence;
        left_Sequence = nullptr;
    }

    if (right_Sequence)
    {
        right_Sequence->destroy();
        delete right_Sequence;
        right_Sequence = nullptr;
    }
}

std::string MeasureSequence::get_value() noexcept
{
    return left_Sequence->get_value() + " | " + right_Sequence->get_value();
}

bool MeasureSequence::semantic_analysis() noexcept
{
    if (!time)
    {
        if (left_Sequence)
        {
            left_pulse = left_Sequence->pulse();
            if (left_pulse > 4.0f)
            {
               return false;
            }
        }

        if (right_Sequence)
        {
            right_pulse = right_Sequence->pulse();
            if (right_pulse > 4.0f)
            {
                return false;
            }
        }
    }

    return true;
}

void MeasureSequence::generate_sound(AudioGenerator &audio_gen) noexcept
{
    if (left_Sequence) left_Sequence->generate_sound(audio_gen);

    if (right_Sequence) right_Sequence->generate_sound(audio_gen);
}

void NotesSequence::destroy() noexcept
{
    if (left_Sequence)
    {
        left_Sequence->destroy();
        delete left_Sequence;
        left_Sequence = nullptr;
    }

    if (right_Sequence)
    {
        right_Sequence->destroy();
        delete right_Sequence;
        right_Sequence = nullptr;
    }
}

std::string NotesSequence::get_value() noexcept
{
    return left_Sequence->get_value() + " , " + right_Sequence->get_value();
}

bool NotesSequence::semantic_analysis() noexcept
{
    if (!time)
    {   
        float pulse_total = 0.0f;

        if (left_Sequence)
        {
            left_pulse = left_Sequence->pulse();
        }

        if (right_Sequence)
        {
            right_pulse = right_Sequence->pulse();
        }

        pulse_total = left_pulse + right_pulse;

        if (pulse_total > 4.0f)
        {
            return false; 
        }
    }

    return true;
}

void NotesSequence::generate_sound(AudioGenerator &audio_gen) noexcept
{
    if (left_Sequence) left_Sequence->generate_sound(audio_gen);

    if (right_Sequence) right_Sequence->generate_sound(audio_gen);
}

float NotesSequence::pulse() noexcept
{
    left_pulse = left_Sequence ? left_Sequence->pulse() : 0.0f; 
    right_pulse = right_Sequence ? right_Sequence->pulse() : 0.0f;

    return left_pulse + right_pulse;
}

Note::Note(Statement* note_, Statement* alteration_, Statement* duration_, Statement* dottes_, bool time_) noexcept
    : note(note_), alteration(alteration_), duration(duration_), dottes(dottes_), time(time_)
{
}

std::string Note::get_value() noexcept
{
    return (note ? note->get_value() : "") +
           (alteration ? alteration->get_value() : "") +
           (duration ? duration->get_value() : "") +
           (dottes ? dottes->get_value() : "");
}

bool Note::semantic_analysis() noexcept
{
    if (!time)
    {
        float pulse_ = pulse(); 
        if (pulse_ > 4.0f)
        {
            return false; 
        }
    }

    return true;
}

void Note::generate_sound(AudioGenerator &audio_gen) noexcept
{
    int midi_note = audio_gen.convert_to_midi(note->get_value());
    float duration = pulse(); 
    
    audio_gen.play_note(midi_note, duration, 100);
}

float Note::pulse() noexcept
{
    static std::unordered_map<std::string, float> durations = {
        {"w", 4}, {"h", 2}, {"q", 1}, {"e", 0.5}, {"s", 0.25}
    };

    auto it = durations.find(duration->get_value());

    float pulse = it->second;

    if (dottes)
    {
        pulse += pulse * 0.5f;
    }

    return pulse;
}

void Note::destroy() noexcept
{
    if (note)
    {
        note->destroy();
        delete note;
        note = nullptr;
    }
    
    if (alteration)
    {
        alteration->destroy();
        delete alteration;
        alteration = nullptr;
    }

    if (duration)
    {
        duration->destroy();
        delete duration;
        duration = nullptr;
    }
    
    if (dottes)
    {
        dottes->destroy();
        delete dottes;
        dottes = nullptr;
    }

}

SectionDeclaration::SectionDeclaration(Statement* _id, Statement* _measures)
    : id(_id), measures(_measures)
{
}

void SectionDeclaration::destroy() noexcept
{
    id->destroy();
    delete id;
    id = nullptr;

    measures->destroy();
    delete measures;
    measures = nullptr;
}

bool SectionDeclaration::resolve_name(SymbolTable &symbol_table) noexcept
{
    std::string id_ = id->get_value();

    if (!symbol_table.bind(id_, measures))
    {
        return false; 
    }
    
    return true;
}

Value::Value(std::string v) noexcept
    : value(v)
{
}

std::string Value::get_value() noexcept
{
    return value;
}

void Value::destroy() noexcept
{
}

Time::Time(Statement* pulse_, Statement* figure_, Statement* body_)
    : pulse_(pulse_), figure_(figure_), body(body_)
{
}

void Time::destroy() noexcept
{
    pulse_->destroy();
    delete pulse_;
    pulse_ = nullptr;

    figure_->destroy();
    delete figure_;
    figure_ = nullptr;

    body->destroy();
    delete body;
    body = nullptr;
}

bool Time::semantic_analysis() noexcept
{
    int pulse = std::stoi(pulse_->get_value());
    int figure = std::stoi(figure_->get_value());

    static std::unordered_map<int, float> FIGURES = {
        {1, 4}, {2, 2}, {4, 1}, {8, 0.5}, {16, 0.25}
    };
    
    auto it = FIGURES.find(figure);

    if (it == FIGURES.end())
    {
       return false;
    }

    if (pulse > 12)
    {
        return false;
    }

    if (!body->semantic_analysis())
    {
        return false;
    }

    float pulse__ = body->pulse();   

    if ((it->second * pulse) != pulse__)
    {
        return false;
    }

    return true;
}

bool Time::resolve_name(SymbolTable &symbol_table) noexcept
{
    return body->resolve_name(symbol_table);
}

void Time::generate_sound(AudioGenerator &audio_gen) noexcept
{
    body->generate_sound(audio_gen);
}

SectionReference::SectionReference(std::string _id) noexcept
    : id(_id), measures(nullptr)
{
}

void SectionReference::destroy() noexcept
{
    measures->destroy();
    delete measures;
    measures = nullptr;
}

float SectionReference::pulse() noexcept
{
    return measures->pulse();
}

bool SectionReference::resolve_name(SymbolTable &symbol_table) noexcept
{
    auto resolved = symbol_table.lookup(id);

    if (!resolved)
    {
        return false; 
    }

    measures = resolved->measures;
    return true;
}

bool SectionReference::semantic_analysis() noexcept
{
    return measures->semantic_analysis();
}

void SectionReference::generate_sound(AudioGenerator &audio_gen) noexcept
{
    measures->generate_sound(audio_gen);
}

RepeatDeclaration::RepeatDeclaration(Statement* count, Statement* measures_) noexcept
    : repeat_count(count), measures(measures_)
{
}

float RepeatDeclaration::pulse() noexcept
{
    return measures->pulse();
}

bool RepeatDeclaration::semantic_analysis() noexcept
{
    return measures->semantic_analysis();
}

void RepeatDeclaration::generate_sound(AudioGenerator &audio_gen) noexcept
{
    for (int i = 0; i < std::stoi(repeat_count->get_value()); ++i)
    {
        measures->generate_sound(audio_gen);
    }
}

void RepeatDeclaration::destroy() noexcept
{
    repeat_count->destroy();
    delete repeat_count;
    repeat_count = nullptr;

    measures->destroy();
    delete measures;
    measures = nullptr;
}
