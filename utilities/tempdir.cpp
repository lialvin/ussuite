/**
 *  @file
 *  @copyright defined in uos/LICENSE.txt
 */

#include <uosio/utilities/tempdir.hpp>

#include <cstdlib>

namespace uosio { namespace utilities {

fc::path temp_directory_path()
{
   const char* uos_tempdir = getenv("UOS_TEMPDIR");
   if( uos_tempdir != nullptr )
      return fc::path( uos_tempdir );
   return fc::temp_directory_path() / "uos-tmp";
}

} } // uosio::utilities
