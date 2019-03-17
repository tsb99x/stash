FROM gradle:4.10 AS BUILD_IMAGE
USER root
WORKDIR /usr/local/src/transfer
COPY . .
RUN gradle --stacktrace shadowJar

FROM openjdk:8-jre
WORKDIR /usr/local/bin/
COPY --from=BUILD_IMAGE /usr/local/src/transfer/build/libs/transfer*.jar ./transfer.jar
EXPOSE 8080
CMD ["java","-jar","transfer.jar"]
