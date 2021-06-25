# Project Summary
The CornerGrocer program analyses the purchases and presents the data in an easy-to-read format. It reads the number of times the items were purchased and displays a table or a histogram (using * = 1 item scale) of purchases, and also allows the user to search through the list for a specific item.

# What Worked Well
I think the program integrates (x64) Python with C++ fairly well and is organised well enough to separate the various steps of the process. The C++ functions that call functions from the Python script are highly reusable with little modification, and facilitate both calling with and without arguments. The tasks are divided well between C++ and Python, because Python has a built-in function to find the number of occurrences of an item in a list.

# Scope for Improvement
The two major parts that could be improved are the search feature, which is currently case-sensitive, which can be made case-insensitive, and the other is a redesign, where the entire Python code could be structured as one function with two flags (whether to search for one item or all items, and whether to display numbers or a histogram) instead of three functions. However, this would mean that the histogram would be printed from Python and not C++, as mentioned in the specification.

# Challenges
I did not face many challenges in writing this program, because I had worked with C++ and Python before. However, structuring the program in accordance with the specification (as three separate functions) was an important thing I had to keep in mind, as the one-function solution seemed more intuitive to me given the requirements.
In the present form, one of the Python functions exports the data as a .dat file, which is read by C++. I had to change the loop condition from while(f) to using the stream operator as while(f >> name >> quantity) because the former printed the last line twice. The only tools I relied on were my own knowledge of the languages and IntelliSense to speed up development and identify an occasional typo.

# Important Skills
The focus of this program was embedding Python in C++, which can be useful for a number of other programs where some of the steps involve something that Python is better at doing. Similarly, other programming languages could be embedded too; calling a C++ script from within a Java program is another example that may be useful. This effectively allows the programmer to use the best of both worlds when developing a program.

# Maintainability, Readability, Adaptability
The program's modular design makes it maintainable, readable, and adaptable. Three Python functions that do three separate tasks (search all, search one, store data) and a C++ function that displays the histogram separate the tasks to be performed at various steps.
Because the three Python functions reuse a lot of code, I think that the alternate design proposed above (one function with two flags) will be more concise and readable, except that it would get rid of the C++ function to print the histogram entirely.
The code is largely adaptable because the C++ functions to call procedures from Python scripts, optionally with arguments, can be used with any Python script set up similarly. Adhering to naming conventions also makes the code easy to follow.
