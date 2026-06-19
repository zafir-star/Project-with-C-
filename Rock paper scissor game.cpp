#include <iostream>
#include <cstdlib>
#include <ctime>

// Function to convert the choice number to a string name
std::string getChoiceName(int choice) {
    if (choice == 1) return "Rock";
    if (choice == 2) return "Paper";
    if (choice == 3) return "Scissors";
    return "Unknown";
}

int main() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(0)));

    int userChoice = 0;
    int computerChoice = 0;
    char playAgain = 'y';

    std::cout << "=================================\n";
    std::cout << " Welcome to Rock, Paper, Scissors!\n";
    std::cout << "=================================\n";

    while (playAgain == 'y' || playAgain == 'Y') {
        // Get user input
        std::cout << "\nChoose your weapon:\n";
        std::cout << "1. Rock\n";
        std::cout << "2. Paper\n";
        std::cout << "3. Scissors\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> userChoice;

        // Validate input
        while (userChoice < 1 || userChoice > 3) {
            std::cout << "Invalid choice. Please enter 1, 2, or 3: ";
            std::cin >> userChoice;
        }

        // Generate computer choice (1 to 3)
        computerChoice = (std::rand() % 3) + 1;

        // Reveal choices
        std::cout << "\nYou chose: " << getChoiceName(userChoice) << "\n";
        std::cout << "Computer chose: " << getChoiceName(computerChoice) << "\n\n";

        // Determine the winner
        if (userChoice == computerChoice) {
            std::cout << "It's a tie!\n";
        } 
        else if ((userChoice == 1 && computerChoice == 3) || // Rock beats Scissors
                 (userChoice == 2 && computerChoice == 1) || // Paper beats Rock
                 (userChoice == 3 && computerChoice == 2)) { // Scissors beats Paper
            std::cout << "You win! 🎉\n";
        } 
        else {
            std::cout << "Computer wins! 🤖\n";
        }

        // Ask to play again
        std::cout << "\nDo you want to play again? (y/n): ";
        std::cin >> playAgain;
    }

    std::cout << "\nThanks for playing! Goodbye.\n";
    return 0;
}