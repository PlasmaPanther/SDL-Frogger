#pragma once
#include "../AnimatedTexture2D.h"

class FroggerEntity
{
public:
	FroggerEntity() = default;
	~FroggerEntity() = default;

	virtual void Init(Vector2 _pos) = 0;

	virtual void Update() = 0;
	virtual void Render() = 0;

	virtual void Move(Vector2 _vel) { m_Texture2D.Move(_vel); m_AnimatedTexture.Move(_vel); m_Position += _vel; }

	virtual Vector2 GetPosition() { return m_Position; }
	virtual Texture2D& GetTexture() { return m_Texture2D; }

	virtual void Clean() = 0;

protected:

	AnimatedTexture2D m_AnimatedTexture;
	Texture2D m_Texture2D;

	Vector2 m_Velocity;
	Vector2 m_Position;

};

