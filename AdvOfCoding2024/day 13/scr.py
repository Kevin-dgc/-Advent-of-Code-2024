import numpy as np

def simToken():
    a = np.array([[1, 2], [3,5]])
    b = np.array([1, 2])
    x = np.linalg.solve(a, b)
    return x


def main():
    print(simToken())
    
    
main()