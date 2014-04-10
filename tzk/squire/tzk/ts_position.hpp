#ifndef SQUIRE_TZK_TS_POSITION_HPP_INCLUDED
#define SQUIRE_TZK_TS_POSITION_HPP_INCLUDED

#include <cstdlib>
#include <squire/tzk/ts_type.hpp>

namespace squire { namespace tzk 
{
    template<ts_type>
    class ts_position;

    typedef ts_position<ts_type::ANALOG> ts_position_analog;
    typedef ts_position<ts_type::DIGITAL> ts_position_digital;

    template<>
    class ts_position<ts_type::ANALOG>
    {
	public:
	    ts_position(unsigned _group = 0);

	public:
	    operator unsigned() const;
	    bool operator<(ts_position const &_other) const;
	    ts_position& operator=(unsigned _group);
	    ts_position& operator++();
	    ts_position operator++(int);

	public:
	    unsigned get_group() const;
	    void set_group(unsigned _group);
	    
	private:
	    unsigned group;
    };

    template<>
    class ts_position<ts_type::DIGITAL> : protected ts_position<ts_type::ANALOG>
    {
	public:
	    ts_position(unsigned _group = 0, unsigned short _impulse = 0);

	public:
	    bool operator<(ts_position const &_other) const;
	    ts_position& operator++();
	    ts_position operator++(int);

	public:
	    using ts_position<ts_type::ANALOG>::get_group;
	    using ts_position<ts_type::ANALOG>::set_group;
	    unsigned short get_impulse() const;
	    void set_impulse(unsigned short _impulse);

	public:
	    static const constexpr std::size_t num_impulses = 8;

	private:
	    unsigned short impulse;
    };
}}

#endif //SQUIRE_TZK_TS_POSITION_HPP_INCLUDED
