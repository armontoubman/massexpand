/*

The MIT License (MIT)

Copyright (c) 2010 The writers of BWSAL

Permission is hereby granted, free of charge, to any person obtaining a copy 
of this software and associated documentation files (the "Software"), to 
deal in the Software without restriction, including without limitation the 
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in 
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
DEALINGS IN THE SOFTWARE.

*/

#pragma once
#include <BWAPI.h>
#include "RectangleArray.h"

/**
 * The BuildingPlacer class from BWSAL http://code.google.com/p/bwsal/
 */
class BuildingPlacer
{
  public:
    BuildingPlacer();
    bool canBuildHere(BWAPI::TilePosition position, BWAPI::UnitType type) const;
    bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type) const;
    bool canBuildHereWithSpace(BWAPI::TilePosition position, BWAPI::UnitType type, int buildDist) const;
    BWAPI::TilePosition getBuildLocation(BWAPI::UnitType type) const;
    BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position,BWAPI::UnitType type) const;
    BWAPI::TilePosition getBuildLocationNear(BWAPI::TilePosition position,BWAPI::UnitType type, int buildDist) const;
    bool buildable(int x, int y) const;
    void reserveTiles(BWAPI::TilePosition position, int width, int height);
    void freeTiles(BWAPI::TilePosition position, int width, int height);
    void setBuildDistance(int distance);
    int getBuildDistance() const;
    bool isReserved(int x, int y) const;
  private:
    Util::RectangleArray<bool> reserveMap;
    int buildDistance;
};