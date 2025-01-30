#ifndef _SCENE_H_
#define _SCENE_H_

#include "camera.h"
#include "../thirdparty/httplib.h"
#include <graphics.h>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    virtual void on_enter() {}
    virtual void on_update(float delta) {}
    virtual void on_render() {}
    virtual void on_input(const ExMessage& msg) {}
    virtual void on_exit() {}

private:

};

#endif