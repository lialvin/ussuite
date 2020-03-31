//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
// 
// Copyright (c) 2003-2017 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>
#include "uoswallet.h"
#include "wallet_mgr.hpp"
#include <regex>
#include "chain/include/uosio/chain/name.hpp"

void printhelp()
{
       cout<<"1  help  :"  <<endl;
       cout<<"2  listkey"<<endl;
       cout<<"3  importkey  privkey"<<endl;
       cout<<"4  importhexkey hexprivkey : only  for gm sm2 "<<endl;	   
       cout<<"5  signdigest digest pubkey"<<endl;	   
       cout<<"6  newkey"<<endl;
       cout<<"7  nameto  [name or 123322]"<<endl;
       cout<<"8  newpwdkey accout rule passwd"<<endl;
       cout<<"9  uos2hexaddr uosaddr"<<endl;
       cout<<"10  hex2uosaddr hexaddr  remark:must 33byte"<<endl;
       cout<<"10  sm3hash  "<<endl;	   

}

void callFun(int argc, char* argv[], shared_ptr<uosio::wallet::wallet_manager> wallet_mgr )
{

    if(argc<2) // help 
    {
       printhelp();
       return ;
    }

    string stropt;
    if(argc>1)
    {
        stropt = string(argv[1]);
    }
    if(stropt==string("help") )
    {
       printhelp();
       return; 
    }
    else if(stropt==string("listkey") )
    {
         auto list_key = wallet_mgr->list_keys();

         auto  iter = list_key.begin();
         while(iter != list_key.end()) {
              //cout << std::string(iter->first) << " : " << std::string(iter->second) << endl;
              iter++;
         }
    }
    else if(stropt==string("importkey") )
    {
       string  strKey(argv[2]);
       wallet_mgr->import_key(strKey);
       //cout<<"dump wallet   "<<strKey<<endl;
    }
    else if(stropt==string("importhexkey") )
    {
       string  strKey(argv[2]);
       wallet_mgr->import_hexkey(strKey);
       //cout<<"dump wallet   "<<strKey<<endl;
    }
    else if(stropt==string("sm3hash") )
    {
       string  strKey(argv[2]);
       wallet_mgr->sm3_hash(strKey);
       //cout<<"dump wallet   "<<strKey<<endl;
    }	
    else if(stropt==string("signdigest") )
    {
       string  strdigest(argv[2]);
       string  strpubk(argv[3]);
       string  sig = wallet_mgr->signdigest(strdigest,strpubk);
       cout<<" sig string=" <<  sig << endl;
    }
    else if(stropt==string("newkey") )
    {
         string key1 =   wallet_mgr->create_key("");
         std::cout <<key1<<std::endl; 
    }
    else if(stropt==string("newpwdkey"))
    {
        string  strname(argv[2]);
        string  strrule(argv[3]);
        string  strpasswd(argv[4]);
        string key1 =   wallet_mgr->get_password_key( strname, strrule, strpasswd );
        std::cout <<key1<<std::endl; 
        
    }
    else if(stropt==string("nameto") )
    {
       std::string str (argv[2]);
       std::regex rx("[0-9]+");
       bool bl = std::regex_match(str.begin(),str.end(), rx);
       if(bl)
       {
           uint64_t   idate =boost::lexical_cast<uint64_t>(argv[2]);
           uosio::chain::name nameto(idate);
           cout<< "name str="<< nameto.to_string()<<std::endl; 
       }
       else
       { 
          uint64_t  value = uosio::chain::string_to_name(argv[2] ); 
          cout<< " name value="<< value<<std::endl;
       }
    }
    else if(stropt==string("uos2hexaddr"))
    {
       std::string str(argv[2]);
       wallet_mgr->uos2hexaddr( str); 
    }
    else if(stropt==string("hex2uosaddr"))
    {
       std::string str(argv[2]);
       wallet_mgr->hex2uosaddr( str); 
    }
    else
    {
        printhelp();
    }

}

int main(int argc, char* argv[])
{
  try
  {
      string password("PWPVT_SM2_CMR8gY9win6jW9NAdLSQgm7M8sYcQDJ2m6WuQCjsEmj8PGhmP");
      auto wallet_mgr(std::make_shared<uosio::wallet::wallet_manager>());
      std::string retpassword = wallet_mgr->create();


      if(retpassword == "error")
      {
     	 wallet_mgr->open(password);
         std::cout <<" open wallet   "<<std::endl;
         callFun(argc, argv, wallet_mgr );
      }
      else
      {
         std::cout <<" create wallet   "<<std::endl;
         string key =   wallet_mgr->create_key("");
         std::cout <<key<<std::endl;
         string key1 =   wallet_mgr->create_key("");
         std::cout <<key1<<std::endl;
         std::cout <<" password:   "<<retpassword<<std::endl;
         wallet_mgr->save_wallet_file();
      
      
         auto list_key = wallet_mgr->list_keys();
     
         auto  iter = list_key.begin();
         while(iter != list_key.end()) {
		 //std::cout << std::string(iter->first) << " : " << std::string(iter->second) << endl;
              iter++;
         }
  
         wallet_mgr->testsign( list_key);       
      }     

     system("pause");
	  
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}



