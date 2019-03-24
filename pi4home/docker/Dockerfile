ARG BUILD_FROM=pi4home/pi4home-base-amd64:1.3.0
FROM ${BUILD_FROM}

COPY . .
RUN \
    pip2 install --no-cache-dir --no-binary :all: -e .

WORKDIR /config
ENTRYPOINT ["pi4home"]
CMD ["/config", "dashboard"]
