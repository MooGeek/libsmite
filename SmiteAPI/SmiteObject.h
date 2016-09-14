#pragma once
#include <string>

namespace SmiteAPI
{
	class SmiteObject
	{
	public:
		SmiteObject() {};
		virtual ~SmiteObject() {};
		virtual const std::string operator[](const std::string& key) = 0;
		virtual void parse(std::string& input) = 0;
	};
}