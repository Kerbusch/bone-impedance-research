import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# =========================================================
# CONFIGURATION
# =========================================================

FOLDERS = {
    "full-drumstick/test3-0": "No fracture",
    "full-drumstick/test3-100": "100% Fracture"
}

OUTPUT_PREFIX = "fracture_comparison_hammer2"

# =========================================================
# LOAD AND AVERAGE DATA
# =========================================================

datasets = []

for folder, label in FOLDERS.items():

    csv_files = sorted(Path(folder).glob("*.csv"))


    if not csv_files:
        print(f"No CSV files found in {folder}")
        continue

    impedance_data = []
    frequency = None

    for csv_file in csv_files:

        df = pd.read_csv(csv_file)

        print(
            csv_file.name,
            len(df)
        )

        if frequency is None:
            frequency = df["frequency"].values

        impedance_data.append(df["impedance"].values)

    impedance_data = np.array(impedance_data)

    mean_impedance = np.mean(impedance_data, axis=0)
    std_impedance = np.std(impedance_data, axis=0)

    datasets.append({
        "label": label,
        "frequency": frequency,
        "mean": mean_impedance,
        "std": std_impedance,
        "n": len(csv_files)
    })

    print(f"{label}: {len(csv_files)} files loaded")

# =========================================================
# IMPEDANCE PLOT
# =========================================================

plt.figure(figsize=(10, 6))

for dataset in datasets:

    plt.plot(
        dataset["frequency"],
        dataset["mean"],
        marker='o',
        label=f"{dataset['label']} (n={dataset['n']})"
    )

    # Optional error bars
    plt.fill_between(
        dataset["frequency"],
        dataset["mean"] - dataset["std"],
        dataset["mean"] + dataset["std"],
        alpha=0.2
    )

# plt.xscale("log")

plt.ticklabel_format(
    style='plain',
    axis='y',
    useOffset=False
)

plt.xlabel("Frequency (Hz)")
plt.ylabel("Impedance (Ohms)")
plt.title("Average Impedance Spectrum")
plt.grid(True)
plt.legend()

plt.ylim(0, 1000)

plt.savefig(
    f"{OUTPUT_PREFIX}_impedance.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()

print("\nSaved:")
print(f"- {OUTPUT_PREFIX}_impedance.png")