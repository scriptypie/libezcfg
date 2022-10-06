#include <iostream>

#include "ezcfg/ezcfg.hpp"

int main()
{
    ezcfg::Config config;
    config.Set("window_title", "victoriam_engine_window");
    config.Set("window_width", 1920);
    config.Set("window_height", 1080);
    std::vector<float> coords = {13.2, 142.0, 13.4};
    config.Set("window_pos", coords);
    config.Set("window_fullscreen", false);
    config.Set("window_width", 1341);
    config.SaveToFile("window");

    return 0;
}
