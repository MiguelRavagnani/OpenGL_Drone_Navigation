FROM ubuntu:20.04

RUN mkdir /home/opengl
WORKDIR /home/opengl

COPY . .

RUN ln -snf /bin/bash /bin/sh

RUN : \
    && apt-get update \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        software-properties-common \
    && add-apt-repository -y ppa:deadsnakes \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        python3.8-venv \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && :

RUN python3.8 -m venv /venv
ENV PATH=/venv/bin:$PATH

RUN apt-get update \
    && apt-get install git -y \
    && apt-get install wget -y \
    && apt-get install build-essential -y \
    && apt-get install libssl-dev -y

RUN apt-get install gcc-7 g++-7 g++-7-multilib gfortran-7 -y \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
    && update-alternatives --config gcc \
    && echo `gcc --version | grep ^gcc | sed 's/^.* //g'`

RUN wget http://www.cmake.org/files/v3.23/cmake-3.23.2.tar.gz
RUN tar xzf cmake-3.23.2.tar.gz 
WORKDIR /home/opengl/cmake-3.23.2
RUN ./bootstrap
RUN make
RUN make install

WORKDIR /home/opengl/vendor/emsdk
RUN python -X utf8 emsdk.py install 3.1.12
RUN python -X utf8 emsdk.py activate 3.1.12
RUN chmod +x emsdk_env.sh
RUN source  /home/opengl/vendor/emsdk/emsdk_env.sh

WORKDIR /home/opengl

RUN apt-get install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev extra-cmake-modules vim -y

RUN source  /home/opengl/vendor/emsdk/emsdk_env.sh \
   && cd /home/opengl \
   && mkdir build_emscripten \
   && cd build_emscripten \
   && CC=emcc CXX=em++ cmake .. \
   && make

ARG OPENGL_UID=1000
ARG OPENGL_GID=1000
RUN groupadd -f -g ${OPENGL_GID} opengl \
    && useradd -d /home/opengl -s /bin/bash -g ${OPENGL_GID} -u ${OPENGL_UID} opengl

USER opengl