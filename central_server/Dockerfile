FROM node:17

ENV SOCKET_PORT 10005
ENV DASHBOARD_PORT 3002

EXPOSE 10005
EXPOSE 3002

COPY ./package.json /code/package.json
COPY ./src /code/src

WORKDIR /code

CMD ["sh","-c", "yarn install && yarn dev"]