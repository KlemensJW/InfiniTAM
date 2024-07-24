//
// Created by parallels on 7/17/24.
//

#include "DroneEngine.h"

#include "../../ITMLib/Core/ITMMainEngine.h"
#include <iostream>
#include <thread>

DroneEngine* DroneEngine::instance;

void DroneEngine::Initialise(ITMLib::ITMMainEngine* mainEngine)
{
    this->mainEngine = mainEngine;
    this->running = true;
}

void DroneEngine::Run()
{
    while(running)
    {
        // What needs to happen in here?
        // - if we have a next Waypoint --> navigate the drone to this waypoint
        //

        // Drone Commands
        // - takeoff
        // - land
        // - go forward
        // - rotate x degrees
        // - stop movement (we want the drone to stop when it reached its waypoint
        // - up/down


        Vector3f translation;
        Vector3f rotation;
        this->mainEngine->GetTrackingState()->pose_d->GetParams(translation, rotation);
        std::cout << "translation: " << translation << " , rotation: " << rotation << std::endl;
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
    }
}

void DroneEngine::Stop()
{
    this->running = false;
}

void DroneEngine::Shutdown()
{
    instance = nullptr;
}

