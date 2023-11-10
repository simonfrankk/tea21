#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"

#include <vector>   // Für std::vector
#include <random>   // Für std::random_device und std::mt19937
#include <algorithm> // Für std::sort
#include <chrono>    // Für std::chrono



auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    int count = 20;  // Standardwert für count

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        //Aufgabenteil 1 - Parameterabfrage count
        app.add_option("-c,--count", count, "Set the count parameter")->check(CLI::PositiveNumber);

        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());

    // Erstellen Vektor mit der Größe von 'count' und füllen mit zufälligen Werten von 1 bis 100
    std::vector<int> randomValues;
    
    // Initialisieren Zufallszahlengenerator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 100);  // Verteilung von 1 bis 100

    for (int i = 0; i < count; ++i) {
        randomValues.push_back(dist(gen));
    }
    // Startzeit messen
    auto start = std::chrono::high_resolution_clock::now();

    // Sortieren Vektor
    std::sort(randomValues.begin(), randomValues.end());

    // Endzeit messen
    auto end = std::chrono::high_resolution_clock::now();
    
    // Berechnen Zeitdauer
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // Ausgeben sortierte Werte
    fmt::print("Sorted Values: ");
    for (int value : randomValues) {
        fmt::print("{} ", value);
    }
    fmt::print("\n");

    // Ausgeben Sortierung
    fmt::print("Time taken to sort: {} nanoseconds\n", elapsed.count());

    /* INSERT YOUR CODE HERE */

    return 0; /* exit gracefully*/
}
