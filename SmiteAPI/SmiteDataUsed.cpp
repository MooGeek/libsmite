#include "stdafx.h"
#include "SmiteDataUsed.h"
#include <iostream>

namespace SmiteAPI
{
	SmiteDataUsed::SmiteDataUsed()
	{
	}

	SmiteDataUsed::SmiteDataUsed(std::string & input)
	{
		this->parse(input);
	}


	SmiteDataUsed::~SmiteDataUsed()
	{
	}

	const std::string SmiteDataUsed::operator[](const std::string& key)
	{
		return this->object[key.c_str()].GetString();
	}

	void SmiteDataUsed::parse(std::string& input)
	{
		this->object.Parse(input.c_str());

		std::cout << this->object["Concurrent_Sessions"].GetString() << std::endl;
	}
}