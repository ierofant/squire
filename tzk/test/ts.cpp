#include <squire/tzk/ts.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE data_test
#include <boost/test/unit_test.hpp>

using namespace squire::tzk;

BOOST_AUTO_TEST_SUITE(ts_channel_test_suite)

struct fixture
{
    ts tstab;
};

BOOST_FIXTURE_TEST_CASE(ts, fixture)
{
    BOOST_CHECK(!tstab.has_channel("foo"));

    std::string key;
    BOOST_CHECK(!tstab.get_key("foo", 0, key));
}

BOOST_FIXTURE_TEST_CASE(ts_add_channel, fixture)
{
    std::string key;

    tstab.add_channel("digital", ts_type::DIGITAL);
    BOOST_CHECK(tstab.has_channel("digital"));
    BOOST_CHECK(tstab.get_channel_type("digital") == ts_type::DIGITAL);

    tstab.add_channel("analog", ts_type::ANALOG);
    BOOST_CHECK(tstab.has_channel("analog"));
    BOOST_CHECK(tstab.get_channel_type("analog") == ts_type::ANALOG);
}

BOOST_FIXTURE_TEST_CASE(ts_remove_channel, fixture)
{
    tstab.add_channel("foo", ts_type::DIGITAL);
    tstab.remove_channel("foo");
    BOOST_CHECK(!tstab.has_channel("foo"));
}

BOOST_FIXTURE_TEST_CASE(ts_set_key, fixture)
{
    std::string key;

    tstab.add_channel("digital", ts_type::DIGITAL);
    BOOST_CHECK(tstab.set_key("digital", ts_position_digital(0, 0), "A"));
    BOOST_CHECK(tstab.get_key("digital", ts_position_digital(0, 0), key));
    BOOST_CHECK_EQUAL(key, "A");

    BOOST_CHECK(!tstab.set_key("digital", ts_position_digital(0, 1), "A"));

    BOOST_CHECK(tstab.set_key("digital", ts_position_digital(0, 0), "B"));
    BOOST_CHECK(tstab.get_key("digital", ts_position_digital(0, 0), key));
    BOOST_CHECK_EQUAL(key, "B");
}

BOOST_AUTO_TEST_SUITE_END()
