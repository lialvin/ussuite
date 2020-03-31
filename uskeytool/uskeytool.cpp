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

#include <fc/crypto/private_key.hpp>
#include <fc/crypto/elliptic.hpp>
#include <fc/crypto/elliptic_r1.hpp>
#include <fc/crypto/openssl.hpp>
#include <fc/crypto/base58.hpp>
#include <fc/crypto/signature.hpp>
#include <fc/crypto/public_key.hpp>

#include "time_deal.hpp"

using boost::asio::ip::tcp;


int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: async_tcp_echo_server <file>\n";
      return 1;
    }
    fc::crypto::public_key  a;
    fc::crypto::public_key  t_pubkey;
    //fc::ecc::public_key  t_pubkey;
    fc::crypto::private_key  t_key(fc::crypto::private_key::generate());
    t_pubkey=  t_key.get_public_key();

    std::string  pkstr= std::string(t_pubkey);
    //std::string  pkstr= t_pubkey.to_base58();
    std::cout<< "priv str==" <<std::string(t_key)<<std::endl; 
    std::cout<< "comp privstr==" <<t_key.towifcomp()<<std::endl; 
    std::cout<< "pubkey str==" << pkstr<<std::endl; 
    fc::crypto::public_key  t_pubkey2(pkstr);
    boost::asio::io_context io_context;

    int count = 0;
    timeDeal  tiSave(io_context,std::string(argv[1]));
    g_timeDeal = &tiSave;

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
