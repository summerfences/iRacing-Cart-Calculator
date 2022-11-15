# iRacing-Addon-Cost-Calculator

This program allows you to calculate how much it would cost to buy a specific quantity of tracks and cars for iRacing. Currently, there are prompts to allow you to specify any number of cars, $11.95 tracks, $14.95 tracks, legacy cars, and legacy tracks to be purchased. The program then calculates the cost of these items and includes the bulk discount on applicable items if the cart is eligible to apply for either the 10% or 15% discount rate.

Currently, no functionality for calculating the VAT or sales tax of the car is included. 

If compiling for yourself on a GNU/Linux distribution, be sure to include the -lpthread flag when compiling as the program utilizes multithreading. 

Windows execution is as easy as extracting the .zip archive and running the executable.

For Linux users, pull up a terminal pointing to the directory in which the executable is stored, and run it with 
`./iRacing-Cost-Calculator-v0.1`
Alternatively, you could enter `./` into the terminal, and then click and drag the file to the terminal.
