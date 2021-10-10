#include "project.hpp"

namespace vrm {
    void FrameCounter(float dt) {
        print(std::to_string(dt));
    }
    std::function<void(float)> OnRenderStepped(FrameCounter);

    void ProjectMain(WorldRoot* worldRoot) {
        RunServiceContainer RS = worldRoot->RunService;
        Workspace* workspace = static_cast<Workspace*>(worldRoot->FindFirstChild("workspace"));
        Object* sphere = new Object;
        SphereSDF* sphereSDF = new SphereSDF(glm::vec3(0), 2);
        sphere->SetSDF(sphereSDF);
        sphere->name = "sphere";
        Folder* folder = new Folder;
        folder->name = "folder";
        sphere->SetParent(workspace);
        folder->SetParent(workspace);
        RS.RenderStepped.Connect(OnRenderStepped);
    }
}