rm -R ./build
cmake . -B ./build/
make -C ./build/
./build/playerTest
./build/agario