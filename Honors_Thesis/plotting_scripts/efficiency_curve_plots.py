import numpy as np
import matplotlib.pyplot as plt
import scipy.stats as stats


if __name__ == "__main__":
    x = np.linspace(0.0,100.0,10000)
    thresh = 30.
    plt.plot(x, stats.expon.pdf(x,scale=thresh),label='Background',color='blue')
    plt.plot(x, stats.norm.pdf(x,
    loc=thresh,scale=thresh),label='Signal',color='red')
    plt.legend()
    plt.axvline(thresh,color='k',linestyle='dashed')
    plt.annotate(r'$x_{\tau}$ = MET Threshold',xy=(thresh,0.0),fontsize=16,
            xytext=(thresh+5,0.004),arrowprops={'facecolor':'black','linewidth':0.5})
    plt.ylim(0.0,0.05)
    plt.xlabel("CELL MET [GeV] (True MET)")
    plt.show()

