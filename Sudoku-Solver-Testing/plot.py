import pandas as pd
import matplotlib.pyplot as plt

# Read CSV data
df = pd.read_csv("../data/output_average.csv")

# Plot with logarithmic y-axis
plt.figure(figsize=(10, 6))
plt.plot(df['key'], df['solving_time_ms'], label='Solving Time (ms)')
plt.yscale('log')
plt.xlabel("Key")
plt.ylabel("Solving Time (log scale)")
plt.title("Solving Time vs Key (Log Scale)")
plt.legend()
plt.grid(True)
plt.show()