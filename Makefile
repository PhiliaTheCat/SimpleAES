bin/SimpleAES.exe: lib/Block.lib lib/SimpleAES.lib \
                   lib/Key.lib lib/AESAlgo.lib
	g++ lib/Block.lib lib/SimpleAES.lib \
	    lib/Key.lib lib/AESAlgo.lib \
		-o bin/SimpleAES.exe

lib/Block.lib: src/Block.cpp
	g++ -c src/Block.cpp -o lib/Block.lib

lib/SimpleAES.lib: src/SimpleAES.cpp
	g++ -c src/SimpleAES.cpp -o lib/SimpleAES.lib

lib/Key.lib: src/Key.cpp
	g++ -c src/Key.cpp -o lib/Key.lib

lib/AESAlgo.lib: src/AESAlgo.cpp
	g++ -c src/AESAlgo.cpp -o lib/AESAlgo.lib

run: bin/SimpleAES.exe
	./bin/SimpleAES.exe
