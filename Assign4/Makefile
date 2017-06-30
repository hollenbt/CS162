CC = g++ -std=c++11
exe = Pokemon_Go

$(exe)): 
	$(CC) AI.cpp Cave.cpp Charizard.cpp Espeon.cpp Blank.cpp Flying.cpp Game_World.cpp Geodude.cpp Location.cpp main.cpp Mewtwo.cpp Onix.cpp Poke_stop.cpp Pokemon.cpp Prof.cpp Psychic.cpp Rayquaza.cpp Rock.cpp Trainer.cpp validation_library.cpp -o $(exe)

debug: 
	$(CC) -D DEBUG AI.cpp Cave.cpp Charizard.cpp Espeon.cpp Blank.cpp Flying.cpp Game_World.cpp Geodude.cpp Location.cpp main.cpp Mewtwo.cpp Onix.cpp Poke_stop.cpp Pokemon.cpp Prof.cpp Psychic.cpp Rayquaza.cpp Rock.cpp Trainer.cpp validation_library.cpp -o $(exe)_DEBUG

clean:
	rm -f *.o $(exe)*
