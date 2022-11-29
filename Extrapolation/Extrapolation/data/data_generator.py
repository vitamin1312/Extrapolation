import numpy as np
from matplotlib import pyplot as plt
np.random.seed(42)

x = np.linspace(-5, 5, 30)
functions = [lambda x: np.sin(x),
             lambda x: np.log(abs(x)),
             lambda x: np.random.randint(-1, 1),
             lambda x: (x-15)*(x+4)*(x-3)*(x+2)*(x-1) / 1000,
             lambda x: (x-5)*(x+5)*(x-1)/30 + np.random.randint(-1, 1)
            ]

for count, func in enumerate(functions):
    with open(str(count), 'w') as f:
        for elem in x[:-1]:
            f.write(str(elem) + ' ')
        f.write(str(x[-1]) + '\n')

        for elem in x[:-1]:
            f.write(str(func(elem)) + ' ')
        f.write(str(func(x[-1])) + '\n')



files = [str(i) for i in range(len(functions))]

for file in files:
    with open(file, 'r') as f:
        x = list(map(float, f.readline().split()))
        y = list(map(float, f.readline().split()))

        plt.figure()
        plt.plot(x, y)
        plt.savefig(file)
