#include "StdAfx.h"
#include <iostream>
#include "SmiteProtocolConfig.h"

namespace SmiteAPI
{
	SmiteProtocolConfig::SmiteProtocolConfig(SmiteProtocolEndpoint endpoint)
	{
		this->initialize();
		this->setEndpoint(endpoint);
	}

	SmiteProtocolConfig::SmiteProtocolConfig(std::string devId, std::string apiKey, SmiteProtocolEndpoint endpoint, SmiteProtocolLanguage language)
	{
		this->initialize();
		this->setDevId(devId);
		this->setApiKey(apiKey);
		this->setEndpoint(endpoint);
	}

	SmiteProtocolConfig::~SmiteProtocolConfig()
	{
	}

	void SmiteProtocolConfig::initialize()
	{
		this->api_url.insert(std::pair<SmiteProtocolEndpoint, std::string>(
			SmiteProtocolEndpoint::PC, "http://api.smitegame.com/smiteapi.svc"
		));
		this->api_url.insert(std::pair<SmiteProtocolEndpoint, std::string>(
			SmiteProtocolEndpoint::PS, "http://api.ps4.smitegame.com/smiteapi.svc"
		));
		this->api_url.insert(std::pair<SmiteProtocolEndpoint, std::string>(
			SmiteProtocolEndpoint::XBOX, "http://api.xbox.smitegame.com/smiteapi.svc"
		));
	}

	std::string SmiteProtocolConfig::getDevID()
	{
		return this->dev_id;
	}

	std::string SmiteProtocolConfig::getApiKey()
	{
		return this->api_key;
	}

	SmiteProtocolEndpoint SmiteProtocolConfig::getEndpoint()
	{
		return this->endpoint;
	}

	SmiteProtocolLanguage SmiteProtocolConfig::getLanguage()
	{
		return this->language;
	}

	std::string SmiteProtocolConfig::getApiUrl()
	{
		return this->api_url[this->getEndpoint()];
	}

	void SmiteProtocolConfig::setDevId(std::string devId)
	{
		this->dev_id = devId;
	}

	void SmiteProtocolConfig::setApiKey(std::string apiKey)
	{
		this->api_key = apiKey;
	}

	void SmiteProtocolConfig::setEndpoint(SmiteProtocolEndpoint endPoint)
	{
		this->endpoint = endPoint;
	}

	void SmiteProtocolConfig::setLanguage(SmiteProtocolLanguage lang)
	{
		this->language = lang;
	}
}