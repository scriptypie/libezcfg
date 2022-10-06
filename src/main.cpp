#include <iostream>

#include "ezcfg/ezcfg.hpp"

int main()
{
    ezcfg::ezconfig config;
    config.set("window_title", "victoriam_engine_window");
    config.set("window_width", 1920);
    config.set("window_height", 1080);
    std::vector<float> coords = {13.2, 142.0, 13.4};
    config.set("window_pos", coords);
    config.set("window_fullscreen", false);
    config.save("window");
    
    return 0;
}
