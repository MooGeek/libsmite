#pragma once
#include "SmiteObject.h"
#include <string>
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"

namespace SmiteAPI
{
	class SmiteSession:
		SmiteObject
	{
	public:
		SmiteSession();
		SmiteSession(std::string& input);
		~SmiteSession();

		const std::string operator[](const std::string& key);

		void parse(std::string& input);
		const std::string getID();

	private:
		rapidjson::Document* object;
	};
}