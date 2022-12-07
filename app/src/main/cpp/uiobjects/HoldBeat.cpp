//
// Created by Anne on 25-5-2018.
//

#include "HoldBeat.h"

HoldBeat::HoldBeat(Beat beat, LaneSide laneSide, short targetX, short targetY) :
        ScreenBeat(beat, laneSide, targetX, targetY, BeatType::HOLDBEAT) {
    _initializeBeat();
}

HoldBeat::~HoldBeat() {
    delete _spriteDown;
    delete _spriteMiddle;
    delete _spriteUp;

    if (_tailBeat) {
        delete _spriteDownTail;
        delete _spriteUpTail;
    }
}

void HoldBeat::Update(float audioPosition) {
    float delta = audioPosition - _beat.position;

    if (delta == 0.0f) return;

    /*
     * Distance from hit area of the DOWN note
     */
    short downDistance = static_cast<short>((delta / 1000) * Properties.HEIGHT);

    /*
     * Distance from hit area of the UP note
     */
    short upDistance = static_cast<short>(((delta - _beat.duration) / 1000) * Properties.HEIGHT);

    /*
     * Actual position of the Y of the DOWN note
     */
    short downPositionY = _targetY;
    if (!_isPressed) downPositionY += downDistance;

    /*
     * Actual position of the Y of the UP note
     */
    short upPositionY = _targetY + upDistance;

    if (_spriteDown != nullptr) {

        float yPos = downPositionY - (_height * _verticalAlign);

        _spriteDown->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                yPos,
                0));
    }

    if (_spriteMiddle != nullptr) {
        /*
         * Position of the middle lane is top left
         */
        _spriteMiddle->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                upPositionY + _height * 0.5f,
                0));
    }

    /*
     * Distance between DOWN and UP note
     */
    float diff = downPositionY - upPositionY;
    _spriteMiddle->SetScale(_width, diff - _height, 1);

    if (_spriteUp != nullptr) {
        _spriteUp->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                upPositionY - (_height * _verticalAlign),
                0));
    }

    if (_spriteUpTail != nullptr) {
        _spriteUpTail->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                upPositionY - (_height * _verticalAlign),
                0));
    }

    if (_spriteDownTail != nullptr) {
        _spriteDownTail->SetPosition(glm::vec3(
                _x - (_width * _horizontalAlign),
                downPositionY - (_height * _verticalAlign),
                0));
    }

    if (diff <= _height - 20) {
        if (_spriteDownTail != nullptr && _spriteUpTail != nullptr) {
            _removeTail();
        }
    }
}

void HoldBeat::_initializeBeat() {
    ResourceManager& resourceManager = ResourceManager::GetInstance();
    _spriteDown = new Sprite(resourceManager.GetTexture("hold_beat_down"));
    _spriteDown->SetZIndex(1);
    _spriteDown->SetScale(_width, _height, 1);

    _spriteMiddle = new Sprite(resourceManager.GetTexture("hold_beat_middle"));
    _spriteMiddle->SetZIndex(1);
    _spriteMiddle->SetScale(_width, _height, 1);

    _spriteUp = new Sprite(resourceManager.GetTexture("hold_beat_up"));
    _spriteUp->SetZIndex(1);
    _spriteUp->SetScale(_width, _height, 1);

    _spriteDownTail = new Sprite(resourceManager.GetTexture("hold_beat_down_tail"));
    _spriteDownTail->SetZIndex(1);
    _spriteDownTail->SetScale(_width, _height, 1);

    _spriteUpTail = new Sprite(resourceManager.GetTexture("hold_beat_up_tail"));
    _spriteUpTail->SetZIndex(1);
    _spriteUpTail->SetScale(_width, _height, 1);

    _horizontalAlign = UIObject::CENTER;
    _verticalAlign = UIObject::CENTER;

    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _spriteDown
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _spriteMiddle
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _spriteUp
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _spriteDownTail
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::ADD_OBJECT2D,
            _spriteUpTail
    });

}

float HoldBeat::GetBeatEnd() {
    return (_beat.position + _beat.duration);
}

void HoldBeat::ClearBeat() {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _spriteDown
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _spriteMiddle
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _spriteUp
    });
    if (_tailBeat) {
        _clearTailBeats();
    }
}

void HoldBeat::_clearTailBeats() {
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _spriteDownTail
    });
    ServiceManager::GetInstance().Send(new Message{
            MessageType::REMOVE_OBJECT2D,
            _spriteUpTail
    });
}

void HoldBeat::_removeTail() {
    _clearTailBeats();
    delete _spriteDownTail;
    delete _spriteUpTail;
    _spriteDownTail = nullptr;
    _spriteUpTail = nullptr;
    _tailBeat = false;
}



