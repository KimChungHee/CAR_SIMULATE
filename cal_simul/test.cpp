#include "gtest/gtest.h"
#include "car_simul.hpp"

TEST(CarValidationTest, ValidCombinationPasses) {
    Car car;
    car.carType = std::make_shared<CarType>("SUV");
    car.engine = std::make_shared<Engine>("GM");
    car.brake = std::make_shared<Brake>("MANDO");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_TRUE(car.isValid(reason));
    EXPECT_TRUE(car.canRun(reason));
}

TEST(CarValidationTest, BoschBrakeWithoutBoschSteeringFails) {
    Car car;
    car.carType = std::make_shared<CarType>("SUV");
    car.engine = std::make_shared<Engine>("GM");
    car.brake = std::make_shared<Brake>("BOSCH");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "BOSCH 제동장치에는 BOSCH 조향장치만 사용 가능.");
}

TEST(CarValidationTest, SedanFailsWithContinentalBrake) {
    Car car;
    car.carType = std::make_shared<CarType>("Sedan");
    car.engine = std::make_shared<Engine>("GM");
    car.brake = std::make_shared<Brake>("CONTINENTAL");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "Sedan에는 Continental 제동장치 사용 불가.");
}

TEST(CarValidationTest, SuvFailsWithToyotaEngine) {
    Car car;
    car.carType = std::make_shared<CarType>("SUV");
    car.engine = std::make_shared<Engine>("TOYOTA");
    car.brake = std::make_shared<Brake>("MANDO");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "SUV에는 TOYOTA 엔진 사용 불가.");
}

TEST(CarValidationTest, TruckFailsWithWiaEngine) {
    Car car;
    car.carType = std::make_shared<CarType>("Truck");
    car.engine = std::make_shared<Engine>("WIA");
    car.brake = std::make_shared<Brake>("BOSCH");
    car.steering = std::make_shared<Steering>("BOSCH");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "Truck에는 WIA 엔진 사용 불가.");
}

TEST(CarValidationTest, TruckFailsWithMandoBrake) {
    Car car;
    car.carType = std::make_shared<CarType>("Truck");
    car.engine = std::make_shared<Engine>("GM");
    car.brake = std::make_shared<Brake>("MANDO");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "Truck에는 MANDO 제동장치 사용 불가.");
}

TEST(CarRunTest, BrokenEngineFailsToRun) {
    Car car;
    car.carType = std::make_shared<CarType>("Truck");
    car.engine = std::make_shared<Engine>("고장난 엔진");
    car.brake = std::make_shared<Brake>("BOSCH");
    car.steering = std::make_shared<Steering>("BOSCH");

    std::string reason;
    EXPECT_FALSE(car.canRun(reason));
    EXPECT_EQ(reason, "엔진이 고장났습니다.");
}