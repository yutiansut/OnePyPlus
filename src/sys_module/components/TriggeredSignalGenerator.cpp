#include "Environment.h"
#include "sys_module/components/SignalChecker.h"
#include "sys_module/components/TriggeredSignalGenerator.h"
#include "sys_module/models/PendingOrderBase.h"
#include "utils/utils.h"

OP_NAMESPACE_START

TriggeredSignalGenerator::TriggeredSignalGenerator()
    : signal_checker(make_shared<SignalChecker>()){};

void TriggeredSignalGenerator::_generate_bare_signal(const shared_ptr<PendingOrderBase> &order) {
    static map<string, double> info;
    info["size"] = order->size;
    auto signal = make_shared<SignalByTrigger>(
        info,
        order->ticker,
        order->strategy_name,
        order->get_action_type(),
        order->get_order_type(),
        order->mkt_id,
        order->trigger_key,
        order->target_price(),
        order->get_first_cur_price(),
        order->difference());
    signal_checker->save_signals(signal);
};

void TriggeredSignalGenerator::_generate_full_signal(const shared_ptr<PendingOrderBase> &order) {

    auto signal = make_shared<SignalByTrigger>(
        order->signal_info,
        order->ticker,
        order->strategy_name,
        order->get_action_type(),
        order->get_order_type(),
        order->mkt_id,
        order->trigger_key,
        order->target_price(),
        order->get_first_cur_price(),
        order->difference());
    signal_checker->save_signals(signal);
};

bool TriggeredSignalGenerator::generate_triggered_signal(const shared_ptr<PendingOrderBase> &order) {
    static Environment *env = Environment::get_instance();
    if (!utils::Stl::is_elem_in_vector(env->cur_suspended_tickers, order->ticker))
        if (order->is_triggered()) {
            if (order->is_with_mkt())
                TriggeredSignalGenerator::_generate_bare_signal(order);
            else
                TriggeredSignalGenerator::_generate_full_signal(order);
            return true;
        }
    return false;
};

OP_NAMESPACE_END
