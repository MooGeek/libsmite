#pragma once
#include "SmiteObject.h"
#include "SmiteSession.h"
#include "SmiteDataUsed.h"

namespace SmiteAPI
{
	enum /*class*/ SmiteProtocolEndpoint { 
		PC, 
		XBOX, 
		PS
	};

	enum /*class*/ SmiteProtocolLanguage {
		English = 1,
		German = 2,
		French = 3,
		Spanish = 7,
		LatinSpanish = 9,
		Portuguese = 10,
		Russian = 11,
		Polish = 12,
		Turkish = 13
	};

	enum /*class*/ SmiteProtocolQueue {
	};
}