
# A script to run cppcheck with the necessary 
# command-line options.

from os import system
import sys

COLOR_RESET = "\033[0m"
COLOR_BOLD_RED = "\033[1m\033[31m"

def printError(msg : str):
    print(COLOR_BOLD_RED + "FATAL ERROR: " + COLOR_RESET + msg, file=sys.stderr)

# Tests that can be performed are:
# -> error
# -> warning
# -> style
# -> performance
# -> portability
# -> information
# -> all
OPTIONS = "--inconclusive --inline-suppr --enable=warning --enable=style --enable=performance --enable=portability "

system("color")
sys.argv.remove(sys.argv[0]) # Remove the name of the program

logFile = open("./error.log", "w")
logFile.close()

if len(sys.argv) == 0:
    printError("No arguments given.")

for arg in sys.argv:
    system("cppcheck " + OPTIONS + arg + " >> error.log 2>&1")
    
    
