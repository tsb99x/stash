FROM gcc AS builder

RUN apt-get update \
    && apt-get install -y cmake

WORKDIR /usr/src/app
COPY . .
RUN mkdir build \
    && cd build \
    && cmake .. \
    && cmake --build .

FROM debian

WORKDIR /usr/local/app
COPY --from=builder /usr/src/app/build/main .
ENTRYPOINT [ "./main" ]
