FROM gcc:13.2.0 AS build
WORKDIR /src
COPY server/ server/
RUN g++ -std=c++11 -O2 -pthread -static-libstdc++ -static-libgcc server/main.cpp -o tividy

FROM debian:bookworm-slim
WORKDIR /app
COPY --from=build /src/tividy .
COPY web/ web/
EXPOSE 8080
CMD ["./tividy"]
