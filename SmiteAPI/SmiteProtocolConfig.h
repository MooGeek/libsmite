#pragma once
#include "SmiteProtocolTypes.h"
#include <string>
#include <map>

namespace SmiteAPI
{
	class SmiteProtocolConfig
	{
	public:
		SmiteProtocolConfig(SmiteProtocolEndpoint endpoint);
		SmiteProtocolConfig(std::string devId, std::string apiKey, SmiteProtocolEndpoint endpoint, SmiteProtocolLanguage language);
		~SmiteProtocolConfig();

		std::string getDevID();
		std::string getApiKey();
		std::string getApiUrl();
		SmiteProtocolEndpoint getEndpoint();
		SmiteProtocolLanguage getLanguage();

		void setDevId(std::string devId);
		void setApiKey(std::string apiKey);
		void setEndpoint(SmiteProtocolEndpoint endPoint);
		void setLanguage(SmiteProtocolLanguage lang);

	private:
		void initialize();

	private:
		std::string dev_id;
		std::string api_key;
		SmiteProtocolLanguage language;
		SmiteProtocolEndpoint endpoint;
		std::map<SmiteProtocolEndpoint, std::string> api_url;
	};
}