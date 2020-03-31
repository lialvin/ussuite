/**
 */
#pragma once

#include <fc/container/flat_fwd.hpp>
#include <fc/io/varint.hpp>
#include <fc/io/enum_type.hpp>
#include <fc/crypto/sha224.hpp>
#include <fc/optional.hpp>
#include <fc/safe.hpp>
#include <fc/container/flat.hpp>
#include <fc/string.hpp>
#include <fc/io/raw.hpp>
#include <fc/static_variant.hpp>
#include <fc/smart_ref_fwd.hpp>
#include <fc/crypto/ripemd160.hpp>
#include <fc/fixed_string.hpp>
#include <fc/crypto/private_key.hpp>

//#include <uosio/chain/types.hpp>
//#include <uosio/wallet_plugin/wallet_api.hpp>

#include <fc/real128.hpp>
#include <fc/crypto/base58.hpp>

using namespace std;
//using namespace uosio::chain;



namespace uosio { namespace wallet {

   using public_key_type  = fc::crypto::public_key;
   using private_key_type = fc::crypto::private_key;
   using signature_type   = fc::crypto::signature;

   using std::unique_ptr;
   using fc::optional;
   using boost::container::flat_set;

   using block_id_type       = fc::sha256;
   using checksum_type       = fc::sha256;
   using checksum256_type    = fc::sha256;
   using checksum512_type    = fc::sha512;
   using checksum160_type    = fc::ripemd160;
   using transaction_id_type = checksum_type;
   using digest_type         = checksum_type;
   using weight_type         = uint16_t;
   using block_num_type      = uint32_t;
   using share_type          = int64_t;
   using int128_t            = __int128;
   using uint128_t           = unsigned __int128;
   using bytes               = vector<char>;


typedef uint16_t transaction_handle_type;

struct wallet_data
{
   vector<char>              cipher_keys; /** encrypted keys */
};

namespace detail {
class soft_wallet_impl;
}

class soft_wallet  //  final : public wallet_api
{
   public:

	  
      soft_wallet( const wallet_data& initial_data );

      ~soft_wallet();

      bool copy_wallet_file( string destination_filename );


      string                            get_wallet_filename() const;

      private_key_type get_private_key( public_key_type pubkey )const ;

      pair<public_key_type,private_key_type>  get_private_key_from_password( string account, string role, string password );

      bool    is_new()const;

      bool    is_locked()const ;

      void    lock() ;

      void    unlock(string password) ;

      void    check_password(string password) ;

      void    set_password(string password) ;

      map<public_key_type, private_key_type> list_keys() ;
      
      flat_set<public_key_type> list_public_keys() ;

      bool    load_wallet_file(string wallet_filename = "");

      void    save_wallet_file(string wallet_filename = "");

      void    set_wallet_filename(string wallet_filename);

      bool import_key( string wif_key ) ;

      bool import_key(private_key_type & priv);

	  void  sm3_hash(string hex_key);
	   
	  bool import_hexkey(string hex_key);

      bool remove_key( string key ) ;

      string create_key( string key_type ) ;

      optional<signature_type> try_sign_digest( const digest_type digest, const public_key_type public_key ) ;

      std::shared_ptr<detail::soft_wallet_impl> my;
      void encrypt_keys();
};

struct plain_keys {
   fc::sha512                            checksum;
   map<public_key_type,private_key_type> keys;
};

} }

FC_REFLECT( uosio::wallet::wallet_data, (cipher_keys) )

FC_REFLECT( uosio::wallet::plain_keys, (checksum)(keys) )

