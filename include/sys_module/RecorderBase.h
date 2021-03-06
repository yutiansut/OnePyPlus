#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;
class MatchEngine;
class BarBase;

class HoldingPnlSeriesBase;
class RealizedPnlSeriesBase;
class CommissionSeriesBase;
class MarketValueSeriesBase;
class MarginSeriesBase;
class PositionSeries;
class AvgPriceSeries;
class MoneySeries;
class MoneySeries;
class MoneySeries;

class RecorderBase {
  public:
    RecorderBase();
    virtual ~RecorderBase() = default;

    Environment *env;
    shared_ptr<MatchEngine> match_engine;


    double initial_cash = 100000;
    double per_comm = 1;
    double per_comm_pct = 0;
    double margin_rate = 0.1;

    shared_ptr<HoldingPnlSeriesBase> holding_pnl;
    shared_ptr<RealizedPnlSeriesBase> realized_pnl;
    shared_ptr<CommissionSeriesBase> commission;
    shared_ptr<MarketValueSeriesBase> market_value;
    shared_ptr<MarginSeriesBase> margin;
    shared_ptr<PositionSeries> position;
    shared_ptr<AvgPriceSeries> avg_price;
    shared_ptr<MoneySeries> cash;
    shared_ptr<MoneySeries> frozen_cash;
    shared_ptr<MoneySeries> balance;

    void run();
    void update(const bool &order_executed);

    virtual shared_ptr<BarBase> bar_class(const string &ticker,
                                          const string &frequency) = 0;
    virtual void initialize() = 0;
    virtual void set_setting(const double initial_cash,
                             const double comm,
                             const double comm_pct,
                             const double margin_rate) = 0;

  protected:
    virtual void _update_cash(const string &trading_date) = 0;

  private:
    void _update_balance(const string &trading_date);
    void _record_order();
};

OP_NAMESPACE_END
