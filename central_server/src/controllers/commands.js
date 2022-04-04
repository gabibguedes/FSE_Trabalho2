const { write_on_socket } = require('../socket')

const change_gpio_value = (req, res) => {
  const { gpio, value, destination_server } = req.body

  console.log(req.body)

  if(!gpio || !value || !destination_server)
    return res.send({
      success: false,
      message: ''
    }).status(400)

  const socket_message = JSON.stringify({
    gpio, value, destination_server
  })

  write_on_socket(socket_message)

  res.send({
    success: true,
    message: 'Sent to distributed server'
  }).status(200);
}

module.exports = {
  change_gpio_value
}