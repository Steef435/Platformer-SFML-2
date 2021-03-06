#ifndef LEVELEDITORSTATE_HPP_INCLUDED
#define LEVELEDITORSTATE_HPP_INCLUDED

#include "mainmenu.hpp"
#include "button.hpp"
#include "gamestate.hpp"
#include "leveleditormenu.hpp"
#include "player.hpp"
#include "inlinefunctions.hpp"
#include "popupbox.hpp"

class LevelEditorState : public GameState
{
    public:
        LevelEditorState(sf::RenderWindow* renderWindow, StateManager* manager);
        ~LevelEditorState();

        void handle_events();
        void logic(double passed, double deltaTime);
        void render(double alpha);

        void MouseButtonPressed(sf::Vector2i mousePos, bool leftMouseClick);

        void SetSelectedTileFilename(std::string filename, bool _selectionRespectsGrid = true) { selectedTileFilename = filename; selectionRespectsGrid = _selectionRespectsGrid; }
        std::string GetSelectedTileFilename() { return selectedTileFilename; }
        bool HasSelectedTile() { return selectedTileFilename != ""; }

        void AddSprite(SpriteInfo spriteInfo) { sprites.push_back(spriteInfo); }
        std::vector<SpriteInfo>& GetSprites() { return sprites; }
        std::vector<CollidableObject>& GetCollidableObjects() { return collidableObjects; }

        sf::Vector2f GetPositionForSelectedTile(sf::Vector2i mousePos);
        bool IsSpotTakenBySprite(sf::Vector2f position);

        static void testOut(void* inst, Button* button);
        static void save(void* inst, Button* button);
        static void toggleGrid(void* inst, Button* button);
        static void setSelectedTile(void* inst, Button* button);
        static void clear(void* inst, Button* button);
        static void toggleCollisionLines(void* inst, Button* button);

    private:
        sf::RenderWindow* m_window;
        StateManager* m_manager;
        LevelEditorMenu* m_levelEditorMenu;
        sf::RenderWindow* m_tileSetWindow;
        PopUpBox* m_popUpBox;

        std::string selectedTileFilename;
        bool enabledGrid, selectionRespectsGrid, justReselectedTile, movedCursorOutOfNewTile, testingLevelOut, drawingCollisionLine, minimizedWindow, m_placeTileWithCtrl;
        bool m_showCollisionLines;
        std::vector<SpriteInfo> sprites;
        std::vector<CollidableObject> collidableObjects;
        std::vector<sf::VertexArray> grid;
        std::vector<sf::VertexArray> collisionLines;
        sf::VertexArray collisionLineSelection;
        Player* player;
        sf::Vector2i prevTilesetWindowPos;

        GameStates gameStateAfterPopUpBox;
};

#endif // LEVELEDITORSTATE_HPP_INCLUDED
