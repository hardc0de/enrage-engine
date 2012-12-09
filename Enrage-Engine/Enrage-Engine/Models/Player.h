#include <cmath>
#include "Map.h"

#pragma once

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    Map* map;

    double xPosition;
    double yPosition;

    double xDirection;
    double yDirection;
    
    double xPlane;
    double yPlane;

    double speed;
    double currentSpeed;
    double acceleration;

    bool moveForward;
    bool moveBackwards;
    bool rotateLeft;
    bool rotateRight;

public:
    Player();
    Player(Map* map, double xPosition, double yPosition, double xDirection, double yDirection, double xPlane, double yPlane, double speed);
    ~Player();

    void MoveThink();

    void Move();

    void RotateLeft();
    void RotateRight();

    void Rotate(double angle);

    void Shoot();

    bool CollidesX(int direction);
    bool CollidesY(int direction);

    double GetXPosition();
    double GetYPosition();

    void SetXPosition(double x);
    void SetYPosition(double y);

    void SetPosition(double x, double y);

    double GetXDirection();
    double GetYDirection();

    void SetXDirection(double xDirection);
    void SetYDirection(double yDirection);

    double GetXPlane();
    double GetYPlane();

    void SetXPlane(double xPlane);
    void SetYPlane(double yPlane);

    double GetSpeed();
    void SetSpeed(double speed);

    double GetCurrentSpeed();
    void SetCurrentSpeed(double currentSpeed);

    double GetAcceleration();
    void SetAcceleration(double acceleration);

    void ChangeAcceleration();

    bool GetMoveForward();
    void SetMoveForward(bool moveForward);

    bool GetMoveBackwards();
    void SetMoveBackwards(bool moveBackwards);

    bool GetRotateLeft();
    void SetRotateLeft(bool rotateLeft);

    bool GetRotateRight();
    void SetRotateRight(bool rotateRight);

    int Signum(double x);
};

#endif // PLAYER_H
