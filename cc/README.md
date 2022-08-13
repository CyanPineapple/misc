### C++ Notes
#### `std::thread::detach()`

if not detach, calling threading will sigabort once out of scope.

#### Class Initialization Order

Static member is constexpr, initialize once before program body.

Virtual Base classes -> Direct Base Classes -> nonstatic data member -> Constructor
