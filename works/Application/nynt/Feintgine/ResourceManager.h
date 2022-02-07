
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include "TextureCache.h"
#include <string>
#include <iostream>
#include <fstream>
#include "IOFileCache.h"
namespace Feintgine
{

	class ResourceManager
	{
	public:
		static GLTexture getTexture(const std::string & filePath);

		static std::vector<char> getPreloadedFile(const std::string & filePath);

		static GLuint boundTexture;

	private:
		static TextureCache _textureCache;
		static IOFileCache m_IOCache;
		

	};
}

#endif

