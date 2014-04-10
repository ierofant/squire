#ifndef SQUIRE_TZK_TS_CHANNEL_HPP_INCLUDED
#define SQUIRE_TZK_TS_CHANNEL_HPP_INCLUDED

#include <boost/bimap.hpp>
#include <boost/bimap/support/lambda.hpp>
#include <squire/tzk/ts_position.hpp>

namespace squire { namespace tzk
{
    template<ts_type TYPE>
    class ts_channel
    {
	public:
	    typedef ts_position<TYPE> position_type;
	    typedef boost::bimap<position_type, std::string> keymap_type;
	    typedef typename keymap_type::left_map::const_iterator const_iterator;

	public:
	    const_iterator begin() const {return keymap.left.begin();}
	    const_iterator end() const {return keymap.right.end();}
	    bool has_key(std::string const &_key) const {return (keymap.right.find(_key) != keymap.right.end());}
	    bool get_key(position_type const &_pos, std::string &_key) const
	    {
		auto itr = keymap.left.find(_pos);
		bool retval = (itr != keymap.left.end());
		if(retval) _key = itr->second;
		return retval;
	    }

	    bool set_key(position_type const &_pos, std::string const &_key)
	    {
		bool retval = !has_key(_key);
		if(retval)
		{
		    auto itr = keymap.left.find(_pos);
		    if(itr == keymap.left.end()) keymap.left.insert(std::make_pair(_pos, _key));
		    else keymap.left.modify_data(itr, boost::bimaps::_data = _key);
		}
		return retval;
	    }

	    void erase(std::size_t _pos)
	    {
		auto itr = keymap.left.find(position_type(_pos));
		if(itr != keymap.left.end()) keymap.left.erase(itr);
	    }

	    void erase(position_type const &_pos)
	    {
		auto itr = keymap.left.find(_pos);
		if(itr != keymap.left.end()) keymap.left.erase(itr);
	    }

	    void erase(std::string const &_key)
	    {
		auto itr = keymap.right.find(_key);
		if(itr != keymap.right.end()) keymap.right.erase(itr);
	    }

	private:
	    keymap_type keymap;
    };

    typedef ts_channel<ts_type::DIGITAL> ts_channel_digital;
    typedef ts_channel<ts_type::ANALOG> ts_channel_analog;
}}

#endif //SQUIRE_TZK_TS_CHANNEL_HPP_INCLUDED
