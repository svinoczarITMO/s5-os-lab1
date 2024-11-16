# Use the official Fedora base image
FROM fedora:latest

# Install necessary packages
RUN dnf -y update && \
    dnf -y install \
    gcc-c++ \
    make \
    git \
    perf \
    perl \
    && dnf clean all

# Install flamegraph
RUN git clone https://github.com/brendangregg/FlameGraph.git /usr/local/FlameGraph

# Copy the necessary files from the host to the container
COPY shell.cpp /usr/local/src/shell.cpp
COPY stress/bench1.cpp /usr/local/src/bench1.cpp
COPY stress/bench2.cpp /usr/local/src/bench2.cpp
COPY stress/combined.cpp /usr/local/src/combined.cpp

# Set the working directory
WORKDIR /usr/local/src

# Compile the source files
RUN g++ -o shell shell.cpp
RUN g++ -o bench1 bench1.cpp
RUN g++ -o bench2 bench2.cpp
RUN g++ -o combined combined.cpp

# Set the default command to run
CMD ["bash"]

