#include "resources_manager.h"
#include <vector>
#include <fstream>
#include <sstream>

struct ImageResInfo
{
    std::string id;
    LPCTSTR path;
};

struct AtlasResInfo
{
    std::string id;
    LPCTSTR path;
    int num_frame = 0;
};

static const std::vector<ImageResInfo> image_info_list =
{
    { "default", _T(R"(resources/background.png)")},
    { "ui_heart",   _T(R"(resources/ui_heart.png)")},
    { "menu",       _T(R"(resources/menu.png)")},

    {"ui_1",        _T(R"(resources/ui_1.png)")},
    {"ui_2",        _T(R"(resources/ui_2.png)")},
    {"ui_3",        _T(R"(resources/ui_3.png)")},
    {"ui_fight",    _T(R"(resources/ui_fight.png)")},

    {"ui_start_hovered",    _T(R"(resources/ui_start_hovered.png)")},
    {"ui_start_idle",       _T(R"(resources/ui_start_idle.png)")},
    {"ui_start_pushed",     _T(R"(resources/ui_start_pushed.png)")},
    {"ui_quit_hovered",     _T(R"(resources/ui_quit_hovered.png)")},
    {"ui_quit_idle",        _T(R"(resources/ui_quit_idle.png)")},
    {"ui_quit_pushed",      _T(R"(resources/ui_quit_pushed.png)")},

    {"pea",                 _T(R"(resources/pea.png)")},

    {"shadow_player",       _T(R"(resources/shadow_player.png)")},
    {"shadow_pig",          _T(R"(resources/shadow_enemy.png)")}
};

static const std::vector<AtlasResInfo> atlas_info_list =
{
    { "hajimi_idle_left",           _T(R"(resources/hajimi/hajimi_idle_left_%d.png)"),      4},
    { "hajimi_idle_up",             _T(R"(resources/hajimi/hajimi_idle_back_%d.png)"),      4},
    { "hajimi_idle_down",           _T(R"(resources/hajimi/hajimi_idle_front_%d.png)"),     4},
    { "hajimi_idle_right",          _T(R"(resources/hajimi/hajimi_idle_right_%d.png)"),     4},
    { "hajimi_run_left",            _T(R"(resources/hajimi/hajimi_run_left_%d.png)"),       4},
    { "hajimi_run_up",              _T(R"(resources/hajimi/hajimi_run_back_%d.png)"),       4},
    { "hajimi_run_down",            _T(R"(resources/hajimi/hajimi_run_front_%d.png)"),      4},
    { "hajimi_run_right",           _T(R"(resources/hajimi/hajimi_run_right_%d.png)"),      4},
   
    { "manbo_idle_left",            _T(R"(resources/manbo/manbo_idle_left_%d.png)"),        4},
    { "manbo_idle_up",              _T(R"(resources/manbo/manbo_idle_back_%d.png)"),        4},
    { "manbo_idle_down",            _T(R"(resources/manbo/manbo_idle_front_%d.png)"),       4},
    { "manbo_idle_right",           _T(R"(resources/manbo/manbo_idle_right_%d.png)"),       4},
    { "manbo_run_left",             _T(R"(resources/manbo/manbo_run_left_%d.png)"),         4},
    { "manbo_run_up",               _T(R"(resources/manbo/manbo_run_back_%d.png)"),         4},
    { "manbo_run_down",             _T(R"(resources/manbo/manbo_run_front_%d.png)"),        4},
    { "manbo_run_right",            _T(R"(resources/manbo/manbo_run_right_%d.png)"),        4},

    { "paimeng_left",               _T(R"(resources/paimeng/player_left_%d.png)"),          6},
    { "paimeng_right",              _T(R"(resources/paimeng/player_right_%d.png)"),         6},

    { "pig_left",                   _T(R"(resources/pig/player_left_%d.png)"),              6},
    { "pig_right",                  _T(R"(resources/pig/player_right_%d.png)"),             6},
};

ResourcesManager* ResourcesManager::manager = nullptr;

ResourcesManager* ResourcesManager::instance()
{
    if (!manager)
    {
        manager = new ResourcesManager();
    }

    return manager;
}

static inline bool check_image_valid(IMAGE* image)
{
    return GetImageBuffer(image);
}

Atlas* ResourcesManager::find_atlas(const std::string& id) const
{
    const auto& itor = atlas_pool.find(id);
    if (itor == atlas_pool.end())
        return nullptr;

    return itor->second;
}

IMAGE* ResourcesManager::find_image(const std::string& id) const
{
    const auto& itor = image_pool.find(id);
    if (itor == image_pool.end())
        return nullptr;

    return itor->second;
}

std::string ResourcesManager::find_address() const
{
    return str_address;
}

ResourcesManager::ResourcesManager() = default;

ResourcesManager::~ResourcesManager() = default;


void ResourcesManager::load(HWND hwnd)
{
    AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, NULL);

    for (const auto& info : image_info_list)
    {
        IMAGE* image = new IMAGE();
        loadimage(image, info.path);
        if (!check_image_valid(image))
            throw info.path;
        image_pool[info.id] = image;
    }

    for (const auto& info : atlas_info_list)
    {
        Atlas* atlas = new Atlas();
        atlas->load(info.path, info.num_frame);
        for (int i = 0; i < atlas->get_size(); i++)
        {
            IMAGE* image = atlas->get_image(i);
            if (!check_image_valid(image))
                throw info.path;
        }
        atlas_pool[info.id] = atlas;
    }

    load_audio(_T(R"(resources/audio/bgm.mp3)"), _T("bgm"));
    load_audio(_T(R"(resources/audio/barb_break.mp3)"), _T("barb_break"));
    load_audio(_T(R"(resources/audio/bullet_time.mp3)"), _T("bullet_time"));

    load_audio(_T("resources/audio/ui_1.mp3"), _T("ui_1"));
    load_audio(_T("resources/audio/ui_2.mp3"), _T("ui_2"));
    load_audio(_T("resources/audio/ui_3.mp3"), _T("ui_3"));
    load_audio(_T("resources/audio/ui_fight.mp3"), _T("ui_fight"));

    std::ifstream file("config.cfg");

    if (!file.good())
    {
        MessageBox(hwnd, L"无法打开配置 config.cfg", L"配置失败", MB_OK | MB_ICONERROR);
        exit(-1);
    }

    std::stringstream str_stream;
    str_stream << file.rdbuf();
    str_address = str_stream.str();

    file.close();
}
