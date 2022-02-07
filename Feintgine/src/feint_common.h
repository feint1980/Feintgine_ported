
#ifndef _FEINT_COMMON_H_
#define _FEINT_COMMON_H_

#include <string>
#include <glm/glm.hpp>
#include <fcntl.h>
#ifdef _WIN32 
#include <io.h>
#include <windows.h>
#elif __linux__ 

#endif

#include <locale>
#include <clocale>
#include <codecvt>
#include <iostream>
#include <SDL/SDL.h>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "objectData.pb.h"
#include <time.h>
#include <fstream>


#define RANDOM_VALUE (_type_,t_lo,t_hi) t_lo + static_cast <_type_> (rand()) / (static_cast <_type_> (RAND_MAX / (t_hi - t_lo)))


class feint_common
{
public:
	feint_common();

	static feint_common *Instance()
	{
		if (p_Instance == 0)
		{
			p_Instance = new feint_common;
			return p_Instance;
		}
		return p_Instance;
	}

	~feint_common();

	float getRandomNum(float low, float hight);

	void testPrintUtf8(const std::wstring & msg);

	void showMessageBox(const std::string & msgtitle, const std::string & msgcontent);

	bool showConfirmationBox(const std::string & msgtitle, const std::string & msgcontent);

	inline bool isFileExist(const std::string& name) {
		std::ifstream f(name.c_str());
		return f.good();
	}

	std::string convertWstringToString(const std::wstring & value);

	std::wstring convertStringtoWstring(const std::string & value);

	std::string findAndRepalce(const std::string &source,const std::string &a, const std::string & b);

	std::string convertVec2toString(const glm::vec2 & t_value);

	glm::vec2 convertStringToVec2(const std::string & x_string , const std::string & y_string);
	
	std::string getPathName(const std::string & str);

	std::string getFileNameFromPath(const std::string & str);

	std::string getNonTypeFile(const std::string & str);

	std::string convertPreciousFloatToString(float value, int precious = 2);

	std::string convertVec2ToStringWithPrecious(const glm::vec2 & value, int precious);

	glm::vec2 convertProcVec2ToVec2(const Proc_Vec2 & v2);


	glm::vec3 convertProcVec3ToVec3(const Proc_Vec3 & v3);


	glm::vec4 convertProcVec4ToVec4(const Proc_Vec4 & v4);

	Proc_Vec2 convertVec2ToProcVec2(const glm::vec2 & v2);


	Proc_Vec3 convertVec3ToProcVec3(const glm::vec3 & v3);

	Proc_Vec4 convertVec4ToProcVec4(const glm::vec4 & v4);

	float randomFloat(float a, float b);



private:

	static feint_common *p_Instance;

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	
};
#endif 

