#include <squire/tzk/ts_position.hpp>

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE data_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ts_position_test_suite)

struct fixture
{
    squire::tzk::ts_position_digital digital_pos;
    squire::tzk::ts_position_analog analog_pos;
};

BOOST_FIXTURE_TEST_CASE(ts_position_test, fixture)
{
    BOOST_CHECK_EQUAL(digital_pos.get_group(), 0);
    BOOST_CHECK_EQUAL(digital_pos.get_impulse(), 0);

    BOOST_CHECK_EQUAL(analog_pos.get_group(), 0);
}

BOOST_FIXTURE_TEST_CASE(ts_position_set_group, fixture)
{
    digital_pos.set_group(5);
    BOOST_CHECK_EQUAL(digital_pos.get_group(), 5);

    analog_pos.set_group(100);
    BOOST_CHECK_EQUAL(analog_pos.get_group(), 100);
}

BOOST_FIXTURE_TEST_CASE(ts_position_set_impulse, fixture)
{
    digital_pos.set_impulse(6);
    BOOST_CHECK_EQUAL(digital_pos.get_impulse(), 6);
}

BOOST_FIXTURE_TEST_CASE(ts_position_increment, fixture)
{
    for(std::size_t i = 0; i < digital_pos.num_impulses; ++i, ++digital_pos)
	BOOST_CHECK_EQUAL(digital_pos.get_impulse(), i);

    BOOST_CHECK_EQUAL(digital_pos.get_impulse(), 0);
    BOOST_CHECK_EQUAL(digital_pos.get_group(), 1);

    digital_pos++;
    BOOST_CHECK_EQUAL(digital_pos.get_impulse(), 1);
    BOOST_CHECK_EQUAL(digital_pos.get_group(), 1);

    ++analog_pos;
    BOOST_CHECK_EQUAL(analog_pos.get_group(), 1);

    analog_pos++;
    BOOST_CHECK_EQUAL(analog_pos.get_group(), 2);
}

BOOST_AUTO_TEST_SUITE_END()
