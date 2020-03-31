/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include <wallet_mgr.hpp>
#include <wallet.hpp>
#include <boost/algorithm/string.hpp>
#include <fc/io/datastream.hpp>
#include <fc/crypto/public_key.hpp>

namespace uosio {
namespace wallet {


constexpr auto file_ext = ".wallet";
constexpr auto password_prefix = "PW";

std::string  wallet_file_  = "uoswallet";

//fc::crypto::private_key
std::string gen_password(std::string key_type ) {

 if(key_type == "K1")
 {
   auto key = private_key_type::generate();
   return password_prefix + key.to_string();
 }
  if(key_type == "R1")
 {
   auto key = private_key_type::generate_r1();
   return password_prefix + key.to_string();
 }

 if(key_type == "SM2")
 {
   auto key = private_key_type::generate_sm2();
   return password_prefix + key.to_string();
 }
 
}

std::string wallet_manager::create( ) {

   auto wallet_filename = dir / (wallet_file_ + file_ext);

   if (fc::exists(wallet_filename)) {
      return std::string("error"); 
   }
	
   std::string password = gen_password("SM2");
   wallet_data d;
   wallet_ = make_unique<soft_wallet>(d);
   wallet_->set_password(password);
   wallet_->set_wallet_filename(wallet_filename.string());
   wallet_->unlock(password);
   wallet_->lock();
   wallet_->unlock(password);


   // Explicitly save the wallet file here, to ensure it now exists.
   wallet_->save_wallet_file();

	
   return password;
}

void wallet_manager::save_wallet_file()
{
   wallet_->save_wallet_file();
}

void wallet_manager::open( std::string & password ) {

   wallet_data d;
   wallet_ = std::make_unique<soft_wallet>(d);
   auto wallet_filename = dir / (wallet_file_ + file_ext);
   wallet_->set_wallet_filename(wallet_filename.string());
   if (!wallet_->load_wallet_file()) {
      FC_THROW( "Unable to open file:  " );
   }
   unlock(password);
    
}

map<public_key_type,private_key_type> wallet_manager::list_keys(  ) {

   return wallet_->list_keys();
}


flat_set<public_key_type> wallet_manager::get_public_keys() {


   flat_set<public_key_type> result;
   result.merge(wallet_->list_public_keys());
	
   return result;
}

void wallet_manager::lock( ) {

   wallet_->lock();
}

void wallet_manager::unlock( const std::string& password) {

   wallet_->unlock(password);
}

void wallet_manager::import_key( const std::string& wif_key) {

   wallet_->import_key(wif_key);
}

void wallet_manager::import_hexkey( const std::string& hex_key) {

   wallet_->import_hexkey(hex_key);
}


void wallet_manager::sm3_hash( const std::string& hex_key) {

   wallet_->sm3_hash(hex_key);
}

void wallet_manager::remove_key( const std::string& password, const std::string& key) {

   wallet_->check_password(password); //throws if bad password
   wallet_->remove_key(key);
}


string wallet_manager::create_key( const std::string& key_type) {

   string upper_key_type = boost::to_upper_copy<std::string>(key_type);
   return wallet_->create_key(upper_key_type);
}

signature_type  wallet_manager::sign_digest(const digest_type& digest, const public_key_type& key) 
{
  optional<signature_type> sig = wallet_->try_sign_digest(digest, key);
  if (sig)
      return *sig;
}

void  wallet_manager::assert_recover_key( const fc::sha256& digest,
      char * sig, size_t siglen,  char * pub, size_t publen )
{
     fc::crypto::signature s;
     fc::crypto::public_key p;
     fc::datastream<const char*> ds( sig, siglen );
     fc::datastream<char*> pubds( pub, publen );

     fc::raw::unpack(ds, s);
     fc::raw::unpack(pubds, p);
         
     auto check = fc::crypto::public_key( s, digest, false );
     FC_ASSERT( check == p, "Error expected key different than recovered key" ); 
     
    cout<< " assert_recover_key =" <<check.to_string()<<endl;
    // fc::raw::pack( pubds, fc::crypto::public_key( s, digest, false ) );
    //     return pubds.tellp();
}


std::string  wallet_manager:: signdigest(std::string signdigest, std::string strpubk)
{
    public_key_type  pubkey(strpubk);
    digest_type dig(signdigest); 
    //cout<<" dig str=="<< dig.str()<<endl;


    fc::crypto::signature  sig_stru = sign_digest(dig, pubkey);
    char  arr_sign[200];
    char  arr_pubkey[100];
    fc::datastream<char*> ds_sign( arr_sign, 200 );

    //std::decay<fc::crypto::signature>::type 
    //fc::raw::pack( ds_sign, std::decay_t<fc::crypto::signature>sig_stru);
    fc::raw::pack( ds_sign, sig_stru);
    int siglen = ds_sign.tellp();
    cout << "siglen ="<< sizeof(sig_stru)<< "  pubkey="<< sizeof(pubkey)<< endl;
    
    fc::datastream<char*> ds_pub( arr_pubkey, 100 );
    fc::raw::pack( ds_pub, pubkey);
    int publen=ds_pub.tellp();
    string sig_str =sig_stru.to_string();
    string pub_str =pubkey.to_string();
    
   // cout<< " arr_sign=" <<fc::to_hex(arr_sign,66 )<<endl; 
    //cout<< " arr_pubkey " <<fc::to_hex(arr_pubkey,publen )<<" publen "<< publen<<endl; 
    assert_recover_key( dig,  arr_sign , siglen,arr_pubkey,  publen );

    return sig_str;
}

std::string   wallet_manager::get_password_key(std::string name , std::string rule ,std::string passwd)
{
   pair<public_key_type,private_key_type>  pair2= wallet_->get_private_key_from_password(name , rule , passwd);
   private_key_type priv = pair2.second;
   return priv.to_string();
}

void wallet_manager::testsign(map<public_key_type, private_key_type> & list_key  )
{    
    auto  iter = list_key.begin();
    std::string dig_str("this is a test ,this is a test , this is a test !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
     
    digest_type dig = digest_type::hash(dig_str);
    public_key_type  pubk= iter->first;
     
    fc::crypto::signature  sig_stru = sign_digest(dig, pubk);
    char  arr_sign[200]; 
    char  arr_pubkey[100]; 
    fc::datastream<char*> ds_sign( arr_sign, 200 );
    
    //std::decay<fc::crypto::signature>::type 
    //fc::raw::pack( ds_sign, std::decay_t<fc::crypto::signature>sig_stru);
    fc::raw::pack( ds_sign, sig_stru);
    int siglen = ds_sign.tellp();
    cout << sizeof(sig_stru)<< "  "<< sizeof(pubk)<< endl;
    
    fc::datastream<char*> ds_pub( arr_pubkey, 100 );
    fc::raw::pack( ds_pub, pubk);
    int publen=ds_pub.tellp();
    string sig_str =sig_stru.to_string();
    string pub_str =pubk.to_string();
    assert_recover_key( dig,  arr_sign , siglen,arr_pubkey,  publen );

}

void wallet_manager::uos2hexaddr(std::string uosaddr) 
{
     fc::crypto::public_key  uosaddr1(uosaddr); 
}

void wallet_manager::hex2uosaddr(std::string uosaddr) 
{
     std::string stdhex("hex");
     fc::crypto::public_key  uosaddr2(uosaddr); 
     std::cout<< uosaddr2.to_string()<< "  "<< uosaddr<<std::endl;
}

} // namespace wallet
} // namespace eosio
