#ifndef LEVELEDITORSTATE_HPP_INCLUDED
#define LEVELEDITORSTATE_HPP_INCLUDED

#include "mainmenu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "leveleditormenu.hpp"
#include "player.hpp"

struct SpriteInfo
{
    std::string filename;
    sf::Vector2f position;
    bool isCollidable;
    bool forceIgnoreGrid;
    bool priorityInDrawing; //! NYI! When set to true it is drawn last (right before player, of course) 

    bool operator == (SpriteInfo spriteInfo)
    {
        return spriteInfo.filename == filename && spriteInfo.position == position && spriteInfo.isCollidable == isCollidable && spriteInfo.forceIgnoreGrid == forceIgnoreGrid && spriteInfo.priorityInDrawing == priorityInDrawing;
    }

    bool operator != (SpriteInfo spriteInfo)
    {
        return spriteInfo.filename != filename || spriteInfo.position != position || spriteInfo.isCollidable != isCollidable || spriteInfo.forceIgnoreGrid != forceIgnoreGrid || spriteInfo.priorityInDrawing != priorityInDrawing;
    }
};

class LevelEditorState : public GameState
{
    public:
        LevelEditorState(sf::RenderWindow* renderWindow, StateManager* manager);

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        void MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick);

        void SetSelectedTileFilename(std::string filename, bool _selectionRespectsGrid = true) { selectedTileFilename = filename; selectionRespectsGrid = _selectionRespectsGrid; }
        std::string GetSelectedTileFilename() { return selectedTileFilename; }
        bool HasSelectedTile() { return selectedTileFilename != ""; }

        void AddSprite(SpriteInfo spriteInfo) { sprites.push_back(spriteInfo); }
        std::vector<SpriteInfo>& GetSprites() { return sprites; }

        sf::Vector2f GetPositionForSelectedTile();
        bool IsSpotTakenBySprite(sf::Vector2f position);

        //bool justReselectedTile, movedCursorOutOfNewTile, testingLevelOut;

        static void save(void* inst, Button* button);
        //static void tiles(void* inst, CollapsableButton* button);
        static void toggleGrid(void* inst, Button* button);
        static void setSelectedTile(void* inst, Button* button, std::string filename);

    private:
        sf::RenderWindow* m_window;
        StateManager* m_manager;
        LevelEditorMenu* m_levelEditorMenu;

        std::string selectedTileFilename;
        bool selectionRespectsGrid;
        std::vector<SpriteInfo> sprites;
        bool enabledGrid;
        sf::RectangleShape grid[20][12];
        Player* player;
        bool justReselectedTile, movedCursorOutOfNewTile, testingLevelOut;
};


#endif // LEVELEDITORSTATE_HPP_INCLUDED