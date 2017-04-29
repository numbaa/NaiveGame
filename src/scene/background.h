#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#include "../misc/stdincs.h"
#include "../surface/surface.h"
#include "../graphics/camera.h"
#include <string>
using std::string;

class Background {
public:
    Background(string name);
    void blit(int16_t x, int16_t y, uint16_t width, uint16_t height, Surface& screen);
    uint16_t getHeight() const;
    uint16_t getWidth() const;
private:
    string name_;       //存的是地图的别名
    Surface surface_;
};

#endif //ifndef BACKGROUND_H_
