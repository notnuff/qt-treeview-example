# Qt TreeList - OM TreeView
A Qt6 application demonstrating a custom tree view for displaying mobile operators organized by country. The app displays countries with their MCC (Mobile Country Code) and operators with their MNC (Mobile Network Code), with custom icons and tree branch rendering.

## Build Instructions

### Prerequisites
CMake 3.28+  
Qt 6.5+  
Ninja build system  
C++20 compatible compiler  

### Build Steps
* Configure with preset (debug/release/relwithdebinfo)  
`cmake --preset debug`

* Build  
`cmake --build build/debug`

* Run  
`./build/debug/qt-treeview_app`

### CMake Cache Variables
USE_MOCK_PROVIDER (default: OFF)

OFF: Uses SQLite database (system.db) for real data  
ON: Uses mock data provider with hardcoded test data (Ukraine, US, India)  

Example:  
`cmake --preset debug -DUSE_MOCK_PROVIDER=ON`

## Result

<img width="805" height="641" alt="image" src="https://github.com/user-attachments/assets/d5b4da43-5f34-4665-94f9-cf975ec1608d" />
