# Property Management System (PMS)

A console-based C++ application designed to help real estate agencies manage properties, track tenants, and generate financial reports.

## 📋 Features

This system allows the user to perform the following operations:

* **Property Management:**
    * **Add Property:** Dynamically add new properties (Apartments, Offices, Garages, etc.).
    * **Remove Property:** Delete properties by ID with automatic memory cleanup.
    * **List Properties:** View all properties or filter only available (FREE) ones.
* **Tenant Management:**
    * **Rent Out:** Assign a tenant to a property (Name, Phone number).
    * **Release:** Remove a tenant and mark the property as free.
* **Financials:**
    * **Financial Report:** Calculate total possible income vs. current actual income and view lost revenue from vacant properties.
* **Data Persistence:**
    * Automatically saves all data to a file (`data.txt`) upon exit.
    * Loads data automatically upon startup.

## 🛠️ Technical Implementation

This project was built to demonstrate proficiency in **C++** and **manual memory management**. Key technical concepts include:

* **Dynamic Memory Management:**
    * Usage of dynamic arrays for storing properties.
    * **Automatic Resizing:** The system automatically doubles its capacity when the array is full (custom resize logic).
    * **Deep Copying:** Proper handling of pointers when resizing arrays or manipulating objects.
    * **Memory Cleanup:** No memory leaks; all dynamic memory is freed before the program exits.
* **Custom String Handling:**
    * Implementation of custom `strLen` and `strCpy` functions instead of relying solely on standard libraries.
    * Handling of C-style strings (`char*`).
* **File I/O:**
    * Reading and writing to text files using `fstream`.
    * Using a custom delimiter (`|`) to handle data parsing safely.
* **Separation of Concerns:**
    * Code is split into header files (`.h`), implementation files (`.cpp`), and the main entry point.

## 🚀 How to Build and Run

### Prerequisites
* A C++ Compiler (supporting C++20 standard).
* CMake (optional, but `CMakeLists.txt` is provided).

### Using CMake
1.  Clone the repository:
    ```bash
    git clone [https://github.com/your-username/property-management-system.git](https://github.com/your-username/property-management-system.git)
    cd property-management-system
    ```
2.  Create a build directory:
    ```bash
    mkdir build && cd build
    ```
3.  Run CMake and Make:
    ```bash
    cmake ..
    make
    ```
4.  Run the application:
    ```bash
    ./Property_managment_system
    ```

## 📂 Data Storage

The application stores data in `data.txt` in the following pipe-separated format:
```text
ID|Address|Type|Area|Price|Status|IsRented|TenantName|TenantPhone|Term|
```
## 👤 Author

**Stefko Nikolaev**
* **Role:** Software Engineering Student at FMI, Sofia University
* **Focus:** C++, Algorithms, and Data Structures