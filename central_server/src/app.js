const express = require('express')
const router = require('./routes')
const net = require('net');

const { PORT } = process.env

const app = express()
app.use(router)

const server = net.createServer((socket) => {
  socket.on('readable',() => {
    let chunk = null;
      while ((chunk = socket.read()) !== null) {
        console.log(`[RECEIVED] ${chunk}`)
        socket.write(chunk);
      }
  });
});

server.listen(PORT, () => console.log(`Server running on port ${PORT}`))
