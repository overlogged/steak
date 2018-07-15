#!/bin/sh
stack install
sudo mkdir /usr/include/steak
sudo cp /tmp/steak/include/steak.h /usr/include/steak
sudo cp /tmp/steak/include/runtime.h /usr/include/steak