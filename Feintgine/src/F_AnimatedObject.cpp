#include "F_AnimatedObject.h"


namespace Feintgine
{



	F_AnimatedObject::F_AnimatedObject()
	{
		//std::cout << "called \n";
	}


	F_AnimatedObject::~F_AnimatedObject()
	{
	}

	void F_AnimatedObject::init(const std::string & filePath,const glm::vec2 & scaleFactor)
	{
		std::cout << "init animate object " << filePath << " \n";
		m_filePath = filePath;
		m_animations.clear();
		m_currentAnimation = nullptr;
		m_scale = scaleFactor;
		xml_document<> doc;

		std::ifstream file(m_filePath.c_str());
		if (!file)
		{
			std::cout << "nothing found \n";
			return;
		}
		std::vector<char> buffer = ResourceManager::getPreloadedFile(m_filePath.c_str());// std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		//buffer.push_back('\0');
		doc.parse<0>(&buffer[0]);

		xml_node<> * F_AObj_node = nullptr;
		F_AObj_node = doc.first_node("F_AObj");
		
		if (!F_AObj_node)
		{
			std::cout << "Error while parsing value F_AnimatedObject.cpp \n";
		}
		m_name = F_AObj_node->first_attribute("name")->value();

		xml_node<> * animations_node = F_AObj_node->first_node("animations");

		for (xml_node<> * animation_node = animations_node->first_node("animation");
			animation_node; animation_node = animation_node->next_sibling())
		{
			f_animation t_animation;
			t_animation.create(animation_node->first_attribute("name")->value());
			
			xml_node<> * anims_node = animation_node->first_node("anims");
			for (xml_node<> * anim_node = anims_node->first_node("anim");
				anim_node; anim_node = anim_node->next_sibling())
			{
				f_anim anim;
				anim.sprite = SpriteManager::Instance()->getSprite(anim_node->first_attribute("name")->value());
				anim.time = std::stof(anim_node->first_attribute("time")->value());
				bool isLoop = false;
				if (anim_node->first_attribute("loop"))
				{
				//	std::cout << "found loop \n";
					
					isLoop = true;
						
				}
				t_animation.addAnim(anim,isLoop);
			}
			
			if (m_animations.insert(std::pair<std::string, f_animation>(t_animation.getAnimName(), t_animation)).second)
			{
			//	std::cout << "added animation " << t_animation.getAnimName() << " successfully \n";
			}
			else
			{
				//std::cout << "failed to add animation " << t_animation.getAnimName() << " \n";
			}
		}
		m_isInited = true;
		m_currentAnimation = &m_animations.begin()->second;

	}

	void F_AnimatedObject::saveToFile(const std::string & name)
	{
		std::string finalName = "Assets/F_AObjects/" + name + ".xml";
		if (feint_common::Instance()->isFileExist(finalName))
		{
			std::cout << "file exist \n";
		}
		else
		{
			std::cout << "file does not exist \n";
		}
		xml_document<> doc;
		xml_node<> * F_AObj_node = doc.allocate_node(node_element,"F_AObj");
		F_AObj_node->append_attribute(doc.allocate_attribute("name", name.c_str()));
		xml_node<> * animations_node = doc.allocate_node(node_element,"animations");
		F_AObj_node->append_node(animations_node);

		
		for (auto it = m_animations.begin(); it != m_animations.end(); it++)
		{
		
			xml_node<> * animation_node = doc.allocate_node(node_element,"animation");
			animation_node->append_attribute(doc.allocate_attribute("name", it->first.c_str()));
			xml_node<> * anims_node = doc.allocate_node(node_element,"anims");
			animation_node->append_node(anims_node);
			std::string nameValue = "";
			std::string timeValue = "";		
			for (auto i = 0; i < it->second.getAnims().size(); i++)
			{
			//	std::cout << "write loop " << i << "\n";
				
				std::string packetName = it->second.getAnims()[i].sprite.getPacketName().c_str();
				size_t lastindex = packetName.find_last_of(".");
				std::string rawname = packetName.substr(0, lastindex);
				std::string spriteName = it->second.getAnims()[i].sprite.getName().c_str();


				nameValue = rawname +"/"+ spriteName;
				const std::string::size_type size = nameValue.size();
				char *buffer = new char[size + 1];   //we need extra char for NUL
				memcpy(buffer, nameValue.c_str(), size + 1);
				xml_node<> * anim_node = doc.allocate_node(node_element,"anim");
				//std::string trimedPacket = feint_common::Instance()->getFileNameFromPath(it->second.getAnims()[i].sprite.getPacketName());
				
				
				anim_node->append_attribute(doc.allocate_attribute("name", buffer));
				
				timeValue = feint_common::Instance()->convertPreciousFloatToString(it->second.getAnims()[i].time);
				const std::string::size_type size2 = timeValue.size();
				char *buffer2 = new char[size2 + 1];   //we need extra char for NUL
				memcpy(buffer2, timeValue.c_str(), size2 + 1);

 				anim_node->append_attribute(doc.allocate_attribute("time",
					buffer2));

 				anims_node->append_node(anim_node);
			}
			
			animations_node->append_node(animation_node);
		}
		doc.append_node(F_AObj_node);
		std::cout << "write " << m_name << " to " << finalName << "\n";
		std::ofstream fileSave(finalName);
		fileSave << doc;
		fileSave.close();
		doc.clear();
		std::cout << "process done\n";
	}

