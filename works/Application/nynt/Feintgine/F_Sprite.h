#ifndef _F_SPRITE_H_
#define _F_SPRITE_H_

#include <string>
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "GLTexture.h"
#include "ResourceManager.h"
#include "objectData.pb.h"

namespace Feintgine {
	
	class F_Sprite
	{
	public:
		F_Sprite();
		~F_Sprite();
		F_Sprite(const glm::vec2 & pos,const glm::vec2 & dim,const glm::vec2 & anchor, const std::string & texture_path, const std::string & packetName, const std::string & name);

		void setDim(const glm::vec2 & dim);

		void setAnchor(const glm::vec2 & anchor);
		void setTextureDim(const glm::vec2 & textureDim);

		void init(const glm::vec2 & pos, const glm::vec2 & dim, const glm::vec2 & anchor, const std::string & texture_path, const std::string & packetName, const std::string & name);


		void createFromProc(const Proc_Sprite & sprite);
		glm::vec2 getDim() const { return m_dim; }
		glm::vec2 getPos() const { return m_pos; }
		glm::vec2 getAnchor() const { return m_anchor; }
		glm::vec2 getTextureDim() const { return m_textureDim; }

		Proc_Vec2 convertVec2ToProcVec2(const glm::vec2 & v2);
		Proc_Vec3 convertVec3ToProcVec3(const glm::vec3 & v3);
		Proc_Vec4 convertVec4ToProcVec4(const glm::vec4 & v4);



		std::string getTexturePath() const { return m_texturePath; }

		Proc_Sprite getProcSprite();

		Feintgine::GLTexture getTexture() const { return m_texture; }


		std::string getName() const { return m_name; }
		std::string getPacketName() const { return m_packetName; }

		std::string getFullPacket() const {
			std::string returnVal;
			size_t lastindex = m_packetName.find_last_of(".");
			std::string rawname = m_packetName.substr(0, lastindex);
			returnVal = rawname + "/"+ m_name;
			return returnVal;
		}

		glm::vec4 getUV() const { return m_uv; }
		void updateUV();

	private:

		Feintgine::GLTexture m_texture;


		std::string m_texturePath;
		std::string m_packetName;
		std::string m_name;

		glm::vec2 m_dim;
		glm::vec2 m_pos;
		glm::vec2 m_anchor;
		glm::vec2 m_textureDim;

		glm::vec4 m_uv;


	};
}
#endif
