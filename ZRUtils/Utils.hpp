#pragma once
#include <boost/asio.hpp>
#include <vector>
#include <exception>
#include <boost/exception/all.hpp>
#include <codecvt>
#include <locale>


namespace zrutils
{
	static inline uint64_t hton64(uint64_t x)
	{
//#if defined(_WIN32)
//#include <WinSock2.h>
//#pragma comment(lib,"ws2_32.lib")
//		return htonll(x);
//#else
		// AABBCCDD EEFFGGHH 
		x = (x >> 32) | (x << 32);                  // EEFFGGHH AABBCCDD 
		x = ((x >> 16) & 0x0000ffff0000ffffull) |   // 0000EEFF 0000AABB 
			((x << 16) & 0xffff0000ffff0000ull);    // GGHH0000 CCDD0000 
													// GGHHEEFF CCDDAABB 
		x = ((x >> 8) & 0x00ff00ff00ff00ffull) |    // 00GG00EE 00CC00AA 
			((x << 8) & 0xff00ff00ff00ff00ull);     // HH00FF00 DD00BB00  
		return x;
//#endif
	}
	static inline uint64_t ntoh64(uint64_t x)
	{
//#if defined(_WIN32)
//#include <WinSock2.h>
//#pragma comment(lib,"ws2_32.lib")
//		return ntohll(x);
//#else
		 //AABBCCDD EEFFGGHH 
		x = (x >> 32) | (x << 32);                  // EEFFGGHH AABBCCDD 
		x = ((x >> 16) & 0x0000ffff0000ffffull) |   // 0000EEFF 0000AABB 
			((x << 16) & 0xffff0000ffff0000ull);    // GGHH0000 CCDD0000 
													// GGHHEEFF CCDDAABB 
		x = ((x >> 8) & 0x00ff00ff00ff00ffull) |    // 00GG00EE 00CC00AA 
			((x << 8) & 0xff00ff00ff00ff00ull);     // HH00FF00 DD00BB00  
		return x;
//#endif
	}



/*************************************************
Author:zr
Date:2018-03-5
Description:异常类 含错误码 逐级增加信息功能
**************************************************/


	//
	//异常类 含错误码 逐级增加信息功能
	class exception :
		virtual public std::exception,
		virtual public boost::exception
	{
	public:
		//@error_str 错误文字
		exception(std::string error_str) {
			typedef boost::error_info<struct tag_erro_no, int> err_no;
			typedef boost::error_info<struct tag_erro_str, std::string> err_str;
			(*this) << err_str(error_str);
			v_.push_back(error_str);
		};
		//@error_str 错误文字
		//@error_code 错误号
		exception(std::string error_str, int error_code) {
			typedef boost::error_info<struct tag_erro_no, int> err_no;
			typedef boost::error_info<struct tag_erro_str, std::string> err_str;
			v_.push_back(error_str);
			this->error_code_ = error_code;
			(*this) << err_str(error_str);
			(*this) << err_no(error_code);
		};
		virtual ~exception() {};
		//在前端加入信息
		virtual void add(std::string a) {
			v_.insert(v_.begin(), a);
			//std::string str;
			//if (!v_.empty())
			//{
			//	for (const auto& i : v_)
			//	{
			//		str += i;
			//	}
			//}
			//(*this) << boost::error_info<struct tag_erro_str, std::string>(str);
		};
		//获取错误信息vector
		virtual std::vector<std::string>& get() {
			return v_;
		};
		//获取全部错误信息
		virtual std::string what() {
			std::string str;
			if (!v_.empty())
			{
				for (const auto& i : v_)
				{
					str += i;
				}
			}
			return str;
		};
		virtual void setError_code(int error_code) {
			this->error_code_ = error_code;
		}
		virtual int getError_code() {
			return error_code_;
		}
	protected:
		std::vector<std::string> v_;
		int error_code_ = 9;
	};
	

	static inline std::vector<uint8_t> char16toNetBytes(std::u16string x)
	{
		std::vector<uint8_t> buf;
		for (size_t i = 0; i < x.size(); i++)
		{
			uint8_t one[2];
			memcpy_s(one, 2, &(x[i]), 2);
			buf.push_back(one[1]);
			buf.push_back(one[0]);
		}
		return buf;
	}
	static inline std::vector<uint8_t> netBytestoChar16Bytes(std::vector<uint8_t> x)
	{
		std::vector<uint8_t> buf;
		for (size_t i = 0; i < x.size()/2; i++)
		{
			uint8_t one[2];
			one[0] = x[i * 2];
			one[1] = x[i * 2 + 1];
			buf.push_back(one[1]);
			buf.push_back(one[0]);
		}
		return buf;
	}
}
