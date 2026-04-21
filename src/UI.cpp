#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "imgui.h"
#include "Engine.hpp"

namespace im = ImGui;

// --- REMPLACÉ PAR CORRECTION ---
// --- VERSION CORRIGÉE ---
void Engine::FuncUI1(WindowData& data)
{
    if (data.window == windows[0].window)
    {
        gamewindow.clear();  // Gris foncé pour contraste
        
        for (auto& e : scene.entities)
        {
            sf::RectangleShape shape;
            shape.setSize(e.size);
            shape.setFillColor(e.color);
            shape.setPosition(e.position);
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
        im::SliderFloat("X", &scene.entities[selected].position.x, 0, 800);
        im::SliderFloat("Y", &scene.entities[selected].position.y, 0, 600);
    }
    else
    {
        im::Text("Aucune entite selectionnee");
        im::Text("Cliquez sur un rectangle");
    }
    im::PopStyleVar();
    im::End();

    im::Begin("game", nullptr, ImGuiWindowFlags_NoBackground);

    
    sf::Vector2f imageSize(800, 600);
    im::Image(gamewindow.getTexture(), imageSize);
    
    // Afficher les infos de debug dans l'UI
    
    im::End();
}
// --- FIN CORRECTION ---
// --- FIN CORRECTION ---

void Engine::FuncUI2(WindowData& data)
{
    renderEntities(data, scene.entities);
}



















