#pragma once

// assets
#include "../assets/sdf.hpp"
#include "../assets/workspace.hpp"
#include "../assets/object.hpp"
#include "../assets/world-root.hpp"
#include "../assets/core-sdfs.hpp"
#include "../assets/folder.hpp"
#include "../assets/instance.hpp"

// services
#include "../services/runservice-container.hpp"
#include "../services/collectionservice-container.hpp"
#include "../services/tweenservice-container.hpp"

// other
#include "../debug/debug.hpp"
#include "../logic/event.hpp"
#include "../logic/function.hpp"

// std lib
#include <functional>
#include <string>

namespace vrm {
    void ProjectMain(WorldRoot* worldRoot);
}