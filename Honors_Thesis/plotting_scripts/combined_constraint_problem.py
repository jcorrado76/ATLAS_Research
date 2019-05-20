if __name__ == "__main__":
    import numpy as np
    import matplotlib.pyplot as plt
    x = np.linspace(0.0,100.0,10000)
    y = x
    y2 = -x**2/100 + 100
    sol = 50 * (np.sqrt(5.0)-1.0)
    plt.grid(True)
    plt.xlabel(r"$f(\tau_{\alpha})$=fraction kept at threshold for algorithm $\alpha$")
    plt.ylabel(r"$f(\tau_{\beta})$= fraction kept at threshold for algorithm $\beta$")
    plt.scatter(sol,sol,c='g',s=200,zorder=4)
    plt.plot(x,y,label='Individual Fractions are Equal Constraint',color='black')
    plt.plot(x,y2,label='Possibility Production Frontier',color='red')
    plt.text(50,80,r"$f(\tau_{\alpha},\tau_{\beta})=C$",fontsize=14,color='red')
    plt.text(50,45,r"$f(\tau_{\alpha})=f(\tau_{\beta})$",fontsize=14)
    plt.title("Solution to Compute Thresholds") 
    plt.savefig("../img/combined_constraint_plot.png",format='png',dpi=100)
    plt.show()
