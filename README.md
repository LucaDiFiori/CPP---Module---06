# CPP---Module---06
This module is designed to help you understand the different casts in CPP.

***
# TYPE CASTING IN C++
***

# Table of contents
- [CASTS IN C](#casts-in-c)
    - [Type Conversion](#type-conversion)
    - [Type Reinterpretation](#type-Reinterpretation)
    - [Type Qualifier Reinterpretation](#type-qualifier-reinterpretation)
- [UPCAST AND DOWNCAST INC C++](#upcast-and-downcast-inc-c++)
    - [Upcasting](#upcasting)
    - [Downcasting](#downcasting)
- [STATIC CAST](#static-cast)
    - [Basic Syntax](#basic-syntax)
    - [Common Uses of static_cast](#common-uses-of-static_cast)
    - [Converting const and non-const Types](#converting-const-and-non-const-types)
    - [Example: Using static_cast in Different Contexts](#example-using-static_cast-in-different-contexts)
- [DYNAMIC CAST](#dynamic-cast)
    - [Purpose of dynamic_cast](#Purpose_of_dynamic_cast)
    - [Syntax](#syntax)
    - [Key Points](#key-points)
    - [When to Use dynamic_cast](#when-to-use-dynamic_cast)

***
***

# CASTS IN C
In C, type conversion and type reinterpretation are ways to change how data is handled or interpreted in terms of its type. Here's how they work and how they differ:

## Type Conversion
Type conversion in C is about changing a value from one data type to another, ensuring that the value retains its logical meaning after the change. There are two main types of conversions: implicit and explicit.
1. **Implicit Conversion (Automatic Type Casting)**: This happens   automatically when assigning a value of one type to a variable of another type if the types are compatible. For example:
    ```C
    int x = 10;
    float y = x; // Implicit conversion from int to float
    ```
    Here, x is converted from int to float automatically, with no data loss in this case.

2. **Explicit Conversion (Type Casting)**: Also known as type casting, explicit conversion is when you manually convert a variable to another type using a cast operator. This is useful when you want to control the conversion or when implicit conversion may lead to data loss. For example:
    ```C
    float x = 10.5;
    int y = (int)x; // Explicit conversion from float to int
    ```
    Here, x is cast to an int, which will drop the decimal part, resulting in y being 10.

## Type Reinterpretation
Type reinterpretation in C, on the other hand, changes how the underlying bits of a value are interpreted without altering the bits themselves. This is generally done by casting pointers, and it can lead to undefined behavior if not done carefully, as it bypasses type safety.

1. **Pointer Type Casting**: In C, you can cast a pointer of one type to another pointer type. This allows you to access the data as though it’s of a different type, but it doesn’t change the actual data in memory. For example:
    ```C
    int x = 65;
    char *y = (char *)&x; // Reinterpretation cast
    printf("%c\n", *y); // Might print 'A' depending on system's endianness
    ```
    Here, x is an int, but by casting its address to a char *, we can interpret its first byte as a char. This may print A, as 65 is the ASCII code for A. However, it depends on the system’s endianness.

**Key Differences**
- Type Conversion changes the logical value to match the new type, often altering the bits if necessary.
- Type Reinterpretation does not alter the bits but only changes how they're viewed, which can lead to undefined behavior if the data types are incompatible.

## Type Qualifier Reinterpretation
In C, qualifier reinterpretation is a process that involves changing or ignoring type qualifiers such as **const** or **volatile** when casting or accessing a variable. Qualifiers control how the compiler treats a variable in terms of modification and optimization, but qualifier reinterpretation can allow for flexibility in certain low-level programming contexts. However, it’s essential to use this approach cautiously, as it can lead to undefined behavior if misused.

**Type Qualifiers**
Before diving into qualifier reinterpretation, let's briefly discuss what qualifiers are:

1. **const**: Indicates that a variable's value should not be modified.
1. **volatile**: Instructs the compiler not to optimize the variable, as it may be changed in ways the compiler cannot predict (e.g., by hardware or another thread).

Qualifier reinterpretation occurs when a cast removes or adds a qualifier to a type. This generally involves using pointer casts to change the qualifiers of a variable indirectly. For example:
```C
const int x = 10;
int *ptr = (int *)&x; // Reinterprets `const int` as `int`
*ptr = 20;            // Modifying `x` through the non-const pointer
```
Here, x is declared as const int, meaning it should not be modified. By casting 
its address to int *, we bypass the const restriction, allowing us to change the 
value indirectly. This is qualifier reinterpretation and is technically allowed in C, 
but it leads to undefined behavior since modifying a const variable violates its 
intended constraints.

***
***

# UPCAST AND DOWNCAST INC C++
In C++, upcasting and downcasting are concepts related to inheritance and casting 
between base and derived class pointers or references. Here's a breakdown of each:

In this first example, we will use C-like syntax to explain some concepts:
Let's say we have a parent class named "Parent" and two child classes, "Child1" and "Child2." 
This inheritance structure creates a hierarchy in which "Parent" serves as the more 
general class, while "Child1" and "Child2" are more specialized.

```C++
#include <iostream>

Class Parent                 {};
Class Child1 : public Parent {};
Class Child2: public Parent  {};

/***********************************************/

int main() {
    Child1  a;                  //Reference value

    Parent* b = &a;             // Implicit 'reinterpretation' cast
    Parent* c = (Parent*)&a;    // Explicit 'reinterpretation' cast

    Parent* d = &a;             // Implicit upcast  --> OK
    Child1* e = d;              // Implicit downcast --> NOT OK (compilation error)
    Child2* f = (Child2*)d;     // Explicit downcast --> This will compile, but there's no 
                                // guarantee that the implementation of Child2 is 
                                // compatible with Child1.
}
```

## Upcasting
*+Upcasting* is the process of **converting a pointer or reference from a derived class to a base class**. 
This is safe and often done automatically in C++ because every derived 
class object inherently contains a base class object.

**Example of Upcasting**
```C++
#include <iostream>
class Animal {
public:
    virtual void makeSound() const { std::cout << "Animal sound\n"; }
};

class Dog : public Animal {
public:
    void makeSound() const { std::cout << "Bark\n"; }
};

int main() {
    Dog myDog;
    Animal* animalPtr = &myDog; // Upcast from Dog* to Animal*
    animalPtr->makeSound(); // Calls Dog's overridden method, outputs "Bark"

    return 0;
}
```

**Explanation**
- Here, Dog is a derived class of Animal.
- When animalPtr is assigned the address of myDog, this is an upcast from Dog* to Animal*.
- Upcasting is generally safe and doesn't require an explicit cast because a derived 
  class is fully compatible with the base class.

If the makeSound method in Animal is **virtual** (as shown), C++ uses polymorphism to 
**call Dog's version of makeSound**, showing that myDog is still treated as a Dog at 
runtime.

## Downcasting
*Downcasting* is the opposite of upcasting: it **converts a base class pointer or reference back to a derived class type**. 
This **requires an explicit cast** and can be unsafe because not every Animal is a Dog. 
To make downcasting safer, C++ provides the **dynamic_cast operator** (C++11 only), which performs 
a runtime check to ensure the cast is valid when casting to a pointer of a derived type.



***


# STATIC CAST
In C++, static_cast is a casting operator that performs explicit type conversions 
at compile time. It's generally used for conversions that are known to be safe, 
such as converting between related types in an inheritance hierarchy (upcasting or 
safe downcasting), or for other conversions like numeric types or non-const to 
const conversions.

Here's a closer look at how static_cast is used and when it's appropriate.

## Basic Syntax
The syntax of static_cast is:
```C++
static_cast<new_type>(expression)
//- "new_type"  :  name of th type i want to cast to
//- "expression":  Wat i wont to cast
```

**C-like example**:
```C++
#include <iostream>
//My classes hirarchy:
Class Parent                 {};
Class Child1 : public Parent {};
Class Child2 : public Parent {};

Class Unrelated              {};


//**********************************************


int main()
{
    Child1 = a;      // Reference value

    Parent*  b = &a; // Implicit upcast --> OK
    Child1*  c = b   // Implicit downcast  --> Hell no!
    Child2*  d = static_cast<Child2 *>(b); // Explicit demotion --> OK. I obey

    Unrelated* e = static_cast<Unrelated *>(&a) //Explicit conversion between unrelated classes -> NO !
                                                //static_cast will ensure we cast between classes within the same inheritance hierarchy.
}
```

## Common Uses of static_cast
1. **Upcasting (Derived to Base Conversion)**
When converting from a derived class pointer to a base class pointer (upcasting), 
static_cast is often used. This conversion is safe because a derived class always 
contains a base class, so no data is lost.
```C++
class Animal {};
class Dog : public Animal {};

Dog myDog;
Animal* animalPtr = static_cast<Animal*>(&myDog); // Safe upcast
```

2. **Downcasting (Base to Derived Conversion)**
When converting from a base class pointer to a derived class pointer (downcasting), 
static_cast can be used if you are certain of the object's type. 
Unlike dynamic_cast, **static_cast does not perform a runtime check**, 
so it can be unsafe if used incorrectly.
```C++
int main() {
    Animal* animalPtr = new Dog(); // Upcast
    Dog* dogPtr = static_cast<Dog*>(animalPtr); // Downcast from Animal* to Dog*
    dogPtr->speak(); // Outputs "Bark"

    delete animalPtr; // Clean up memory
    return 0;
}
```
If animalPtr doesn't actually point to a Dog object, this cast may lead to undefined 
behavior. Use dynamic_cast for safer downcasting if Animal has at least one virtual function.

3. **Converting Numeric Types**
static_cast is commonly used to convert between numeric types, such as int to float, double to int, etc. This conversion is explicit, ensuring that the programmer is aware of any potential data loss (e.g., truncating a double to int).
```C++
int main() {
    double pi = 3.14159;
    int integerPi = static_cast<int>(pi); // Converts double to int, truncating the decimal part
    std::cout << "Integer value: " << integerPi << std::endl; // Outputs "Integer value: 3"

    return 0;
}
```

4. **Converting void* to Other Pointer Types**
static_cast can also be used to convert a void* pointer to a specific type. This is common in C++ code where a void* pointer holds a generic pointer, and you need to cast it to a specific type.
int integerPi = static_cast<int>(pi); // Converts double to int, truncating the decimal part
```C++
int main() {
    void* voidPtr = new Dog(); // Create a Dog object and store its address in a void pointer
    Dog* dogPtr = static_cast<Dog*>(voidPtr); // Convert void* to Dog*
    dogPtr->speak(); // Outputs "Bark"

    delete dogPtr; // Clean up memory
    return 0;
}`
```

## Converting const and non-const Types
static_cast can add const to a type (for instance, converting from int* to const int*). 
However, it cannot remove const. To remove const, you would use const_cast instead.
```C++
int x = 42;
const int* constPtr = static_cast<const int*>(&x); // Adds const-qualification
```

## Example: Using static_cast in Different Contexts
```C++
#include <iostream>

class Animal {
public:
    virtual void speak() const { std::cout << "Animal sound\n"; }
};

class Dog : public Animal {
public:
    void speak() const override { std::cout << "Bark\n"; }
    void wagTail() const { std::cout << "Wagging tail\n"; }
};

int main() {
    Dog myDog;
    
    // 1. Upcasting from Dog* to Animal*
    Animal* animalPtr = static_cast<Animal*>(&myDog);
    animalPtr->speak(); // Outputs "Bark" due to polymorphism

    // 2. Numeric conversion
    double value = 3.14;
    int intValue = static_cast<int>(value); // Converts to int, truncating to 3
    std::cout << "Integer value: " << intValue << "\n";

    // 3. Downcasting back from Animal* to Dog*
    Dog* dogPtr = static_cast<Dog*>(animalPtr); // Unsafe if animalPtr is not actually a Dog
    dogPtr->wagTail(); // Outputs "Wagging tail"

    // 4. void* to Dog* conversion
    void* voidPtr = &myDog;
    Dog* dogPtrFromVoid = static_cast<Dog*>(voidPtr);
    dogPtrFromVoid->speak(); // Outputs "Bark"

    return 0;
}
```

***

# DYNAMIC CAST
In C++, dynamic_cast is used for **safe casting in situations involving polymorphism**, 
allowing you to convert **pointers or references** within an inheritance hierarchy.
Dynamic casting only occurs at runtime (during execution, not compilation), which is why we need 
to handle possible failures.

**Example first**
```C++
#include <iostream>
#include <typeinfo>
#include <exception>

Class Parent                 {public : virtual ~Parent(void){}};
Class Child1 : public Parent {};
Class Child2 : public Parent {};

//***************************************************************

int main() {
    Child   a;       //Reference value
    Parent* b = &a;  //Implicit upcast --> OK

    // (Dynamic cast using a POINTER)
    //Explicit downcast 
    Child1* c = dynamic_cast<Child *>(b);
    if ( c == NULL) {
        std::cout << "Conversin in NOT Ok" << std::endl;
    }
    else {
        std::cout << "Conversion is ok" << std::endl;
    }

    //(Dynamic cast using a REFERENCE)
    //Explicit downcast
    try {
        Child2& d = dynamic_cast<Child2 &>(*b); //b is a pointer, i need to unrefernce it with *
        std::cout << "Conversion is Ok" << std::endl;
    }
    catch (std::bad_cast &bc) {
        std::cout << "Conversion is NOT ok: " << bc.what() << std::endl;
        retun (0);
    }
}
```
This code demonstrates dynamic casting in C++. Dynamic casting is primarily used 
for safe **downcasting** in polymorphic class hierarchies, allowing you to attempt 
casting a **pointer or reference of a base class (like Parent) to a derived class** (like Child1 or Child2). 
Here's a breakdown:
- **Class Hierarchy**:
    - We have a base class Parent with two derived classes, Child1 and Child2.
    - Parent has a virtual destructor (~Parent()) which makes the class polymorphic. This is necessary for dynamic_cast to work.

- **Pointer Upcast**:
```C++
Parent* b = &a;
```
Here, *a* is an instance of Child1, and we assign its address to a Parent* pointer, *b*. 
This is called upcasting (*a*) and is implicit and safe because Child1 is a Parent.
the object *a* (an instance of Child1) is the one being cast:
- a is of type Child1.
- When we assign &a (the address of a) to the Parent* pointer b, a is implicitly cast to type Parent*.
- This cast is safe and implicit because Child1 is derived from Parent, making every Child1 object inherently a Parent.

- **Dynamic Casting Using a Pointer**:
```C++
Child1* c = dynamic_cast<Child1*>(b);
```
- we are creating a new pointer, c, of type Child1*. 
- This is an explicit **downcast** attempt where we try to cast Parent* b to Child1*.
- Since b actually points to a Child1 object (Parent* b = &a) , the cast succeeds, and c will not be NULL.
- If b did not point to a Child1 object (e.g., if it pointed to a Child2 or actually pointed to an object that was 
  a plain Parent instance), dynamic_cast would return NULL to indicate the cast failed.
  - If b actually pointed to an object that was a plain Parent instance, the dynamic_cast to Child1* would fail. 
    In that case, the cast result would be NULL. Here's why:
    - **Object Type Check at Runtime**: dynamic_cast examines the actual type of the object that b points to at runtime. If b points to a Parent object (not a Child1 object), there's no way to safely cast it to Child1*, since Parent itself does not contain the extra data or behaviors of Child1.








## Purpose of dynamic_cast
- dynamic_cast is mainly used when working with polymorphic classes (classes that have **at least one virtual function**).
- It allows you to safely cast a pointer or reference from a base class to a derived class.

## Syntax
```C++
// Using a pointer
derivedType* derivedPtr = dynamic_cast<derivedType*>(basePtr);
if (derivedPtr) {
    // Cast succeeded, safe to use derivedPtr
} else {
    // Cast failed, handle the error
}
```
- basePtr is a pointer to a base class
- derivedType is the type you want to cast to (usually a derived class).
- We are Attempting to cast basePtr to a pointer of type derivedType*


```C++
// Using a Reference
try {
    derivedType& derivedRef = dynamic_cast<derivedType&>(baseRef);
    // Cast succeeded, safe to use derivedRef
} catch (const std::bad_cast& e) {
    // Cast failed, handle the exception
    std::cerr << "Cast failed: " << e.what() << std::endl;
}
```
- baseRef is a reference to the base class.
- derivedType is the type you want to cast to (typically a derived class).

## Key Points
- **Runtime Check**: dynamic_cast performs a runtime **check** to see if the object being cast is of the requested type.
- **Null Return**: If casting a pointer and the cast fails (i.e., the object is not of the target type), dynamic_cast returns nullptr.
- **Throws Exception**: When casting references instead of pointers, dynamic_cast throws a std::bad_cast exception if the cast fails.

## Requirements
- The base class must have at least one **virtual** function for dynamic_cast to work.
- dynamic_cast can **only cast within related classes in the same hierarchy** (upcasting or downcasting).

**Example**
```C++
#include <iostream>

class Animal {
public:
    virtual ~Animal() {}  // Virtual destructor
};

class Dog : public Animal {
public:
    void bark() { std::cout << "Woof!" << std::endl; }
};

int main() {
    Animal* animalPtr = new Dog;  // Upcasting to Animal

    // Attempting to downcast to Dog
    Dog* dogPtr = dynamic_cast<Dog*>(animalPtr);
    if (dogPtr) {
        dogPtr->bark();  // Safe to call, dynamic_cast succeeded
    } else {
        std::cout << "Cast failed!" << std::endl;
    }

    delete animalPtr;  // Clean up
    return 0;
}
```

Note: dynamic_cast incurs a small runtime overhead, so use it only when necessary, as frequent casting can impact performance.