cd mold3D

g++ -c *.cpp -I../

cd ..

#g++ main.cpp mold3D/*.o -lglut -lGLU -lGL -o game -I.
g++ main.cpp mold3D/*.o -lGL -lGLU -lSDL2 -o game -I.
./game