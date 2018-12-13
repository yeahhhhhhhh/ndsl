/**
 * @file MultiplexerTest.cc
 * @brief
 * MultiplexerµÄµ¥Ôª²âÊÔ
 *
 * @author zzt
 * @email 429834658@qq.com
 */

#include "catch.hpp"
#include "ndsl/net/Mutiplexer.h"
#include "ndsl/net/Connection.h"

using namespace ndsl;
using namespace net;

int id = 11;
void fun1(char data*, int len);

TEST_CASE("Mutiplexer/cbmaptest")
{
	using Callback = Boost::function<void(char *data, int len)>;
	using CallbackMap = std::map<int, Callback>;
	CallbackMap cbMap;
	Multiplexer mymulti(conn, cbMap);
	
	SECTION("insert")
	{
		mymulti.insert(id, fun1);
	}
	SECTION("remove")
	{
		mymulti.remove(id);
	}
}