from matplotlib import pyplot as plt

files = ['0_test', '1_test', '2_test', '3_test', '4_test']

for file in files:
    with open(file, 'r') as f:
        x = list(map(float, f.readline().split()))
        y = list(map(float, f.readline().split()))
        predictoin = list(map(float, f.readline().split()))
        plt.figure()
        plt.plot(x, y)
        plt.plot(x, predictoin)
        plt.savefig(file)
