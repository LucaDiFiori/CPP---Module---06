# EX01
- [UNDERSTANDING THE PROBLEM: SERIALIZATION](#understanding-the-problem-serialization)
- [EX01 ROADMAP](#ex01-roadmap)

***
***

# UNDERSTANDING THE PROBLEM: SERIALIZATION
The exercise of converting a pointer to a uintptr_t and back is often used to understand how pointers can be stored as plain numbers for various reasons. Let me explain each part:

## Why Convert a Pointer to uintptr_t?
Converting a pointer to an integer type like uintptr_t is useful in situations where you want to:

- **Store or transmit a pointer as a numeric value**: Sometimes, you may want to store a pointer in a structure or send it over a network as raw data. Converting it to an integer type allows for that, as integer types are often easier to handle than pointers in these contexts.

- **Avoid direct use of pointers**: If your code needs to pass around references to objects but not access them directly, you can use uintptr_t to act as a "safe handle" to the object. Then, other parts of your code can reconstruct the pointer only when needed.

- **Interoperate with low-level systems**: In low-level systems programming or when interacting with hardware, using raw memory addresses as integers can be helpful for memory manipulation, and uintptr_t allows for that kind of low-level control.

In this exercise, converting to uintptr_t is a way to understand how pointers work at a low level and to practice using reinterpret_cast.

## What is uintptr_t?
**uintptr_t** is an **unsigned integer type designed to hold a pointer**. It guarantees enough storage capacity to store any pointer value, regardless of the system architecture.

- The uintptr_t type provides a platform-independent way of representing pointers as integers. For example, on a 64-bit system, uintptr_t will be a 64-bit integer, but on a 32-bit system, it will be a 32-bit integer.

- Unlike plain integers, uintptr_t specifically ensures that you can safely store a pointer in it without losing information or misinterpreting it. It is unsigned, which means it cannot represent negative values, but pointers in memory are non-negative addresses anyway, so this matches well.

## Practical Applications
In real-world code, this kind of pointer-to-integer conversion is occasionally used in:
- **Serialization libraries**: When serializing an object for storage or transmission, pointers may need to be stored as integers for reassembly later.
- **Operating system development**: Systems like kernels and drivers often manipulate memory directly and use integer representations of addresses when interacting with hardware or low-level APIs.
- **Interfacing with C-style APIs**: Some C-style APIs require pointers to be passed as integer IDs (for instance, for callbacks or context pointers).



## Understanding Serialization of Pointers
Serialization is the process of converting an object into a format that can be easily stored (e.g., in a file) or transmitted (e.g., over a network). When serializing simple data like integers or strings, you can directly save their values. However, pointers are more complex:

- **Pointers Represent Memory Addresses**: A pointer contains a memory address that points to an object in memory. This address is specific to the current runtime session and will likely not be the same when you reload or reconstruct the object from storage.
- **Pointers Need Special Handling**: If an object has pointers to other objects, you need a way to preserve the relationships (e.g., which objects point to which others) when serializing. Simply saving the raw memory addresses doesn’t work because they will not be valid when deserialized into a different memory space.


## Why Use uintptr_t for Serialization?
In some serialization libraries or systems, pointers are temporarily converted to an integer type like uintptr_t for serialization purposes. Here’s why and how this approach helps:

1. **Encoding Pointers as Numbers**: By converting a pointer to an integer, the pointer becomes a numeric value that can be stored just like any other data. This integer representation can then be serialized along with the rest of the object’s data. This is where uintptr_t is helpful because it guarantees that the integer can fully represent any pointer value on the platform.

2. **Tracking Relationships**: When serializing complex objects with multiple pointers, converting each pointer to an integer allows you to track the relationships. For example:
	- Each object can be given a unique integer ID, stored in place of the original pointers.
	- You can serialize these integer IDs, then later rebuild the exact pointer structure when deserializing by mapping the IDs back to new memory locations or objects.

3. **Reassembly During Deserialization**: When deserializing, the integer representation of the pointer (like uintptr_t) helps in reconstructing the original structure:
	- The serialization library reads the integer values and recreates the pointers in a new memory space, mapping IDs back to their deserialized objects.
	- This approach allows the deserialized object to maintain the same structure and relationships as the original.

## Summary
In this exercise, converting a pointer to a uintptr_t is a way to simulate what happens when you serialize a memory address, letting you store and retrieve the pointer as a raw number. It demonstrates how memory addresses work and how pointers can be treated as numbers,

***
***

# EX01 ROADMAP
For this exercise, you’ll need to create a **data structure**, such as a struct, with some data members. This structure will serve as the "Data" that you’ll serialize and deserialize using the Serializer class.

Here’s a quick overview of what you need to do:

1. **Define the Data structure**: Create a **struct** with some **non-empty fields** (e.g., an integer, a character, a float). This will allow you to verify that serialization and deserialization work correctly by checking that the original pointer and deserialized pointer point to the same Data object.

2. **Implement the Serializer class**: This class will contain two static methods:
	- **serialize(Data* ptr)**: Converts a Data pointer to uintptr_t.
	- **deserialize(uintptr_t raw)**: Converts a uintptr_t integer back to a Data* pointer.

3. **Write a test**: Create a Data instance, use Serializer::serialize() to convert its pointer to an integer, and then use Serializer::deserialize() to convert it back to a pointer. Verify that the returned pointer is the same as the original pointer to confirm that serialization and deserialization are working.

## why use reinterpret_cast
The reinterpret_cast operator is used in C++ for casting one type to a fundamentally different type—in this case, casting a pointer to an integer type and vice versa.

1. **Casting Between Incompatible Types**:
	- reinterpret_cast allows you to cast between types that are fundamentally different, such as from a pointer type (Data*) to an integer type (uintptr_t), or vice versa.
	- Unlike static_cast, which is used for more “related” types (like casting between base and derived classes), reinterpret_cast handles conversions between unrelated types by reinterpreting the underlying bits.

2. **Memory Address Conversion**:
	- When you use reinterpret_cast to cast a pointer to uintptr_t, you’re treating the pointer’s memory address as a plain integer without changing its bits. This is ideal for serialization, where you want to store the raw address temporarily as a number, without modifying the actual pointer.

3. **Round-Trip Compatibility**:
	- Casting a Data* to uintptr_t and then back to Data* is safe with reinterpret_cast because it preserves the original bit pattern. So, when you cast back to Data*, you get the same memory address.
	- This round-trip conversion (pointer → uintptr_t → pointer) is important in the exercise to ensure that deserialize(serialize(ptr)) returns the same pointer value as ptr.