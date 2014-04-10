#include <iostream>
#include <squire/tzk/ts_position.hpp>

namespace squire { namespace tzk
{
    ts_position<ts_type::ANALOG>::ts_position(unsigned _group)
	: group(_group)
    {

    }

    ts_position<ts_type::ANALOG>::operator unsigned() const
    {
	return get_group();
    }

    bool ts_position<ts_type::ANALOG>::operator<(ts_position const &_other) const
    {
	return get_group() < _other.get_group();
    }

    ts_position<ts_type::ANALOG>& ts_position<ts_type::ANALOG>::operator=(unsigned _group)
    {
	set_group(_group);
	return *this;
    }
    
    ts_position<ts_type::ANALOG>& ts_position<ts_type::ANALOG>::operator++()
    {
	++group;
	return *this;
    }
    
    ts_position<ts_type::ANALOG> ts_position<ts_type::ANALOG>::operator++(int)
    {
	ts_position<ts_type::ANALOG> temp = *this;
	this->operator++();
	return temp;
    }

    unsigned ts_position<ts_type::ANALOG>::get_group() const
    {
	return group;
    }
    
    void ts_position<ts_type::ANALOG>::set_group(unsigned _group)
    {
	group = _group;
    }

    ts_position<ts_type::DIGITAL>::ts_position(unsigned _group, unsigned short _impulse)
	: ts_position<ts_type::ANALOG>(_group)
    {
	set_impulse(_impulse);
    }

    bool ts_position<ts_type::DIGITAL>::operator<(ts_position const &_other) const
    {
	unsigned group = get_group(), other_group = _other.get_group();
	return (group == other_group) ? get_impulse() < _other.get_impulse() : group < other_group;
    }
    
    ts_position<ts_type::DIGITAL>& ts_position<ts_type::DIGITAL>::operator++()
    {
	if(impulse == num_impulses - 1)
	{
	    set_group(get_group() + 1);
	    impulse = 0;
	}
	else ++impulse;
	return *this;
    }
    
    ts_position<ts_type::DIGITAL> ts_position<ts_type::DIGITAL>::operator++(int)
    {
	ts_position<ts_type::DIGITAL> temp = *this;
	this->operator++();
	return temp;
    }

    unsigned short ts_position<ts_type::DIGITAL>::get_impulse() const
    {
	return impulse;
    }
    
    void ts_position<ts_type::DIGITAL>::set_impulse(unsigned short _impulse)
    {
	if(_impulse < num_impulses) impulse = _impulse;
	else 
	{
	    std::cerr << "Номер импульса должен быть <= 7" << std::endl;
	    std::terminate();
	}
    }
}}
