#include "instance.hpp"

namespace vrm {
    std::vector<Instance*> Instance::GetChildren() {
        return children;
    }

    Instance* Instance::FindFirstChild(std::string instanceName) {
        for (size_t i = 0; i < children.size(); i++) {
            Instance* child = children[i];
            if (child->name == instanceName) {
                return child;
            }
        }
        return nullptr;
    }

    void Instance::SetParent(Instance* newParent) {
        parent = newParent;
        newParent->children.push_back(this);
        newParent->ChildAdded.Fire(this);
    }

    Instance* Instance::GetParent() {
        return parent;
    }

    void Instance::Destroy() {
        for (size_t i = 0; i < children.size(); i++) {
            Instance* child = children[i];
            delete child;
        }
        for (size_t i = 0; i < parent->children.size(); i++) {
            Instance* child = parent->children[i];
            if (child == this) {
                parent->children.erase(parent->children.begin() + i);
                break;
            }
        }
        parent->ChildRemoved.Fire();
    }

    Instance::~Instance() {
        this->Destroy();
    }
}