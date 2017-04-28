#ifndef SPRITE_H_
#define SPRITE_H_
#include <memory>
#include <string>
#include "camera.h"

class Physics;

enum StepState { UP, DOWN, LEFT, RIGHT };

const int32_t FPStep = 10;//多少帧一步

class Sprite {
public:
    Sprite(std::string path);
    virtual void blit(std::shared_ptr<Physics> phy, shared_ptr<Camera> camera);
    virtual ~Sprite() = default;
protected:
    int32_t     frames_;
    //StepState   ss_;
    Surface     sf_;
};

class PersonSprite : public Sprite{
public:
    PersonSprite(std::string path)
        :Sprite(path) {}
    void blit(shared_ptr<Physics>phy,shared_ptr<Camera> camera) override;
private:
    ;
};

#endif //ifndef SPRITE_H_
