import numpy as np
from matplotlib import pyplot as plt
np.random.seed(42)

x = np.linspace(-20, 30, 50)

y0 = np.sin(x) + np.random.normal(0, 0.5, 50)
y1 = (x-15)*(x+4)*(x-3)*(x+2)*(x-1) / 1000 + np.random.normal(0, 60, 50)
y2 = (x-5)*(x+5)*(x-1)/30 + np.random.normal(0, 150, 50)
y3 = 0.01*x + np.random.normal(0, 6, 50)

y_all = [y0, y1, y2, y3]


for count, y in enumerate(y_all):
    with open(str(count), 'w') as f:
        for elem in x[:-1]:
            f.write(str(elem) + ' ')
        f.write(str(x[-1]) + '\n')

        for elem in y[:-1]:
            f.write(str(elem) + ' ')
        f.write(str(y[-1]) + '\n')



files = ['0', '1', '2', '3', '4']

for file in files:
    with open(file, 'r') as f:
        x = list(map(float, f.readline().split()))
        y = list(map(float, f.readline().split()))

        plt.figure()
        plt.plot(x, y)
        plt.savefig(file)
