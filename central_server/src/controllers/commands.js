const { write_on_socket } = require('../socket')

const change_gpio_value = (req, res) => {
  const { gpio, value, server_ip, port } = req.body

  console.log(
    `[NODE API] - Change GPIO pin ${gpio} state to ${value} on ${server_ip}:${port}`
  )

  const socket_message = JSON.stringify({
    message: 'Update GPIO',
    type: 2,
    gpio, value, server_ip, port
  })

  write_on_socket(socket_message)

  res.send({
    success: true,
    message: 'Sent to distributed server'
  }).status(200);
}

const change_alarm_value = (req, res) => {
  const { value, server_ip, port } = req.body

  console.log(
    `[NODE API] - ${value? 'Activate' : 'Deactivate'} alarm on ${server_ip}:${port}`
  )
  const socket_message = JSON.stringify({
    message: 'Update alarm',
    type: 3,
    value, server_ip, port
  })

  write_on_socket(socket_message)

  res.send({
    success: true,
    message: `Alarm ${value? 'activated' : 'deactivated'}`
  }).status(200);
}

module.exports = {
  change_gpio_value,
  change_alarm_value
}