//
// Created by patri on 5/24/2018.
//

#ifndef RHYTHMIC_PROGRAMMING_GAME_WORKSPACESERVICE_H
#define RHYTHMIC_PROGRAMMING_GAME_WORKSPACESERVICE_H

#include <vector>

#include "ServiceManager.h"
#include "../workspace/WorkspaceObject.h"

class WorkspaceService : public Service {
private:
    std::vector<WorkspaceObject*> _workspaceObjects;

    void _addWorkspaceObject(WorkspaceObject* workspaceObject);

    void _removeWorkspaceObject(WorkspaceObject* workspaceObject);

    void _updateWorkspaceObject(AudioPlayer* audioPlayer);

    void _clearWorkspaceObjects();

public:
    WorkspaceService();

    void Listener(Message* message) override;

};


#endif //RHYTHMIC_PROGRAMMING_GAME_WORKSPACESERVICE_H
