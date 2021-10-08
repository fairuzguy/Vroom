#pragma once

#include <string>
#include "../logic/event.hpp"

namespace vrm {
    class Instance {
    public:
        Instance() = default;
        std::vector<Instance*> GetChildren();
        Instance* FindFirstChild(std::string childName);
        void SetParent(Instance* newParent);
        Instance* GetParent();
        void Destroy();
        Event<void, Instance*> ChildAdded;
        Event<void> ChildRemoved;
        std::string name = "";
        ~Instance();
    private:
        Instance* parent;
        std::vector<Instance*> children;
    };
}