# Use an official build environment image
FROM ubuntu:24.04 AS build

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

# Create a smaller runtime image
FROM ubuntu:24.04

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install only the runtime dependencies
RUN apt-get update && apt-get install -y \
    libssl-dev \
    libboost-system1.81.0 \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy the built project from the build stage
COPY --from=build /app/build/client1 /app/client1

# Specify the entry point to handle signals properly
ENTRYPOINT ["/app/client1"]
