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
- [REINTERPRET CAST](#reinterpret-cast)
    - [Purpose of reinterpret_cast](#purpose-of-reinterpret_cast)
    - [Syntax](#syntax)
    - [Usage Caution](#usage-caution)
    - [Restrictions](#restrictions)
- [CONST CAST](#const-cast)
    - [purpose](#purpose)
    - [Syntax](#syntax)
    - [Good Practice](#Good-Practice)
- [TYPECAST OPERATOR (METHOD)](#typecast-operator-method)
    - [Syntax](#syntax)
- [EXPLICIT KEYWORD](#explicit-keyword)
    - [explicit Keyword with Constructors](#explicit-keyword-with-constructors)
        - [syntax](#syntax)
        - [Example](#example)

***
***
# CASTS IN C - OVERVIEW
1. **C-style Cast**
- Syntax: 
  ```C
  (type) expression /*or*/ **type(expression)
  ``
- This is the traditional cast from C, and it works for most types.
- It's fast but unsafe because it can perform many conversions, including incompatible types, without warnings.

2. **static_cast**
- Syntax: 
  ```C++
  static_cast<type>(expression)
  ```C
- Used for safe, non-polymorphic casts (e.g., int to double or converting pointers within an inheritance hierarchy when you know the conversion is safe).
- It checks for correctness at compile time but doesn't offer runtime safety.

3. **dynamic_cast**
- Syntax: 
  ```C++
  dynamic_cast<type>(expression)
  ```C
- Used for casting pointers or references within a polymorphic class hierarchy (classes with virtual functions).
- It performs a runtime check and returns nullptr if the cast is unsafe.
- Only works with pointers and references to classes with at least one virtual function.

4. **reinterpret_cast**
- Syntax: **reinterpret_cast<type>(expression)**
- Performs a low-level cast, allowing conversion between unrelated pointer types or between a pointer and an integer type.
- Very powerful but risky because it ignores the actual type compatibility, so it should be used with caution.

5. **const_cast**
- Syntax: 
  ```C++
  const_cast<type>(expression)
  ```C
- Used to add or remove const or volatile qualifiers from a variable.
- Useful if you need to temporarily change a const value, but it should be used 
  carefully to avoid undefined behavior.

6. **Typecast Operator (Method)**
- Syntax:
  ```C++
  operator TargetType() const { return conversionValue}; 
  ```C
- The typecast operator allows instances of a class to be converted to a specified type automatically, as if the class had a built-in conversion to that type.
- This operator enables implicit conversions, which can make the code more intuitive 
  but should be used carefully to avoid unintended conversions.

***
***

**Table**
|                    |**Cast action**  |                  |          |            |                      |
|                    |-----------------|                  |          |            |                      |
| **Cast type**      | Conversion      | reinterpretation | Upcast   | Downcast   | Type qualifier reint.|
|_-------------------|                 |                  |          |            |                      |
| `Implicit`         | Yes             |                  | Yes      |            |                      |
| `static_cast`      | Yes             |                  | Yes      | Yes        |                      |
| `dynamic_cast`     |                 |                  | Yes      | Yes        |                      |
| `const_cast`       |                 |                  |          |            | Yes                  |
| `reinterpret_cast` |                 | Yes              | Yes      | Yes        |                      |
| `C cast`           | Yes             | Yes              | Yes      | Yes        | Yes                  |

---

| Cast               | Semantic check | Reliable at run | Tested at run |
|--------------------|----------------|-----------------|---------------|
| `Implicit`         | Yes            | Yes             |               |
| `static_cast`      | Yes            |                 |               |
| `dynamic_cast`     | Yes            | Yes             | Yes           |
| `const_cast`       |                |                 |               |
| `reinterpret_cast` |                |                 |               |
| `C cast`           |                |                 |               |


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
This is called upcasting (the object *a* ,an instance of Child1, is the one being cast) and is 
implicit and safe because Child1 is a Parent object.


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
    Here's why:
    - **Object Type Check at Runtime**: dynamic_cast examines the actual type of the object that b points to at runtime. 
      If b points to a Parent object (not a Child1 object), there's no way to safely cast it to Child1*, 
      since Parent itself does not contain the extra data or behaviors of Child1.
      ```C++
        Parent p;        // A plain Parent object
        Parent* b = &p;  // b points to Parent, not to Child1

        Child1* c = dynamic_cast<Child1*>(b);  // This will fail
        if (c == NULL) {
        std::cout << "Conversion failed, b points to a Parent, not a Child1." << std::endl;
        } else {
        std::cout << "Conversion succeeded." << std::endl;
        }
      ```

- **Dynamic Casting Using a Referenc**:
```C++
Child2& d = dynamic_cast<Child2&>(*b);
```
- Here, we attempt to cast Parent* b to a Child2& reference, requiring dereferencing (*b) to use dynamic_cast with a reference type
- Since b actually points to a Child1 object and not a Child2 object, this cast will fail.
- When dynamic_cast fails with a reference, it throws a std::bad_cast exception, which is caught in the catch block.
- The catch block outputs "Conversion is NOT OK" and prints the error message from std::bad_cast.


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


***


# REINTERPRET CAST
In C++, reinterpret_cast is a type of cast used for low-level reinterpreting of 
bit patterns between unrelated types. It **allows you to convert one pointer type to another, even if the types are completely unrelated**. 
It's considered the most "powerful" cast in C++, as it bypasses the type-checking 
that the compiler typically enforces, which can lead to unsafe conversions if 
not used carefully.

## Purpose of reinterpret_cast
reinterpret_cast is primarily used when you need to:
1. **Convert one pointer type to another** -  for example, converting a pointer of one class to an unrelated class, or to an integer type.
2. **Cast integer values to pointers** and vice versa
3. **Cast function pointers to a different function pointer type**

## Syntax
```C++
targetType* newPtr = reinterpret_cast<targetType*>(originalPtr);
```

## Example
1. Suppose you want to reinterpret the binary data of an integer as a pointer or vice versa:
```C++
int num = 42;
// Cast integer to a void pointer (inplicit promotion)
void* ptr = &num;

// Cast void pointer back to int pointer and dereference
int* intPtr = reinterpret_cast<int*>(ptr);
std::cout << *intPtr;  // Output will be 42
```

2. This example will illustrate how reinterpret_cast can be used to cast pointers between unrelated classes.
   Let's say we have two unrelated classes, Dog and Cat, with their own attributes and methods. 
   Using reinterpret_cast, we can cast a Dog* to a Cat*. However, this is generally 
   unsafe and serves more as an illustration of the syntax rather than a recommended practice
```C++
#include <iostream>
#include <cstring>

class Dog {
public:
    void bark() {
        std::cout << "Woof! Woof!" << std::endl;
    }
};

class Cat {
public:
    void meow() {
        std::cout << "Meow! Meow!" << std::endl;
    }
};

int main() {
    Dog myDog;
    
    // Use reinterpret_cast to cast Dog* to Cat*
    Cat* catPtr = reinterpret_cast<Cat*>(&myDog);
    
    // This is not safe, but it illustrates what reinterpret_cast does
    catPtr->meow();  // Undefined behavior! The output is unpredictable.
    
    return 0;
}
```


## Usage Caution
- reinterpret_cast does not check if the conversion is meaningful or safe. 
  For example, converting an int pointer to a double pointer can result in unpredictable 
  behavior if you try to use the resulting pointer.
- Use reinterpret_cast only when you're confident about the memory layout of the 
  data you're dealing with.

## Typical Uses
- Casting pointers to void* or back to their original type.
- Casting data structures to raw bytes or arrays.
- Performing conversions required for hardware programming or interacting with specific APIs.

## Restrictions
- reinterpret_cast cannot convert between different types of non-pointer types 
  (e.g., you can't directly cast int to double with it).
- It's not portable in all cases, as it depends on specific memory representations.


# CONST CAST
In C++, **const_cast** is used to **add or remove const (or volatile) qualifiers** from a 
variable. This can be useful when you need to change the const-ness of a variable, 
often for backward compatibility with code that requires a non-const parameter.

## Purpose
- **const_cast** is primarily used to modify the **const** or **volatile** qualifiers of a variable.
- It's often employed when you need to work with APIs that don't support const parameters, 
  or when you need to modify a const variable temporarily.

## Syntax
```C++
TargetType newVariable = const_cast<TargetType>(variableToCast);
```

**Example**
1. Ex1:
```C++
int main() {
    int  a = 42;  // reference vaue

    int const* b = &a;                  //Implicit "promotion" --> OK
    int*       c = b;                   //Implicit demotion    --> NOT OK
    int*       d = const_cast<int*>(b)  // Explicit demotion   --> OK, I OBEY
```

1. Ex2:
```C++
#include <iostream>

void changeValue(int* ptr) {
    *ptr = 100;
}

int main() {
    const int num = 50;
    std::cout << "Before: " << num << std::endl;

    // Remove const qualifier to pass num to a function that expects int*
    changeValue(const_cast<int*>(&num));

    std::cout << "After: " << num << std::endl; // Undefined behavior
    return 0;
}
```

## Good Practice
const_cast should not be used to modify actual const data, as this can easily 
lead to undefined behavior. Instead, it's better for cases where the const 
qualifier is used for logical const-ness (e.g., passing a mutable object as 
const to prevent accidental changes).

***

# TYPECAST OPERATOR (METHOD)
The cast operator as a method of a class in C++ refers to creating a custom type 
conversion operator within a class, allowing an object of the class to be implicitly 
or explicitly converted to another type. This is done by overloading the **operator Type()** 
function, where Type is the target type you want to convert the class object to.

## Syntax
**Define a conversion operator**: The syntax for a type conversion operator in a class is:
```C++
operator target_type() const;
```
- **operator** tells the compiler you're defining a conversion operator
- **target_type** is the type you want to convert to.
- **const** is often used if you're not modifying the object during the conversion

**Example**
```C++
#include <iostream>

class Foo {
    private:
        float _v;
    
    public:
        Foo (float const v) : _v(v) {}
        
        float getV(void)
        {
            return (this->_v);
        }

        //Typecast operator
        operator float()
        {
            return (return -> _v);
        }

        operator int()
        {
            return (static_cast<int>(this->_v));
        }
}

//********************************************************

int main()
{
    Foo   a(420.024f);

    // Thanks to my cast operator, I can initialize a float or int variable directly with my a instance
    float b = a;
    int   c = a;

    std::cout << a.getV() << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;
}
```
Output
```BASH
420.024
420.024
420
```

***

# EXPLICIT KEYWORD
The explicit keyword in C++ is used to prevent the compiler from using certain 
constructors or conversion operators implicitly. This helps avoid unintentional 
conversions and improves code safety and readability. 

You can apply explicit to:
- **Constructors**
- **Conversion Operators**

Using explicit can stop the compiler from performing automatic type conversions, 
which can sometimes lead to unexpected bugs.

## explicit Keyword with Constructors
By default, a constructor with a single parameter **conceptually acts as an implicit conversion constructor** 
(I provide a certain parameter type, and it returns an object of another type—the class type).
This means it can be called automatically to convert an object from one type to 
the type of the class containing the constructor. Marking a constructor as explicit 
disables this implicit behavior.

### Syntax
```C++
class ClassName {
public:
    explicit ClassName(Type param) {
        // Constructor logic
    }
};
```

### Example
```C++
#include <iostream> 

Class A {};
Class B {};

Class C {
    public:
                 C (const A &_) {return;}
        explicit C (const B &_) {return;}
};

//***************************************

void f( const C &_) { return; }

//***************************************

int main()
{
    f (A());  //Implicit conversion  --> OK
              /*(Function f takes a reference to a C object, and I'm passing an A object. 
                The compiler converts the A object into a C objec using this constructor:
                C (const A &_) {return;}) */

    f (B());  //Implicit conversion NOT OK, costructor is explicit
              /*In this case, I must create a C object first and then pass it to the function*/
}
```
**Explanation**
- *class A {}*: Sample class.
- *class B {}*: Sample class.
- *class C {}* This class has two constructors:
    - **C(const A &_)**: This constructor can accept an object of type A and can be called **implicitly**, 
      meaning that the compiler can automatically create an instance of C from an instance of A
    - **explicit C(const B &_)**: This constructor accepts an object of type B but is marked explicit, 
      meaning that **it cannot be called implicitly**. 

- *void f(const C &_)*: This function takes a reference to a const C object. 
  It does not perform any operations in this example, but the important part is 
  how the function can accept different types of arguments.
    - *f(A())*: This line creates a temporary object of type A and tries to pass it to the function f. 
      Because there is a constructor C(const A &_) available (which allows implicit conversion), 
      the compiler creates a temporary C object using the A object and passes it to f. 
      Thus, this line is **valid** and the implicit conversion works fine.

    - *f(B())*: This line creates a temporary object of type B. Here, the compiler 
      looks for a way to convert B into C. However, because the constructor C(const B &_) 
      is marked as explicit, it does not allow implicit conversions. Therefore, 
      this line results in a **compilation error** because the function f cannot 
      accept a B object directly and there is no implicit conversion available.
      Instead, **I must explicitly use the C constructor**
