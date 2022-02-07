
#ifndef _F_TILEPART_H_
#define _F_TILEPART_H_

#include "GLTexture.h"
#include <glm/glm.hpp>
#include "SpriteBatch.h"

namespace Feintgine
{


	class F_TilePart
	{
	public:
		F_TilePart();
		~F_TilePart();
		void create(const glm::vec2 & pos,const glm::vec2 & dim , const glm::vec4 & uv, const glm::vec2 & jumpUV, const GLTexture & texture);
		void setDepth(float depth);
		void draw(SpriteBatch & spriteBatch);
		void update(float delta);

	private:
		glm::vec2 m_dim;
		glm::vec4 m_uv;
		GLTexture m_texture;
		glm::vec2 m_pos;
		glm::vec2 m_uvJump;
		float m_depth;
		Color m_color = Color(255,255,255,255);

		float animationTime = 0;
		float totalTime = 1.25f;


	};
}

#endif