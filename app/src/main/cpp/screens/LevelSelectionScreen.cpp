//
// Created by michelle on 08/06/18.
//

#include "LevelSelectionScreen.h"

LevelSelectionScreen::LevelSelectionScreen(short x, short y)
        : UIScene(x, y, 0, 0) {

    _sprite = new Sprite(nullptr);
}

LevelSelectionScreen::~LevelSelectionScreen() {
    Release();
}

void
LevelSelectionScreen::Initialize(AAssetManager* assetManager, ANativeActivity* nativeActivity) {
    _indexReader = INIReader(assetManager, "level-index.ini");
    INIREADER_SECTION_LIST index = _indexReader.GetSection("general");

    _arrow = new Label(assetManager, 10, 0, 0, 0);
    _arrow->SetText(">");
    _arrow->SetScale(.3);
    float arrowVerticalPos = (Properties.HEIGHT / 2) + (_arrow->GetCalculatedHeight() / 2.0f);
    _arrow->SetY(static_cast<short>(arrowVerticalPos));

    _screenTitle = new Label(assetManager, 10, 10);
    _screenTitle->SetText("Level Selection");
    _screenTitle->SetScale(.5);

    _playButton = new PlayButton(assetManager, 800, 400);
    _playButton->SetXFromRight(10);
    _playButton->SetYFromBottom(10);
    _objects.push_back(_playButton);

    _leaderboardButton = new LeaderboardButton(assetManager, 600, 400);
    _leaderboardButton->SetXFromRight((short) 10 + _playButton->GetWidth());
    _leaderboardButton->SetYFromBottom(10);
    _objects.push_back(_leaderboardButton);

    int counter = 0;
    for (auto it = index.begin(); it != index.end(); it++) {
        Label* label = new Label(assetManager, 60, static_cast<short>(counter * _labelHeight), 0,
                                 0);
        label->SetScale(.3);
        label->SetText(it->first);
        _levels.push_back(it->second);
        _labels.push_back(label);
        counter++;
    }

    if (_labels.size() > 0) {
        _desiredLabel = _labels[0];
    }
}

void LevelSelectionScreen::Release() {
    if (_released) return;

    for (auto it = _labels.begin(); it != _labels.end(); it++) {
        if (*it != NULL) {
            delete *it;
        }
    }
    _labels.clear();

    if (_arrow != nullptr) {
        delete _arrow;
        _arrow = nullptr;
    }

    if (_screenTitle != nullptr) {
        delete _screenTitle;
        _screenTitle = nullptr;
    }

    if (_playButton != nullptr) {
//        delete _playButton;
        _playButton = nullptr;
    }

    if (_leaderboardButton != nullptr) {
//        delete _leaderboardButton;
        _leaderboardButton = nullptr;
    }

    _released = true;
}

void LevelSelectionScreen::ProcessInput(Input* input) {
    UIScene::ProcessInput(input);

    switch (input->type) {
        case InputType::MOVE: {
            glm::vec2 delta = input->position - _previousInputPosition;
            _offset += delta.y;

            _updateLabelPositions();
            break;
        }
        case InputType::DOWN: {
            // Don't process inputs on the button area
            if (input->position.y > 514 && input->position.x > 714) return;

            _inputDown = true;
            _setButtonsEnabled(!_inputDown);
            break;
        }
        case InputType::UP: {
            _inputDown = false;

            _setLevelByIndex(_getSelectedIndex());

            Label* closestLabel = _getLabelClosestToArrow();
            if (closestLabel != nullptr) {
                _desiredLabel = closestLabel;
            }

            _setButtonsEnabled(!_inputDown);

            break;
        }
        default: {
            break;
        }
    }

    _previousInputPosition = input->position;
}

int LevelSelectionScreen::_getSelectedIndex() {
    int index = 0;

    float lineTop = _arrow->GetY() + (_arrow->GetCalculatedHeight() / 2);

    for (auto it = _labels.begin(); it != _labels.end(); it++) {
        Label* label = *it;
        if (lineTop > label->GetY() && lineTop < (label->GetY() + label->GetCalculatedHeight())) {
            break;
        }

        index++;
    }

    // If not found ...
    if (index >= _labels.size()) index = -1;

    return index;
}

void LevelSelectionScreen::Update(double d) {
    if (_inputDown) return;
    if (_desiredLabel == nullptr) return;

    float distance = _getVerticalDistance(_arrow, _desiredLabel);
    if (distance >= 1.0f) {
        float direction = _desiredLabel->GetY() < _arrow->GetY() ? 1.0f : -1.0f;
        float scrollSpeed = _scrollSpeed;
        if (distance > scrollSpeed) {
            scrollSpeed /= (distance / scrollSpeed);
        } else if (distance > _labelHeight / 2) {
            scrollSpeed *= (distance / scrollSpeed) * 10;
        }
        float to_add = static_cast<float>(scrollSpeed * d * direction);
        _offset += std::min(to_add, distance);
        _updateLabelPositions();
        _setLevelByIndex(_getSelectedIndex());
    } else {
        _desiredLabel = nullptr;
    }
}

void LevelSelectionScreen::_updateLabelPositions() {
    float counter = 0;
    for (auto it = _labels.begin(); it != _labels.end(); it++) {
        Label* label = *it;
        label->SetX(60);

        float labelOffset = counter * label->GetCalculatedHeight();
        float calculatedY = _offset + (labelOffset);

        label->SetY(static_cast<short>(calculatedY));

        counter++;
    }
}

Label* LevelSelectionScreen::_getLabelClosestToArrow() {
    Label* result = nullptr;
    float distance = 1e9;
    for (auto it = _labels.begin(); it != _labels.end(); it++) {
        float cdist = _getVerticalDistance(*it, _arrow);
        if (cdist < distance) {
            result = *it;
            distance = cdist;
        }
    }

    return result;
}

float LevelSelectionScreen::_getVerticalDistance(UIObject* left, UIObject* right) {
    return std::abs(right->GetY() - left->GetY());
}

void LevelSelectionScreen::_setButtonsEnabled(bool b) {
    if (_leaderboardButton != nullptr) _leaderboardButton->SetVisible(b);
    if (_playButton != nullptr) _playButton->SetVisible(b);
}

void LevelSelectionScreen::_setLevelByIndex(int index) {
    if (index < 0) {
        _playButton->ClearLevel();
        _leaderboardButton->ClearLevel();
    } else {
        _playButton->SetLevel(_levels[index]);
        _leaderboardButton->SetLevelName(_levels[index]);
    }
}
