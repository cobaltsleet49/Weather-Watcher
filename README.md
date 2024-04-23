# Project 3: Weather Watchers

## Instructions:

### How to Run:
1. Create a new project in CLion.
2. Pull the files from this repository into your project.
3. Make sure your `CMakeLists.txt` file is set up correctly. Here is a sample file:
    ```cmake
    cmake_minimum_required(VERSION 3.28)
    project(Project3)

    set(CMAKE_CXX_STANDARD 17)

    add_executable(Project3 main.cpp
            RedBlackTree.h
            RedBlackTree.cpp
            HashTable.h
            HashTable.cpp
            WeatherData.h)
    ```
4. Copy and Paste all the `.csv` files inside the `Data` folder into your `cmake-build-debug` folder. That way, the program can access these files at run-time.
5. You're all set up! Start the program and follow the instructions given in the CLI.

### How to add more data sets:
1. Head to [NOAA Climate Data Access](https://www.ncei.noaa.gov/access/monitoring/climate-at-a-glance/county/mapping).
2. Make sure the parameters are configured to "Contiguous U.S." for the "State" section and "1-Month" for the "Time Scale" section. We used both average temperature and precipitation for the weather parameters.
3. Choose the desired year and month.
4. Click the blue "Plot" button below the parameters.
5. Scroll down and download the `.csv` file located in the "Download" section.
6. **This is important:** rename the `.csv` to the format "Year-MonthP/T", where `P` stands for precipitation and `T` for average temperature. Months are single-digit for 1-9, and double-digit for 10-12. The `buildTree`/`buildTable` functions are designed to read in files in this format, so if you do not follow the format then the program will not work.
7. Paste the `.csv` file into the `cmake-build-debug` folder. You may also paste them in the `Data` directory to keep track.
8. If you choose to add data files, make sure you add ALL average temperature and precipitation files for each given year you add - that is the way the for-loops are set up.
9. Go into the `buildTree`/`buildTable` functions in the `RedBlackTree.cpp` and `HashTable.cpp` files, respectively, and change the for-loop parameters to accommodate the year(s) you add.
