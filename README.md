# Ecosystem Simulator

A modern behavioral AI ecosystem simulation built from scratch in C++.

This is a complete rewrite of my original thesis project (the messy but fun first C++ attempt). The new version uses **Dear ImGui** for a powerful, interactive interface, allowing real-time tweaking of parameters, creature inspection, live graphs, and much more.

### 🎯 Goal
Create an evolving artificial life environment where creatures with **DNA** compete for resources, reproduce, mutate, and develop complex behaviors over time. Watch natural selection in action as successful traits spread through the population.

### ✨ Features (Planned / In Progress)

- **Genetic System** — Fully customizable DNA with multiple genes (speed, vision range, aggression, size, energy efficiency, mutation rate, etc.)
- **Mutation & Inheritance** — Realistic mutation during reproduction with tunable strength
- **Behavioral AI** — Steering behaviors (seek food, avoid predators, flocking, etc.) influenced by DNA
- **Ecosystem Dynamics** — Herbivores, carnivores, food resources, energy management, death by starvation/age
- **Live ImGui Interface**:
  - Real-time simulation controls (play/pause, speed, reset)
  - Global statistics dashboard
  - Click-to-inspect creature panel (view and even edit DNA live)
  - Population graphs, fitness histograms, gene distribution charts
  - Sliders for mutation rate, food spawn rate, simulation parameters
- **Modern Rendering** — Efficient 2D drawing using OpenGL + ImDrawList
- **High Performance** — Spatial partitioning for handling hundreds to thousands of creatures

### 🛠 Tech Stack

- **Language**: C++20
- **Window & Input**: GLFW
- **Rendering**: OpenGL 3.3+ (core profile)
- **UI**: Dear ImGui (with docking support)
- **Build System**: CMake
- **Dependencies**: GLAD, ImGui (submodule recommended)
