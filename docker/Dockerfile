# Build
FROM ubuntu:16.04

RUN apt-get update \
&& \
apt-get install -y --no-install-recommends \
build-essential \
cmake \
git \
&& \
rm -rf /var/lib/apt /var/lib/dpkg /var/lib/cache /var/lib/log

RUN useradd -m -d /src -s /bin/bash user
USER user
WORKDIR /src/