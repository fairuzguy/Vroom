#include "project.hpp"

namespace vrm {
    void aaah(float dt) {
        print(std::to_string(dt));
    }
    std::function<void(float)> OnRenderStepped(aaah);

    void ProjectMain(WorldRoot* worldRoot) {
        RunServiceContainer RS = worldRoot->RunService;
        RS.RenderStepped.Connect(OnRenderStepped);
    }
}