//
// Created by parallels on 7/17/24.
//

#ifndef DRONEENGINE_H
#define DRONEENGINE_H
#include <string>
#include <vector>

#include "../../ITMLib/Core/ITMMainEngine.h"

constexpr double pi = 3.14159265358979323846;

struct View
{
    Vector3f position; // position is roughly in meters (origin is the position where capturing in Infinitam was started)
    Vector3f rotation; // rotation is in [-pi, pi], only the y rotation is relevant

    bool isCloseTo(const View& other)
    {
        Vector3f positionDifference = (this->position - other.position);
        for (int i = 0; i < positionDifference.size(); ++i)
        {
            if (abs(positionDifference[i]) > 0.05f) return false; // position needs to be within 5cm
        }

        Vector3f rotationDifference = (this->rotation - other.rotation);
        for (int i = 0; i < rotationDifference.size(); ++i)
        {
            if(abs(rotationDifference[i]) > pi/180*5) return false; // view has to be aligned within 5 degrees
        }

    }
};

class DroneEngine
{
    static DroneEngine* instance;
    static std::string baseURL;
    ITMLib::ITMMainEngine *mainEngine = nullptr;
    bool running = true;
    std::vector<View> viewsToVisit = {
        {{1.0f, -1.0f, 1.5f}, {0.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, 1.5f}, {0.0f, -1.0f, 0.0f}},
        {{-1.0f, 1.0f, 1.5f}, {0.0f, 2.0f, 0.0f}},
        {{-1.0f, -1.0f, 1.5f}, {0.0f, -2.0f, 0.0f}}
    };

    View nextView();
    void reachView(View aViewToReach);

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
