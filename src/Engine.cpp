#include <imgui.h>
#include "Engine.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>

namespace im = ImGui;
namespace ims = ImGui::SFML;


Engine::Engine() : createWindow2Pending(false), selected(-1)
{
    if (!gamewindow.create(800, 600))
    {
        std::cout << "erreur" << std::endl;
    }
    sf::RenderWindow* win1 = new sf::RenderWindow(sf::VideoMode(1280, 720), "Fenêtre principale");
    (void)ims::Init(*win1);
    im::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGuiContext* ctx1 = im::GetCurrentContext();
    windows.emplace_back(win1, ctx1);
}

Engine::~Engine()
{
    // Nettoyage de sécurité (normalement déjà fait dans run())
    for (auto& data : windows)
    {
        if (data.window)
        {
            data.window->setVisible(false);
            im::SetCurrentContext(data.context);
            ims::Shutdown(*data.window);
            im::DestroyContext(data.context);
            im::SetCurrentContext(nullptr);
            data.window->close();
            delete data.window;
        }
    }
}

// --- REMPLACÉ PAR CORRECTION ---
// --- VERSION CORRIGÉE AVEC DEBUG ---
void Engine::processEvents(WindowData& data)
{
    sf::Event event;

    while (data.window->pollEvent(event))
    {
        ims::ProcessEvent(*data.window, event);
        if (event.type == sf::Event::Closed)
        {
            data.shouldClose = true;
            data.window->close();
        }
    }
}
// --- FIN CORRECTION ---
// --- FIN CORRECTION ---

void Engine::renderWindow(WindowData& data)
{
    im::SetCurrentContext(data.context);
    ims::Update(*data.window, data.clock.restart());
    data.window->clear();

    if (data.window == windows[0].window)
    {
        FuncUI1(data);
    }
    else
    {
        FuncUI2(data);
    }

    ims::Render(*data.window);
    data.window->display();
}

bool Engine::isClicked(Entity& e, sf::Vector2f mouse)
{
    return (mouse.x >= e.position.x &&
        mouse.x <= e.position.x + e.size.x &&
        mouse.y >= e.position.y &&
        mouse.y <= e.position.y + e.size.y
    );
}

void Engine::renderEntities(WindowData& data, std::vector<Entity>& entities)
{
    if (data.window == windows[1].window)
    {
        for (auto& e : entities)
        {
            sf::RectangleShape shape(e.size);
            shape.setPosition(e.position);
            shape.setFillColor(e.color);
            data.window->draw(shape);
        }
    }
}

// --- VERSION AVEC DEBUG ---
void Engine::Ajouter_entities()
{
    // Vert à (100,100) taille 80x80
    this->scene.entities.push_back({{100, 100}, {80, 80}, sf::Color::Green});
    // Rouge à (300,200) taille 100x100  
    this->scene.entities.push_back({{300, 200}, {100, 100}, sf::Color::Red});
    
    std::cout << "=== ENTITÉS AJOUTÉES ===" << std::endl;
    std::cout << "Vert : position(100,100) taille(80,80)" << std::endl;
    std::cout << "Rouge: position(300,200) taille(100,100)" << std::endl;
    std::cout << "Zone cliquable Vert : X[100-180] Y[100-180]" << std::endl;
    std::cout << "Zone cliquable Rouge: X[300-400] Y[200-300]" << std::endl;
}
// --- FIN CORRECTION ---



void Engine::run()
{
    Ajouter_entities();
    while (!windows.empty())
    {
        // Événements
        for (auto& data : windows)
            processEvents(data);

        // Suppression des fenêtres fermées
        for (auto it = windows.rbegin(); it != windows.rend(); ++it)
        {
            if (it->shouldClose)
            {
                std::cout << "Fermeture d'une fenêtre\n";
                it->window->setVisible(false);
                im::SetCurrentContext(it->context);
                ims::Shutdown(*it->window);
                im::DestroyContext(it->context);
                im::SetCurrentContext(nullptr);   // <-- important !
                it->window->close();
                delete it->window;

                auto toErase = std::next(it).base();
                windows.erase(toErase);
                break;
            }
        }

        if (windows.empty() || windows[0].window == nullptr)
            break;

        // Création fenêtre 2
        if (createWindow2Pending)
        {
            createWindow2Pending = false;
            sf::ContextSettings settings = windows[0].window->getSettings();
            sf::RenderWindow* win2 = new sf::RenderWindow();
            win2->create(sf::VideoMode(800, 600), "Fenêtre secondaire", sf::Style::Default, settings);

            ImGuiContext* ctx2 = im::CreateContext();
            im::SetCurrentContext(ctx2);
            im::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            (void)ims::Init(*win2);

            windows.emplace_back(win2, ctx2);
            std::cout << "Fenêtre secondaire créée avec succès\n";
        }

        // Rendu
        for (auto& data : windows)
            renderWindow(data);
    }

    // À la sortie, on s'assure qu'aucun contexte n'est actif pour éviter l'assertion
    im::SetCurrentContext(nullptr);
}
