#include "builtin_module/CsvReader.h"
#include "setting_for_test.hpp"
#include "sys_module/models/BarBase.h"
#include "utils/arrow.h"
#include <gtest/gtest.h>

using namespace op;

TEST(BarTest, test_000001_LE) {
    using namespace utils;
    SettingFunc::global_setting();
    CsvReader csv_reader("../data/", TICKER, TICKER);

    double shift_num = 0;

    if (FREQUENCY == "H1")
        shift_num = 1.0 / 24; //TODO 设置成符合下面变换的
    else if (FREQUENCY == "D")
        shift_num = 1;

    auto bars = BarBase(TICKER, FREQUENCY);
    bars.initialize(7);

    auto start = arrow::str_to_sec(START);
    auto pre_start = arrow::shift_days(start, -shift_num);
    ASSERT_LE(arrow::str_to_sec(bars.current_ohlc->date), pre_start);
    ASSERT_LE(arrow::str_to_sec(bars.next_ohlc->date), start);

    bars.next_directly();
    ASSERT_LE(arrow::str_to_sec(bars.previous_ohlc->date), pre_start);
    ASSERT_LE(arrow::str_to_sec(bars.current_ohlc->date), start);

    // 成交价格控制
    bars.env->execute_on_close_or_next_open = "open";
    ASSERT_EQ(bars.execute_price(), bars.next_ohlc->open);
    bars.env->execute_on_close_or_next_open = "close";
    ASSERT_EQ(bars.execute_price(), bars.close());

    // 最后数据
    while (!bars.is_bar_series_end())
        bars.next_directly();
    ASSERT_LE(arrow::str_to_sec(bars.current_ohlc->date), arrow::shift_days(END, 0));
};

TEST(BarTest, test_000002_EQ) {
    using namespace utils;
    const string TICKER_2 = "000002";
    CsvReader csv_reader("../data/", TICKER_2, TICKER_2);
    SettingFunc::global_setting();

    double shift_num = 0;

    if (FREQUENCY == "H1")
        shift_num = 1.0 / 24; //TODO 设置成符合下面变换的
    else if (FREQUENCY == "D")
        shift_num = 1;

    auto bars = BarBase(TICKER_2, FREQUENCY);
    bars.initialize(7);

    auto start = arrow::str_to_sec(START);
    auto pre_start = arrow::shift_days(start, -shift_num);
    ASSERT_EQ(arrow::str_to_sec(bars.current_ohlc->date), pre_start);
    ASSERT_EQ(arrow::str_to_sec(bars.next_ohlc->date), start);

    bars.next_directly();
    ASSERT_EQ(arrow::str_to_sec(bars.previous_ohlc->date), pre_start);
    ASSERT_EQ(arrow::str_to_sec(bars.current_ohlc->date), start);

    // 成交价格控制
    bars.env->execute_on_close_or_next_open = "open";
    ASSERT_EQ(bars.execute_price(), bars.next_ohlc->open);
    bars.env->execute_on_close_or_next_open = "close";
    ASSERT_EQ(bars.execute_price(), bars.close());

    // 最后数据
    while (!bars.is_bar_series_end())
        bars.next_directly();
    ASSERT_LE(bars.current_ohlc->date, arrow::shift_days_to_str(END, 0));
};
