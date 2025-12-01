#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus,
                   int planet, int totalPlanets)
{
    if (fuel <= 0) {
        printf("Planet %d: Fuel Remaining = 0\n", planet);
        printf("\nMission Failed: Fuel exhausted!\n");
        return;
    }
    if (planet > totalPlanets) {
        printf("\nMission Successful: Spacecraft completed the journey!\n");
        return;
    }

    fuel -= consumption;

    fuel += recharge;

    if (planet % 4 == 0)
        fuel += solarBonus;

    if (fuel < 0) fuel = 0;

    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);

    calculateFuel(fuel, consumption, recharge, solarBonus,
                  planet + 1, totalPlanets);
}

int main()
{
    int initialFuel = 200;
    int consumption = 30;
    int recharge = 10;
    int solarBonus = 40;
    int totalPlanets = 8;

    calculateFuel(initialFuel, consumption, recharge,
                  solarBonus, 1, totalPlanets);

    return 0;
}

