#include "config.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class EVENT;
class MarketMaker;
class PendingOrderChecker;
class Environment;

class OnePiece {
  public:
    OnePiece();
    op::Environment *env;
    void sunny(const bool &show_summary = true); // 主循环
    void initialize_trading_system();
    void set_date(const string &fromdate,
                  const string &todate,
                  const string &frequency,
                  const string &instrument);

  private:
    vector<op::SingleLoop> _event_loop;
    const shared_ptr<op::MarketMaker> _market_maker;
    const shared_ptr<op::PendingOrderChecker> _pending_order_checker;

    void output_summary(){};
    void _run_event_loop(const op::EVENT &event);
    bool _event_is_executed(const op::EVENT &cur_event,
                            op::SingleLoop &single_loop) const;
    void _reset_all_counter() const;
    void _pre_initialize_trading_system();
};

OP_NAMESPACE_END
