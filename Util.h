#include <random>
#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <zlib.h>

namespace util {

	int random_int( int low, int high );

	std::string create_random_key( std::string::size_type length );

	std::string compress( const std::string& s, int compress_lvl );

	std::string decompress( const std::string& s );


} /* namespace util */


