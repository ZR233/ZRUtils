#pragma once
#include "boost/asio.hpp"

namespace zrutils
{
	static inline uint64_t hton64(uint64_t x)
	{
#if defined(_WIN32)
#include <WinSock2.h>
		return htonll(x);
#else
		// AABBCCDD EEFFGGHH 
		x = (x >> 32) | (x << 32);                  // EEFFGGHH AABBCCDD 
		x = ((x >> 16) & 0x0000ffff0000ffffull) |   // 0000EEFF 0000AABB 
			((x << 16) & 0xffff0000ffff0000ull);    // GGHH0000 CCDD0000 
													// GGHHEEFF CCDDAABB 
		x = ((x >> 8) & 0x00ff00ff00ff00ffull) |    // 00GG00EE 00CC00AA 
			((x << 8) & 0xff00ff00ff00ff00ull);     // HH00FF00 DD00BB00  
		return x;
#endif
	}
	static inline uint64_t ntoh64(uint64_t x)
	{
#if defined(_WIN32)
#include <WinSock2.h>
		return ntohll(x);
#else
		 AABBCCDD EEFFGGHH 
		x = (x >> 32) | (x << 32);                  // EEFFGGHH AABBCCDD 
		x = ((x >> 16) & 0x0000ffff0000ffffull) |   // 0000EEFF 0000AABB 
			((x << 16) & 0xffff0000ffff0000ull);    // GGHH0000 CCDD0000 
													// GGHHEEFF CCDDAABB 
		x = ((x >> 8) & 0x00ff00ff00ff00ffull) |    // 00GG00EE 00CC00AA 
			((x << 8) & 0xff00ff00ff00ff00ull);     // HH00FF00 DD00BB00  
		return x;
#endif
	}
}
