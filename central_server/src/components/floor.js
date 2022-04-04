const { get_socket_data } = require('../socket')

const floor = () => {
  const title = 'Terreo'
  const outputs = [
    {
      tag: 'Lâmpada da Sala T01',
      value: true
    },
    {
      tag: "Lâmpada da Sala T02",
      value: false
    },
    {
      tag: "Lâmpadas do Corredor Terreo",
      value: true
    },
    {
        tag: "Ar-Condicionado Terreo",
      value: false
    },
    {
        tag: "Aspersor de Água (Incêndio)",
        value: true
    }
  ]

  const sensors_data = () => {
    return outputs.map((sensor) => (
      `
        <p>${sensor.tag}: ${sensor.value? 'ON' : 'OFF'}</p>
      `
    )).join(' ')
  }

  return `
    <div>
      <h2 style="color: red">${title}</h2>
      <h2 style="color: red">${get_socket_data()}</h2>
      ${sensors_data()}
    </div>
  `
}

module.exports = floor;