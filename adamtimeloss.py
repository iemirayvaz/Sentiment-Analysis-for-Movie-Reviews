import matplotlib.pyplot as plt

def plot_data(file_path):
    times = []
    losses = []

    # Read data from the text file
    with open(file_path, 'r') as file:
        for line in file:
            time, loss = map(float, line.split())
            times.append(time)
            losses.append(loss)

    # Plot the data
    plt.plot(times, losses, label='Loss over time')
    plt.xlabel('Time')
    plt.ylabel('Loss')
    plt.title('Loss over Time')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    file_path = "adamtimeloss.txt"
    plot_data(file_path)
