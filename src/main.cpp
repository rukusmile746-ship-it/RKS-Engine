#include "Engine.hpp"
#include "imgui.h"   // pour ImGui::DestroyContext

int main()
{
    Engine engine;
    engine.run();
    ImGui::DestroyContext(nullptr);   // <-- suppression propre du contexte global
    return 0;
}
