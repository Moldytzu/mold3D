cd mold3D

g++ -c GameObject.cpp -I../
g++ -c Pyramid.cpp -I../
g++ -c Cube.cpp -I../
g++ -c Core.cpp -I../
g++ -c Camera.cpp -I../
g++ -c EventSystem.cpp -I../

cd ..

#g++ main.cpp mold3D/*.o -lglut -lGLU -lGL -o game -I.
g++ main.cpp mold3D/*.o -lGL -lGLU -lSDL2 -o game -I.
./game