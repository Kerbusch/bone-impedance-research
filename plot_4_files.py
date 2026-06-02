import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# =========================================================
# FILE CONFIGURATION
# =========================================================

CSV_FILES = [
    "0/sweep_20260602_131656.csv",
    "25/sweep_20260602_132808.csv",
    "50/sweep_20260602_133210.csv",
    "90/sweep_20260602_133957.csv"
]

LABELS = [
    "No fracture",
    "25% Fracture",
    "50% Fracture",
    "90% Fracture",
]

OUTPUT_PREFIX = "comparison"

# =========================================================
# LOAD ALL CSV FILES
# =========================================================

datasets = []

for csv_file, label in zip(CSV_FILES, LABELS):

    df = pd.read_csv(csv_file)

    # Compute phase
    df["phase"] = np.degrees(
        np.arctan2(
            df["imaginary"],
            df["real"]
        )
    )

    datasets.append({
        "label": label,
        "data": df
    })

# =========================================================
# IMPEDANCE PLOT
# =========================================================

plt.figure(figsize=(10, 6))

for dataset in datasets:
    plt.plot(
        dataset["data"]["frequency"],
        dataset["data"]["impedance"],
        marker='o',
        label=dataset["label"]
    )

# plt.xscale('log')

plt.ticklabel_format(
    style='plain',
    axis='y',
    useOffset=False
)

plt.xlabel("Frequency (Hz)")
plt.ylabel("Impedance (Ohms)")
plt.title("Impedance Spectrum")
plt.grid(True)
plt.legend()

plt.savefig(
    f"{OUTPUT_PREFIX}_impedance.png",
    dpi=300,
    bbox_inches='tight'
)

# # =========================================================
# # PHASE PLOT
# # =========================================================
#
# plt.figure(figsize=(10, 6))
#
# for dataset in datasets:
#     plt.plot(
#         dataset["data"]["frequency"],
#         dataset["data"]["phase"],
#         marker='o',
#         label=dataset["label"]
#     )
#
# plt.xscale('log')
#
# plt.xlabel("Frequency (Hz)")
# plt.ylabel("Phase (Degrees)")
# plt.title("Phase Response")
# plt.grid(True)
# plt.legend()
#
# plt.savefig(
#     f"{OUTPUT_PREFIX}_phase.png",
#     dpi=300,
#     bbox_inches='tight'
# )
#
# # =========================================================
# # REAL COMPONENT
# # =========================================================
#
# plt.figure(figsize=(10, 6))
#
# for dataset in datasets:
#     plt.plot(
#         dataset["data"]["frequency"],
#         dataset["data"]["real"],
#         marker='o',
#         label=dataset["label"]
#     )
#
# plt.xscale('log')
#
# plt.xlabel("Frequency (Hz)")
# plt.ylabel("Real")
# plt.title("Real Component")
# plt.grid(True)
# plt.legend()
#
# plt.savefig(
#     f"{OUTPUT_PREFIX}_real.png",
#     dpi=300,
#     bbox_inches='tight'
# )
#
# # =========================================================
# # IMAGINARY COMPONENT
# # =========================================================
#
# plt.figure(figsize=(10, 6))
#
# for dataset in datasets:
#     plt.plot(
#         dataset["data"]["frequency"],
#         dataset["data"]["imaginary"],
#         marker='o',
#         label=dataset["label"]
#     )
#
# plt.xscale('log')
#
# plt.xlabel("Frequency (Hz)")
# plt.ylabel("Imaginary")
# plt.title("Imaginary Component")
# plt.grid(True)
# plt.legend()
#
# plt.savefig(
#     f"{OUTPUT_PREFIX}_imaginary.png",
#     dpi=300,
#     bbox_inches='tight'
# )
#
# # =========================================================
# # NYQUIST PLOT
# # =========================================================
#
# plt.figure(figsize=(8, 8))
#
# for dataset in datasets:
#     plt.plot(
#         dataset["data"]["real"],
#         -dataset["data"]["imaginary"],
#         marker='o',
#         label=dataset["label"]
#     )
#
# plt.xlabel("Real")
# plt.ylabel("-Imaginary")
# plt.title("Nyquist Plot")
# plt.axis('equal')
# plt.grid(True)
# plt.legend()
#
# plt.savefig(
#     f"{OUTPUT_PREFIX}_nyquist.png",
#     dpi=300,
#     bbox_inches='tight'
# )
#
# # =========================================================
# # SHOW ALL PLOTS
# # =========================================================

plt.show()

print("Plots saved:")
print(f"- {OUTPUT_PREFIX}_impedance.png")
# print(f"- {OUTPUT_PREFIX}_phase.png")
# print(f"- {OUTPUT_PREFIX}_real.png")
# print(f"- {OUTPUT_PREFIX}_imaginary.png")
# print(f"- {OUTPUT_PREFIX}_nyquist.png")