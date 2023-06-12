import numpy as np


def test1():
    "matrix"
    a = np.mat([[1, 2], [3, 4]])
    b = np.mat([[1, 3], [5, 7]])

    print(a)
    print(a.shape)


def get2dReverse(theMat: np.matrix):
    "获取2d矩阵的逆"
    a = theMat[0, 0]
    b = theMat[0, 1]
    c = theMat[1, 0]
    d = theMat[1, 1]

    left = 1/(a*d-b*c)
    right = np.mat([[d, -b], [-c, a]])

    return left * right


def test2():
    m1 = np.matrix([[1, 2], [3, 4]])
    print(m1)

    theReverse = get2dReverse(m1)
    print(theReverse)

    I = m1*theReverse
    print(I)


# Gauss求逆
