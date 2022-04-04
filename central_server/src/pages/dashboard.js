const html = require('./html')
const floor = require('../components/floor')
const { get_socket_data } = require('../socket')

const dashboard = () => {
  const data = get_socket_data()
  let people_sum = 0

  const render_floors = () => {
    const keys = Object.keys(data)
    return keys.map(key => (
      floor(key, data[key])
    )).join(' ')
  }

  const total_people_count = () => {
    Object.keys(data).forEach(key => {
      people_sum += data[key].people_count
    })
  }

  total_people_count()

  return html(`
    <div style="padding: 20px 50px 0 50px">
      <h1>Dashboard do Servidor Central</h1>
      <p>Total de pessoas no prédio: <b>${people_sum}</b></p>
      <div>
        ${render_floors()}
      </div>
    </div>
  `)
}

module.exports = dashboard;