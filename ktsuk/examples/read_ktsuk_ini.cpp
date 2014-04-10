#include <boost/property_tree/xml_parser.hpp>
#include <squire/ktsuk/ktsuk_ini_parser.hpp>

static constexpr const char *str = 
    "root {"
    "	Section1 {"
    "		s1:1"
    "		s2:2"
    "		Child1 { 1:a 2:b 3: 4:d }"
    "	}"
    "	Section2 { }"
    "}";

int main()
{
    std::istringstream in(str);
    boost::property_tree::ptree ptree;
    squire::ktsuk::read_ktsuk_ini(in, ptree);

    boost::property_tree::write_xml(std::cout, ptree,
				    boost::property_tree::xml_writer_make_settings('\t', 1));
    return 0;
}
