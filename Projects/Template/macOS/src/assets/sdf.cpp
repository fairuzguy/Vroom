#include "sdf.hpp"
#include "../logic/compose.hpp"

namespace vrm {
    float DefaultSignedDistance(glm::vec3 origin) {
        return 0;
    }
    const glm::mat3x3 DefaultOrientation = glm::mat3x3(
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );
    const glm::vec3 DefaultPosition = glm::vec3(0.0f);


    SDF::SDF() :
        GetSignedDistance(std::function<float(glm::vec3)>(DefaultSignedDistance)),
        position(DefaultPosition),
        orientation(DefaultOrientation) {
    }
    
    SDF::SDF(SDF* oldSDFs) : 
        GetSignedDistance(std::function<float(glm::vec3)>(DefaultSignedDistance)),
        position(DefaultPosition),
        orientation(DefaultOrientation),
        previousComposition(oldSDFs) {
    }

    glm::vec3 SDF::GetPosition() {
        return position;
    }
    glm::mat3x3 SDF::GetOrientation() {
        return orientation;
    }
    void SDF::SetPosition(glm::vec3 newPosition) {
        position = newPosition;
    }
    void SDF::SetOrientation(glm::mat3x3 newOrientation) {
        orientation = newOrientation;
    }
    bool SDF::IsPrimitive() {
        return isPrimitive;
    }

    SDF SDF::Union(SDF* sdf) {
        std::function<float(glm::vec3)> newDistPtr = ComposeUnion(
            (GetSignedDistance),
            (sdf->GetSignedDistance)
        );
        std::vector<glm::vec3> positionOffsetList = {DefaultPosition};
        std::vector<glm::mat3x3> orientationOffsetList = {DefaultOrientation};
        if (!isPrimitive) { // case 1, preceding sdf is not a primitive
            for (size_t i = 1; i < positionOffsets.size(); i++) {
                positionOffsetList.push_back(positionOffsets[i]);
                orientationOffsetList.push_back(orientationOffsets[i]);
            }
        }
        positionOffsetList.push_back(sdf->position - position);
        orientationOffsetList.push_back(sdf->orientation*glm::inverse(orientation));
        if (!sdf->IsPrimitive()) { // case 2, trailing sdf is not a primitive
            for (size_t i = 1; i < sdf->positionOffsets.size(); i++) {
                positionOffsetList.push_back(sdf->positionOffsets[i] + sdf->GetPosition() - position);
                orientationOffsetList.push_back(sdf->orientationOffsets[i]*sdf->orientation*glm::inverse(orientation));
            }
        }

        SDF* oldSDFs = new SDF[2];
        oldSDFs[0] = (*this);
        oldSDFs[1] = (*sdf);
        SDF newSDF = SDF(oldSDFs);
        newSDF.GetSignedDistance = newDistPtr;
        newSDF.positionOffsets = positionOffsetList;
        newSDF.position = position;
        newSDF.orientation = orientation;
        newSDF.isPrimitive = false;
        return newSDF;
    }

    SDF SDF::Sub(SDF* sdf) {
        std::function<float(glm::vec3)> newDistPtr = ComposeSubtraction(
            (GetSignedDistance),
            (sdf->GetSignedDistance)
        );
        std::vector<glm::vec3> positionOffsetList = {DefaultPosition};
        std::vector<glm::mat3x3> orientationOffsetList = {DefaultOrientation};
        if (!isPrimitive) { // case 1, preceding sdf is not a primitive
            for (size_t i = 1; i < positionOffsets.size(); i++) {
                positionOffsetList.push_back(positionOffsets[i]);
                orientationOffsetList.push_back(orientationOffsets[i]);
            }
        }
        positionOffsetList.push_back(sdf->position - position);
        orientationOffsetList.push_back(sdf->orientation*glm::inverse(orientation));
        if (!sdf->IsPrimitive()) { // case 2, trailing sdf is not a primitive
            for (size_t i = 1; i < sdf->positionOffsets.size(); i++) {
                positionOffsetList.push_back(sdf->positionOffsets[i] + sdf->GetPosition() - position);
                orientationOffsetList.push_back(sdf->orientationOffsets[i]*sdf->orientation*glm::inverse(orientation));
            }
        }

        SDF* oldSDFs = new SDF[2];
        oldSDFs[0] = (*this);
        oldSDFs[1] = (*sdf);
        SDF newSDF = SDF(oldSDFs);
        newSDF.GetSignedDistance = newDistPtr;
        newSDF.positionOffsets = positionOffsetList;
        newSDF.position = position;
        newSDF.orientation = orientation;
        newSDF.isPrimitive = false;
        return newSDF;
    }

    SDF SDF::Intersect(SDF* sdf) {
        std::function<float(glm::vec3)> newDistPtr = ComposeIntersection(
            (GetSignedDistance),
            (sdf->GetSignedDistance)
        );
        std::vector<glm::vec3> positionOffsetList = {DefaultPosition};
        std::vector<glm::mat3x3> orientationOffsetList = {DefaultOrientation};
        if (!isPrimitive) { // case 1, preceding sdf is not a primitive
            for (size_t i = 1; i < positionOffsets.size(); i++) {
                positionOffsetList.push_back(positionOffsets[i]);
                orientationOffsetList.push_back(orientationOffsets[i]);
            }
        }
        positionOffsetList.push_back(sdf->position - position);
        orientationOffsetList.push_back(sdf->orientation*glm::inverse(orientation));
        if (!sdf->IsPrimitive()) { // case 2, trailing sdf is not a primitive
            for (size_t i = 1; i < sdf->positionOffsets.size(); i++) {
                positionOffsetList.push_back(sdf->positionOffsets[i] + sdf->GetPosition() - position);
                orientationOffsetList.push_back(sdf->orientationOffsets[i]*sdf->orientation*glm::inverse(orientation));
            }
        }

        SDF* oldSDFs = new SDF[2];
        oldSDFs[0] = (*this);
        oldSDFs[1] = (*sdf);
        SDF newSDF = SDF(oldSDFs);
        newSDF.GetSignedDistance = newDistPtr;
        newSDF.positionOffsets = positionOffsetList;
        newSDF.position = position;
        newSDF.orientation = orientation;
        newSDF.isPrimitive = false;
        return newSDF;
    }

    SDF* SDF::UndoPrevious() {
        return previousComposition;
    }

    SDF::~SDF() {
        if (!isPrimitive) {
            delete[] previousComposition;
        }
    }
}