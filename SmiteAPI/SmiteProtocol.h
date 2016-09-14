#pragma once
#include "SmiteProtocolTypes.h"
#include "SmiteProtocolConfig.h"
#include <initializer_list>
#include <memory>

namespace SmiteAPI
{
	class SmiteProtocol
	{
	public:
		SmiteProtocol(std::string devID, std::string apiKey, SmiteProtocolEndpoint endpoint, SmiteProtocolLanguage language);
		~SmiteProtocol();

		std::shared_ptr<SmiteSession> getSession();
		std::shared_ptr<SmiteDataUsed> getDataUsed();
		bool checkSession();

	private:
		std::shared_ptr<SmiteProtocolConfig> config;
		std::string response_format;
		std::shared_ptr<SmiteSession> session;
		
		static const std::string SESSION_TEST_KEYWORD;


		static size_t writeResponse(void* contents, size_t size, size_t nmemb, void* userp);
		std::string sendRequest(std::string url);
		std::string createSignature(std::string method);
		std::string getTimestamp();
		std::string digest(std::string str);
		std::string request(std::string method);
		template <class T> std::string request(std::string method, std::initializer_list<T> parameters);
		void initSession();
		
	};
}