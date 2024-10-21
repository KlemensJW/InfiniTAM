#include "DroneEngine.h"
#include <iostream>
#include <memory>
#include <thread>
#include <curl/curl.h>

std::string DroneEngine::baseURL = "128.130.234.148:8080";

// Callback function to handle the data received from the server
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

bool performPostRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::cout << "Post URL: " << url << std::endl;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            curl_easy_cleanup(curl);
            std::cout << "ERROR: " << url << std::endl;
            return false;
        }
        curl_easy_cleanup(curl);
        std::cout << "Success: " << url << std::endl;
        return true;
    }
    std::cout << "Error2: " << url << std::endl;
    return false;
}

std::string performGetRequest(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

bool DroneEngine::startVelocityControl() {
    return performPostRequest(baseURL + "/startVelocityControl");
}

bool DroneEngine::setVelocityCommand(double xVel, double yVel, double zVel, double yawRate) {
    std::string url = baseURL + "/setVelocityCommand/" + std::to_string(xVel) + "/" + std::to_string(yVel) + "/" + std::to_string(zVel) + "/" + std::to_string(yawRate);
    return performPostRequest(url);
}

std::string DroneEngine::getCurrentVelocityCommand() {
    return performGetRequest(baseURL + "/getCurrentVelocityCommand");
}

bool DroneEngine::stopVelocityControl() {
    return performPostRequest(baseURL + "/stopVelocityControl");
}

// Connection Commands
std::string DroneEngine::connectionTest() {
    return performGetRequest(baseURL + "/");
}

// Takeoff and Landing Commands
std::string DroneEngine::takeoff() {
    return performGetRequest(baseURL + "/takeoff");
}

std::string DroneEngine::land() {
    return performGetRequest(baseURL + "/land");
}

bool DroneEngine::confirmLanding() {
    return performPostRequest(baseURL + "/confirmLanding");
}

bool DroneEngine::isLandingProtectionEnabled() {
    return performGetRequest(baseURL + "/isLandingProtectionEnabled") == "true";
}

bool DroneEngine::enableLandingProtection() {
    return performPostRequest(baseURL + "/enableLandingProtection");
}

bool DroneEngine::disableLandingProtection() {
    return performPostRequest(baseURL + "/disableLandingProtection");
}

// Control Mode Commands
std::string DroneEngine::getControlMode() {
    return performGetRequest(baseURL + "/getControlMode");
}

bool DroneEngine::setControlMode(const std::string& mode) {
    std::string url = baseURL + "/setControlMode/" + mode;
    return performPostRequest(url);
}

// Motion Planning Commands
double DroneEngine::getMaxSpeed() {
    return std::stod(performGetRequest(baseURL + "/getMaxSpeed"));
}

bool DroneEngine::setMaxSpeed(double speed) {
    std::string url = baseURL + "/setMaxSpeed/" + std::to_string(speed);
    return performPostRequest(url);
}

double DroneEngine::getMaxAngularSpeed() {
    return std::stod(performGetRequest(baseURL + "/getMaxAngularSpeed"));
}

bool DroneEngine::setMaxAngularSpeed(double speed) {
    std::string url = baseURL + "/setMaxAngularSpeed/" + std::to_string(speed);
    return performPostRequest(url);
}

std::string DroneEngine::getVelocityProfile() {
    return performGetRequest(baseURL + "/getVelocityProfile");
}

bool DroneEngine::setVelocityProfile(const std::string& profile) {
    std::string url = baseURL + "/setVelocityProfile/" + profile;
    return performPostRequest(url);
}

void DroneEngine::SetBaseURL(const std::string& newBaseURL) {
    baseURL = newBaseURL;
}

DroneEngine* DroneEngine::instance;

void DroneEngine::Initialise(ITMLib::ITMMainEngine* mainEngine) {
    this->mainEngine = mainEngine;
    this->running = true;
}

void DroneEngine::Run() {

    std::cout << connectionTest() << std::endl;

    std::cout << takeoff() << std::endl;

    /*
    if(startVelocityControl()) {
        std::cout << "Started velocity control" << std::endl;
    }

    if(setVelocityCommand(1.0, 0.0, 0.0, 0.5)) {
        std::cout << "Set velocity command" << std::endl;
    }

    std::string currentVelocity = getCurrentVelocityCommand();
    std::cout << "Current velocity command: " << currentVelocity << std::endl;

    if(stopVelocityControl()) {
        std::cout << "Stopped velocity control" << std::endl;
    }
        */
    while(running) {
        Vector3f translation;
        Vector3f rotation;
        this->mainEngine->GetTrackingState()->pose_d->GetParams(translation, rotation);
        std::cout << "translation: " << translation << " , rotation: " << rotation << std::endl;
        std::this_thread::sleep_for(std::chrono::duration<int>(1));
    }

    std::cout << land() << std::endl;
}

void DroneEngine::Stop() {
    this->running = false;
}

void DroneEngine::Shutdown() {
    instance = nullptr;
}