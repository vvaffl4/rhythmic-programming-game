//
// Created by patri on 5/24/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_WORKSPACEOBJECT_H
#define RHYTHMIC_PROGRAMMING_GAME_WORKSPACEOBJECT_H

#include "../AudioPlayer.h"
#include "../sprite/Sprite.h"

class WorkspaceObject {
protected:

    short _x;
    short _y;
    short _width;
    short _height;
    float _horizontalAlign;
    float _verticalAlign;
    bool _toBeDeleted = false;

public:
    WorkspaceObject();

    WorkspaceObject(short x, short y, short width, short height);

    virtual ~WorkspaceObject();

    virtual void Initialize() = 0;

    virtual void Clear() = 0;

    virtual void Update(AudioPlayer* audioPlayer) = 0;

    void SetX(short x);

    void SetY(short y);

    void SetWidth(short width);

    void SetHeight(short height);

    virtual void SetAlign(float x, float y);

    virtual void SetPosition(short x, short y);

    bool ShouldBeDeleted();

};


#endif //RHYTHMIC_PROGRAMMING_GAME_WORKSPACEOBJECT_H
