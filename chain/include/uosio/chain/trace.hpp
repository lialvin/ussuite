/**
 *  @file
 *  @copyright defined in uos/LICENSE.txt
 */
#pragma once

#include <uosio/chain/action.hpp>
#include <uosio/chain/action_receipt.hpp>
#include <uosio/chain/block.hpp>

namespace uosio { namespace chain {

   struct account_delta {
      account_delta( const account_name& n, int64_t d):account(n),delta(d){}
      account_delta(){}

      account_name account;
      int64_t delta = 0;

      friend bool operator<( const account_delta& lhs, const account_delta& rhs ) { return lhs.account < rhs.account; }
   };

   struct base_action_trace {
      base_action_trace( const action_receipt& r ):receipt(r){}
      base_action_trace(){}

      action_receipt       receipt;
      action               act;
      bool                 context_free = false;
      fc::microseconds     elapsed;
      uint64_t             cpu_usage = 0;
      string               console;

      uint64_t             total_cpu_usage = 0; /// total of inline_traces[x].cpu_usage + cpu_usage
      transaction_id_type  trx_id; ///< the transaction that generated this action
      uint32_t             block_num = 0;
      block_timestamp_type block_time;
      fc::optional<block_id_type>     producer_block_id;
      flat_set<account_delta>         account_ram_deltas;
   };

   struct action_trace : public base_action_trace {
      using base_action_trace::base_action_trace;

      vector<action_trace> inline_traces;
   };

   struct transaction_trace;
   using transaction_trace_ptr = std::shared_ptr<transaction_trace>;

   struct transaction_trace {
      transaction_id_type                        id;
      uint32_t                                   block_num = 0;
      block_timestamp_type                       block_time;
      fc::optional<block_id_type>                producer_block_id;
      fc::optional<transaction_receipt_header>   receipt;
      fc::microseconds                           elapsed;
      uint64_t                                   net_usage = 0;
      bool                                       scheduled = false;
      vector<action_trace>                       action_traces; ///< disposable

      transaction_trace_ptr                      failed_dtrx_trace;
      fc::optional<fc::exception>                except;
      std::exception_ptr                         except_ptr;
   };

} }  /// namespace uosio::chain

FC_REFLECT( uosio::chain::account_delta,
            (account)(delta) )

FC_REFLECT( uosio::chain::base_action_trace,
                    (receipt)(act)(context_free)(elapsed)(cpu_usage)(console)(total_cpu_usage)(trx_id)
                    (block_num)(block_time)(producer_block_id)(account_ram_deltas) )

FC_REFLECT_DERIVED( uosio::chain::action_trace,
                    (uosio::chain::base_action_trace), (inline_traces) )

FC_REFLECT( uosio::chain::transaction_trace, (id)(block_num)(block_time)(producer_block_id)
                                             (receipt)(elapsed)(net_usage)(scheduled)
                                             (action_traces)(failed_dtrx_trace)(except) )
