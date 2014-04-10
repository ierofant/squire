#ifndef SQUIRE_KTSUK_KTSUK_INI_PARSER_HPP_INCLUDED
#define SQUIRE_KTSUK_KTSUK_INI_PARSER_HPP_INCLUDED

#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <squire/ktsuk/detail/ktsuk_ini_parser_read.hpp>
#include <squire/ktsuk/detail/ktsuk_ini_parser_write.hpp>

namespace squire { namespace ktsuk
{
    template<typename Ptree>
    void read_ktsuk_ini(std::basic_istream<typename Ptree::key_type::value_type> &_stream,
			Ptree &_ptree)
    {
	read_ktsuk_ini_internal(_stream, _ptree, std::string());
    }

    template<typename Ptree>
    void read_ktsuk_ini(std::string const &_filename,
			Ptree &_ptree,
			std::locale const &_locale = std::locale())
    {
	std::basic_ifstream<typename Ptree::key_type::value_type> stream(_filename.c_str());
	stream.imbue(_locale);
	read_ktsuk_ini_internal(stream, _ptree, _filename);
    }

    template<typename Ptree>
    void write_ktsuk_ini(std::basic_ostream<typename Ptree::key_type::value_type> &_stream,
			 Ptree const &_ptree)
    {
	write_ktsuk_ini_internal(_stream, _ptree, std::string());
    }

    template<typename Ptree>
    void write_ktsuk_ini(std::string const &_filename,
			 Ptree const &_ptree,
			 std::locale const &_locale = std::locale())
    {
	std::basic_ofstream<typename Ptree::key_type::value_type> stream(_filename.c_str());
	stream.imbue(_locale);
	write_ktsuk_ini_internal(stream, _ptree, _filename);
    }
} }

#endif //SQUIRE_KTSUK_KTSUK_INI_PARSER_HPP_INCLUDED
