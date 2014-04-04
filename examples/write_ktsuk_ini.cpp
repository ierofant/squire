#include <iostream>
#include <squire/ktsuk/ktsuk_ini_parser.hpp>

int main()
{
    boost::property_tree::ptree ptree, section1, section2, child1;
    child1.put("<xmlattr>.1", "a");
    child1.put("<xmlattr>.2", "b");
    child1.put("<xmlattr>.3", "");
    child1.put("<xmlattr>.4", "d");
    section1.put("<xmlattr>.s1", 1);
    section1.put("<xmlattr>.s2", 2);
    section1.add_child("Child1", child1);
    ptree.add_child("root.Section1", section1);
    ptree.add_child("root.Section2", section2);
    
    squire::ktsuk::write_ktsuk_ini(std::cout, ptree);

    return 0;
}
