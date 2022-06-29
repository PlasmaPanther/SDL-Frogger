#include "Object2D.h"

Object2D::Object2D(float x, float y) {

    _Vector2.x = x;
    _Vector2.y = y;

    m_DestRect = { 0, 0, 0, 0 };
    m_SrcRect = { 0, 0, 0, 0 };

}

void Object2D::Move(Vector2 _vec){
	m_DestRect.x += _vec.x;
	m_DestRect.y += _vec.y;
}

bool CheckCollision(Object2D& ObjectA, Object2D& ObjectB)
{
    SDL_FRect RectA = ObjectA.GetRect();
    SDL_FRect RectB = ObjectB.GetRect();

    if (RectA.y + RectA.h >= RectB.y) {
        return true;
    }

    if (RectA.y <= RectB.y + RectB.h) {
        return true;
    }

    if (RectA.x + RectA.w >= RectB.x) {
        return true;
    }

    if (RectA.x >= RectB.x + RectB.w) {
        return true;
    }

    return false;
}

SDL_FRect& Object2D::GetRect()
{
	return m_DestRect;
}