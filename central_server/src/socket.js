const net = require('net');

let socket;
let data;

const write_on_socket = (message) => {
  socket.write(message);
}
const get_socket_data = (message) => {
  return data;
}

const initSocketServer = () => {
  return net.createServer((net_socket) => {
    socket = net_socket
    socket.on('readable',() => {
      let chunk = null;
        while ((chunk = socket.read()) !== null) {
          console.log(`[RECEIVED] ${chunk}`)
          data = chunk;
          write_on_socket(chunk)
        }
    });
  });
}


module.exports = {
  write_on_socket,
  initSocketServer,
  get_socket_data
}

