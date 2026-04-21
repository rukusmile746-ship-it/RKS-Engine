// Engine.hpp
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "imgui.h"
#include "Struct.hpp"
#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>

struct WindowData
{
    sf::RenderWindow* window;
    ImGuiContext* context;
    sf::Clock clock;
    bool shouldClose;

    WindowData(sf::RenderWindow* w, ImGuiContext* ctx)
    : window(w), context(ctx), shouldClose(false) {}
};

class Engine
{
private:
    int selected;
    Scene scene;
    sf::RenderTexture gamewindow;


    std::vector<WindowData> windows;
    bool createWindow2Pending;

    void processEvents(WindowData& data);
    void renderWindow(WindowData& data);

    bool isClicked(Entity& e, sf::Vector2f mouse);
    void renderEntities(WindowData& data, std::vector<Entity>& entities);

    void Ajouter_entities();

public:
    Engine();
    ~Engine();
    void run();

    void FuncUI1(WindowData& data);
    void FuncUI2(WindowData& data);
};

#endif
