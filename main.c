#include <stdio.h>
#include <stdlib.h>

#define board_size 5 // 4 sections and ruma section

// Function to print the state of the game
void gameState(int ruma[]) {
    printf("%d %d %d %d | %d\n", ruma[0], ruma[1], ruma[2], ruma[3], ruma[4]);
}

int isValidSection(int section, int ruma[]) {
    if (ruma[section-1] == 0){
        return 0;
    }
    return section >= 1 && section <= 4;
}

// Function to sow seeds in different sections based on the provided 'section' parameter
void sowSeeds(int ruma[], int section) {
    // Retrieve the number of seeds to sow from the specified section
    int seedsToSow = ruma[section - 1];
    // Reset the seeds count for the specified section to 0
    ruma[section - 1] = 0;

    // Initialize the current section to the provided section minus 1
    int currentSection = section - 1;
    int lastLandedSection = currentSection;  // Keep track of the last section where a seed landed

    // Loop until all seeds are sown
    while (seedsToSow > 0) {
        // Circularly move to the next section (0 to 3) for sowing seeds
        currentSection = (currentSection + 1) % 5;
        
        if (ruma[currentSection] == 0 && currentSection != 4 && seedsToSow == 1) {
            // If the last piece falls into an empty space, the player loses
            ruma[currentSection] += 1;
            gameState(ruma);
            printf("You lost because the last counter fell into section %d.\n", currentSection + 1);
            exit(0);
        }

        // Sow a seed in the current section and decrement the seeds count
        ruma[currentSection] += 1;
        seedsToSow -= 1;

        // Update the last landed section
        lastLandedSection = currentSection;

        // Check if all seeds have been sown
        if (seedsToSow == 0 && currentSection != 4) {
            seedsToSow = ruma[currentSection];
            gameState(ruma);
            ruma[currentSection] = 0;
            printf("Last piece landed in section %d. Continue sowing seeds!\n", lastLandedSection + 1);

        }
    }
    
}

int main() {
    int ruma[board_size] = {2, 2, 2, 2, 0}; // Initial state of the game
    int noError = 1;
    while (1) {
        if(noError){
            gameState(ruma);
            printf("Choose a section (1-4): ");
        }
        

        int section;
        scanf("%d", &section);

        if (isValidSection(section, ruma)) {
            sowSeeds(ruma, section);

            // Check for winning condition
            if (ruma[4] == 8) {
                printf("You won!\n");
                break;
            }

            // Check for losing condition after each move
            if (ruma[2] >= 8) {
                printf("You lost because section 3 has 8 or more seeds.\n");
                break;
            }
            noError=1;
        } else {
            printf("Invalid choice. Choose a section (1-4): ");
            noError = 0;
        }
    }

    return 0;
}
