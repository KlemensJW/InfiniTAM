//
// Created by parallels on 7/17/24.
//

#include "DroneEngine.h"

#include "../../ITMLib/Core/ITMMainEngine.h"
#include <iostream>
#include <memory>
#include <thread>
#include <mavsdk/plugins/action/action.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <mavsdk/plugins/offboard/offboard.h>


DroneEngine* DroneEngine::instance;

DroneEngine::DroneEngine()
    : mavsdk(mavsdk::Mavsdk::Configuration{mavsdk::Mavsdk::ComponentType::GroundStation})
{

}

void DroneEngine::Initialise(ITMLib::ITMMainEngine* mainEngine)
{
    this->mainEngine = mainEngine;
    mavsdk::ConnectionResult connection_result = mavsdk.add_any_connection(connection_url);

    if (connection_result != mavsdk::ConnectionResult::Success)
    {
        std::cerr << "Connection failed: " << connection_result << std::endl;
        return;
    }

    std::cout << "Connection successful" << std::endl;

    this->running = true;

    auto start = std::chrono::steady_clock::now();

    while (true) {
        if (!mavsdk.systems().empty()) {
            for (const auto& sys : mavsdk.systems()) {
                if (sys->has_autopilot()) {
                    system = sys;
                    break;
                }
            }
        }

        if (system) {
            std::cout << "System discovered!" << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - start).count();
        if (duration > 30) { // Timeout after 30 seconds
            std::cerr << "Timed out waiting for system" << std::endl;
            return;
        }
    }

    /*
    auto telemetry = std::make_shared<mavsdk::Telemetry>(system);
    auto action = std::make_shared<mavsdk::Action>(system);
    auto offboard = std::make_shared<mavsdk::Offboard>(system);

    // Wait for the drone to be ready
    while (!telemetry->health_all_ok()) {
        std::cout << "Waiting for the drone to be ready..." << std::endl;
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
    }

    std::cout << "Connected and ready..." << std::endl;
    */
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

void takeoff(std::shared_ptr<mavsdk::Action> action) {
    auto result = action->arm();
    if (result != mavsdk::Action::Result::Success) {
        std::cerr << "Arming failed: " << result << std::endl;
        return;
    }

    result = action->takeoff();
    if (result != mavsdk::Action::Result::Success) {
        std::cerr << "Takeoff failed: " << result << std::endl;
        return;
    }

    // Wait for the drone to reach a stable hover
    //std::this_thread::sleep_for(10s);
}

