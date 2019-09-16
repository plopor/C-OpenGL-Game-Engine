#pragma once
#include <string>

namespace Core {
    struct WindowInfo {
        std::string name;
        int width, height;
        int position_x, position_y;
        bool isReshapable;

        WindowInfo() {
            name = "Test openGL";
            width = 800;
            height = 600;
            position_x = 300;
            position_y = 300;
            isReshapable = true;
        }

        WindowInfo(std::string name,
            int start_position_x,
            int width,
            int height,
            bool is_reshapable) {
            this->name = name;
            this->height = height;
            this->width = width;
            this->position_x = position_x;
            this->position_y = position_y;
            this->isReshapable = isReshapable;
        }

        //copy constructor
        WindowInfo(const WindowInfo& windowInfo) {
            name = windowInfo.name;
            height = windowInfo.height;
            width = windowInfo.width;
            position_x = windowInfo.position_x;
            position_y = windowInfo.position_y;
            isReshapable = windowInfo.isReshapable;
        }

        //operator overload for windowInfo
        void operator=(const WindowInfo& windowInfo) {
            name = windowInfo.name;
            height = windowInfo.height;
            width = windowInfo.width;
            position_x = windowInfo.position_x;
            position_y = windowInfo.position_y;
            isReshapable = windowInfo.isReshapable;
        }
    };
}