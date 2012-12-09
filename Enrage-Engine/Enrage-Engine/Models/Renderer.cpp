#include "Renderer.h"

Renderer::Renderer()
{
    this -> display = NULL;
    this -> objectManager = NULL;
}

Renderer::Renderer(Display* display, ObjectManager* objectManager)
{
    this -> display = display;
    this -> objectManager = objectManager;
    lookupTableSize = display -> GetHeight() / 2;

    floorCastingLookupTable = new double[lookupTableSize];

    for(uint i = 0; i < lookupTableSize; i++)
        floorCastingLookupTable[i] = display -> GetHeight() / (2.0 * (i + lookupTableSize) - display -> GetHeight());

    zBuffer = new uint[display -> GetWidth()];

    for(uint i = 0; i < display -> GetWidth(); i++)
        zBuffer[i] = 0;

    this -> useSepia = false;
    this -> useNegative = false;
}

Renderer::~Renderer()
{
    if(floorCastingLookupTable)
        delete[] floorCastingLookupTable;

    if(zBuffer)
        delete[] zBuffer;
}

void Renderer::Draw(Map* map, Player* player)
{
    double xPlane = player -> GetXPlane();
    double yPlane = player -> GetYPlane();

    double fogDistance = map -> GetFogDistance();
    double inverseFogDistance = map -> GetInverseFogDistance();
        
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
        bool hitADoor = false;
            
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
        double doorDistance;

        double xDoorDelta = 0.0;
        double yDoorDelta = 0.0;
            
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

            if (map -> GetTileAtPosition(xMapPosition, yMapPosition) != 0)
            {
                if(map -> GetTileAtPosition(xMapPosition, yMapPosition) == -1)
                {
                    if(wallSide == 0)
                    {
                        if(!hitADoor && yDistance + yDeltaDistance > xDistance + 0.5 * xDeltaDistance)
                        {
                            hitADoor = true;
                        }
                        else
                            continue;
                    }
                    else
                    {
                        if(!hitADoor && xDistance + xDeltaDistance > yDistance + 0.5 * yDeltaDistance)
                        {
                            hitADoor = true;
                        }
                        else
                            continue;
                    }
                }

                hitAWall = true;
            }
        }
            
        if (wallSide == 0)
            totalWallDistance = fabs(((double)xMapPosition - xRayPosition + (1.0 - (double)xVectorDirection) / 2.0) / xRayDirection);
        else
            totalWallDistance = fabs(((double)yMapPosition - yRayPosition + (1.0 - (double)yVectorDirection) / 2.0) / yRayDirection);

        if(hitADoor)
        {
            if(xDeltaDistance < yDeltaDistance)
                doorDistance = totalWallDistance + (0.5 * xDeltaDistance);
            else
                doorDistance = totalWallDistance + 0.5 * yDeltaDistance;
        }

        int lineHeight = 0;

        if(hitADoor)
            lineHeight = fabs((display -> GetHeight() / doorDistance));
        else
            lineHeight = fabs((display -> GetHeight() / totalWallDistance));
            
        int lineStart = display -> GetHeight() / 2 - lineHeight / 2;
            
        if(lineStart < 0)
            lineStart = 0;
            
        int lineEnd = display -> GetHeight() / 2 + lineHeight / 2;
            
        if(lineEnd >= display -> GetHeight())
            lineEnd = display -> GetHeight();
        
        double wallX;

        if (wallSide == 1)
            wallX = xRayPosition + ((yMapPosition - yRayPosition + (1 - yVectorDirection) / 2) / yRayDirection) * xRayDirection;
        else
            wallX = yRayPosition + ((xMapPosition - xRayPosition + (1 - xVectorDirection) / 2) / xRayDirection) * yRayDirection;
        
        wallX -= (int)(wallX);

        IImage* currentTexture;

        if(map -> GetTileAtPosition(xMapPosition, yMapPosition) == -1)
            currentTexture = map -> GetTexture(map -> GetDoorTextureIndex());
        else
            currentTexture = map -> GetTexture(map -> GetTileAtPosition(xMapPosition, yMapPosition) - 1);

        int texX = (int)(wallX * (double)(currentTexture -> GetWidth()));
        if(wallSide == 0 && xRayDirection > 0)
            texX = currentTexture -> GetWidth() - texX - 1;
        if(wallSide == 1 && yRayDirection < 0)
            texX = currentTexture -> GetWidth() - texX - 1;
            
        for(int y = lineStart; y < lineEnd; y++)
        {
            int d = y * 256 - display -> GetHeight() * 128 + lineHeight * 128;
            int texY = ((d * currentTexture -> GetHeight()) / lineHeight) / 256;

            uint color = currentTexture -> GetPixel(texX, texY);

            if(wallSide == 1)
                color = (color >> 1) & 0xFF7F7F7F;

            if(map -> UsesFog())
            {
                color = Fog(color, totalWallDistance, fogDistance, inverseFogDistance);
            }

            if(useSepia)
                color = Sepia(color);

            if(useNegative)
                color = Negative(color);

            display -> pixels[currentDisplayColumn + y] = color;
        }

        zBuffer[i] = totalWallDistance;

        // -------------
        // FLOOR CASTING
        // -------------

        double xFloorWallPosition, yFloorWallPosition;

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
        uint ceilingColor, floorColor;  

        distWall = totalWallDistance;
        distPlayer = 0.0;

        if (lineStart < 0)
            lineEnd = display -> GetHeight();

        for(int y = lineEnd + 1; y <= display -> GetHeight(); y++)
        {
            currentDist = floorCastingLookupTable[y - lookupTableSize];
    
            double weight = (currentDist - distPlayer) / (distWall - distPlayer);
    
            double currentFloorX = weight * xFloorWallPosition + (1.0 - weight) * player -> GetXPosition();
            double currentFloorY = weight * yFloorWallPosition + (1.0 - weight) * player -> GetYPosition();
    
            int floorTexX, floorTexY;
            floorTexX = (int)(currentFloorX * map -> GetTexture(5) -> GetHeight()) % map -> GetTexture(5) -> GetWidth();
            floorTexY = (int)(currentFloorY * map -> GetTexture(5) -> GetHeight()) % map -> GetTexture(5) -> GetHeight();

            ceilingColor = map -> GetTexture(map -> GetCeilingTextureIndex()) -> GetPixel(floorTexX, floorTexY);
            floorColor = map -> GetTexture(map -> GetFloorTextureIndex()) -> GetPixel(floorTexX, floorTexY);

            if(map -> UsesFog())
            {
                ceilingColor = Fog(ceilingColor, currentDist, fogDistance, inverseFogDistance);
                floorColor = Fog(floorColor, currentDist, fogDistance, inverseFogDistance);
            }

            if(useSepia)
            {
                floorColor = Sepia(floorColor);
                ceilingColor = Sepia(ceilingColor);
            }

            if(useNegative)
            {
                floorColor = Negative(floorColor);
                ceilingColor = Negative(ceilingColor);
            }

            display -> pixels[currentDisplayColumn + y - 1] = floorColor;
            display -> pixels[currentDisplayColumn + display -> GetHeight() - y] = ceilingColor;
        }
    }

    // --------------
    // SPRITE CASTING
    // --------------

    for(int i = 0; i < objectManager -> GetSpriteCount(); i++)
    {
        objectManager -> renderingSpriteOrder[i] = i;
        objectManager -> renderingSpriteDistance[i] =
            ((player -> GetXPosition() - objectManager -> GetSpriteAtIndex(i) -> GetXPosition()) *
            (player -> GetXPosition() - objectManager -> GetSpriteAtIndex(i) -> GetXPosition())
            + (player -> GetYPosition() - objectManager -> GetSpriteAtIndex(i) -> GetYPosition())
            * (player -> GetYPosition() - objectManager -> GetSpriteAtIndex(i) -> GetYPosition()));
    }

    objectManager -> Sort();

    for(int i = 0; i < objectManager -> GetSpriteCount(); i++)
    {
        double spriteX = objectManager -> GetSpriteAtIndex(objectManager -> renderingSpriteOrder[i]) -> GetXPosition() - player -> GetXPosition();
        double spriteY = objectManager -> GetSpriteAtIndex(objectManager -> renderingSpriteOrder[i]) -> GetYPosition() - player -> GetYPosition();

        double invDet = 1.0 / (player -> GetXPlane() *
                               player -> GetYDirection() -
                               player -> GetXDirection() *
                               player -> GetYPlane());

        double transformX = invDet * (player -> GetYDirection() * spriteX - player -> GetXDirection() * spriteY);
        double transformY = invDet * (-player -> GetYPlane() * spriteX + player -> GetXPlane() * spriteY);

        int spriteScreenX = int((display -> GetWidth() / 2) * (1 + transformX / transformY));

        int spriteHeight = abs(int(display -> GetHeight() / (transformY)));
        int drawStartY = -spriteHeight / 2 + display -> GetHeight() / 2;

        if(drawStartY < 0)
            drawStartY = 0;

        int drawEndY = spriteHeight / 2 + display -> GetHeight() / 2;

        if(drawEndY >= display -> GetHeight())
            drawEndY = display -> GetHeight() - 1;

        int spriteWidth = abs( int (display -> GetHeight() / (transformY)));
        int drawStartX = -spriteWidth / 2 + spriteScreenX;
        if(drawStartX < 0)
            drawStartX = 0;
        int drawEndX = spriteWidth / 2 + spriteScreenX;
        if(drawEndX >= (int)display -> GetWidth())
            drawEndX = display -> GetWidth() - 1;

        for(int stripe = drawStartX; stripe < drawEndX; stripe++)
        {
            int texX = int(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * map -> GetTextureSize() / spriteWidth) / 256;
            if(transformY > 0 && stripe > 0 && stripe < display -> GetWidth() && transformY < zBuffer[stripe]) 
                for(int y = drawStartY; y < drawEndY; y++)
                {
                    int d = y * 256 - display -> GetHeight() * 128 + spriteHeight * 128;
                    int texY = ((d * map -> GetTextureSize()) / spriteHeight) / 256;

                    uint color = objectManager -> GetSpriteAtIndex(objectManager -> renderingSpriteOrder[i]) -> GetSprite() -> GetPixel(texX, texY);

                    if(map -> UsesFog())
                        color = Fog(color, transformY, fogDistance, inverseFogDistance);

                    if(useSepia)
                        color = Sepia(color);

                    if(useNegative)
                        color = Negative(color);

                    if(((color & 0xFF000000) >> 24) >= 10)
                        display -> pixels[stripe * display -> GetHeight() + y] = color;
                }
        }
    }
}

