#ifndef SQUIRE_TZK_TS_HPP_INCLUDED
#define SQUIRE_TZK_TS_HPP_INCLUDED

#include <boost/variant.hpp>
#include <squire/tzk/ts_channel.hpp>
#include <squire/tzk/detail/ts_visitors.hpp>

namespace squire { namespace tzk
{
    class ts
    {
	public:
	    typedef boost::variant< ts_channel_digital,
				    ts_channel_analog> channel_type;
	    typedef std::map<std::string, channel_type> chanmap_type;

	public:
	    bool has_channel(std::string const &_chankey) const;
	    ts_type get_channel_type(std::string const &_chankey) const;

	    template<ts_type TYPE>
	    ts_channel<TYPE> const& get_channel(std::string const &_chankey) const
	    {
		return boost::get<ts_channel<TYPE> const&>(chanmap.at(_chankey));
	    }

	    bool get_key(std::string const &_channel, unsigned _pos, std::string &_key) const;

	    template<ts_type TYPE>
	    bool get_key(std::string const &_channel, ts_position<TYPE> const &_pos, std::string &_key) const
	    {
		bool retval = false;
		auto itr = chanmap.find(_channel);
		if(itr != chanmap.end()) retval = boost::apply_visitor(detail::ts_get_key_visitor<TYPE>(_pos, _key), itr->second);
		return retval;
	    }

	    bool add_channel(std::string const &_chankey, ts_type _type);
	    void remove_channel(std::string const &_chankey);

	    template<ts_type TYPE>
	    bool set_key(std::string const &_channel, ts_position<TYPE> const &_pos, std::string const &_key)
	    {
		bool retval = false;
		auto itr = chanmap.find(_channel);
		if(itr != chanmap.end()) retval = boost::apply_visitor(detail::ts_set_key_visitor<TYPE>(_pos, _key), itr->second);
		return retval;
	    }

	private:
	    chanmap_type chanmap;
    };
}}

#endif //SQUIRE_TZK_TS_HPP_INCLUDED
