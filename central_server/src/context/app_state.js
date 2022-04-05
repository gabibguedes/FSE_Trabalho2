let distributed_server_data = {};

const get_distributed_server_data = () => {
  return distributed_server_data;
}

const set_distributed_server_data = (new_data) => {
  distributed_server_data = new_data
}


module.exports = {
  get_distributed_server_data,
  set_distributed_server_data
}