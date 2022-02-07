#ifndef _LIGHTBATCH_H_
#define _LIGHTBATCH_H_

#include <vector>
#include <glm/glm.hpp>
#include "GLSLProgram.h"


namespace Feintgine
{

	class LightBatch
	{
	public:
		LightBatch();
		~LightBatch();


		void initShader(Feintgine::GLSLProgram *shader);

		void begin();

		void addLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation);


		void renderLight();

	private:

		Feintgine::GLSLProgram * m_shader;
		std::vector<glm::vec2> m_lightListPos;

		std::vector<glm::vec4> m_lightListColor;
		std::vector<glm::vec3> m_lightListAttenuation;


	};
}

#endif
