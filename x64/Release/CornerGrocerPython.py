import re
import string


'''
STARTER CODE

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v
'''

# The specification explicitly requires THREE functions (as developed)
# They could be replaced with one function with a bunch of flags for
# (1) Whether to look for a specific item
# (2) Whether to print as a histogram or a number
# The last would mean that Python would print the histogram, not C++
# Alternatively, (2) can be whether to export data to a file or not

def FrequencyOf(item):
    with open('CornerGrocerInput.txt', 'r') as inFile: # OPen the file
        data = inFile.read().replace('\n', ' ')
        data = data.split() # Get a list of every entry in the input

        return data.count(item) # Return the count of item in data

def FrequenciesOfItems():
    with open('CornerGrocerInput.txt', 'r') as inFile: # Open the file
        data = inFile.read().replace('\n', ' ')
        data = data.split() # Get a list of every entry in the input
        uniqueItems = [] # Stores unique items

        # Basically, append without duplicates (Useful to print frequencies of all items)
        for item in data:
            if item not in uniqueItems: # If not already appended
                uniqueItems.append(item)

        for item in uniqueItems: # For each item
            line = '{:<15} : {:>3}'.format(item, data.count(item))
            print(line) # Print its name and frequency

def ExportFrequencyData(): # A LOT of reused code to conform with the spec.
    with open('CornerGrocerInput.txt', 'r') as inFile: # OPen the file
        data = inFile.read().replace('\n', ' ')
        data = data.split() # Get a list of every entry in the input
        uniqueItems = [] # Stores unique items

        # Basically, append without duplicates (Useful to print frequencies of all items)
        for item in data:
            if item not in uniqueItems: # If not already appended
                uniqueItems.append(item)

        with open('frequency.dat', 'w') as outFile: # Open the output file
            for item in uniqueItems: # For each item
                line = '{} {}\n'.format(item, data.count(item))
                outFile.write(line) # Write the appropriate data (space-separated)