import matplotlib.pyplot as plt

# Define weight values
weights = [-0.008, 0, 0.008, 0.08, 0.000002]

# Define lists to store accuracies
adamw_accuracies = []
gdw_accuracies = []
sgdw_accuracies = []

def read_accuracy(filename):
  with open(filename, "r") as f:
    accuracy = float(f.read())
  return accuracy

# Read the accuracy data for each algorithm
for i in range(5):
  adamw_file = f"adamw{i+1}accuracy.txt"
  gdw_file = f"gdw{i+1}accuracy.txt"
  sgdw_file = f"sgdw{i+1}accuracy.txt"
  adamw_accuracies.append(read_accuracy(adamw_file))
  gdw_accuracies.append(read_accuracy(gdw_file))
  sgdw_accuracies.append(read_accuracy(sgdw_file))

# Create a single plot
plt.figure(figsize=(10, 6))

# Plot the accuracy for each algorithm
plt.plot(weights, adamw_accuracies, marker='o', linestyle='None', markersize = 20, label="Adam")
plt.plot(weights, gdw_accuracies, marker='v', linestyle='None', markersize = 20, label="GD")
plt.plot(weights, sgdw_accuracies, marker='^', linestyle='None', markersize = 20, label="SGD")

# Add labels, title, and grid
plt.legend()
plt.xlabel('Weights (w)')
plt.ylabel('Accuracy')
plt.title('Accuracy Comparison of Adam, GD, and SGD')
plt.grid(True)

# Save the plot as an image file and print a success message
plt.savefig('algorithm_comparison.png')
plt.show()

print("Single plot generated successfully!")
