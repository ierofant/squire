#ifndef SQUIRE_TZK_DETAIL_TS_VISITORS_HPP_INCLUDED
#define SQUIRE_TZK_DETAIL_TS_VISITORS_HPP_INCLUDED

#include <squire/tzk/ts_channel.hpp>

namespace squire { namespace tzk { namespace detail
{
    template<ts_type TYPE>
    class ts_get_key_visitor : public boost::static_visitor<bool>
    {
	public:
	    ts_get_key_visitor(ts_position<TYPE> const &_pos, std::string &_key) : pos(_pos), key(_key) {}

	public:
	    template<ts_type TYPE1>
	    bool operator()(ts_channel<TYPE1> const &_channel) const {return false;}
	    bool operator()(ts_channel<TYPE> const &_channel) const {return _channel.get_key(pos, key);}

	private:
	    ts_position<TYPE> const &pos;
	    std::string &key;
    };

    template<ts_type TYPE>
    class ts_set_key_visitor : public boost::static_visitor<bool>
    {
	public:
	    ts_set_key_visitor(ts_position<TYPE> const &_pos, std::string const &_key) : pos(_pos), key(_key) {}

	public:
	    template<ts_type TYPE1>
	    bool operator()(ts_channel<TYPE1> &_channel) const {return false;}
	    bool operator()(ts_channel<TYPE> &_channel) const {return _channel.set_key(pos, key);}

	private:
	    ts_position<TYPE> const &pos;
	    std::string const &key;
    };

}}}

#endif //SQUIRE_TZK_DETAIL_TS_VISITORS_HPP_INCLUDED
