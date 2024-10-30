# CPP---Module---06
This module is designed to help you understand the different casts in CPP.

***
# TYPE CASTING IN C++
***

# Table of contents
- [CASTS IN C](#casts-in-c)
    - [Type Conversion](#type-conversion)
    - [Type Reinterpretation](#type-Reinterpretation)

***
***

# CASTS IN C
In C, type conversion and type reinterpretation are ways to change how data is handled or interpreted in terms of its type. Here’s how they work and how they differ:

## Type Conversion
Type conversion in C is about changing a value from one data type to another, ensuring that the value retains its logical meaning after the change. There are two main types of conversions: implicit and explicit.
1. **Implicit Conversion (Automatic Type Casting)**: This happens   automatically when assigning a value of one type to a variable of another type if the types are compatible. For example:
    ```C
    int x = 10;
    float y = x; // Implicit conversion from int to float
    ```
    Here, x is converted from int to float automatically, with no data loss in this case.