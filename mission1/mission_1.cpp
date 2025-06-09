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
        printf("��ȿ�� ���ڸ� �Է��ϼ��� (%d ~ %d)\n", min, max);
        delay(500);
        return -1;
    }
    return val;
}

void selectCarType() {
    while (1) {
        clearScreen();
        printf("���� Ÿ���� �����ϼ���:\n1. Sedan\n2. SUV\n3. Truck\n> ");
        int input = getUserInput(1, 3);
        if (input != -1) {
            carType = input;
            const char* names[] = { "", "Sedan", "SUV", "Truck" };
            printf("���� Ÿ������ %s�� �����ϼ̽��ϴ�.\n", names[carType]);
            delay(800);
            return;
        }
    }
}

int selectEngine() {
    while (1) {
        clearScreen();
        printf("������ �����ϼ���:\n0. �������� ���ư���\n1. GM\n2. TOYOTA\n3. WIA\n4. ���峭 ����\n> ");
        int input = getUserInput(0, 4);
        if (input == 0) return 0;
        if (input != -1) {
            engine = input;
            const char* names[] = { "", "GM", "TOYOTA", "WIA", "���峭 ����" };
            printf("�������� %s�� �����ϼ̽��ϴ�.\n", names[engine]);
            delay(800);
            return 1;
        }
    }
}

int selectBrake() {
    while (1) {
        clearScreen();
        printf("������ġ�� �����ϼ���:\n0. �������� ���ư���\n1. MANDO\n2. CONTINENTAL\n3. BOSCH\n> ");
        int input = getUserInput(0, 3);
        if (input == 0) return 0;
        if (input != -1) {
            brake = input;
            const char* names[] = { "", "MANDO", "CONTINENTAL", "BOSCH" };
            printf("������ġ�� %s�� �����ϼ̽��ϴ�.\n", names[brake]);
            delay(800);
            return 1;
        }
    }
}

int selectSteering() {
    while (1) {
        clearScreen();
        printf("������ġ�� �����ϼ���:\n0. �������� ���ư���\n1. BOSCH\n2. MOBIS\n> ");
        int input = getUserInput(0, 2);
        if (input == 0) return 0;
        if (input != -1) {
            steering = input;
            const char* names[] = { "", "BOSCH", "MOBIS" };
            printf("������ġ�� %s�� �����ϼ̽��ϴ�.\n", names[steering]);
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
    printf("�׽�Ʈ ���:\n");
    int valid = 1;
    if (carType == SEDAN && brake == CONTINENTAL) {
        printf("FAIL - Sedan���� Continental ������ġ�� ����� �� �����ϴ�.\n"); valid = 0;
    }
    if (carType == SUV && engine == TOYOTA) {
        printf("FAIL - SUV���� TOYOTA ������ ����� �� �����ϴ�.\n"); valid = 0;
    }
    if (carType == TRUCK && engine == WIA) {
        printf("FAIL - Truck���� WIA ������ ����� �� �����ϴ�.\n"); valid = 0;
    }
    if (carType == TRUCK && brake == MANDO) {
        printf("FAIL - Truck���� MANDO ������ġ�� ����� �� �����ϴ�.\n"); valid = 0;
    }
    if (brake == BOSCH_B && steering != BOSCH_S) {
        printf("FAIL - BOSCH ������ġ�� ����� ��� ������ġ�� BOSCH���� �մϴ�.\n"); valid = 0;
    }
    if (brake != BOSCH_B && steering == BOSCH_S) {
        printf("FAIL - BOSCH ������ġ�� ����� ��� ������ġ�� BOSCH���� �մϴ�.\n"); valid = 0;
    }
    if (valid) {
        printf("PASS - ��ǰ ������ ��ȿ�մϴ�.\n");
    }
    delay(2000);
}

void runCar() {
    clearScreen();
    if (!isValidCombination() || engine == BROKEN) {
        if (engine == BROKEN) {
            printf("�ڵ����� �������� �ʽ��ϴ� - ������ ���峵���ϴ�.\n");
        }
        else {
            printf("�ڵ����� �������� �ʽ��ϴ� - ��ǰ ������ ��ȿ���� �ʽ��ϴ�.\n");
        }
    }
    else {
        printf("�ڵ����� ���� �����մϴ�.\n");
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
            printf("1. �ڵ��� ����\n2. ���� �׽�Ʈ\n0. ó������ ���ư���\n> ");
            int choice = getUserInput(0, 2);
            if (choice == 1) runCar();
            else if (choice == 2) testCar();
            else if (choice == 0) break;
        }
    }
    return 0;
}