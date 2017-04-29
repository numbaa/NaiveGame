#ifndef SPRITE_H_
#define SPRITE_H_
#include <memory>
#include <string>
#include "camera.h"
using std::string;
class Physics;

const int32_t FPStep = 50;//多少帧一步

//chentao:  Sprite持有的仍然是图片的名字，Surface持有最终的路径
class Sprite {
public:
    Sprite(string name);
    virtual void blit(std::shared_ptr<Physics> phy, shared_ptr<Camera> camera);
    virtual ~Sprite() = default;
protected:
    void sub_blit(int16_t x, int16_t y, uint16_t w, uint16_t h, shared_ptr<Physics> phy, shared_ptr<Camera> camera);
    Surface     sf_;
    string picture_name_;
};

class PersonSprite : public Sprite{
public:
    PersonSprite(std::string path, int32_t row, int32_t col)
        :Sprite(path), row_(row), col_(col) {}
    void blit(shared_ptr<Physics>phy,shared_ptr<Camera> camera) override;
private:
    int32_t     row_;
    int32_t     col_;
};

#endif //ifndef SPRITE_H_
