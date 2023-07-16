/* Program that calculates how much different quantities
 * of NON-LEGACY tracks and cars cost on iRacing
 * Use this when budgeting out a cart in the service
 * VAT/Sales tax not yet implemented
 * https://github.com/summerfences v0.1
 * 11/14/2022
 */

#include <iostream>
#include <iomanip>
#include <thread> // use -pthread in g++ to compile on GNU/Linux

using std::cout;
using std::cin;
using std::endl;
using std::thread;

double add_legacy_cars(int legacy, double total);
double add_legacy_tracks(int legacy, double total);

int main() {
    // calculate the cost of the cars
    auto calculate_cars=[] (int num, double *cost) {
        double price = (double) num * 11.95;
        *cost = price;
        return 0;
    };
    // calculate the cost of the $14.95 tracks
    auto calculate_1495_tracks=[] (int num, double *cost) {
        double price = (double) num * 14.95;
        *cost = price;
        return 0;
    };
    // calculate the cost of the $11.95 tracks
    auto calculate_1195_tracks=[] (int num, double *cost) {
        double price = (double) num * 11.95;
        *cost = price;
        return 0;
    };

    int tracks1495, tracks1195, cars, combinedQty, legacyCars, legacyTracks;
    double carCost, trackCost1495, trackCost1195, total;

    cout << "This program calculates the cost of the iRacing wishlist you've thought up!" << endl;
    cout << "How many tracks would you like to buy for $14.95? ";
    cin >> tracks1495;
    cout << "How many tracks would you like to buy for $11.95? ";
    cin >> tracks1195;
    cout << "How many LEGACY tracks would you like to buy?";
    cin >> legacyTracks;
    cout << "How many NON-LEGACY cars would you like to buy? ";
    cin >> cars;
    cout << "How many LEGACY cars would you like to buy? ";
    cin >> legacyCars;

    std::mutex mtx;
    thread carThread(calculate_cars, cars, &carCost);
    carThread.detach();
    thread trackThread1195(calculate_1195_tracks, tracks1195, &trackCost1195);
    trackThread1195.detach();
    thread trackThread1495(calculate_1495_tracks, tracks1495, &trackCost1495);
    trackThread1495.join();
    total = carCost + trackCost1195 + trackCost1495;
    combinedQty = cars + tracks1495;

    cout << std::setprecision(4);

    if (combinedQty < 3) {
        total = add_legacy_cars(legacyCars, total);
        total = add_legacy_tracks(legacyTracks, total);
        cout << "Your total cost is:" << endl << "$"  << total << endl;
    }
    else if (combinedQty >= 3 && combinedQty <= 5) {
        cout << "You qualify for:" << endl << "10% off bulk discount" << endl;
        total = total - (total * 0.10);
        total = add_legacy_cars(legacyCars, total);
        total = add_legacy_tracks(legacyTracks, total);
        cout << "Your total cost is:" << endl << "$"  << total << endl;
    }
    else if (combinedQty >= 6) {
        cout << "You qualify for:" << endl << "15% off bulk discount" << endl;
        total = total - (total * 0.15);
        total = add_legacy_cars(legacyCars, total);
        total = add_legacy_tracks(legacyTracks, total);
        cout << "Your total cost is $" << total << endl;
    }
    else {
        cout << "Invalid input. Double check values and run the program again." << endl;
    }

    return 0;
}

// add the cost of purchased legacy cars, which do not apply to discounts
double add_legacy_cars(int legacy, double total) {
    return total + (legacy * 2.95);
}
double add_legacy_tracks(int legacy, double total) {
    return total + (legacy * 4.95);
}
