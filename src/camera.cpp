#include "camera.h"

void Camera::rotateFromCenter(double offset)
{

}
void Camera::moveBy(Vector vec)
{
    position.translate(vec);

}

void Camera::update(Terrain *terrain) {
    terrain->showAllFaces();

    if (position.z <=  - LENGTH/2) {
        terrain->hideFace(BACK);
    }
    if (position.x >=  WIDTH/2) {
        terrain->hideFace(LEFT);
    } else if (position.x <=  -WIDTH/2) {
        terrain->hideFace(RIGHT);
    }
}
