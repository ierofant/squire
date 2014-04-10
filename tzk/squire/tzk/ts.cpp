#include <squire/tzk/ts.hpp>

namespace squire { namespace tzk
{
    bool ts::has_channel(std::string const &_chankey) const
    {
	return chanmap.find(_chankey) != chanmap.end();
    }

    ts_type ts::get_channel_type(std::string const &_chankey) const
    {
	return static_cast<ts_type>(chanmap.at(_chankey).which());
    }

    bool ts::get_key(std::string const &_channel, unsigned _pos, std::string &_key) const
    {
	return get_key(_channel, ts_position_analog(_pos), _key);
    }

    bool ts::add_channel(std::string const &_chankey, ts_type _type)
    {
	bool retval = !has_channel(_chankey);
	if(retval) 
	{
	    switch(_type)	
	    {
		case ts_type::DIGITAL:
		    chanmap[_chankey] = ts_channel<ts_type::DIGITAL>();
		    break;

		case ts_type::ANALOG:
		    chanmap[_chankey] = ts_channel<ts_type::ANALOG>();
		    break;
	    }
	}
	return retval;
    }

    void ts::remove_channel(std::string const &_chankey)
    {
	auto itr = chanmap.find(_chankey);
	if(itr != chanmap.end()) chanmap.erase(itr);
    }
}}
