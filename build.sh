cd mold3D

g++ -c GameObject.cpp -I../
g++ -c Pyramid.cpp -I../
g++ -c Cube.cpp -I../
g++ -c Core.cpp -I../
g++ -c Camera.cpp -I../

cd ..

g++ main.cpp mold3D/*.o -lglut -lGLU -lGL -o game -I.
./game