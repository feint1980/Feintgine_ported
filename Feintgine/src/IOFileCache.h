
#ifndef _IOFILECACHE_H_
#define _IOFILECACHE_H_

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <rapidxml.hpp>
#include <vector>

using namespace rapidxml;
namespace Feintgine {
	class IOFileCache
	{
	public:
		IOFileCache();
		~IOFileCache();
	//	std::ifstream * getFilePreloaded(const std::string & filePath);

	//	xml_document<> getFullDoc(const std::string &filePath);
		std::vector<char> getBuffer(const std::string &filePath);
	private:
		std::map<std::string, std::vector<char> > m_xmlPreload;

	};
}

#endif