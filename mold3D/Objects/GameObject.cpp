#include <mold3D/3D.h>

using namespace mold::render::objects;

GameObject::GameObject(Point3D point, RGB color, Float3D Size, uint32_t TextureIndex)
{
    this->coords = point;
    this->color = color;
    this->Size = Size;
    this->TextureIndex = TextureIndex;
}

GameObject::GameObject() {}

void GameObject::Draw() {}