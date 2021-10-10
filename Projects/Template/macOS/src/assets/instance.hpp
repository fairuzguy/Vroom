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
        virtual void Destroy();
        Event<void, Instance*> ChildAdded;
        Event<void, Instance*> ChildRemoved;
        std::string name = "";
        virtual ~Instance();
    private:
        Instance* parent = nullptr;
        std::vector<Instance*> children;
    };
}