#include "camera.h"

void Camera::update()
{
    position = Point(look_at.x + cos(degree*ANGLE2RAD)*radius, position.y, look_at.z + sin(degree*ANGLE2RAD)*radius);
}

void Camera::rotateBy(double offset)
{
    degreeOffset = -offset;
}

void Camera::moveBy(double offset)
{

    radiusOffset = -offset;
}

void Camera::stopRotating()
{
     degreeOffset = 0.0;
}

void Camera::stopMoving()
{
    radiusOffset = 0.0;
}

void Camera::update(Terrain *terrain) {
    terrain->showAllFaces();

    if (position.z <=  - LENGTH/2) {
        terrain->hideFace(BACK);
    } else if (position.z >=  LENGTH/2) {
        terrain->hideFace(FRONT);
    }
    if (position.x >=  WIDTH/2) {
        terrain->hideFace(LEFT);
    } else if (position.x <=  -WIDTH/2) {
        terrain->hideFace(RIGHT);
    }

    if (degreeOffset ==0.0 && radiusOffset == 0.0) {
        return;
    }
    degree += degreeOffset;
    radius += radiusOffset;
    update();
}
