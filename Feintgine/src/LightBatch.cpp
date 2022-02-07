#include "LightBatch.h"


namespace Feintgine {



	LightBatch::LightBatch()
	{
	}


	LightBatch::~LightBatch()
	{
	}

	void LightBatch::initShader(Feintgine::GLSLProgram *shader)
	{
		m_shader = shader;
	}

	void LightBatch::begin()
	{
		m_lightListPos.reserve(m_lightListPos.size());
		m_lightListColor.reserve(m_lightListPos.size());
		m_lightListAttenuation.reserve(m_lightListPos.size());

		

		m_lightListPos.clear();
		m_lightListColor.clear();
		m_lightListAttenuation.clear();


	}

	void LightBatch::addLight(const glm::vec2 & pos, const glm::vec4 & color, const glm::vec3 & attenuation)
	{
		m_lightListPos.push_back(pos);
		m_lightListColor.push_back(color);
		m_lightListAttenuation.push_back(attenuation);
	}

	void LightBatch::renderLight()
	{

		GLint lightPosIndex = m_shader->getUniformLocation("lightPos");
		glUniform2fv(lightPosIndex, m_lightListPos.size(), reinterpret_cast<GLfloat *>(m_lightListPos.data()));

		GLint lightColorIndex = m_shader->getUniformLocation("lightColor");
		glUniform4fv(lightColorIndex, m_lightListColor.size(), reinterpret_cast<GLfloat *>(m_lightListColor.data()));

		GLint lightAttenuationIndex = m_shader->getUniformLocation("lightAttenuation");
		glUniform3fv(lightAttenuationIndex, m_lightListAttenuation.size(), reinterpret_cast<GLfloat *>(m_lightListAttenuation.data()));

		GLint countIndex = m_shader->getUniformLocation("lightCount");
		glUniform1i(countIndex, m_lightListPos.size());
	}
}


