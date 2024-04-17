#include <iostream>
#include <sstream>

enum switches {

    LIGHTS_INSIDE = 1,
    LIGHTS_OUTSIDE = 2,
    HEATERS = 4,
    WATER_PIPE_HEATING = 8,
    CONDITIONER = 16
};

int state = 0;

bool isMovement(const std::string& move) {

    if (move == "yes") {
        return true;
    }
    else {
        return false;
    }
}

bool lightsOn(const std::string& lights) {

    if (lights == "on") {
        return true;
    }
    else {
        return false;
    }
}

bool checkStr(const std::string& str) {

    if ((str == "yes") || (str == "no") || (str == "on") || (str == "off")) {
        return true;
    }
    else {
        return false;
    }
}

void lightsOutside(int time, bool movement) {

    int startTime = 16, endTime = 5;

    if (movement && (time >= startTime || time < endTime)
        && ((state & LIGHTS_OUTSIDE) != LIGHTS_OUTSIDE)) {
        state |= LIGHTS_OUTSIDE;
        std::cout << "Lights outside ON!" << std::endl;
    }
    if ((!movement) && ((state & LIGHTS_OUTSIDE) == LIGHTS_OUTSIDE)) {
        state &= ~LIGHTS_OUTSIDE;
        std::cout << "Lights outside OFF!" << std::endl;
    }
}

void lightsInside(bool lights) {

    if ((lights) && ((state & LIGHTS_INSIDE) != LIGHTS_INSIDE)) {
        state |= LIGHTS_INSIDE;
        std::cout << "Lights inside ON!" << std::endl;
    }
    if ((!lights) && ((state & LIGHTS_INSIDE) == LIGHTS_INSIDE)) {
        state &= ~LIGHTS_INSIDE;
        std::cout << "Lights inside OFF!" << std::endl;
    }
}

int temperatureLight(int time) {

    int startTime = 16;
    int endTime = 20;
    int max = 5000, min = 2700, temp = 0;

    if (time >= startTime && time < endTime) {
        temp = max - ((max - min) / (endTime - startTime) * (time - startTime));
    }
    if (time >= endTime) {
        temp = min;
    }
    if (time >= 0 && time < startTime) {
        temp = max;
    }
    return temp;
}

void heatingWaterSupply(int temperature) {

    int max = 5, min = 0;

    if ((temperature <= min) && ((state & WATER_PIPE_HEATING) != WATER_PIPE_HEATING)) {
        state |= WATER_PIPE_HEATING;
        std::cout << "Water pipe heating ON!" << std::endl;
    }
    if ((temperature >= max) && ((state & WATER_PIPE_HEATING) == WATER_PIPE_HEATING)) {
        state &= ~WATER_PIPE_HEATING;
        std::cout << "Water pipe heating OFF!" << std::endl;
    }
}

void heatingInside(int temperature) {

    int max = 25, min = 22;

    if ((temperature < min) && ((state & HEATERS) != HEATERS)) {
        state |= HEATERS;
        std::cout << "Heaters ON!" << std::endl;
    }
    if ((temperature >= max) && ((state & HEATERS) == HEATERS)) {
        state &= ~HEATERS;
        std::cout << "Heaters OFF!" << std::endl;
    }
}

void airCondition(int temperature) {

    int max = 30, min = 25;

    if ((temperature >= max) && ((state & CONDITIONER) != CONDITIONER)) {
        state |= CONDITIONER;
        std::cout << "Conditioner ON!" << std::endl;
    }
    if ((temperature <= min) && ((state & CONDITIONER) == CONDITIONER)) {
        state &= ~CONDITIONER;
        std::cout << "Conditioner OFF!" << std::endl;
    }
}

int main() {

    std::string options;
    std::string temperatureOut;
    std::string temperatureIn;
    std::string movement;
    std::string lights;

    int time = 0;
    int day = 0;

    while (day != 2) {

        if (time == 24) {
            ++day;
            time = 0;
        }

        std::cout << "Temperature inside, temperature outside, movement, lights:" << std::endl;
        std::getline(std::cin, options);
        std::stringstream options_stream(options);
        options_stream >> temperatureIn >> temperatureOut >> movement >> lights;

        if (checkStr(movement) && checkStr(lights)) {

            heatingWaterSupply(std::stoi(temperatureOut));
            heatingInside(std::stoi(temperatureIn));
            airCondition(std::stoi(temperatureIn));
            lightsOutside(time, isMovement(movement));
            lightsInside(lightsOn(lights));

            if (lightsOn(lights)) {
                std::cout << "The lighting temperature: " <<
                    temperatureLight(time) << "K" << std::endl;
            }

            ++time;
        }
        else {
            std::cout << "Invalid data entered, try again!" << std::endl;
            continue;
        }
    }
}

