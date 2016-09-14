#pragma once
#include "SmiteObject.h"
#include "rapidjson\document.h"
#include "rapidjson\writer.h"
#include "rapidjson\stringbuffer.h"

namespace SmiteAPI
{
	class SmiteDataUsed :
		public SmiteObject
	{
	public:
		SmiteDataUsed();
		SmiteDataUsed(std::string& input);
		~SmiteDataUsed();

		const std::string operator[](const std::string& key);

		void parse(std::string& input);

	private:
		rapidjson::Document object;
	};
}