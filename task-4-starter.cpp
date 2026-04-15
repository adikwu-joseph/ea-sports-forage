#include <string>
#include<iostream>
#include <utility>

// Represents a single item in the inventory
class Item {
private:
    std::string name;   // Name of the item
    int quantity;       // Number of items in stock
    float price;        // Price per item

public:
    // Constructor to initialise item values
    Item(
            std::string name,
            int quantity,
            float price
    ) :
            name{std::move(name)},  // Move for efficiency
            quantity{quantity},
            price{price} {

    }

    // Getter for item name
    std::string get_name() const {
        return name;
    }

    // Getter for quantity
    int get_quantity() const {
        return quantity;
    }

    // Setter to update quantity
    void set_quantity(int new_quantity) {
        quantity = new_quantity;
    }

    // Getter for price
    float get_price() const {
        return price;
    }

    // Checks if item name matches a given string
    bool is_match(const std::string &other) {
        return name == other;
    }
};

// Manages a collection of items
class Inventory {
private:
    Item *items[20];     // Fixed-size array of pointers to items (max 20)
    float total_money;   // Total money earned from sales
    int item_count;      // Current number of items in inventory

    // Helper function to display item details
    static void display_data(Item &item) {
        std::cout << "\nItem name: " << item.get_name();
        std::cout << "\nQuantity: " << item.get_quantity();
        std::cout << "\nPrice: " << item.get_price();
    }

public:
    // Constructor initialises inventory state
    Inventory() :
            items{},           // Initialise all pointers to nullptr
            total_money{0},    // No money earned initially
            item_count{0} {    // No items initially

    }

    // Adds a new item to the inventory
    void add_item() {
        std::string name;
        int quantity;
        float price;

        std::cin.ignore();  // Clear input buffer

        std::cout << "\nEnter item name: ";
        std::cin >> name;

        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        std::cout << "Enter price: ";
        std::cin >> price;

        // Dynamically create a new Item and store pointer
        items[item_count] = new Item(name, quantity, price);
        item_count++;
    }

    // Handles selling an item by name
    void sell_item() {
        std::string item_to_check;

        std::cin.ignore();  // Clear input buffer

        std::cout << "\nEnter item name: ";
        std::cin >> item_to_check;

        // Search for item in inventory
        for (int i = 0; i < item_count; i++) {
            if (items[i]->is_match(item_to_check)) {
                remove_item(i);  // Process sale
                return;
            }
        }

        // If item not found
        std::cout << "\nThis item is not in your Inventory";
    }

    // Removes (sells) a specific quantity of an item
    void remove_item(int item_index) {
        int input_quantity;
        Item *item = items[item_index];

        std::cout << "\nEnter number of items to sell: ";
        std::cin >> input_quantity;

        int quantity = item->get_quantity();

        // Ensure enough stock is available
        if (input_quantity <= quantity) {
            float price = item->get_price();
            float money_earned = price * input_quantity;

            // Update inventory and total money
            item->set_quantity(quantity - input_quantity);

            std::cout << "\nItems sold";
            std::cout << "\nMoney received: " << money_earned;

            total_money += money_earned;
        } else {
            std::cout << "\nCannot sell more items than you have.";
        }
    }

    // Displays all items in the inventory
    void list_items() {
        if (item_count == 0) {
            std::cout << "\nInventory empty.";
            return;
        }

        for (int i = 0; i < item_count; i++) {
            display_data(*items[i]);
            std::cout << "\n";
        }
    }
};

// Entry point of the program
int main() {
    int choice;
    Inventory inventory_system;

    std::cout << "Welcome to the inventory!";

    while (1) {
        // Display menu options
        std::cout << "\n\nMENU\n"
                  << "1. Add new item\n"
                  << "2. Sell item\n"
                  << "3. List items\n"
                  << "4. Exit\n\n"
                  << "Enter your choice: ";

        std::cin >> choice;

        // Handle user choice
        switch (choice) {
            case 1:
                inventory_system.add_item();
                break;

            case 2:
                inventory_system.sell_item();
                break;

            case 3:
                inventory_system.list_items();
                break;

            case 4:
                exit(0);  // Exit program

            default:
                std::cout << "\nInvalid choice entered";

                // Clear invalid input
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');
                break;
        }
    }
}
