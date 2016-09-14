// SmiteAPI.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include "SmiteProtocolTypes.h"
#include "SmiteProtocol.h"

#include <iostream>

using namespace std;

int main()
{
	SmiteAPI::SmiteProtocol *api = new SmiteAPI::SmiteProtocol("1759", "DAB436BEE6E4463985A2A7BB24A2DAF6", SmiteAPI::SmiteProtocolEndpoint::PC, SmiteAPI::SmiteProtocolLanguage::English);
	std::string json = "{\"ret_msg\": \"Approved\", \"session_id\": \"wqifn3r039f3iwf\", \"timestamp\": \"215/125/1235 151:125:5\"}";

//	api->getDataUsed();


	rapidjson::Document* obj = new rapidjson::Document();
	rapidjson::Document& object = *obj;
	object.Parse("[{\"Active_Sessions\":8,\"Concurrent_Sessions\":50,\"Request_Limit_Daily\":7500,\"Session_Cap\":500,\"Session_Time_Limit\":15,\"Total_Requests_Today\":62,\"Total_Sessions_Today\":82,\"ret_msg\":null}]");
	
	static const char* kTypeNames[] =
	{ "Null", "False", "True", "Object", "Array", "String", "Number" };
	
	for (rapidjson::Value::ConstMemberIterator itr = object[0].MemberBegin();
		itr != object[0].MemberEnd(); ++itr)
	{
		printf("Type of member %s is %s\n",
			itr->name.GetString(), kTypeNames[itr->value.GetType()]);
	}

    return 0;
}

