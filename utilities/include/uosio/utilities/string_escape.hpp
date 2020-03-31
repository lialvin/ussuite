/**
 *  @file
 *  @copyright defined in uos/LICENSE.txt
 */
#pragma once

#include <string>

namespace uosio { namespace utilities {

  std::string escape_string_for_c_source_code(const std::string& input);

} } // end namespace uosio::utilities
