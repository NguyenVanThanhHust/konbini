FROM nvidia/cuda:12.3.2-cudnn9-devel-ubuntu22.04

ARG DEBIAN_FRONTEND=noninteractive
ARG OPENCV_VERSION=4.10.0

RUN apt-get update && apt-get upgrade -y &&\
    # Install build tools, build dependencies and python
    apt-get install -y \
	python3-pip \
        build-essential \
        cmake \
        git \
        wget \
        unzip \
        yasm \
        pkg-config \
        libswscale-dev \
        libtbb2 \
        libjpeg-dev \
        libpng-dev \
        libtiff-dev \
        libavformat-dev \
        libpq-dev \
        libxine2-dev \
        libglew-dev \
        libtiff5-dev \
        zlib1g-dev \
        libavcodec-dev \
        libavutil-dev \
        libpostproc-dev \
        libeigen3-dev \
        libtbb-dev \
        libgtk2.0-dev \
        pkg-config \
        python3-dev \
        python3-numpy \
    && rm -rf /var/lib/apt/lists/*

RUN cd /opt/ &&\
    # Download and unzip OpenCV and opencv_contrib and delte zip files
    wget --no-check-certificate https://github.com/opencv/opencv/archive/$OPENCV_VERSION.zip &&\
    unzip $OPENCV_VERSION.zip &&\
    rm $OPENCV_VERSION.zip &&\
    wget --no-check-certificate https://github.com/opencv/opencv_contrib/archive/$OPENCV_VERSION.zip &&\
    unzip ${OPENCV_VERSION}.zip &&\
    rm ${OPENCV_VERSION}.zip &&\
    # Create build folder and switch to it
    mkdir /opt/opencv-${OPENCV_VERSION}/build && cd /opt/opencv-${OPENCV_VERSION}/build &&\
    # Cmake configure
    cmake \
        -DOPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib-${OPENCV_VERSION}/modules \
        -DWITH_CUDA=ON \
        -DCUDA_ARCH_BIN=7.5,8.0,8.6 \
        -DCMAKE_BUILD_TYPE=RELEASE \
        # Install path will be /usr/local/lib (lib is impli cit)
        -DCMAKE_INSTALL_PREFIX=/usr/local \
        ..
WORKDIR /opt/opencv-${OPENCV_VERSION}/build 
RUN make -j12 && \
    # Install to /usr/local/lib
    make install && \
    ldconfig &&\
    # Remove OpenCV sources and build folder
    rm -rf /opt/opencv-${OPENCV_VERSION} && rm -rf /opt/opencv_contrib-${OPENCV_VERSION}
    
RUN python3 -m pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org "pybind11[global]"
RUN python3 -m pip install --trusted-host pypi.org --trusted-host files.pythonhosted.org pytest

RUN apt update && apt install -y vim fish libboost-all-dev
WORKDIR /opt/
RUN git config --global http.sslVerify false && git clone https://github.com/stotko/stdgpu && git config --global http.sslVerify true
WORKDIR /opt/stdgpu
RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=RELEASE
RUN cmake --build build --config Release --parallel 8
RUN cmake --install build --config Release

WORKDIR /workspace/