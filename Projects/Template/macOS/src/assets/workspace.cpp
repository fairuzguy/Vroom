#include "workspace.hpp"

namespace vrm {
    void OnWorkspaceChildAdded(Instance* newChild) {
        Workspace* workspace = static_cast<Workspace*>(newChild->GetParent());
        if (typeid(*newChild) == typeid(Object)) {
            workspace->renderTargets[static_cast<Object*>(newChild)] = true;
        }
    }

    void OnWorkspaceChildRemoved(Instance* oldChild) {
        Workspace* workspace = static_cast<Workspace*>(oldChild->GetParent());
        if (typeid(*oldChild) == typeid(Object)) {
            if (workspace->renderTargets.find(static_cast<Object*>(oldChild)) == workspace->renderTargets.end()) {
                return;
            }
            workspace->renderTargets.erase(static_cast<Object*>(oldChild));
        }
    }

    Workspace::Workspace() :
        currentCamera(Camera(640, 640)) { // temporarily this way, need to update camera class
        ChildAdded.Connect(std::function<void(Instance*)>(OnWorkspaceChildAdded));
        ChildRemoved.Connect(std::function<void(Instance*)>(OnWorkspaceChildRemoved));
    }
}