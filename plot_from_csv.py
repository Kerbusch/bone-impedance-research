import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from pathlib import Path

# =========================================================
# FILE CONFIGURATION
# =========================================================

CSV_FILE = "sweep_20260528_114405.csv"

# Get filename without extension
base_filename = Path(CSV_FILE).stem

# =========================================================
# LOAD CSV
# =========================================================

df = pd.read_csv(CSV_FILE)

# =========================================================
# COMPUTE PHASE
# =========================================================

df["phase"] = np.degrees(
    np.arctan2(
        df["imaginary"],
        df["real"]
    )
)

# =========================================================
# IMPEDANCE PLOT
# =========================================================

plt.figure(figsize=(10, 6))

plt.plot(
    df["frequency"],
    df["impedance"],
    marker='o'
)

plt.xscale('log')

plt.ticklabel_format(
    style='plain',
    axis='y',
    useOffset=False
)

plt.xlabel("Frequency (Hz)")
plt.ylabel("Impedance (Ohms)")
plt.title("Impedance Spectrum")

plt.grid(True)

plt.savefig(
    f"{base_filename}_impedance.png",
    dpi=300,
    bbox_inches='tight'
)

# =========================================================
# PHASE PLOT
# =========================================================

plt.figure(figsize=(10, 6))

plt.plot(
    df["frequency"],
    df["phase"],
    marker='o'
)

plt.xscale('log')

plt.xlabel("Frequency (Hz)")
plt.ylabel("Phase (Degrees)")
plt.title("Phase Response")

plt.grid(True)

plt.savefig(
    f"{base_filename}_phase.png",
    dpi=300,
    bbox_inches='tight'
)

# =========================================================
# REAL COMPONENT
# =========================================================

plt.figure(figsize=(10, 6))

plt.plot(
    df["frequency"],
    df["real"],
    marker='o'
)

plt.xscale('log')

plt.xlabel("Frequency (Hz)")
plt.ylabel("Real")
plt.title("Real Component")

plt.grid(True)

plt.savefig(
    f"{base_filename}_real.png",
    dpi=300,
    bbox_inches='tight'
)

# =========================================================
# IMAGINARY COMPONENT
# =========================================================

plt.figure(figsize=(10, 6))

plt.plot(
    df["frequency"],
    df["imaginary"],
    marker='o'
)

plt.xscale('log')

plt.xlabel("Frequency (Hz)")
plt.ylabel("Imaginary")
plt.title("Imaginary Component")

plt.grid(True)

plt.savefig(
    f"{base_filename}_imaginary.png",
    dpi=300,
    bbox_inches='tight'
)

# =========================================================
# NYQUIST PLOT
# =========================================================

plt.figure(figsize=(8, 8))

plt.plot(
    df["real"],
    -df["imaginary"],
    marker='o'
)

plt.xlabel("Real")
plt.ylabel("-Imaginary")
plt.title("Nyquist Plot")

plt.axis('equal')

plt.grid(True)

plt.savefig(
    f"{base_filename}_nyquist.png",
    dpi=300,
    bbox_inches='tight'
)

# =========================================================
# SHOW ALL PLOTS
# =========================================================

plt.show()

print("Plots saved:")
print(f"- {base_filename}_impedance.png")
print(f"- {base_filename}_phase.png")
print(f"- {base_filename}_real.png")
print(f"- {base_filename}_imaginary.png")
print(f"- {base_filename}_nyquist.png")