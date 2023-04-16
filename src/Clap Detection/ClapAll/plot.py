import matplotlib.pyplot as plt
import numpy as np

# Open the file for reading
filename = "vector_file.txt"
with open(filename) as f:
    data = f.readlines()

# Remove whitespace and convert to floats
data = [float(x.strip()) for x in data]

# Convert the list to a numpy array
data = np.array(data)
print(data)

# Plot the data using Gnuplot
plt.plot(data)
plt.show()
