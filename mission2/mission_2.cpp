#ifdef _DEBUG
#include "gmock/gmock.h"

int main()
{
    testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <cstdlib>

#define CLEAR_SCREEN "\033[H\033[2J"

using namespace std;

class Component {
public:
    virtual string name() const = 0;
    virtual ~Component() = default;
};

class Engine : public Component {
    string type;
public:
    Engine(string t) : type(t) {}
    string name() const override { return type; }
};

class Brake : public Component {
    string type;
public:
    Brake(string t) : type(t) {}
    string name() const override { return type; }
};

class Steering : public Component {
    string type;
public:
    Steering(string t) : type(t) {}
    string name() const override { return type; }
};

class CarType : public Component {
    string type;
public:
    CarType(string t) : type(t) {}
    string name() const override { return type; }
};

void clearScreen() {
    printf(CLEAR_SCREEN);
}

void delay(int ms)
{
    volatile int sum = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            for (int t = 0; t < ms; t++)
            {
                sum++;
            }
        }
    }
}

class Car {
public:
    shared_ptr<CarType> carType;
    shared_ptr<Engine> engine;
    shared_ptr<Brake> brake;
    shared_ptr<Steering> steering;

    bool isValid(string& reason) const {
        string t = carType->name(), e = engine->name();
        string b = brake->name(), s = steering->name();

        if (b == "BOSCH" && s != "BOSCH") { reason = "BOSCH 제동장치에는 BOSCH 조향장치만 사용 가능."; return false; }
        if (t == "Sedan" && b == "CONTINENTAL") { reason = "Sedan에는 Continental 제동장치 사용 불가."; return false; }
        if (t == "SUV" && e == "TOYOTA") { reason = "SUV에는 TOYOTA 엔진 사용 불가."; return false; }
        if (t == "Truck" && e == "WIA") { reason = "Truck에는 WIA 엔진 사용 불가."; return false; }
        if (t == "Truck" && b == "MANDO") { reason = "Truck에는 MANDO 제동장치 사용 불가."; return false; }
        return true;
    }

    bool canRun(string& reason) const {
        if (engine->name() == "고장난 엔진") {
            reason = "엔진이 고장났습니다."; return false;
        }
        return isValid(reason);
    }
};

map<string, vector<string>> componentOptions = {
    {"CarType", {"Sedan", "SUV", "Truck"}},
    {"Engine", {"GM", "TOYOTA", "WIA", "고장난 엔진"}},
    {"Brake", {"MANDO", "CONTINENTAL", "BOSCH"}},
    {"Steering", {"BOSCH", "MOBIS"}}
};

shared_ptr<Component> createComponent(const string& category, int index) {
    string name = componentOptions[category][index];
    if (category == "CarType") return make_shared<CarType>(name);
    if (category == "Engine") return make_shared<Engine>(name);
    if (category == "Brake") return make_shared<Brake>(name);
    if (category == "Steering") return make_shared<Steering>(name);
    return nullptr;
}

int getUserInputWithBack(const string& label, const vector<string>& options, bool allowBack) {
    while (true) {
        clearScreen();
        cout << "\n" << label << endl;
        if (allowBack) cout << "0. 이전으로 돌아가기" << endl;
        for (int i = 0; i < options.size(); ++i)
            cout << i + 1 << ". " << options[i] << endl;
        cout << "> ";

        string input;
        getline(cin, input);
        if (input == "exit") exit(0);
        try {
            int sel = stoi(input);
            if (allowBack && sel == 0) return -1;
            if (sel >= 1 && sel <= options.size()) return sel - 1;
        }
        catch (...) {}
        cout << "잘못된 입력입니다. 다시 선택하세요.\n";
        delay(2000);
    }
}

void printSelection(const string& category, const string& value) {
    cout << category << "(으)로 " << value << "을 선택하셨습니다.\n";
    delay(2000);
}

void printResult(const Car& car, bool runMode) {
    string reason;
    bool success = runMode ? car.canRun(reason) : car.isValid(reason);
    clearScreen();
    if (success) cout << "PASS - 자동차가 정상 동작합니다.\n";
    else cout << "FAIL - " << reason << "\n";
}

#else

int main() {
    while (true) {
        auto car = make_shared<Car>();
        clearScreen();
        int sel = getUserInputWithBack("차량 타입을 선택하세요:", componentOptions["CarType"], false);
        car->carType = dynamic_pointer_cast<CarType>(createComponent("CarType", sel));
        printSelection("차량 타입", car->carType->name());

        while (true) {
            sel = getUserInputWithBack("엔진을 선택하세요:", componentOptions["Engine"], true);
            if (sel == -1) break;
            car->engine = dynamic_pointer_cast<Engine>(createComponent("Engine", sel));
            printSelection("엔진", car->engine->name());

            while (true) {
                sel = getUserInputWithBack("제동장치를 선택하세요:", componentOptions["Brake"], true);
                if (sel == -1) break;
                car->brake = dynamic_pointer_cast<Brake>(createComponent("Brake", sel));
                printSelection("제동장치", car->brake->name());

                sel = getUserInputWithBack("조향장치를 선택하세요:", componentOptions["Steering"], true);
                if (sel == -1) continue;
                car->steering = dynamic_pointer_cast<Steering>(createComponent("Steering", sel));
                printSelection("조향장치", car->steering->name());

                clearScreen();

                while (true) {
                    cout << "\n1. 자동차 실행\n2. 조합 테스트\n0. 처음으로 돌아가기\n> ";
                    string input; getline(cin, input);
                    if (input == "0") break;
                    if (input == "1") printResult(*car, true);
                    else if (input == "2") printResult(*car, false);
                }
                break;
            }
        }
    }
    return 0;
}

#endif