uint Renderer::Sepia(uint color)
{
    ubyte red   = (color & 0x00FF0000) >> 16;
    ubyte green = (color & 0x0000FF00) >> 8;
    ubyte blue  =  color & 0x000000FF;

    uint alphaChannel = color & 0xFF000000;

    // uint sepiaRed = red * 0.393 + green * 0.769 + blue * 0.189;
    uint sepiaRed = red * 402 + green * 787 + blue * 194;
    sepiaRed >>= 10;

    if(sepiaRed > 255)
        sepiaRed = 255;

    // uint sepiaGreen = red * 0.349 + green * 0.686 + blue * 0.168;
    uint sepiaGreen = red * 357 + green * 702 + blue * 172;
    sepiaGreen >>= 10;

    if(sepiaGreen > 255)
        sepiaGreen = 255;

    //uint sepiaBlue = red * 0.272 + green * 0.534 + blue * 0.131;
    uint sepiaBlue = red * 279 + green * 547 + blue * 134;
    sepiaBlue >>= 10;

    if(sepiaBlue > 255)
        sepiaBlue = 255;

    return sepiaRed << 16 | sepiaGreen << 8 | sepiaBlue | alphaChannel;
}

uint Renderer::Fog(uint color, double distance, double fogDistance, double inverseFogDistance)
{
    uint fogColor;

    double colorMultiplier = (fogDistance - distance) / fogDistance;

    if(colorMultiplier > 1)
        colorMultiplier = 1;

    if(distance < fogDistance)
    {
        uint alphaChannel = color & 0xFF000000;

        fogColor = (uint) ((color & 0x000000FF)        * colorMultiplier)        & 0x000000FF |
                  ((uint)(((color & 0x0000FF00) >> 8)  * colorMultiplier) << 8)  & 0x0000FF00 |
                  ((uint)(((color & 0x00FF0000) >> 16) * colorMultiplier) << 16) & 0x00FF0000;

        fogColor |= alphaChannel;
    }
    else
        fogColor = 0;

    return fogColor;
}

uint Renderer::Negative(uint color)
{
    uint alphaChannel = color & 0xFF000000;

    color = ~color;
    color &= 0x00FFFFFF;
    color |= alphaChannel;

    return color;
}

bool Renderer::UsesSepia()
{
    return useSepia;
}

void Renderer::SetUsesSepia(bool useSepia)
{
    this -> useSepia = useSepia;
}

bool Renderer::UsesNegative()
{
    return useNegative;
}

void Renderer::SetUsesNegative(bool useNegative)
{
    this -> useNegative = useNegative;
}
