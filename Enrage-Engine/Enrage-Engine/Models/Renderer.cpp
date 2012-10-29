#include "Renderer.h"

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

void Renderer::Draw(Display* display, Map* map, Player* player)
{
    double xPlane = player -> GetXPlane();
    double yPlane = player -> GetYPlane();
        
    for(uint i = 0; i < display -> GetWidth(); i++)
    {
        double xCamera = 2 * i / (double)display -> GetWidth() - 1.0;
        double xRayPosition = player -> GetXPosition();
        double yRayPosition = player -> GetYPosition();
        double xRayDirection = player -> GetXDirection() + xPlane * xCamera;
        double yRayDirection = player -> GetYDirection() + yPlane * xCamera;

        uint currentDisplayColumn = i * display -> GetHeight();
            
        int xVectorDirection;
        int yVectorDirection;
            
        bool hitAWall = false;
            
        int wallSide = 0;
            
        int xMapPosition = (int)xRayPosition;
        int yMapPosition = (int)yRayPosition;
            
        double xDistance;
        double yDistance;

        double xRayDirSquare = xRayDirection * xRayDirection;
        double yRayDirSquare = yRayDirection * yRayDirection;
            
        double xDeltaDistance = sqrt(1.0 + yRayDirSquare / xRayDirSquare);
        double yDeltaDistance = sqrt(1.0 + xRayDirSquare / yRayDirSquare);
            
        double totalWallDistance;
            
        if(xRayDirection < 0.0)
        {
            xVectorDirection = -1;
            xDistance = (xRayPosition - (double)xMapPosition) * xDeltaDistance;
        }
            
        else
        {
            xVectorDirection = 1;
            xDistance = ((double)xMapPosition + 1.0 - xRayPosition) * xDeltaDistance;
        }
            
        if(yRayDirection < 0.0)
        {
            yVectorDirection = -1;
            yDistance = (yRayPosition - (double)yMapPosition) * yDeltaDistance;
        }
            
        else
        {
            yVectorDirection = 1;
            yDistance = ((double)yMapPosition + 1.0 - yRayPosition) * yDeltaDistance;
        }
            
        while (!hitAWall)
        {
            if (xDistance < yDistance)
            {
                xDistance += xDeltaDistance;
                xMapPosition += xVectorDirection;
                wallSide = 0;
            }
            else
            {
                yDistance += yDeltaDistance;
                yMapPosition += yVectorDirection;
                wallSide = 1;
            }

            if (map -> GetTileAtPosition(xMapPosition, yMapPosition) > 0)
                hitAWall = true;
        }
            
        if (wallSide == 0)
            totalWallDistance = fabs(((double)xMapPosition - xRayPosition + (1.0 - (double)xVectorDirection) / 2.0) / xRayDirection);
        else
            totalWallDistance = fabs(((double)yMapPosition - yRayPosition + (1.0 - (double)yVectorDirection) / 2.0) / yRayDirection);

        int lineHeight = fabs((display -> GetHeight() / totalWallDistance));
            
        int lineStart = display -> GetHeight() / 2 - lineHeight / 2;
            
        if(lineStart < 0)
            lineStart = 0;
            
        int lineEnd = display -> GetHeight() / 2 + lineHeight / 2;
            
        if(lineEnd >= display -> GetHeight())
            lineEnd = display -> GetHeight();
            
        //calculate value of wallX
        double wallX; //where exactly the wall was hit
        if (wallSide == 1) wallX = xRayPosition + ((yMapPosition - yRayPosition + (1 - yVectorDirection) / 2) / yRayDirection) * xRayDirection;
        else           wallX = yRayPosition + ((xMapPosition - xRayPosition + (1 - xVectorDirection) / 2) / xRayDirection) * yRayDirection;
        wallX -= (int)(wallX);

        Image* currentTexture = map -> GetTexture(map -> GetTileAtPosition(xMapPosition, yMapPosition) - 1);
             
        //x coordinate on the texture
        int texX = (int)(wallX * (double)(currentTexture -> GetWidth()));
        if(wallSide == 0 && xRayDirection > 0)
            texX = currentTexture -> GetWidth() - texX - 1;
        if(wallSide == 1 && yRayDirection < 0)
            texX = currentTexture -> GetWidth() - texX - 1;
        //Image scaledTextureLine = textureline.getScaledInstance(1, lineHeight, Image.SCALE_AREA_AVERAGING);
            
        for(int y = lineStart; y < lineEnd; y++)
        {
            int d = y * 256 - display -> GetHeight() * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
            int texY = ((d * currentTexture -> GetHeight()) / lineHeight) / 256;

            uint color = currentTexture -> pixels[texX * currentTexture -> GetHeight() + texY];

            if(wallSide == 1)
                color = (color >> 1) & 8355711;

            display -> pixels[currentDisplayColumn + y] = color;
        }

        // FLOOR CASTING

        double xFloorWallPosition, yFloorWallPosition; //x, y position of the floor texel at the bottom of the wall

        // 4 different wall directions possible
        if(wallSide == 0 && xRayDirection > 0)
        {
            xFloorWallPosition = xMapPosition;
            yFloorWallPosition = yMapPosition + wallX;
        }
        else if(wallSide == 0 && xRayDirection < 0)
        {
            xFloorWallPosition = xMapPosition + 1.0;
            yFloorWallPosition = yMapPosition + wallX;
        }
        else if(wallSide == 1 && yRayDirection > 0)
        {
            xFloorWallPosition = xMapPosition + wallX;
            yFloorWallPosition = yMapPosition;
        }
        else
        {
            xFloorWallPosition = xMapPosition + wallX;
            yFloorWallPosition = yMapPosition + 1.0;
        } 

        double distWall, distPlayer, currentDist;  

        distWall = totalWallDistance;
        distPlayer = 0.0;

        if (lineStart < 0)
            lineEnd = display -> GetHeight(); //becomes < 0 when the integer overflows

        //draw the floor from drawEnd to the bottom of the screen
        for(int y = lineEnd + 1; y <= display -> GetHeight(); y++)
        {
            currentDist = display -> GetHeight() / (2.0 * y - display -> GetHeight()); //you could make a small lookup table for this instead
    
            double weight = (currentDist - distPlayer) / (distWall - distPlayer);
    
            double currentFloorX = weight * xFloorWallPosition + (1.0 - weight) * player -> GetXPosition();
            double currentFloorY = weight * yFloorWallPosition + (1.0 - weight) * player -> GetYPosition();
    
            int floorTexX, floorTexY;
            floorTexX = (int)(currentFloorX * map -> GetTexture(5) -> GetHeight()) % map -> GetTexture(5) -> GetWidth();
            floorTexY = (int)(currentFloorY * map -> GetTexture(5) -> GetHeight()) % map -> GetTexture(5) -> GetHeight();

            display -> pixels[currentDisplayColumn + y - 1] = map -> GetTexture(7) -> pixels[floorTexX *  map -> GetTextureSize() + floorTexY];
            display -> pixels[currentDisplayColumn + display -> GetHeight() - y] = map -> GetTexture(6) -> pixels[floorTexX *  map -> GetTextureSize() + floorTexY];
        }
    }
}