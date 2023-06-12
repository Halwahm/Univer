import numpy as np
import scipy.integrate as spi
import scipy.special as sps
import matplotlib.pyplot as plt

# Задаем функцию f(x)
def f(x):
    return np.where(x < 0, 0, np.where(x > 0, (np.pi - x) / 2, 0))

# Функция для вычисления коэффициентов ряда Фурье по многочленам Лежандра
def an(n):
    return (2*n + 1) / 2 * spi.fixed_quad(lambda x: f(x) * sps.legendre(n)(x), -1, 1)[0]

# Вычисляем первые N коэффициентов ряда Фурье по многочленам Лежандра
N = 50
coeffs = [an(n) for n in range(N)]
print(coeffs)

# Функция для вычисления частичной суммы ряда Фурье по многочленам Лежандра
def partial_sum(x, coeffs, n):
    s = 0
    for k in range(n):
        s += coeffs[k] * sps.legendre(k)(x)
    return s

# Строим график функции и нескольких частичных сумм ряда Фурье
x = np.linspace(-1, 1, 100)
y = [f(x_i) for x_i in x]
plt.plot(x, y, label='f(x)')
for n in [50]:
    y_n = [partial_sum(x_i, coeffs, n) for x_i in x]
    plt.plot(x, y_n, label=f'n={n}')
plt.legend()
plt.show()