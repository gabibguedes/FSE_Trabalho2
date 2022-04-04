const net = require('net');


let socket;

const write_on_socket = (message) => {
  socket.write(message);
}

const initSocketServer = () => {
  return net.createServer((net_socket) => {
    socket = net_socket
    socket.on('readable',() => {
      let chunk = null;
        while ((chunk = socket.read()) !== null) {
          console.log(`[RECEIVED] ${chunk}`)
          // socket.write(chunk);
          write_on_socket(chunk)
        }
    });
  });
}


module.exports = {
  write_on_socket,
  initSocketServer
}

