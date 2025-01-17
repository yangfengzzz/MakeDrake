"""
Produces ideal_stiction.png for contact documentation.
"""

import numpy as np
import pylab as plt


def main():
    f_p = np.array((0, 0, 0, 5))
    f_t = np.array((0, 0.9, 0.7, 0.7))

    plt.plot(f_p, f_t)
    plt.plot(f_p[1], f_t[1], 'ro')
    plt.plot(f_p[2], f_t[2], 'bo')
    plt.text(f_p[1] + 0.1, f_t[1], 'Stiction')
    plt.text((f_p[-2] + f_p[-1]) * 0.5, f_t[-1] + 0.01,
             'Dynamic Friction',
             horizontalalignment='center')
    plt.title('Tangent Force vs. Sliding Velocity (m/s)')
    plt.xlabel('Sliding Velocity (m/s)')
    plt.ylabel('Tangent Force (N)')

    f = plt.gca()
    f.axes.get_xaxis().set_ticks([0])
    f.axes.get_yaxis().set_ticks([0])
    image_file = './ideal_stiction.png'
    plt.savefig(image_file)
    print(f"Created: {image_file}")


assert __name__ == "__main__"
main()
