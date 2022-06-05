FROM python:3.7.13-buster

RUN mkdir /home/opengl
WORKDIR /home/opengl

COPY . .

RUN ln -snf /bin/bash /bin/sh

RUN apt-get update \
    && apt-get install git -y \
    && apt-get install wget -y \
    && apt-get install build-essential -y \
    && apt-get install libssl-dev -y

RUN apt-get install gcc-7 g++-7 g++-7-multilib gfortran-7 -y \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
    && update-alternatives --config gcc \
    && echo `gcc --version | grep ^gcc | sed 's/^.* //g'`

RUN wget http://www.cmake.org/files/v3.21/cmake-3.21.6.tar.gz
RUN tar xzf cmake-3.21.6.tar.gz 
WORKDIR /home/opengl/cmake-3.21.6
RUN ./bootstrap
RUN make
RUN make install

WORKDIR /home/opengl/vendor/emsdk
RUN python -X utf8 emsdk.py install 3.1.12
RUN python -X utf8 emsdk.py activate 3.1.12
RUN chmod +x emsdk_env.sh
RUN source  /home/opengl/vendor/emsdk/emsdk_env.sh

WORKDIR /home/opengl

RUN apt-get install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev extra-cmake-modules -y

#RUN source  /home/opengl/vendor/emsdk/emsdk_env.sh \
#    && cd /home/opengl
#    && mkdir build_emscripten \
#    && cd build_emscripten \
#    && CC=emcc CXX=em++ cmake -DGLFW_USE_WAYLAND=ON ..

ARG OPENGL_UID=1000
ARG OPENGL_GID=1000
RUN groupadd -f -g ${OPENGL_GID} opengl \
    && useradd -d /home/opengl -s /bin/bash -g ${OPENGL_GID} -u ${OPENGL_UID} opengl

USER opengl