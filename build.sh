#!/bin/bash

# Create build directory if it doesn't exist
mkdir -p build

# Navigate to build directory
cd build

# Run cmake to configure the project
cmake ..

# Build the project using all available cores
make -j$(nproc)

echo "Build complete! Run the application with: ./build/bin/ACT"
