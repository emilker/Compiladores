🎼 Musical Notation Compiler
A domain-specific language (DSL) compiler for musical notation, built with Flex, Bison, and C++. It parses and analyzes structured music notation and generates audio output in .wav format. Future releases aim to include sheet music export via LilyPond.

🚀 Features
✅ Custom lexer and parser for music notation
✅ Abstract Syntax Tree (AST) construction
✅ Semantic validation of musical structure
✅ Named section declaration and referencing
✅ Time signature nesting and validation
✅ Audio generation using FluidSynth (Melodia.wav)
⏳ [WIP] Export to LilyPond .ly format for sheet music rendering
🧱 Language Components
🔹 Notes and Alterations
Notes: A to G (Anglo-Saxon notation)
Octaves: 1 to 8 (e.g., C4, G5)
Alterations: # (sharp), b (flat)
Dotted notes: e.g., C5 q. increases duration by 50%
Rests: - q, - h, - w, etc.
🔹 Duration Symbols
w: Whole note (4 beats)
h: Half note (2 beats)
q: Quarter note (1 beat)
e: Eighth note (0.5 beats)
s: Sixteenth note (0.25 beats)
🔹 Separators
,: separates notes within a measure ➔ handled by NotesSequence
|: separates different measures ➔ handled by MeasureSequence
🔹 Time Signature
time 4/4 {
  C4 q, D4 q, E4 q, F4 q |
  G4 h, A4 q, G4 q;
}
Defines beats per measure and beat duration.

🔹 Repeat Blocks
repeat 2 {
  A4 q, B4 q, C5 q, D5 q
}
Repeats the block n times.

🔹 Section Declaration and Reference
section intro {
  E5 e, F5 e, G5 e, A5 e;
}

intro
Reusable sections for modular composition.

🌳 AST Overview
Main AST Classes:

StatementSequence: chains multiple statements
Note: represents individual notes with pitch, duration, and modifiers
NotesSequence: comma-separated list of notes/rests
MeasureSequence: pipe-separated measures
Time: defines a time signature block
RepeatDeclaration: defines repeat blocks
SectionDeclaration & SectionReference: manage reusable blocks
🤍 Semantic Rules
time blocks must contain measures matching the defined duration
Notes/rests must not exceed 4.0 beats (in 4/4 context)
Repeated/referenced sections must comply with time constraints
Sections must be declared before being referenced
🔊 Audio Generation
Using FluidSynth and libsndfile, the compiler converts parsed music to audio.

Notes ➔ MIDI values (C1 to C8, with sharps/flats)
Rests ➔ zeroed audio buffers
Output:
Melodia.wav
⚙️ Installation (WSL/Linux)
sudo apt update
sudo apt install bison flex libfluidsynth-dev libsndfile1-dev
📦 Additional Setup
To support audio generation, download the required SoundFont (.sf2) files using Git LFS:

# 1. Install Git LFS
sudo apt install git-lfs

# 2. Configure Git LFS
git lfs install

# 3. Download large files (SoundFonts)
git lfs pull
▶️ Usage
make
./validator input.txt
If parsing and analysis succeed, the file Melodia.wav will be generated.

📙 Repository
https://github.com/emilker/Compiladores.git