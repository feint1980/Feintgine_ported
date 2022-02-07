#include "ResourceManager.h"

namespace Feintgine{

	TextureCache ResourceManager::_textureCache;

	IOFileCache ResourceManager::m_IOCache;

	GLTexture ResourceManager::getTexture(const std::string & filePath)
	{
		return _textureCache.getTexture(filePath);

	}


	std::vector<char> ResourceManager::getPreloadedFile(const std::string & filePath)
	{
		return m_IOCache.getBuffer(filePath);
	}

}
