#include <stdio.h>
#include <stdlib.h>

// ANSI Color Codes to make the terminal look like a sci-fi console
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define CYAN    "\033[1;36m"
#define WHITE   "\033[1;37m"

// Function to display the current player status
void print_status(int day, int ox, int energy, int food) {
    printf("\n" WHITE "========== DAY %d STATUS ==========" RESET "\n", day);
    printf("Oxygen Level:  " CYAN "%d%%" RESET "\n", ox);
    printf("Base Energy :  " YELLOW "%d%%" RESET "\n", energy);
    printf("Food Supplies: " GREEN "%d units" RESET "\n", food);
    printf(WHITE "====================================" RESET "\n\n");
}

int main() {
    // Game variables tracking player survival stats
    int day = 1;
    int oxygen = 100;
    int energy = 100;
    int food = 30;
    int choice;

    // ASCII Art Rocket Welcome Banner
    printf(CYAN   "      /\\"             RESET "\n");
    printf(CYAN   "     /  \\"            RESET "\n");
    printf(CYAN   "    /____\\"           RESET "\n");
    printf(CYAN   "    |NASA |"           RESET "\n");
    printf(CYAN   "    |     |"           RESET "\n");
    printf(RED    "   /|##!##|\\"          RESET "\n");
    printf(RED    "  //      \\\\"         RESET "\n");
    printf(YELLOW "  *** MISSION TO MARS ***" RESET "\n");
    printf("Welcome, Commander. Can you survive 5 days on Ares Prime?\n");

    // Main game loop runs for 5 days
    while (day <= 5) {
        print_status(day, oxygen, energy, food);

        // Scenario presentation
        printf(WHITE "What is your command for today?" RESET "\n");
        printf("1. Send a rover to search for frozen water (Uses Energy, gains Food)\n");
        printf("2. Stay inside the habitat and repair oxygen scrubbers (Restores O2, uses Food/Energy)\n");
        printf("3. Ration supplies and rest (Restores Energy, saves Food)\n");
        printf("Enter choice (1-3): ");
        
        // Take user input and check if it's a valid integer
        if (scanf("%d", &choice) != 1) {
            printf(RED "Invalid system input! Skipping turn." RESET "\n");
            // Clear input buffer in case of character typos to prevent infinite loops
            while (getchar() != '\n'); 
            choice = 3; // Default fallback choice
        }

        // Process player choices using conditional logic
        if (choice == 1) {
            printf(YELLOW "\n[MISSION LOG] Rover encountered a dust storm! Found resources but drained battery." RESET "\n");
            energy -= 30;
            food += 10;
            oxygen -= 10;
        } 
        else if (choice == 2) {
            printf(GREEN "\n[MISSION LOG] Scrubbers successfully cleared. Air quality improved." RESET "\n");
            oxygen += 20;
            if (oxygen > 100) oxygen = 100; // Cap stat at 100%
            food -= 5;
            energy -= 10;
        } 
        else if (choice == 3) {
            printf(CYAN "\n[MISSION LOG] Crew rested. Power cells recharged slightly." RESET "\n");
            energy += 25;
            if (energy > 100) energy = 100; // Cap stat at 100%
            food -= 2;
            oxygen -= 5;
        } 
        else {
            printf(RED "\n[ALERT] Invalid command entered! Resources wasted wandering around." RESET "\n");
            energy -= 15;
            oxygen -= 15;
        }

        // Check fail conditions (Game Over if any stat hits zero)
        if (oxygen <= 0) {
            printf(RED "\n>>> MISSION FAILURE: The habitat ran out of oxygen on Day %d. <<<" RESET "\n", day);
            return 0; 
        }
        if (energy <= 0) {
            printf(RED "\n>>> MISSION FAILURE: Life support systems lost power on Day %d. <<<" RESET "\n", day);
            return 0;
        }
        if (food <= 0) {
            printf(RED "\n>>> MISSION FAILURE: The crew starved on Day %d. <<<" RESET "\n", day);
            return 0;
        }

        // Progress to the next day
        day++;
    }

    // Victory Condition and Final Score Calculation
    int final_score = oxygen + energy + (food * 2);
    
    printf(GREEN "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" RESET);
    printf(GREEN "\nCONGRATULATIONS COMMANDER! YOU SURVIVED THE WEEK." RESET);
    printf(WHITE "\nThe rescue vehicle has landed. Returning home to Earth." RESET);
    printf(CYAN "\nFinal Survival Score: %d points" RESET, final_score);
    printf(GREEN "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" RESET);

    return 0;
}