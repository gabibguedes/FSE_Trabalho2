const net = require('net');
const {
  get_distributed_server_data,
  set_distributed_server_data
} = require('./context/app_state')

let socket;

const write_on_socket = (message) => {
  socket.write(message);
}

const handle_message_received = (message) => {
  let data = get_distributed_server_data()
  try{
    const payload = JSON.parse(message)
    if(payload.code === 1){
      data[payload.name] = {
        ...payload.data,
        server_ip: payload.server_ip,
        port: payload.port
      }
      set_distributed_server_data(data)
      console.log(
        `[SOCKET RECEIVED] - Message from ${payload.server_ip}:${payload.port} (${payload.name})`
      )
    }
  }catch (err) {
    console.log('[SOCKET ERROR] - Error on parsing input to JSON.')
  }
}

const initSocketServer = () => {
  return net.createServer((net_socket) => {
    socket = net_socket
    socket.on('readable',() => {
      let chunk = null;
        while ((chunk = socket.read()) !== null) {
          handle_message_received(chunk)
        }
    });
  });
}


module.exports = {
  write_on_socket,
  initSocketServer
}

