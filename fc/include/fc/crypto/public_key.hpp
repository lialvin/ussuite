#pragma once
#include <fc/crypto/elliptic.hpp>
#include <fc/crypto/elliptic_r1.hpp>
#include <fc/crypto/elliptic_sm2.hpp>
#include <fc/crypto/signature.hpp>
#include <fc/reflect/reflect.hpp>
#include <fc/reflect/variant.hpp>
#include <fc/static_variant.hpp>

namespace fc { namespace crypto {
   namespace config {
      constexpr const char* public_key_legacy_prefix = "UOS";
      constexpr const char* public_key_base_prefix = "PUB";
      constexpr const char* public_key_prefix[] = {
         "K1",
         "R1",
         "SM2"
      };
   };

   class public_key
   {
      public:
         using storage_type = static_variant<ecc::public_key_shim, r1::public_key_shim, sm2::public_key_shim >;

         public_key() = default;
         public_key( public_key&& ) = default;
         public_key( const public_key& ) = default;
         public_key& operator= (const public_key& ) = default;

         public_key( const signature& c, const sha256& digest, bool check_canonical = true );

         public_key( storage_type&& other_storage )
         :_storage(forward<storage_type>(other_storage))
         {}

         bool valid()const;

         int which()const;

         // serialize to/from string
         explicit public_key(const string& base58str);
         std::string to_string(const fc::time_point& deadline = fc::time_point::maximum()) const;

         storage_type _storage;
		 

		 
      private:
         friend std::ostream& operator<< (std::ostream& s, const public_key& k);
         friend bool operator == ( const public_key& p1, const public_key& p2);
         friend bool operator != ( const public_key& p1, const public_key& p2);
         friend bool operator < ( const public_key& p1, const public_key& p2);
         friend struct reflector<public_key>;
         friend class private_key;
   }; // public_key

} }  // fc::crypto

namespace fc {
   void to_variant(const crypto::public_key& var, variant& vo, const fc::time_point& deadline = fc::time_point::maximum());
   int SM3_hash(const unsigned char *message, size_t len, unsigned char *hash, unsigned int *hash_len);
   void from_variant(const variant& var, crypto::public_key& vo);
} // namespace fc

FC_REFLECT(fc::crypto::public_key, (_storage) )
