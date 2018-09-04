
#include "config.h"
#include "Environment.h"
#include "EventEngine.h"
#include "OnePy.h"
#include "builtin_module/CsvReader.h"
#include "builtin_module/backtest_stock/StockBroker.h"
#include "builtin_module/backtest_stock/StockRecorder.h"
#include "builtin_module/backtest_stock/StockSeries.h"
#include "custom_module/backtest.h"
#include "sys_module/BrokerBase.h"
#include "sys_module/CleanerBase.h"
#include "sys_module/ReaderBase.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/RiskManagerBase.h"
#include "sys_module/StrategyBase.h"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/components/OrderGenerator.h"
#include "sys_module/components/PendingOrderChecker.h"
#include "sys_module/components/SignalGenerator.h"
#include "sys_module/components/SubmitOrderChecker.h"
#include "sys_module/components/TriggeredSignalGenerator.h"
#include "sys_module/models/BarBase.h"
#include "sys_module/models/Calendar.h"
#include "sys_module/models/CancelOrderBase.h"
#include "sys_module/models/Counter.h"
#include "sys_module/models/GeneralOrder.h"
#include "sys_module/models/OrderBase.h"
#include "sys_module/models/PendingOrderBase.h"
#include "sys_module/models/SeriesBase.h"
#include "sys_module/models/Signal.h"
#include "sys_module/models/SignalCancel.h"
#include "sys_module/models/TrailingOrderBase.h"

#pragma once

class Luffy : public op::StrategyBase {
  public:
    Luffy() {
        auto module = std::make_shared<Luffy>(*this);
        env->save_module("Luffy", module);

        //save_to_env(this, "luffy");
        //env->strategies["luffy"] = std::make_shared<Luffy>(*this);
        //throw 1;
    };
    const string get_name() override { return "luffy"; };
    void handle_bar() override {
        //buy(10, "000001", 0, 0, 0, 0, 0, 0, 0, 0.01);
        buy(10, "000001");
        //cout << env->recorder->balance->latest()
        //<< ", "
        //<< env->sys_date
        //<< endl;
    };
};
