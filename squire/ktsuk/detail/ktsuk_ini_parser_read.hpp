#ifndef SQUIRE_KTSUK_DETAIL_KTSUK_INI_PARSER_READ_HPP_INCLUDED
#define SQUIRE_KTSUK_DETAIL_KTSUK_INI_PARSER_READ_HPP_INCLUDED

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace squire { namespace ktsuk
{
    struct get_attr_key_impl
    {
	template<typename Key, typename Arg>
	struct result
	{
	    typedef void type;
	};

	template<typename Key, typename Arg>
	typename result<Key, Arg>::type operator()(Key &_key, Arg const &_arg) const
	{
	    _key = Key("<xmlattr>.") + _arg;
	}
    };

    struct put_value_impl
    {
	template<typename Ptree, typename Arg>
	struct result
	{
	    typedef void type;
	};

	template<typename Ptree, typename Arg>
	typename result<Ptree, Arg>::type operator()(Ptree &_ptree, Arg const &_arg) const
	{
	    _ptree.put_value(_arg);
	}
    };

    struct add_child_impl
    {
	template<typename Ptree, typename Arg>
	struct result
	{
	    typedef void type;
	};

	template<typename Ptree, typename Arg>
	typename result<Ptree, Arg>::type operator()(Ptree &_ptree, Arg const &_arg) const
	{
	    _ptree.add_child(_arg.first, _arg.second);
	}
    };

    boost::phoenix::function<get_attr_key_impl> const get_attr_key = get_attr_key_impl();
    boost::phoenix::function<put_value_impl> const put_value = put_value_impl();
    boost::phoenix::function<add_child_impl> const add_child = add_child_impl();


    template<typename Ptree, typename Iterator>
    struct ktsuk_ini_grammar 
	: public boost::spirit::qi::grammar<Iterator, Ptree(), boost::spirit::qi::space_type>
    {
	typedef typename Ptree::key_type key_type;
	typedef typename Ptree::data_type data_type;
	typedef std::pair<key_type, Ptree> value_type;

	ktsuk_ini_grammar() : ktsuk_ini_grammar<Ptree, Iterator>::base_type(root)
	{
	    namespace qi = boost::spirit::qi;
	    namespace phoenix = boost::phoenix;

	    keychar = 	qi::char_('{') | qi::char_('}') | qi::char_(':') | qi::space;
	    key = 	*(qi::char_ - keychar);
	    data = 	qi::lexeme[':' >> *(qi::char_ - keychar)];

	    attr =	key		[get_attr_key(phoenix::at_c<0>(qi::_val), qi::_1)]
		    >>	data		[put_value(phoenix::at_c<1>(qi::_val), qi::_1)]
		;

	    obj =	key		[phoenix::at_c<0>(qi::_val) = qi::_1]
		    >>	'{'
		    >>	*(attr | obj)	[add_child(phoenix::at_c<1>(qi::_val), qi::_1)]
		    >>	'}'
		;

	    root = 	*obj		[add_child(qi::_val, qi::_1)];
		    
	}
	boost::spirit::qi::rule<Iterator> keychar;
	boost::spirit::qi::rule<Iterator, key_type(), boost::spirit::qi::space_type> key;
	boost::spirit::qi::rule<Iterator, data_type(), boost::spirit::qi::space_type> data;
	boost::spirit::qi::rule<Iterator, value_type(), boost::spirit::qi::space_type> attr, obj;
	boost::spirit::qi::rule<Iterator, Ptree(), boost::spirit::qi::space_type> root;
    };

    template<typename Ptree>
    void read_ktsuk_ini_internal(std::basic_istream<typename Ptree::key_type::value_type> &_stream,
				 Ptree &_ptree,
				 std::string const &_filename)
    {
	namespace qi = boost::spirit::qi;

	typedef typename Ptree::key_type::value_type Char;
	typedef typename std::vector<Char> Buffer;
	typedef typename Buffer::iterator Iterator;

	Buffer buffer(std::istreambuf_iterator<Char>(_stream.rdbuf()), std::istreambuf_iterator<Char>());
	ktsuk_ini_grammar<Ptree, Iterator> grammar;

	bool res = qi::phrase_parse(buffer.begin(), buffer.end(), grammar, qi::space, _ptree);
    }
} }

#endif //SQUIRE_KTSUK_DETAIL_KTSUK_INI_PARSER_READ_HPP_INCLUDED
