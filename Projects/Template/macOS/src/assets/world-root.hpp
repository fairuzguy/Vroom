#include "instance.hpp"

namespace vrm {
    class WorldRoot : public Instance {
    public:
        WorldRoot() = default;
        void Destroy() override;
        ~WorldRoot() = default;
    };
}