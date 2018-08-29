#include <string>
#include <vector>
#pragma once

namespace sys {
class Environment;
class OrderBase;
class SignalByTrigger;
class MarketOrder;
class PendingOrderBase;
using std::shared_ptr;
using std::string;
using std::vector;

class OrderGenerator {

  public:
    OrderGenerator();
    Environment *env;
    void run();

  private:
    const double cur_price(const string &ticker);

    template <typename T>
    const bool is_buy(const T &signal);
    template <typename T>
    const bool is_sell(const T &signal);
    template <typename T>
    const bool is_short(const T &signal);
    template <typename T>
    const bool is_shortcover(const T &signal);
    template <typename T>
    const bool is_absolute_mkt(const T &signal);
    template <typename T>
    const bool is_normal_mkt(const T &signal);

    template <typename T1, typename T2>
    void _child_of_mkt(const shared_ptr<T2> &signal,
                       const int mkt_id,
                       const string &key,
                       vector<shared_ptr<OrderBase>> &orders_basket);

    template <typename T>
    shared_ptr<MarketOrder> _generate_mkt_order(const shared_ptr<T> &signal);

    template <typename T>
    vector<shared_ptr<OrderBase>> _generate_child_of_mkt(const int mkt_id,
                                                         const shared_ptr<T> &signal);

    template <typename T>
    shared_ptr<PendingOrderBase> _generate_pending_order(const shared_ptr<T> &signal);

    void submit_mkt_order_with_child(shared_ptr<MarketOrder> mkt_order,
                                     const vector<shared_ptr<OrderBase>> &orders_basket,
                                     vector<shared_ptr<OrderBase>> orders_cur);

    void _process_mkt_signals();
    void _process_triggered_signals();
    void _process_pending_signals();
    void _process_cancel_signals();
    void _clear_current_signals_memory();
    static int _counter;
};

int OrderGenerator::_counter = 1;
} // namespace sys