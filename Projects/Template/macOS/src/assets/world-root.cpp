#include "world-root.hpp"

namespace vrm {
    WorldRoot::WorldRoot() {
        //services = CreateServices();
    }

    void WorldRoot::Destroy() {
        // world root only allowed to be destroyed once out of scope,
        //   preventing unintentional deletes so things don't break...
    }

    WorldRoot::~WorldRoot() {
        
    }
}