#include "pch.h"
#include "Square.h"
#include "SelectGDI.h"
#include "Collider.h"

Square::Square(Vec2 pos, Vec2 scale)
{
	SetPos(pos);
	SetScale(scale);
	CreateCollider();
	GetCollider()->SetScale(scale);
}

Square::~Square()
{
}

void Square::Update()
{
}

void Square::Render(HDC _dc)
{
	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	RECT rt =
	{
		pos.x - scale.x / 2.f,
		pos.y - scale.y / 2.f,
		pos.x + scale.x / 2.f,
		pos.y + scale.y / 2.f
	};

	HBRUSH brush = (HBRUSH)GetStockObject(BLACK_BRUSH);
	HBRUSH old = (HBRUSH)SelectObject(_dc, brush);

	Rectangle(_dc, rt.left, rt.top, rt.right, rt.bottom);

	//DeleteObject(brush);
	SelectObject(_dc, old);
}
