#ifndef _F_ANIMATEDOBJECT_H_
#define _F_ANIMATEDOBJECT_H_


#include "F_Sprite.h"
#include <rapidxml.hpp>
#include <fstream>
#include "Error.h"
#include <map>
#include "SpriteManager.h"
using namespace rapidxml;

namespace Feintgine
{

	struct f_anim
	{
		F_Sprite sprite;
		float time;
	};

	class f_animation
	{
	public:
		f_animation()
		{

		}
		~f_animation()
		{
		}

		void create(const std::string & animationName)
		{
			m_animName = animationName;
			//std::cout << "adding animation " << m_animName << "\n";
		}
		
		void addAnim(const f_anim & tsprite, bool isLoop )
		{
			m_anims.push_back(tsprite);
			if (isLoop)
			{
				
				m_loop = m_anims.size() - 1;	
			}
		}

		void playAnimation(int time )
		{
			
			m_time = time;
			m_playing = true;
			if (m_anims.size() > 0)
			{
				//m_curIndex = 0;
				m_currentSprite = &m_anims[m_curIndex];
			}
			if (!m_currentSprite)
			{
				return;
			}
		}

		void setAnimation()
		{
			m_currentSprite = &m_anims[m_curIndex];
		}
		void updateAnim(float deltaTime)
		{
			if (m_currentSprite)
			{
				if (m_time > 0)
				{
					if (m_playing)
					{

						m_animTime += (m_animSpeed * deltaTime);
						if (m_animTime > m_currentSprite->time)
						{
							m_animTime = 0;
							m_curIndex++;
							if (m_curIndex >= m_anims.size())
							{
								m_curIndex = m_loop;
								m_time--;
								if (m_time == 0)
								{
									m_playing = false;
								}
							}
							m_currentSprite = &m_anims[m_curIndex];
						}
					}
				}

				else if (m_time < 0)
				{
					if (m_playing)
					{
						if (m_currentSprite)
						{
							m_animTime += (m_animSpeed * deltaTime);
							if (m_animTime > m_currentSprite->time)
							{
								m_animTime = 0;
								m_curIndex++;
								if (m_curIndex >= m_anims.size())
								{
									m_curIndex = m_loop;
								}
								m_currentSprite = &m_anims[m_curIndex];
							}
						}
					}
				}
			}


		}
		void stop()
		{
			m_playing = false;
		}

		bool isPlaying() const { return m_playing; }

		
		std::vector<f_anim> getAnims() { return m_anims; }
		std::string getAnimName() const { return m_animName; }

		f_anim * getCurrentAnim() const { return m_currentSprite; }

		void setCurrentAnimTime(float value)
		{
			if (m_currentSprite)
			{
				std::cout << "set data to " << value << "\n";
				m_currentSprite->time = value;
			}
		}

		int getCurrentIndex() const { return m_curIndex; }

		size_t getSize() const { return m_anims.size(); }
		
		void setAnimIndex(int index)
		{
			m_curIndex = index;
			m_currentSprite = &m_anims[m_curIndex];
		}
		
	private :

		std::vector<f_anim> m_anims;
		f_anim * m_currentSprite;
		std::string m_animName;
		int loopIndex = 0;

		int m_curIndex = 0;
		float m_animTime = 0;
		float m_animSpeed = 1.0f;

		int m_time = -1;

		int m_loop = 0;

		bool m_playing = false;
	};

	class F_AnimatedObject
	{
	public:
		F_AnimatedObject();
		~F_AnimatedObject();

		void init(const std::string & filePath, const glm::vec2 & scaleFactor = glm::vec2(1));

		void saveToFile(const std::string & name);
		

		void playAnimation(const std::string & name,int time = -1);

		void setAnimation(const std::string & name);

		void draw(Feintgine::SpriteBatch & spriteBatch);

		void update(float deltaTime);

		void setDepth(float depth);

		void setAngle(float angle);

		void rotate(float angle);

		float getAngle() const { return m_angle; }

		void setAlpha(float alpha);

		std::string getName() const { return m_name; }

		bool isPlaying() const { 
			
			if(m_currentAnimation)
			return m_currentAnimation->isPlaying(); }

		void setScale(const glm::vec2 & scale);
		void setPos(const glm::vec2 & pos);

		glm::vec2 getDim() const { return m_scale * m_currentAnimation->getCurrentAnim()->sprite.getDim(); }

		glm::vec2 getPos() const { return m_pos; }

		bool isInited() const { return m_isInited; }

		f_animation * getCurrentAnimation() const { return m_currentAnimation; }

		std::map<std::string, f_animation> getMap() const { return m_animations; }
	private:

		std::string m_filePath;
		std::string m_name;
		glm::vec2 m_pos;
		glm::vec2 m_scale = glm::vec2(1);

		bool m_isInited = false;


		float m_depth = 4;
		float m_angle = 0.0;
		Feintgine::Color m_color = Feintgine::Color(255, 255, 255, 255);
		std::map<std::string,f_animation> m_animations;
		f_animation * m_currentAnimation = nullptr;
	};
}

#endif