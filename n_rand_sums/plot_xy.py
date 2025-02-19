#!/usr/bin/env python3
import plotly.graph_objects as go
from plotly.subplots import make_subplots
import sys
import math

data = sys.stdin.read()

# Split data into lines
lines = data.strip().split('\n')

# Initialize variables
subplots = []
current_subplot = {'title': '', 'data': [], 'axis_labels': []}

# Read data into subplots
for line in lines:
    if line.startswith('!'):  # Subplot description
        if current_subplot['title']:
            subplots.append(current_subplot)
            current_subplot = {'title': '', 'data': [], 'axis_labels': []}
        current_subplot['title'] = line.lstrip('!')
    elif line.startswith('#'):  # Axis labels
        axis_labels = line.lstrip('#').split(',')
        if len(axis_labels) == 2:
            current_subplot['axis_labels'] = axis_labels
    elif line == '':  # End of subplot
        subplots.append(current_subplot)
        current_subplot = {'title': '', 'data': [], 'axis_labels': []}
    else:  # Data points
        values = line.strip().split(',')
        if len(values) == 2:
            try:
                x, y = float(values[0]), float(values[1])
                current_subplot['data'].append((x, y))
            except ValueError:
                print(f"Skipping line: Invalid numeric values")

# Add last subplot
if current_subplot['title']:
    subplots.append(current_subplot)

# Calculate rows and columns
rows = math.ceil(len(subplots) / 2)
cols = 2

# Create Plotly figure with subplots
fig = make_subplots(rows=rows, cols=cols, subplot_titles=[subplot['title'] for subplot in subplots])

# Add subplots
for i, subplot in enumerate(subplots):
    x_values = [point[0] for point in subplot['data']]
    y_values = [point[1] for point in subplot['data']]
    row = (i // 2) + 1
    col = (i % 2) + 1
    fig.add_trace(go.Scatter(x=x_values, y=y_values), row=row, col=col)
    if subplot['axis_labels']:
        fig.update_xaxes(title_text=subplot['axis_labels'][0], row=row, col=col)
        fig.update_yaxes(title_text=subplot['axis_labels'][1], row=row, col=col)

# Show plot
fig.show()
