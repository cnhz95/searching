import matplotlib.pyplot as plt
import numpy as np

file = open("/home/christian/Documents/JetBrains/CLionProjects/searching/results.txt", "r")
results = file.readlines()
measurements = 4

time_complexity = ["O(1)", "O(N)", "O(logN)"]
order = [1, 2, 2, 0]

for i in range(measurements):
    elements, time, stddev = ([] for i in range(3))
    title = results[0]

    for x in range(2, 22):
        temp = results[x].split("\t\t\t")
        elements.append(int(temp[0]))
        time.append(float(temp[1]))
        stddev.append(float(temp[2]))

    plt.errorbar(elements, time, yerr=stddev, label=time_complexity[order[i]], ecolor='m', capsize=3)
    plt.title(title)
    plt.xlabel("N elements")
    plt.ylabel("t [s]")
    plt.legend()
    plt.show()

    del results[:23]

file.close()