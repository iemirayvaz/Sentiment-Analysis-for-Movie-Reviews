import numpy as np
import matplotlib.pyplot as plt
from sklearn.manifold import TSNE

def load_weights(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
        indices = []
        weights = []
        for line in lines:
            data = line.strip().split()
            indices.append(int(data[0]))
            weights.append(list(map(float, data[1:])))
        return np.array(indices), np.array(weights)

init_values = [-0.008, 0, 0.008, 0.08, 0.000002]
file_paths = ['weightplot1.txt', 'weightplot2.txt', 'weightplot3.txt', 'weightplot4.txt', 'weightplot5.txt']

plt.figure(figsize=(10, 8))
for i, file_path in enumerate(file_paths):
    indices, weights = load_weights(file_path)

    tsne = TSNE(n_components=2, random_state=42)
    reduced_weights = tsne.fit_transform(weights)

    plt.plot(reduced_weights[:, 0], reduced_weights[:, 1], label=f'Initialization {i+1}: {init_values[i]}')

plt.xlabel('t-SNE Dimension 1')
plt.ylabel('t-SNE Dimension 2')
plt.title('t-SNE Visualization of Weight Trajectories')
plt.legend()
plt.show()