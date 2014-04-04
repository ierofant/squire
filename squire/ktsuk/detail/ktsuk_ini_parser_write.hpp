#ifndef SQUIRE_KTSUK_INI_PARSER_WRITE_HPP_INCLUDED
#define SQUIRE_KTSUK_INI_PARSER_WRITE_HPP_INCLUDED

#include <string>

namespace squire { namespace ktsuk
{
    template<typename Ptree>
    void write_ktsuk_ini_internal_attrs(std::basic_ostream<typename Ptree::key_type::value_type> &_stream,
					  Ptree const &_ptree,
					  unsigned _depth)
    {
	typedef typename Ptree::const_iterator const_iterator;
	typedef typename Ptree::data_type data_type;
	
	for(const_iterator itr = _ptree.begin(); itr != _ptree.end(); ++itr)
	{
	    for(unsigned i = 0; i < _depth; ++i) _stream.put('\t');
	    Ptree const &child = itr->second;
	    _stream << itr->first << ':' << itr->second.template get_value<data_type>() << std::endl;
	}
    }

    template<typename Ptree>
    void write_ktsuk_ini_internal_recurse(std::basic_ostream<typename Ptree::key_type::value_type> &_stream,
					  Ptree const &_ptree,
					  unsigned _depth)
    {
	for(typename Ptree::const_iterator itr = _ptree.begin(); itr != _ptree.end(); ++itr)
	{
	    if(itr->first == "<xmlattr>") write_ktsuk_ini_internal_attrs(_stream, itr->second, _depth);
	    else
	    {
		for(unsigned i = 0; i < _depth; ++i) _stream.put('\t');
		_stream << itr->first << " {" << std::endl;
		write_ktsuk_ini_internal_recurse(_stream, itr->second, _depth + 1);
		for(unsigned i = 0; i < _depth; ++i) _stream.put('\t');
		_stream << '}' << std::endl;
	    }
	}
    }

    template<typename Ptree>
    void write_ktsuk_ini_internal(std::basic_ostream<typename Ptree::key_type::value_type> &_stream,
				  Ptree const &_ptree,
				  std::string const &_filename)
    {
	write_ktsuk_ini_internal_recurse(_stream, _ptree, 0);
    }
} }

#endif //SQUIRE_KTSUK_INI_PARSER_WRITE_HPP_INCLUDED
