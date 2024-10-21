//
// Created by parallels on 7/17/24.
//

#ifndef DRONEENGINE_H
#define DRONEENGINE_H
#include <string>
#include "../../ITMLib/Core/ITMMainEngine.h"



class DroneEngine
{
    static DroneEngine* instance;
    static std::string baseURL;
    ITMLib::ITMMainEngine *mainEngine = nullptr;
    bool running = true;

    //Velocity Control Commands
    static bool startVelocityControl();
    static bool setVelocityCommand(double xVel, double yVel, double zVel, double yawRate);
    static std::string getCurrentVelocityCommand();
    static bool stopVelocityControl();

    // Connection Commands
    static std::string connectionTest();

    // Takeoff and Landing Commands
    static std::string takeoff();
    static std::string land();
    static bool confirmLanding();
    static bool isLandingProtectionEnabled();
    static bool enableLandingProtection();
    static bool disableLandingProtection();

    // Control Mode Commands
    static std::string getControlMode();
    static bool setControlMode(const std::string& mode);

    // Motion Planning Commands
    static double getMaxSpeed();
    static bool setMaxSpeed(double speed);
    static double getMaxAngularSpeed();
    static bool setMaxAngularSpeed(double speed);
    static std::string getVelocityProfile();
    static bool setVelocityProfile(const std::string& profile);

public:
    static DroneEngine* Instance() {
        if (instance == nullptr) instance = new DroneEngine();
        return instance;
    }


    void Initialise(ITMLib::ITMMainEngine* mainEngine);

    void Shutdown();

    void Run();

    void Stop();

    static void SetBaseURL(const std::string& baseURL);
};

#endif //DRONEENGINE_H
