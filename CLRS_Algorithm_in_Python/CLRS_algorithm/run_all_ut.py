import os
import unittest

suite = unittest.TestSuite()

for file in os.listdir('.'):
    if file.endswith('.py'):
        if os.path.basename(__file__) == file:
            continue
            
        print('add test in file: ' + file)
        test = unittest.TestLoader().loadTestsFromName(file[:-3])
        suite.addTest(test)

unittest.TextTestRunner().run(suite)

