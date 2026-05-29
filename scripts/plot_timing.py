import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("../timing_results.csv")

plt.figure(figsize=(10, 6))

for gen in df["generator"].unique():

    subset = df[df["generator"] == gen]

    plt.plot(
        subset["n"],
        subset["time_ms"],
        marker="o",
        label=gen
    )

plt.xscale("log")

plt.xlabel("Sample size")
plt.ylabel("Time (ms)")

plt.title(
    "RNG Performance Comparison"
)

plt.grid(True)

plt.legend()

plt.tight_layout()

plt.savefig(
    "../timing_plot.png",
    dpi=300
)

print("timing_plot.png saved")