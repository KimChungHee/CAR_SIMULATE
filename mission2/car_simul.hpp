#include <string>
#include <vector>
#include <map>
#include <memory>

class Component {
public:
    virtual std::string name() const = 0;
    virtual ~Component() = default;
};

class CarType : public Component {
    std::string type;
public:
    CarType(std::string t) : type(t) {}
    std::string name() const override { return type; }
};

class Engine : public Component {
    std::string type;
public:
    Engine(std::string t) : type(t) {}
    std::string name() const override { return type; }
};

class Brake : public Component {
    std::string type;
public:
    Brake(std::string t) : type(t) {}
    std::string name() const override { return type; }
};

class Steering : public Component {
    std::string type;
public:
    Steering(std::string t) : type(t) {}
    std::string name() const override { return type; }
};

class Car {
public:
    std::shared_ptr<CarType> carType;
    std::shared_ptr<Engine> engine;
    std::shared_ptr<Brake> brake;
    std::shared_ptr<Steering> steering;

    bool isValid(std::string& reason) const;
    bool canRun(std::string& reason) const;
};

extern std::map<std::string, std::vector<std::string>> componentOptions;
std::shared_ptr<Component> createComponent(const std::string& category, int index);