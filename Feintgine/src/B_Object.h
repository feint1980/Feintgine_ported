#ifndef _B_OBJECT_H
#define _B_OBJECT_H

#include "SimpleDrawingObejct.h"

const int TYPE_ALL = -1;
const int TYPE_TERRIAN = 0;
const int TYPE_OBJECT = 1;
const int TYPE_TREE = 2;
const int TYPE_PLANT = 3;
const int TYPE_DECAL = 4;

class B_Object : public SimpleDrawingObject
{
public:
	B_Object();
	~B_Object();

	void create(const std::string & prefab, glm::vec2 pos, glm::vec2 scale, float t_angle , float depth);

	void reScale(glm::vec2 scale);

	void drawRect(Feintgine::DebugRender & renderer);

	void checkInside(const glm::vec2 & mouse);

	bool checkMouse(const glm::vec2 & mouse);

	Sprite getProtoSer();

	glm::vec2 getScale();

	bool isDestroyed() const { return destroyed; }

	bool isHover() const { return hovered; }

	bool isSelect() const { return selected; }

	void setSelect(bool val);

	void draw(Feintgine::SpriteBatch & spriteBatch);

	void updateColiders();

	void Destroy();

	void drag(const glm::vec2 & pos);

	void calculateOffset(glm::vec2 pos);

	void calculatePriority();

private:

	Feintgine::Color t_rectColor;

	bool destroyed = false;

	bool hovered = false;

	bool selected = false;

	float t_priority = 0;

	glm::vec2 m_offset;

};

#endif

