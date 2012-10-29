#include "Player.h"

Player::Player()
{
    map = NULL;

    moveForward = false;
    moveBackwards = false;
    rotateLeft = false;
    rotateRight = false;

    xPosition = 0.0;
    yPosition = 0.0;

    xDirection = 0.0;
    yDirection = 0.0;

    xPlane = 0.0;
    yPlane = 0.0;

    speed = 0;
}

Player::Player(Map* map, double xPosition, double yPosition, double xDirection, double yDirection, double xPlane, double yPlane, double speed)
{
    this -> map = map;

    moveForward = false;
    moveBackwards = false;
    rotateLeft = false;
    rotateRight = false;

    this -> xPosition = xPosition;
    this -> yPosition = yPosition;

    this -> xDirection = xDirection;
    this -> yDirection = yDirection;

    this -> xPlane = xPlane;
    this -> yPlane = yPlane;

    this -> speed = speed;
}

Player::~Player()
{
}

void Player::Move()
{
    if(moveForward)
        MoveForward();
    if(moveBackwards)
        MoveBackwards();
    if(rotateLeft)
        RotateLeft();
    if(rotateRight)
        RotateRight();
}

void Player::MoveForward()
{
    if(!CollidesX(1))
        xPosition += xDirection * speed;
    if(!CollidesY(1))
        yPosition += yDirection * speed;
}

void Player::MoveBackwards()
{
    if(!CollidesX(-1))
        xPosition -= xDirection * speed;
    if(!CollidesY(-1))
        yPosition -= yDirection * speed;
}

void Player::RotateLeft()
{
    double oldxDirectionVector = xDirection;
    xDirection = xDirection * cos(speed / 5) - yDirection * sin(speed / 5);
    yDirection = oldxDirectionVector * sin(speed / 5) + yDirection * cos(speed / 5);
        
    double oldxPlaneVector = xPlane;
    xPlane = xPlane * cos(speed / 5) - yPlane * sin(speed / 5);
    yPlane = oldxPlaneVector * sin(speed / 5) + yPlane * cos(speed / 5);
}

void Player::RotateRight()
{
    double oldxDirectionVector = xDirection;
    xDirection = xDirection * cos(-speed / 5) - yDirection * sin(-speed / 5);
    yDirection = oldxDirectionVector * sin(-speed / 5) + yDirection * cos(-speed / 5);
        
    double oldxPlaneVector = xPlane;
    xPlane = xPlane * cos(-speed / 5) - yPlane * sin(-speed / 5);
    yPlane = oldxPlaneVector * sin(-speed / 5) + yPlane * cos(-speed / 5);
}

bool Player::CollidesX(int direction)
{
    if( map -> GetTileAtPosition((uint)(xPosition + (direction * Signum(xDirection) * (0.3 + speed))), (uint)yPosition) > 0)
        return true;
    /*else if( map -> GetTileAtPosition((uint)(xPosition + (direction * Signum(xDirection) * (0.3 + speed))),  (uint)(yPosition + (direction * Signum(yDirection) * (0.3 + speed)))) > 0)
        return true;*/
    else
        return false;
}

bool Player::CollidesY(int direction)
{
    if( map -> GetTileAtPosition((uint)xPosition, (uint)(yPosition + (direction * Signum(yDirection) * (0.3 + speed)))) > 0)
        return true;
    /*else if( map -> GetTileAtPosition((uint)(xPosition + (direction * Signum(xDirection) * (0.3 + speed))),  (uint)(yPosition + (direction * Signum(yDirection) * (0.3 + speed)))) > 0)
        return true;*/
    else
        return false;
}

double Player::GetXPosition()
{
    return xPosition;
}

double Player::GetYPosition()
{
    return yPosition;
}

void Player::SetXPosition(double x)
{
    this -> xPosition = x;
}

void Player::SetYPosition(double y)
{
    this -> yPosition = y;
}

void Player::SetPosition(double x, double y)
{
    this -> xPosition = x;
    this -> yPosition = y;
}

double Player::GetXDirection()
{
    return xDirection;
}

double Player::GetYDirection()
{
    return yDirection;
}

void Player::SetXDirection(double xDirection)
{
    this -> xDirection = xDirection;
}

void Player::SetYDirection(double yDirection)
{
    this -> yDirection = yDirection;
}

double Player::GetXPlane()
{
    return xPlane;
}

double Player::GetYPlane()
{
    return yPlane;
}

void Player::SetXPlane(double xPlane)
{
    this -> xPlane = xPlane;
}

void Player::SetYPlane(double yPlane)
{
    this -> yPlane = yPlane;
}

double Player::GetSpeed()
{
    return speed;
}

void Player::SetSpeed(double speed)
{
    this -> speed = speed;
}

bool Player::GetMoveForward()
{
    return moveForward;
}

void Player::SetMoveForward(bool moveForward)
{
    this -> moveForward = moveForward;
}

bool Player::GetMoveBackwards()
{
    return moveBackwards;
}

void Player::SetMoveBackwards(bool moveBackwards)
{
    this -> moveBackwards = moveBackwards;
}

bool Player::GetRotateLeft()
{
    return rotateLeft;
}

void Player::SetRotateLeft(bool rotateLeft)
{
    this -> rotateLeft = rotateLeft;
}

bool Player::GetRotateRight()
{
    return rotateRight;
}

void Player::SetRotateRight(bool rotateRight)
{
    this -> rotateRight = rotateRight;
}

int Player::Signum(double x)
{
    if(x > 0)
        return 1;
    else if(x < 0)
        return -1;
    else
        return 0;
}
