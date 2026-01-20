import matplotlib.pyplot as plt

# Import the data from grain_size_times.txt
grain_sizes = []
times = []
with open('grain_size_times.txt', 'r') as file:
    for line in file:
        grain_size, time_taken = line.split()
        grain_sizes.append(int(grain_size))
        times.append(int(time_taken))

# Plot
plt.figure()
plt.plot(grain_sizes, times, marker='o')
plt.xlabel("Grain size")
plt.ylabel("Time taken (microseconds)")
plt.title("Grain size vs Execution Time (1200x1200, 2 cores)")
plt.show()