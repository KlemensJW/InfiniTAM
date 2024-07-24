//
// Created by parallels on 7/17/24.
//

#ifndef DRONEENGINE_H
#define DRONEENGINE_H
#include <cstddef>


namespace ITMLib
{
    class ITMMainEngine;
}

class DroneEngine
{
    static DroneEngine* instance;
    ITMLib::ITMMainEngine *mainEngine = nullptr;
    bool running = true;

public:
    static DroneEngine* Instance() {
        if (instance == nullptr) instance = new DroneEngine();
        return instance;
    }

    void Initialise(ITMLib::ITMMainEngine* mainEngine);

    void Shutdown();

    void Run();

    void Stop();
};

#endif //DRONEENGINE_H
