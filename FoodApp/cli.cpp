#include "cli.h"

#include <fstream>

#include "cart.h"
#include "fileio.h"
#include <iostream>
#include <string>
#include <limits>

#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define RED "\033[31m"

void runInteractiveMode() {
    Cart cart;
    auto menu = readMenuFile("menu.txt");

    std::string cmd;
    std::cout << CYAN << "Welcome to FoodApp CLI. Type 'menu', 'add', 'order', or 'exit'.\n" << RESET;

    while (true) {
        std::cout << YELLOW << "> " << RESET;
        std::cin >> cmd;

        if (cmd == "exit") break;
        else if (cmd == "menu") {
            std::cout << GREEN << "\n--- MENU ---\n" << RESET;
            for (const auto& item : menu)
                std::cout << item.first << " - $" << item.second << "\n";
        } else if (cmd == "add") {
            std::string item;
            int qty;
            std::string custom;

            std::cout << "Item: ";
            std::cin.ignore();
            std::getline(std::cin, item);

            std::cout << "Qty: ";
            std::cin >> qty;
            std::cin.ignore();

            std::cout << "Custom: ";
            std::getline(std::cin, custom);

            if (menu.count(item)) {
                std::string fullCustom = custom;

                if (item.find("Pizza") != std::string::npos) {
                    std::string customizeChoice;
                    std::cout << "Do you want to customize this pizza? (yes/no): ";
                    std::getline(std::cin, customizeChoice);

                    if (customizeChoice == "yes") {
                        std::string size, toppings, sauces;
                        std::cout << "Choose size (small/medium/large): ";
                        std::getline(std::cin, size);
                        std::cout << "Choose toppings (comma-separated): ";
                        std::getline(std::cin, toppings);
                        std::cout << "Choose sauces (comma-separated): ";
                        std::getline(std::cin, sauces);

                        fullCustom = "Size: " + size + ", Toppings: " + toppings + ", Sauces: " + sauces;
                        if (!custom.empty())
                            fullCustom += ", Note: " + custom;
                    } else if (!custom.empty()) {
                        fullCustom = "Note: " + custom;
                    }
                }

                cart.addItem({item, menu[item], qty, fullCustom});
                std::cout << GREEN << "[OK] Added!\n" << RESET;
            }
            else {
                std::cout << RED << "[ERROR] Not found.\n";
            }
        } else if (cmd == "order") {
            std::cout << CYAN << "\nTotal: $" << cart.getTotal() << "\n" << RESET;
            std::string name, address, phone;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Name: "; std::getline(std::cin, name);
            std::cout << "Address: "; std::getline(std::cin, address);
            std::cout << "Phone: "; std::getline(std::cin, phone);

            writeOrderToCSV("orders_history.csv", cart, cart.getTotal(), name, address, phone);
            std::cout << GREEN << "[OK] Order saved to history!\n" << RESET;
            break;
        }
    }
}

void showOrderHistory(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open order history file.\n";
        return;
    }

    std::string line;
    std::cout << CYAN << "\n--- Order History ---\n" << RESET;
    while (std::getline(file, line)) {
        std::cout << line << "\n";
    }
    std::cout << CYAN << "----------------------\n" << RESET;
}
