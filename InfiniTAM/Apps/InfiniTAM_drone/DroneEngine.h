//
// Created by parallels on 7/17/24.
//

#ifndef DRONEENGINE_H
#define DRONEENGINE_H
#include <cstddef>
#include <mavsdk.h>


namespace ITMLib
{
    class ITMMainEngine;
}

class DroneEngine
{

private:
    static DroneEngine* instance;
    ITMLib::ITMMainEngine *mainEngine = nullptr;
    bool running = true;
    mavsdk::Mavsdk mavsdk;
    std::shared_ptr<mavsdk::System> system;

    std::string connection_url = "udpin://0.0.0.0:14550";

public:
    DroneEngine();
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
