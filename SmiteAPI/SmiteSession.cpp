#include "stdafx.h"
#include "SmiteSession.h"
#include <iostream>

namespace SmiteAPI
{
	SmiteSession::SmiteSession()
	{
		this->object = new rapidjson::Document();
	}

	SmiteSession::SmiteSession(std::string& input)
	{
		this->object = new rapidjson::Document();
		this->parse(input);
	}

	SmiteSession::~SmiteSession()
	{
	}

	const std::string SmiteSession::operator[](const std::string& key)
	{
		return (*(this->object))[key.c_str()].GetString();
	}

	void SmiteSession::parse(std::string& input)
	{
		this->object->Parse(input.c_str());
	}

	const std::string SmiteSession::getID()
	{
		return (*(this->object))["session_id"].GetString();
	}
}