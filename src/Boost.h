/*
 * Boost.h
 *
 *  Created on: Jan 30, 2013
 *      Author: hrushi
 */

#ifndef BOOST_H_
#define BOOST_H_

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/version.hpp>
#include <boost/algorithm/string.hpp> // String operations like toupper
#include <boost/shared_ptr.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assert.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/math/special_functions/fpclassify.hpp>


#include <boost/archive/tmpdir.hpp>

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/assume_abstract.hpp>

#include <boost/assign/std/vector.hpp>


namespace po = boost::program_options;
namespace fs = boost::filesystem;
namespace ss = boost::assign;

#endif /* BOOST_H_ */
