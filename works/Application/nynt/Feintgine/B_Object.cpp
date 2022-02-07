#include "B_Object.h"



B_Object::B_Object()
{
}


B_Object::~B_Object()
{
}

void B_Object::create(const std::string & prefab, glm::vec2 pos, glm::vec2 scale, float t_angle, float depth)
{
	init(prefab);
	m_pos = pos;
	reScale(scale);
	m_angle = t_angle;
	m_depth = depth;
	//selected = false;
	
	updateColiders();

}

void B_Object::reScale(glm::vec2 scale)
{
	m_dims.x = actual_dim.x * scale.x;
	m_dims.y = actual_dim.y * scale.y;
}

void B_Object::drawRect(Feintgine::DebugRender & renderer)
{
	if (!selected)
	{

		if (!hovered)
		{
			return;
		}
		else
		{
			t_rectColor = Feintgine::Color(0, 255, 255, 255);
		}
		

	}
	else
	{
		t_rectColor = Feintgine::Color(255, 255, 0, 255);
	}
	renderer.drawBox_center(glm::vec4(m_pos, m_dims), t_rectColor, m_angle);
	
}

void B_Object::checkInside(const glm::vec2 & mouse)
{
	hovered = checkMouse(mouse);
	
}

bool B_Object::checkMouse(const glm::vec2 & mouse)
{
	glm::vec2 halfdim = m_dims / 2.0f;
	if (mouse.x > m_pos.x - halfdim.x && mouse.x < m_pos.x + halfdim.x && mouse.y > m_pos.y - halfdim.y && mouse.y < m_pos.y + halfdim.y)
	{
		return true;
	}
	return false;


}

Sprite B_Object::getProtoSer()
{
	Sprite t_sprite;
	
	t_sprite.set_x_pos(m_pos.x);
	t_sprite.set_y_pos(m_pos.y);

	glm::vec2 scale = getScale();
	t_sprite.set_x_scale(scale.x);
	t_sprite.set_y_scale(scale.y);
	t_sprite.set_angle(m_angle);
	t_sprite.set_prefab(prefabPath);
	
	return t_sprite;
}

glm::vec2 B_Object::getScale()
{
	glm::vec2 scale;

	scale.x = m_dims.x / actual_dim.x;
	scale.y = m_dims.y / actual_dim.y;
	
	return scale;
}

void B_Object::setSelect(bool val)
{
	selected = val;

}

void B_Object::draw(Feintgine::SpriteBatch & spriteBatch)
{
	glm::vec4 desRect;
	desRect.x = m_pos.x - m_dims.x / 2.0f;
	desRect.y = m_pos.y - m_dims.y / 2.0f;
	desRect.z = m_dims.x;
	desRect.w = m_dims.y;
	spriteBatch.draw(desRect, m_uv, m_texture.id, m_depth +t_priority, m_color, m_angle);
}

void B_Object::updateColiders()
{
	for (int i = 0; i < m_coliders.size(); i++)
	{
		m_coliders[i].setPos(m_coliders[i].getPos() + m_pos);
	}
}

void B_Object::Destroy()
{
	destroyed = true;
}

void B_Object::drag(const glm::vec2 & pos)
{
	glm::vec2 des = pos + m_offset;

	m_pos = des;

	updateColiders();
	

}

void B_Object::calculateOffset(glm::vec2 pos)
{
	m_offset = m_pos - pos;
}

void B_Object::calculatePriority()
{
	if (m_type == TYPE_OBJECT || m_type == TYPE_TREE || m_type == TYPE_PLANT)
	{
		float amount = 0.05;
		float repost = (m_pos.y - (m_dims.y / 2.0f)) / 10000.0f;
		t_priority = amount - repost;
	}
	if (m_type == TYPE_DECAL)
	{
		t_priority = 0.06;
	}


}
