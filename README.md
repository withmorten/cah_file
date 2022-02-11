# cah_file
### Battle for Middle-Earth II - Rise of the Witch-king: .cah (CreateAHero) parser/writer (ALAESTR2)

quick & dirty parser/writer for the CreateAHero file format found in bfme2 and rise of the witch king, but only tested on the latter.

it's a commandline tool when you include main.cpp in the compilation, but cah_file.h and cah_file.cpp can be compiled into a project as a library.

can read and write files, and update the checksum according to edits so that the game accepts it as valid.

main purpose for me so far has been changing GUIDs so I can use them across computers without potentially causing desyncs (I have no idea how this game uses the GUIDs).

run premake-vs20**.cmd and compile, for my test project.

write stuff in `edit_cah()` in main.cpp, to do stuff.
