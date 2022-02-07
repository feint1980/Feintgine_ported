#include "IOFileCache.h"

namespace Feintgine {

	IOFileCache::IOFileCache()
	{
	}


	IOFileCache::~IOFileCache()
	{
	}
		

	std::vector<char> IOFileCache::getBuffer(const std::string &filePath)
	{

		auto map_interator = m_xmlPreload.find(filePath);

		if (map_interator == m_xmlPreload.end())
		{

			std::ifstream file(filePath);
			if (!file)
			{
				//FLOG("file " + filePath + " not found");
				std::vector<char> buffer;
				return buffer;
			}
			else
			{
				std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
				buffer.push_back('\0');
				m_xmlPreload.insert(std::make_pair(filePath, buffer));
				return buffer;
			}	
		}
		return map_interator->second;
		
	}

	//	xml_document<> IOFileCache::getFullDoc(const std::string &filePath)
//	{
// 		auto map_interator = m_xmlPreload.find(filePath);
// 
// 		if (map_interator == m_xmlPreload.end())
// 		{
// 			std::ifstream file(filePath);
// 			m_xmlPreload.insert(std::make_pair(filePath, &file));
// 			return &file;
// 		}
// 

		
// 		return map_interator->second;
		//xml_document<> doc;
		//return nullptr;
//	}
	

}