	void F_AnimatedObject::playAnimation(const std::string & name, int time)
	{
		//std::cout << "play animation " << name << "\n";
		auto it = m_animations.find(name);
		if (it != m_animations.end())
		{
			m_currentAnimation = &it->second;
			if (m_currentAnimation)
			{
				m_currentAnimation->playAnimation(time);
			}
			else
			{
				//std::cout << "not play \n";
			}
		}
		else
		{
			//std::cout << "animation " << name << " not found !\n";
		}

	
	}

	void F_AnimatedObject::setAnimation(const std::string & name)
	{
		auto it = m_animations.find(name);
		if (it != m_animations.end())
		{
			m_currentAnimation = &it->second;
			if (m_currentAnimation)
			{
				m_currentAnimation->setAnimation();
			}
			else
			{
				std::cout << "not play \n";
			}
		}
		else
		{
			//std::cout << "animation " << name << " not found !\n";
		}
	}

	void F_AnimatedObject::draw(Feintgine::SpriteBatch & spriteBatch)
	{
		if (m_currentAnimation)
		{
			if (m_currentAnimation->getCurrentAnim())
			{
				glm::vec4 desRect;// (0, 0, 50, 50);
				desRect.x = m_pos.x - (m_currentAnimation->getCurrentAnim()->sprite.getDim().x * m_scale.x / 2.0f);
				desRect.y = m_pos.y - (m_currentAnimation->getCurrentAnim()->sprite.getDim().y * m_scale.y / 2.0f);
				desRect.z = m_scale.x * m_currentAnimation->getCurrentAnim()->sprite.getDim().x;
				desRect.w = m_scale.y * m_currentAnimation->getCurrentAnim()->sprite.getDim().y;

				spriteBatch.draw(desRect, m_currentAnimation->getCurrentAnim()->sprite.getUV(), m_currentAnimation->getCurrentAnim()->sprite.getTexture().id, m_depth, m_color, m_angle);
			}
		}
			
		
	}

	void F_AnimatedObject::update(float deltaTime)
	{
		if (m_currentAnimation)
		{
			m_currentAnimation->updateAnim(deltaTime);
		}
	}

	void F_AnimatedObject::setDepth(float depth)
	{
		m_depth = depth;
	}

	void F_AnimatedObject::setAngle(float angle)
	{
		m_angle = angle;
	}

	void F_AnimatedObject::rotate(float angle)
	{
		m_angle += angle;
	}

	void F_AnimatedObject::setAlpha(float alpha)
	{
		m_color.a = alpha;
	}

	void F_AnimatedObject::setScale(const glm::vec2 & scale)
	{
		m_scale = scale;
	}

	void F_AnimatedObject::setPos(const glm::vec2 & pos)
	{
		m_pos = pos;
	}

	

}
