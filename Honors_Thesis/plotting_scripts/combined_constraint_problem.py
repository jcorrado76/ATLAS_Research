
import numpy as np
import matplotlib.pyplot as plt


if __name__ == "__main__":
    x = np.linspace(0.0,100.0,10000)
    y = x
    y2 = -x**2/100 + 100
    plt.grid(True)
    plt.xlabel(r"$\tau_{\alpha}$=threshold for algorithm $\alpha$")
    plt.ylabel(r"$\tau_{\beta}$=threshold for algorithm $\beta$")
    plt.plot(x,y,label='Individual Fractions are Equal Constraint',color='black')
    plt.plot(x,y2,label='Possibility Production Frontier',color='red')
    plt.legend()
    plt.show()
