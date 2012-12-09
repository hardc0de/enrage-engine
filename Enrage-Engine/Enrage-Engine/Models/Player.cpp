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

void Player::MoveThink()
{
    ChangeAcceleration();
    Move();

    if(rotateLeft)
        RotateLeft();
    if(rotateRight)
        RotateRight();
}

void Player::Move()
{
    if(!CollidesX(Signum(acceleration)))
        xPosition += xDirection * speed * acceleration;
    if(!CollidesY(Signum(acceleration)))
        yPosition += yDirection * speed * acceleration;
}

void Player::RotateLeft()
{
    double oldxDirectionVector = xDirection;
    xDirection = xDirection * cos(speed / 2.5) - yDirection * sin(speed / 2.5);
    yDirection = oldxDirectionVector * sin(speed / 2.5) + yDirection * cos(speed / 2.5);
        
    double oldxPlaneVector = xPlane;
    xPlane = xPlane * cos(speed / 2.5) - yPlane * sin(speed / 2.5);
    yPlane = oldxPlaneVector * sin(speed / 2.5) + yPlane * cos(speed / 2.5);
}

void Player::RotateRight()
{
    double oldxDirectionVector = xDirection;
    xDirection = xDirection * cos(-speed / 2.5) - yDirection * sin(-speed / 2.5);
    yDirection = oldxDirectionVector * sin(-speed / 2.5) + yDirection * cos(-speed / 2.5);
        
    double oldxPlaneVector = xPlane;
    xPlane = xPlane * cos(-speed / 2.5) - yPlane * sin(-speed / 2.5);
    yPlane = oldxPlaneVector * sin(-speed / 2.5) + yPlane * cos(-speed / 2.5);
}

void Player::Rotate(double angle)
{
    double oldxDirectionVector = xDirection;
    xDirection = xDirection * cos(angle) - yDirection * sin(angle);
    yDirection = oldxDirectionVector * sin(angle) + yDirection * cos(angle);
        
    double oldxPlaneVector = xPlane;
    xPlane = xPlane * cos(angle) - yPlane * sin(angle);
    yPlane = oldxPlaneVector * sin(angle) + yPlane * cos(angle);
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

double Player::GetCurrentSpeed()
{
    return currentSpeed;
}

void Player::SetCurrentSpeed(double currentSpeed)
{
    this -> currentSpeed = currentSpeed;
}

double Player::GetAcceleration()
{
    return acceleration;
}

void Player::SetAcceleration(double acceleration)
{
    this -> acceleration = acceleration;
}

void Player::ChangeAcceleration()
{
    if((moveForward) && acceleration <= 1.0)
        acceleration += 0.1;
    else if((moveBackwards) && acceleration >= -1.0)
        acceleration -= 0.1;
    else if(acceleration > 0.0)
        acceleration -= 0.1;
    else if(acceleration < 0.0)
        acceleration += 0.1;
    if(acceleration < 0.1 && acceleration > 0)
        acceleration = 0;
    if(acceleration > -0.1 && acceleration < 0)
        acceleration = 0;
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
