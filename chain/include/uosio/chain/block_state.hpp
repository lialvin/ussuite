/**
 *  @file
 *  @copyright defined in uos/LICENSE.txt
 */
#pragma once

#include <uosio/chain/block_header_state.hpp>
#include <uosio/chain/block.hpp>
#include <uosio/chain/transaction_metadata.hpp>
#include <uosio/chain/action_receipt.hpp>

namespace uosio { namespace chain {

   struct block_state : public block_header_state {
      block_state( const block_header_state& cur ):block_header_state(cur){}
      block_state( const block_header_state& prev, signed_block_ptr b, bool trust = false );
      block_state( const block_header_state& prev, block_timestamp_type when );
      block_state() = default;

      /// weak_ptr prev_block_state....
      signed_block_ptr                                    block;
      bool                                                validated = false;
      bool                                                in_current_chain = false;

      /// this data is redundant with the data stored in block, but facilitates
      /// recapturing transactions when we pop a block
      vector<transaction_metadata_ptr>                    trxs;
   };

   using block_state_ptr = std::shared_ptr<block_state>;

} } /// namespace uosio::chain

FC_REFLECT_DERIVED( uosio::chain::block_state, (uosio::chain::block_header_state), (block)(validated)(in_current_chain) )
