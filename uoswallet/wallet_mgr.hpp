
#pragma once

#include "wallet.hpp"
#include <boost/filesystem/path.hpp>

namespace fc { class variant; }

namespace uosio {
namespace wallet {

class wallet_manager {
public:
   wallet_manager() = default;
   wallet_manager(const wallet_manager&) = delete;
   wallet_manager(wallet_manager&&) = delete;
   wallet_manager& operator=(const wallet_manager&) = delete;
   wallet_manager& operator=(wallet_manager&&) = delete;
   ~wallet_manager() = default;

   /// Set the path for location of wallet files.
   /// @param p path to override default ./ location of wallet files.
   void set_dir(const boost::filesystem::path& p) { dir = p; }

   signature_type sign_digest(const digest_type& digest, const public_key_type& key);
   /// create wallet return password
   std::string create();
   void save_wallet_file();
   void open(std::string&  password);

   map<public_key_type,private_key_type> list_keys( );

   flat_set<public_key_type> get_public_keys();

   void lock( );

   void unlock(  const std::string& password);

   void import_key(  const std::string& wif_key);
   void import_hexkey( const std::string& hex_key);
   void sm3_hash( const std::string& hex_value);
	 
   void remove_key(  const std::string& password, const std::string& key);
   void uos2hexaddr(std::string );
   void hex2uosaddr(std::string );
  
   string create_key(  const std::string& key_type);
   std::string   get_password_key(std::string name , std::string rule ,std::string passwd);
   void assert_recover_key(const fc::sha256&,  char*, size_t,  char*, size_t);
   void testsign(map<public_key_type, private_key_type> & list_key );
   std::string   signdigest(std::string signdigest, std::string strpubk);

private:
   std::unique_ptr<soft_wallet> wallet_;

   boost::filesystem::path dir = ".";
};

} // namespace wallet
} // namespace eosio


