#include "instance.hpp"
#include "../services/service.hpp"
#include "../services/runservice-container.hpp"
#include <string>
#include <map>

namespace vrm {
    class WorldRoot : public Instance {
    public:
        WorldRoot();
        RunServiceContainer RunService = RunServiceContainer();
        void Destroy() override;
        ~WorldRoot();
    };
}