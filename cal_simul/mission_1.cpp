#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CLEAR_SCREEN "\033[H\033[2J"

enum CarType { SEDAN = 1, SUV, TRUCK };
enum Engine { GM = 1, TOYOTA, WIA, BROKEN };
enum Brake { MANDO = 1, CONTINENTAL, BOSCH_B };
enum Steering { BOSCH_S = 1, MOBIS };

int carType = 0;
int engine = 0;
int brake = 0;
int steering = 0;

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

void clearScreen() {
    printf(CLEAR_SCREEN);
}

int getUserInput(int min, int max) {
    char buf[100];
    char* context;
    fgets(buf, sizeof(buf), stdin);
    strtok_s(buf, "\n", &context);

    if (strcmp(buf, "exit") == 0) {
        exit(0);
    }

    char* end;
    int val = strtol(buf, &end, 10);
    if (*end != '\0' || val < min || val > max) {
        printf("유효한 숫자를 입력하세요 (%d ~ %d)\n", min, max);
        delay(500);
        return -1;
    }
    return val;
}

void selectCarType() {
    while (1) {
        clearScreen();
        printf("차량 타입을 선택하세요:\n1. Sedan\n2. SUV\n3. Truck\n> ");
        int input = getUserInput(1, 3);
        if (input != -1) {
            carType = input;
            const char* names[] = { "", "Sedan", "SUV", "Truck" };
            printf("차량 타입으로 %s을 선택하셨습니다.\n", names[carType]);
            delay(800);
            return;
        }
    }
}

int selectEngine() {
    while (1) {
        clearScreen();
        printf("엔진을 선택하세요:\n0. 이전으로 돌아가기\n1. GM\n2. TOYOTA\n3. WIA\n4. 고장난 엔진\n> ");
        int input = getUserInput(0, 4);
        if (input == 0) return 0;
        if (input != -1) {
            engine = input;
            const char* names[] = { "", "GM", "TOYOTA", "WIA", "고장난 엔진" };
            printf("엔진으로 %s을 선택하셨습니다.\n", names[engine]);
            delay(800);
            return 1;
        }
    }
}

int selectBrake() {
    while (1) {
        clearScreen();
        printf("제동장치를 선택하세요:\n0. 이전으로 돌아가기\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n> ");
        int input = getUserInput(0, 3);
        if (input == 0) return 0;
        if (input != -1) {
            brake = input;
            const char* names[] = { "", "MANDO", "CONTINENTAL", "BOSCH" };
            printf("제동장치로 %s을 선택하셨습니다.\n", names[brake]);
            delay(800);
            return 1;
        }
    }
}

int selectSteering() {
    while (1) {
        clearScreen();
        printf("조향장치를 선택하세요:\n0. 이전으로 돌아가기\n1. BOSCH\n2. MOBIS\n> ");
        int input = getUserInput(0, 2);
        if (input == 0) return 0;
        if (input != -1) {
            steering = input;
            const char* names[] = { "", "BOSCH", "MOBIS" };
            printf("조향장치로 %s을 선택하셨습니다.\n", names[steering]);
            delay(800);
            return 1;
        }
    }
}

int isValidCombination() {
    if ((brake == BOSCH_B && steering != BOSCH_S) ||
        (brake != BOSCH_B && steering == BOSCH_S)) return 0;
    if (carType == SEDAN && brake == CONTINENTAL) return 0;
    if (carType == SUV && engine == TOYOTA) return 0;
    if (carType == TRUCK && engine == WIA) return 0;
    if (carType == TRUCK && brake == MANDO) return 0;
    return 1;
}

void testCar() {
    clearScreen();
    printf("테스트 결과:\n");
    int valid = 1;
    if (carType == SEDAN && brake == CONTINENTAL) {
        printf("FAIL - Sedan에는 Continental 제동장치를 사용할 수 없습니다.\n"); valid = 0;
    }
    if (carType == SUV && engine == TOYOTA) {
        printf("FAIL - SUV에는 TOYOTA 엔진을 사용할 수 없습니다.\n"); valid = 0;
    }
    if (carType == TRUCK && engine == WIA) {
        printf("FAIL - Truck에는 WIA 엔진을 사용할 수 없습니다.\n"); valid = 0;
    }
    if (carType == TRUCK && brake == MANDO) {
        printf("FAIL - Truck에는 MANDO 제동장치를 사용할 수 없습니다.\n"); valid = 0;
    }
    if (brake == BOSCH_B && steering != BOSCH_S) {
        printf("FAIL - BOSCH 제동장치를 사용할 경우 조향장치도 BOSCH여야 합니다.\n"); valid = 0;
    }
    if (brake != BOSCH_B && steering == BOSCH_S) {
        printf("FAIL - BOSCH 조향장치를 사용할 경우 제동장치도 BOSCH여야 합니다.\n"); valid = 0;
    }
    if (valid) {
        printf("PASS - 부품 조합이 유효합니다.\n");
    }
    delay(2000);
}

void runCar() {
    clearScreen();
    if (!isValidCombination() || engine == BROKEN) {
        if (engine == BROKEN) {
            printf("자동차가 동작하지 않습니다 - 엔진이 고장났습니다.\n");
        }
        else {
            printf("자동차가 동작하지 않습니다 - 부품 조합이 유효하지 않습니다.\n");
        }
    }
    else {
        printf("자동차가 정상 동작합니다.\n");
    }
    delay(2000);
}

int main() {
    while (1) {
        selectCarType();
        if (selectEngine() == 0) continue;
        if (selectBrake() == 0) { selectEngine(); continue; }
        if (selectSteering() == 0) { selectBrake(); continue; }

        while (1) {
            clearScreen();
            printf("1. 자동차 실행\n2. 조합 테스트\n0. 처음으로 돌아가기\n> ");
            int choice = getUserInput(0, 2);
            if (choice == 1) runCar();
            else if (choice == 2) testCar();
            else if (choice == 0) break;
        }
    }
    return 0;
}