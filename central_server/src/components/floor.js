const { CENTRAL_SERVER_IP, DASHBOARD_PORT } = process.env
const { dark_blue, red, green } = require('./colors')


const floor = (name, data) => {
  const render_input_list = () => {
    return data.inputs.map(sensor => (
      `
        <p>${sensor.tag}:
          <b style="color: ${sensor.value? green : red}">
            ${sensor.value? 'ON' : 'OFF'}
          </b>
        </p>
      `
    )).join(' ')
  }

  const render_buttons = () =>{
    return data.outputs.map(item => {
      const req_body = {
        gpio: item.gpio,
        value: !item.value,
        destination_server: name
      }
      return(`
        <button
          style="margin: 10px"
          onclick='activate_element(${JSON.stringify(req_body)})'
        >
          ${item.value? 'Desligar' : 'Ligar'} ${item.tag}
        </buton>
      `)
    }).join(' ')
  }

  return `
    <div style="border: 1px solid ${dark_blue}; border-radius: 5px; padding: 20px">
      <h2 style="color: ${dark_blue}">${name}</h2>
      <p>Temperatura: <b>${data.temperature}ºC</b></p>
      <p>Humidade: <b>${data.humidity}%</b></p>
      <div style="display: flex; justify-content: space-between">
        <div>
          ${render_input_list()}
        </div>
        <div style="display: flex; flex-direction: column">
          ${render_buttons()}
        </div>
      </div>
    </div>
    <script>

      function activate_element(body){
        console.log(body)
        fetch('http://localhost:${DASHBOARD_PORT}/gpio-update', {
          method: 'POST',
          headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(body)
        })
      }

    </script>
  `
}

module.exports = floor;