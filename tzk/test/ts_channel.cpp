#include <squire/tzk/ts_channel.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE data_test
#include <boost/test/unit_test.hpp>

using namespace squire::tzk;

BOOST_AUTO_TEST_SUITE(ts_channel_test_suite)

struct fixture
{
    ts_channel_analog channel;
};

BOOST_FIXTURE_TEST_CASE(ts_channel, fixture)
{
    BOOST_CHECK(!channel.has_key("foo"));
}

BOOST_FIXTURE_TEST_CASE(ts_channel_set_key, fixture)
{
    std::string key;
    BOOST_CHECK(channel.set_key(0, "foo"));
    BOOST_CHECK(channel.has_key("foo"));
    BOOST_CHECK(channel.get_key(0, key));
    BOOST_CHECK_EQUAL(key, "foo");

    BOOST_CHECK(!channel.set_key(1, "foo"));

    BOOST_CHECK(channel.set_key(0, "foo1"));
    BOOST_CHECK(channel.has_key("foo1"));
    BOOST_CHECK(channel.get_key(0, key));
    BOOST_CHECK_EQUAL(key, "foo1");
    BOOST_CHECK(!channel.has_key("foo"));
}

BOOST_FIXTURE_TEST_CASE(ts_channel_erase, fixture)
{
    std::string key;

    channel.set_key(0, "foo");
    channel.erase(0);
    BOOST_CHECK(!channel.has_key("foo"));
    BOOST_CHECK(!channel.get_key(0, key));

    channel.set_key(0, "foo");
    channel.erase(ts_position_analog(0));
    BOOST_CHECK(!channel.has_key("foo"));
    BOOST_CHECK(!channel.get_key(0, key));

    channel.set_key(0, "foo");
    channel.erase("foo");
    BOOST_CHECK(!channel.has_key("foo"));
    BOOST_CHECK(!channel.get_key(0, key));
}

BOOST_AUTO_TEST_SUITE_END()
