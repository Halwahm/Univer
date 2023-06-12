import numpy as np
import matplotlib.pyplot as plt

# Определим функцию f(x)
def f(x):
    if x >= 0 and x <= np.pi:
        return (np.pi - x) / 2
    else:
        return 0

# Вычислим коэффициенты a0, an и bn
a0 = (1 / np.pi) * np.sum([f(x) for x in np.linspace(-np.pi, np.pi, 1000)])
an = lambda n: (1 / np.pi) * np.sum([f(x) * np.cos(n * x) for x in np.linspace(-np.pi, np.pi, 1000)])
bn = lambda n: (1 / np.pi) * np.sum([f(x) * np.sin(n * x) for x in np.linspace(-np.pi, np.pi, 1000)])

# Вычислим сумму ряда Фурье для заданного числа слагаемых N
def fourier_series(x, N):
    s = a0
    for n in range(1, N+1):
        s += an(n) * np.cos(n * x) + bn(n) * np.sin(n * x)
    return s

# Построим график функции и нескольких частичных сумм ряда Фурье
x = np.linspace(-np.pi, np.pi, 1000)
plt.plot(x, [f(x) for x in x], label='f(x)')
plt.plot(x, [fourier_series(x, 1) for x in x], label='N=1')
plt.plot(x, [fourier_series(x, 3) for x in x], label='N=3')
plt.plot(x, [fourier_series(x, 5) for x in x], label='N=5')
plt.legend()
plt.show()
