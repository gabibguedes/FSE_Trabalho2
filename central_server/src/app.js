const express = require('express')
const socket = require('socket.io')
const http = require('http')
const router = require('./routes')
const net = require('net');

const { PORT } = process.env

const app = express()
app.use(router)


// NET Socket
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


// Socket IO
// const serverio = http.createServer(app)
// const io = socket(serverio, {
//   cors: {
// 		origin: "*",
//     allowedHeaders: '*',
// 		credentials: false
// 	}
// })

// io.on('connection', socket => {
//   socket.on('dasboard', data => {
//     console.log('[SOCKET DASHBOARD] - data received: ' + data);
//   });
// })

// serverio.listen(PORT, () => console.log(`Server running on port ${PORT}`))
