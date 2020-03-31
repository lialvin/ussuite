/**
 *  @file
 *  @copyright defined in uos/LICENSE.txt
 */

#include <uosio/chain/chain_id_type.hpp>
#include <uosio/chain/exceptions.hpp>

namespace uosio { namespace chain {

   void chain_id_type::reflector_verify()const {
      UOS_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero" );
   }

} }  // namespace uosio::chain

namespace fc {

   void to_variant(const uosio::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, uosio::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
