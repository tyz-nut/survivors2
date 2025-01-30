#ifndef _RESOURCES_MANAGER_H_
#define _RESOURCES_MANAGER_H_

#include "atlas.h"
#include "util.h"

#include <string>
#include <functional>
#include <unordered_map>

class ResourcesManager
{
public:
    static ResourcesManager* instance();

    void load(HWND hwnd);

    Atlas* find_atlas(const std::string& id) const;
    IMAGE* find_image(const std::string& id) const;
    std::string find_address() const;

private:
    static ResourcesManager* manager;

    std::unordered_map<std::string, Atlas*> atlas_pool;
    std::unordered_map<std::string, IMAGE*> image_pool;
    std::string str_address = "";				//·þÎñÆ÷µØÖ·

private:
    ResourcesManager();
    ~ResourcesManager();
};

#endif