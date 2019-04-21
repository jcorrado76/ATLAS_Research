import numpy as np
import matplotlib.pyplot as plt


if __name__ == "__main__":
    x = np.linspace(0.0,100.0,10000)
    y = x
    plt.grid(True)
    plt.xlabel(r"$\tau_{\alpha}$=threshold for algorithm $\alpha$")
    plt.ylabel(r"$\tau_{\beta}$=threshold for algorithm $\beta$")
    plt.plot(x,y)
    plt.show()
