FROM node:17

COPY ./package.json /code/package.json
COPY ./src /code/src
COPY ./public /code/public

WORKDIR /code

CMD ["sh","-c", "yarn install && yarn start"]