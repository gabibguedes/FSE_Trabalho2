const { CENTRAL_SERVER_IP, DASHBOARD_PORT } = process.env
const { dark_blue, red, green } = require('./colors')


const floor = (name, data) => {
  const render_sensor_list = (sensor_arr) => {
    return sensor_arr.map(sensor => (
      `
        <p style="font-size: 12px">
          ${sensor.tag}:
          <b style="color: ${sensor.value? green : red}">
            ${sensor.value? 'ON' : 'OFF'}
          </b>
        </p>
      `
    )).join(' ')
  }

  const render_buttons = () =>{
    const action_buttons = data.outputs.filter(elem => {
      return elem.tag.match(/Lâmpada/) || elem.tag.match(/Ar-Condicionado/)
    })

    return action_buttons.map(item => {
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
    <div style="display: flex; justify-content: space-between; border: 1px solid ${dark_blue}; border-radius: 5px; padding: 20px; margin:20px">
      <div style="display=flex;">
        <h2 style="color: ${dark_blue}">${name}</h2>
        <p>Temperatura: <b>${data.temperature}ºC</b></p>
        <p>Humidade: <b>${data.humidity}%</b></p>
        <p>Pessoas: <b>${data.people_count}</b></p>
      </div>
      <div style="padding: 10px">
        <p><b>Sensores</b></p>
        ${render_sensor_list(data.inputs)}
      </div>
      <div style="padding: 10px">
        <p><b>Saídas</b></p>
        ${render_sensor_list(data.outputs)}
      </div>
      <div style="display: flex; flex-direction: column; padding: 20px">
        ${render_buttons()}
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