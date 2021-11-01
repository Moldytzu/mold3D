#include <mold3D/3D.h>

using namespace mold::objects;

GameObject::GameObject(Float3D X, Float3D Y, Float3D Z)
{
    this->X = X;
    this->Y = Y;
    this->Z = Z;
}

GameObject::GameObject() {}

void GameObject::Draw() {}