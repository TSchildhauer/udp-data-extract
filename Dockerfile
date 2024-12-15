# Use an official build environment image
FROM ubuntu:24.04

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install required dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    libssl-dev \
    libboost-all-dev \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy the project files into the container
COPY . /app

# Run CMake to configure the project and fetch dependencies
RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release

# Build the project
RUN cmake --build build

# Specify the entry point or default command
CMD ["build/client1"]