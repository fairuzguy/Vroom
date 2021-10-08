#include "object.hpp"

namespace vrm {
    glm::vec3 DefaultPosition = glm::vec3(0.0);
    glm::mat3x3 DefaultOrientation = glm::mat3x3(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

    Object::Object() :
        position(DefaultPosition),
        orientation(DefaultOrientation) {
    }

    void Object::SetSDF(SDF* newSDF) {
        sdf = newSDF;
        sdf->SetPosition(position);
        sdf->SetOrientation(orientation);
    }
    SDF* Object::GetSDF() {
        return sdf;
    }

    void Object::SetPosition(glm::vec3 newPosition) {
        position = newPosition;
        sdf->SetPosition(newPosition);
    }
    glm::vec3 Object::GetPosition() {
        return position;
    }

    void Object::SetOrientation(glm::mat3x3 newOrientation) {
        orientation = newOrientation;
        sdf->SetOrientation(newOrientation);
    }
    glm::mat3x3 Object::GetOrientation() {
        return orientation;
    }

    Object::~Object() {
        delete sdf; // necessary, since multiple objects sharing the same sdf, are the same object.
    }
}