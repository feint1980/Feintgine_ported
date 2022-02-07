#include "F_TilePart.h"


namespace Feintgine
{


	F_TilePart::F_TilePart()
	{
	}


	F_TilePart::~F_TilePart()
	{
	}

	void F_TilePart::create(const glm::vec2 & pos, const glm::vec2 & dim, const glm::vec4 & uv,
		const glm::vec2 & jumpUV, const GLTexture & texture)
	{
		m_pos = pos;
		m_uv = uv;
		m_uvJump = jumpUV;
		m_texture = texture;
		m_dim = dim;
	}

	void F_TilePart::setDepth(float depth)
	{
		m_depth = depth;
	}

	void F_TilePart::draw(SpriteBatch & spriteBatch)
	{
		glm::vec4 desRect;
		desRect.x = m_pos.x - m_dim.x / 2.0f;
		desRect.y = m_pos.y - m_dim.y / 2.0f;
		desRect.z = m_dim.x;
		desRect.w = m_dim.y;
		spriteBatch.draw(desRect, m_uv, m_texture.id, m_depth, m_color);
	}

	void F_TilePart::update(float delta)
	{
		if (animationTime >= totalTime)
		{
			m_uv.x += m_uvJump.x;
			animationTime = 0;
		}
		animationTime += 0.1 * delta;
	
	}

}
