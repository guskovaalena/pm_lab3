import random
import matplotlib.pyplot as plt

n = 100000

data = [
    random.random()
    for _ in range(n)
]

plt.figure(figsize=(8, 6))

plt.hist(
    data,
    bins=50
)

plt.xlabel("Value")
plt.ylabel("Frequency")

plt.title(
    "Distribution Histogram"
)

plt.grid(True)

plt.tight_layout()

plt.savefig(
    "../distribution_plot.png",
    dpi=300
)

print("distribution_plot.png saved")