/*
 * simple_parser.hpp - Example parser that only splits the command arguments
 *                     and supports quoted strings
 *
 *   Copyright 2010 Jesús Torres <jmtorres@ull.es>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef SIMPLE_PARSER_HPP_
#define SIMPLE_PARSER_HPP_

#include <string>
#include <vector>

//#define BOOST_SPIRIT_DEBUG

#include <boost/spirit/include/qi.hpp>

#include <cli/base_parser.hpp>
#include <cli/standard.hpp>

namespace cli { namespace parsers
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    //
    // Class SimpleParser
    //

    template<typename Iterator>
    struct SimpleParser
        : qi::grammar<Iterator, std::vector<std::string>(), ascii::space_type>
    {
        SimpleParser() : SimpleParser::base_type(start)
        {
            using qi::lexeme;
            using ascii::char_;
            using ascii::space;

            escape %= lexeme['\\' >> char_];
            word %= lexeme[+(escape | (char_ - space))];
            quoted_string %= lexeme['\'' >> *(char_ - '\'') >> '\''];
            double_quoted_string %= lexeme['"' >> *(char_ - '"') >> '"'];
            argument %= quoted_string | double_quoted_string | word;
            start = +argument;

//            BOOST_SPIRIT_DEBUG_NODE(word);
//            BOOST_SPIRIT_DEBUG_NODE(quoted_string);
//            BOOST_SPIRIT_DEBUG_NODE(double_quoted_string);
//            BOOST_SPIRIT_DEBUG_NODE(argument);
            BOOST_SPIRIT_DEBUG_NODE(start);
        }

        qi::rule<Iterator, char()> escape;
        qi::rule<Iterator, std::string(), ascii::space_type> word;
        qi::rule<Iterator, std::string(), ascii::space_type> quoted_string;
        qi::rule<Iterator, std::string(), ascii::space_type> double_quoted_string;
        qi::rule<Iterator, std::string(), ascii::space_type> argument;
        qi::rule<Iterator, std::vector<std::string>(), ascii::space_type> start;
    };
}}

#endif /* SIMPLE_PARSER_HPP_ */
