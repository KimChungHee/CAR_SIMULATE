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
    EXPECT_EQ(reason, "BOSCH ������ġ���� BOSCH ������ġ�� ��� ����.");
}

TEST(CarValidationTest, SedanFailsWithContinentalBrake) {
    Car car;
    car.carType = std::make_shared<CarType>("Sedan");
    car.engine = std::make_shared<Engine>("GM");
    car.brake = std::make_shared<Brake>("CONTINENTAL");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "Sedan���� Continental ������ġ ��� �Ұ�.");
}

TEST(CarValidationTest, SuvFailsWithToyotaEngine) {
    Car car;
    car.carType = std::make_shared<CarType>("SUV");
    car.engine = std::make_shared<Engine>("TOYOTA");
    car.brake = std::make_shared<Brake>("MANDO");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "SUV���� TOYOTA ���� ��� �Ұ�.");
}

TEST(CarValidationTest, TruckFailsWithWiaEngine) {
    Car car;
    car.carType = std::make_shared<CarType>("Truck");
    car.engine = std::make_shared<Engine>("WIA");
    car.brake = std::make_shared<Brake>("BOSCH");
    car.steering = std::make_shared<Steering>("BOSCH");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "Truck���� WIA ���� ��� �Ұ�.");
}

TEST(CarValidationTest, TruckFailsWithMandoBrake) {
    Car car;
    car.carType = std::make_shared<CarType>("Truck");
    car.engine = std::make_shared<Engine>("GM");
    car.brake = std::make_shared<Brake>("MANDO");
    car.steering = std::make_shared<Steering>("MOBIS");

    std::string reason;
    EXPECT_FALSE(car.isValid(reason));
    EXPECT_EQ(reason, "Truck���� MANDO ������ġ ��� �Ұ�.");
}

TEST(CarRunTest, BrokenEngineFailsToRun) {
    Car car;
    car.carType = std::make_shared<CarType>("Truck");
    car.engine = std::make_shared<Engine>("���峭 ����");
    car.brake = std::make_shared<Brake>("BOSCH");
    car.steering = std::make_shared<Steering>("BOSCH");

    std::string reason;
    EXPECT_FALSE(car.canRun(reason));
    EXPECT_EQ(reason, "������ ���峵���ϴ�.");
}