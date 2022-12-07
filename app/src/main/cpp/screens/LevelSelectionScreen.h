//
// Created by michelle on 08/06/18.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_LEVELSELECTIONSCREEN_H
#define RHYTHMIC_PROGRAMMING_GAME_LEVELSELECTIONSCREEN_H

#include <cmath>
#include <algorithm>
#include "UIScene.h"
#include "../uiobjects/Label.h"
#include "../INIReader.h"
#include "../properties.h"
#include "../uiobjects/PlayButton.h"
#include "../uiobjects/LeaderboardButton.h"

class LevelSelectionScreen : public UIScene {
private:
    std::vector<Label*> _labels;
    Label* _arrow = nullptr;
    Label* _screenTitle = nullptr;
    PlayButton* _playButton = nullptr;
    LeaderboardButton* _leaderboardButton = nullptr;
    float _offset = 0.0f;
    float _labelHeight = 70.0f;
    float _scrollSpeed = 1200.0f;
    bool _inputDown;
    Label* _desiredLabel = nullptr;

    std::vector<std::string> _levels;
    INIReader _indexReader;

    glm::vec2 _previousInputPosition;
    bool _released;

    int _getSelectedIndex();

    void _updateLabelPositions();

    Label* _getLabelClosestToArrow();

    float _getVerticalDistance(UIObject* left, UIObject* right);

    void _setButtonsEnabled(bool b);

    void _setLevelByIndex(int index);
public:

    LevelSelectionScreen(short x, short y);

    ~LevelSelectionScreen();

    void Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) override;

    void Release() override;

    void ProcessInput(Input* input) override;

    void Update(double d) override;
};


#endif //RHYTHMIC_PROGRAMMING_GAME_LEVELSELECTIONSCREEN_H
