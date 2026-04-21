#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "imgui.h"
#include "Engine.hpp"

namespace im = ImGui;

void Engine::FuncUI1(WindowData& data)
{
    if (data.window == windows[0].window)
    {
        gamewindow.clear();
        for (auto& e : scene.entities)
        {
            sf::RectangleShape shape(e.size);
            shape.setPosition(e.position);
            shape.setFillColor(e.color);

            gamewindow.draw(shape);
        }
        gamewindow.display();
    }

    im::SetNextWindowPos(ImVec2(600, 10));
    im::Begin("Fenêtre principale", nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);

    im::PushStyleColor(ImGuiCol_Button, ImVec4(0.7, 0.1, 0.7, 1));
    im::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);
    if (im::Button("play", ImVec2(100, 22)) && data.window == windows[0].window)
    {
        if (windows.size() < 2 && !createWindow2Pending)
        {
            createWindow2Pending = true;
            std::cout << "Demande de creation de la fenetre 2\n";
        }
    }
    im::PopStyleVar();
    im::PopStyleColor(1);

    im::End();


    static float color[4] = {1, 0, 0, 1};
    im::Begin("Color");
    im::ColorPicker4("Pick", color);
    im::End();


    im::Begin("Inspector");
    im::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.f);
    if (selected != -1)
    {
        im::SliderFloat("X", &scene.entities[selected].position.x, 0, 1280);
        im::SliderFloat("Y", &scene.entities[selected].position.y, 0, 720);
    }
    im::PopStyleVar(1);
    im::End();



    im::Begin("game", nullptr, ImGuiWindowFlags_NoBackground);

    gameWindowPos = im::GetWindowPos();
    ImVec2 cursorScenePos = im::GetCursorScreenPos();

    sf::Vector2f imageSize(800, 600);
    im::Image(gamewindow.getTexture(), imageSize);

    gameWindowSize = ImVec2(imageSize.x, imageSize.y);
    isGameWindowHovered = im::IsItemHovered();

    im::End();

}

void Engine::FuncUI2(WindowData& data)
{
    renderEntities(data, scene.entities);
}



















