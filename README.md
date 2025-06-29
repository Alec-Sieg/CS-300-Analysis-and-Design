# CS-300-Analysis-and-Design

Project Overview 
This portfolio demonstrates my work analyzing and implementing data structures for a Computer Science course planning system that manages course information, prerequisites, and provides efficient data retrieval for academic advising.

Portfolio Artifiacs
Runtime and Memory Analysis - Comparative analysis of Vector, Hash Table, and Binary Search Tree
Course Planning System - C++ implementation using hash table for optimal performance

Project Reflection
Problem: I needed to create a system for managing CS course data with efficient lookup, prerequisite validation, and alphabetical listing capabilities.
Approach: I analyzed three data structures comparing runtime complexity. Understanding data structures was crucial because choice directly impacts performance - vectors give O(n²×p) for prerequisite validation while hash tables achieve O(n×p). I chose hash tables for O(1) average lookup time.
Roadblocks: Main challenges included robust file parsing and C++ string handling. I overcame these with two-pass validation (load courses, then validate prerequisites) and careful use of STL containers with proper error handling.
Software Design Evolution: This project taught me to prioritize algorithmic complexity analysis before implementation. I now consider Big O notation for different approaches and design for scalability from the beginning, implementing defensive programming with input validation.
Programming Practice Evolution: My code now emphasizes maintainability through modular design - the CourseHashTable class encapsulates operations for easier testing and modification. I use consistent naming, comprehensive commenting, and STL containers for more readable, error-resistant code.
