import serial
import pandas as pd
import matplotlib.pyplot as plt
from datetime import datetime

# =====================================================
# CONFIG
# =====================================================

PORT = "COM3"          # Change this
BAUDRATE = 115200

# =====================================================
# SERIAL CONNECTION
# =====================================================

ser = serial.Serial(PORT, BAUDRATE, timeout=1)

print(f"Connected to {PORT}")

# =====================================================
# DATA STORAGE
# =====================================================

data = []

capture = False

# =====================================================
# READ SERIAL DATA
# =====================================================

while True:

    try:

        line = ser.readline().decode("utf-8").strip()

        if not line:
            continue

        print(line)

        # ---------------------------------------------
        # START OF SWEEP
        # ---------------------------------------------

        if line == "SWEEP_START":

            print("Starting capture...")

            data = []

            capture = True

            continue

        # ---------------------------------------------
        # END OF SWEEP
        # ---------------------------------------------

        if line == "SWEEP_DONE":

            print("Sweep complete.")

            break

        # ---------------------------------------------
        # CSV HEADER
        # ---------------------------------------------

        if line.startswith("frequency"):
            continue

        # ---------------------------------------------
        # DATA ROWS
        # ---------------------------------------------

        if capture:

            parts = line.split(",")

            if len(parts) != 5:
                continue

            frequency = float(parts[0])
            real = float(parts[1])
            imaginary = float(parts[2])
            magnitude = float(parts[3])
            impedance = float(parts[4])

            data.append([
                frequency,
                real,
                imaginary,
                magnitude,
                impedance
            ])

    except KeyboardInterrupt:

        print("Stopped by user.")

        break

    except Exception as e:

        print(f"Error: {e}")

# =====================================================
# CLOSE SERIAL
# =====================================================

ser.close()

# =====================================================
# CREATE DATAFRAME
# =====================================================

df = pd.DataFrame(
    data,
    columns=[
        "frequency",
        "real",
        "imaginary",
        "magnitude",
        "impedance"
    ]
)

# =====================================================
# SAVE CSV
# =====================================================

timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")

csv_filename = f"sweep_{timestamp}.csv"

df.to_csv(csv_filename, index=False)

print(f"Saved CSV: {csv_filename}")

# =====================================================
# PLOT
# =====================================================

plt.figure(figsize=(10, 6))

plt.plot(
    df["frequency"],
    df["impedance"]
)

plt.ticklabel_format(style='plain', axis='y', useOffset=False)
plt.xlabel("Frequency (Hz)")
plt.ylabel("Impedance (Ohms)")
plt.title("Impedance Sweep")

plt.grid(True)

# safe plot as "sweep_timestamp.png"
plot_filename = f"sweep_{timestamp}.png"

plt.savefig(
    plot_filename,
    dpi=300,
    bbox_inches='tight'
)

print(f"Saved plot: {plot_filename}")

plt.show()

# plot phase
import numpy as np

df["phase"] = np.degrees(
    np.arctan2(
        df["imaginary"],
        df["real"]
    )
)