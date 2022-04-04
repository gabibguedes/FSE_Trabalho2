const { CENTRAL_SERVER_IP, DASHBOARD_PORT } = process.env
const { dark_blue, red, green, grey } = require('./colors')

const floor = (name, data) => {
  const alarm = data.alarm

  const alarm_body = {
    value: !alarm,
    name: name
  }

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
        server_ip: data.server_ip,
        port: data.port
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
    <div style="
      display: flex;
      justify-content: space-between;
      border: 1px solid ${alarm? red : dark_blue};
      border-radius: 5px;
      padding: 20px; margin:20px"
      >
      <div style="display=flex;">
        <h2 style="color: ${alarm? red : dark_blue}">${name}</h2>
        <p>Temperatura: <b>${data.temperature.toFixed(2)}ºC</b></p>
        <p>Humidade: <b>${data.humidity.toFixed(2)}%</b></p>
        <p>Pessoas: <b>${data.people_count}</b></p>
        <p>Alarme: <b style="color: ${alarm? red : grey}">${alarm? 'ATIVADO' : 'DESATIVADO'}</b></p>
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
        <button
          style="margin: 10px"
          onclick='activate_alarm(${JSON.stringify(alarm_body)})'
        >
          ${alarm? 'Desligar' : 'Ligar'} Alarme
        </buton>
      </div>
    </div>
    <script>

      function alarm(alarm){
        let context = new AudioContext(),
        oscillator = context.createOscillator();

        oscillator.type = 'sine';
        oscillator.detune.value = 100;
        oscillator.connect(context.destination);
        // if(alarm){
        //   oscillator.start();
        // }
      }

      function activate_element(body){
        fetch('http://localhost:${DASHBOARD_PORT}/gpio-update', {
          method: 'POST',
          headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(body)
        })
      }

      function activate_alarm(body){
        fetch('http://localhost:${DASHBOARD_PORT}/alarm', {
          method: 'POST',
          headers: {
            'Accept': 'application/json',
            'Content-Type': 'application/json'
          },
          body: JSON.stringify(body)
        })
      }
      alarm(${alarm})

    </script>
  `
}

module.exports = floor;