FROM ubuntu:18.04

LABEL maintainer="nicekingwei@foxmail.com"


RUN apt update
RUN apt install -y gcc g++ git haskell-stack
RUN /usr/bin/stack upgrade
RUN cd /tmp && git clone http://www.github.com/nicekingwei/steak && cd steak && /root/.local/bin/stack install
RUN mv /root/.local/bin/steak /usr/bin
RUN mkdir /usr/include/steak && cp /tmp/steak/include/steak.h /usr/include/steak && cp /tmp/steak/include/runtime.h /usr/include/steak && cp /tmp/steak/include/ret_type_impl.h /usr/include/steak