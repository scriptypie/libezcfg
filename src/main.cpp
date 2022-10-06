#include <iostream>

#include "ezcfg/ezcfg.hpp"

int main()
{
    ezcfg::ezconfig config;
    config.set("window_title", "victoriam_engine_window");
    config.set("window_width", 1920);
    config.set("window_height", 1080);
    config.save("window");
    config.load("window");

    return 0;
}
