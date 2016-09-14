#include "StdAfx.h"
#include <curl\curl.h>
#include <openssl\md5.h>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <iostream>
#include <vector>
#include "SmiteProtocol.h"

namespace SmiteAPI
{
	const std::string SmiteProtocol::SESSION_TEST_KEYWORD = "successful";


	SmiteProtocol::SmiteProtocol(std::string devID, std::string apiKey, SmiteProtocolEndpoint endpoint, SmiteProtocolLanguage language)
	{
		this->config = std::make_shared<SmiteProtocolConfig>(devID, apiKey, endpoint, language);
		this->response_format = "Json";
	}

	SmiteProtocol::~SmiteProtocol()
	{
	}

	std::shared_ptr<SmiteSession> SmiteProtocol::getSession()
	{
		if (this->session == nullptr)
		{
			this->initSession();
		}
		else
		{
			if (this->checkSession())
			{
				return this->session;
			}
			else
			{
				this->session = nullptr;
				return this->getSession();
			}
		}

		return this->session;
	}

	std::shared_ptr<SmiteDataUsed> SmiteProtocol::getDataUsed()
	{
		auto method = "getdataused";
		
		std::string response = this->request(method);
		
		return std::make_shared<SmiteDataUsed>(response);
	}

	void SmiteProtocol::initSession()
	{
		auto method = "createsession";
		auto signature = this->createSignature(method);
		std::stringstream url;

		url << this->config->getApiUrl() << "/"
			<< method
			<< this->response_format << "/"
			<< this->config->getDevID() << "/"
			<< signature << "/"
			<< this->getTimestamp();

		std::string response = this->sendRequest(url.str());

		this->session = std::make_shared<SmiteSession>(response);
	}

	bool SmiteProtocol::checkSession()
	{
		if (this->session)
		{
			auto method = "testsession";
			
			auto signature = this->createSignature(method);
			std::stringstream url;

			url << this->config->getApiUrl() << "/"
				<< method
				<< this->response_format << "/"
				<< this->config->getDevID() << "/"
				<< signature << "/"
				<< this->session->getID() << "/"
				<< this->getTimestamp();

			std::string response = this->sendRequest(url.str());

			if (response.find(SmiteProtocol::SESSION_TEST_KEYWORD) == std::string::npos)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}

	std::string SmiteProtocol::createSignature(std::string method)
	{
		auto timestamp = this->getTimestamp();

		auto signatureString = this->config->getDevID() + method + this->config->getApiKey() + timestamp;
		auto signatureDigest = this->digest(signatureString);

		return std::string(signatureDigest);
	}

	std::string SmiteProtocol::getTimestamp()
	{
		auto time = std::time(nullptr);
		struct tm timeinfo;
		gmtime_s(&timeinfo, &time);
		std::ostringstream oss;
		oss << std::put_time(&timeinfo, "%Y%m%d%H%M%S");

		return oss.str();
	}

	std::string SmiteProtocol::digest(std::string str)
	{
		MD5_CTX md5handler;
		unsigned char md5digest[MD5_DIGEST_LENGTH];
		char md5hex[MD5_DIGEST_LENGTH * 2];
		auto timestamp = this->getTimestamp();

		MD5_Init(&md5handler);
		MD5_Update(&md5handler, str.c_str(), str.length());
		MD5_Final(md5digest, &md5handler);

		for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
		{
			sprintf_s(&md5hex[i * 2], MD5_DIGEST_LENGTH * 2, "%02x", (unsigned int)md5digest[i]);
		}

		return std::string(md5hex);
	}

	std::string SmiteProtocol::request(std::string method)
	{
		return this->request(method, std::initializer_list<int>());
	}

	template <class T>
	std::string SmiteProtocol::request(std::string method, std::initializer_list<T> parameters)
	{
		std::cout << "called this request" << std::endl;
		auto session = this->getSession();
		auto signature = this->createSignature(method);
		std::stringstream url;

		url << this->config->getApiUrl() << "/"
			<< method
			<< this->response_format << "/"
			<< this->config->getDevID() << "/"
			<< signature << "/"
			<< session->getID() << "/"
			<< this->getTimestamp();

		for (auto param : parameters)
		{
			url << "/" << param;
		}
		std::cout << "final url: " << url.str() << std::endl;
		return this->sendRequest(url.str());
	}

	std::string SmiteProtocol::sendRequest(std::string url)
	{
		CURL *curl = curl_easy_init();
		CURLcode res;
		std::string readBuffer;

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, SmiteProtocol::writeResponse);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
		}

		return readBuffer;
	}

	size_t SmiteProtocol::writeResponse(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
}