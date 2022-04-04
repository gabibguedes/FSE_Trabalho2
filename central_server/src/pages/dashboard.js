const html = require('./html')
const floor = require('../components/floor')
const { get_socket_data } = require('../socket')

const dashboard = () => {

  let data = get_socket_data()
  const render_floors = () => {
    const keys = Object.keys(data)
    return keys.map(key => (
      floor(key, data[key])
    )).join(' ')
  }
  return html(`
    <div style="padding: 20px 50px 0 50px">
      <h1>Dashboard do Servidor Central</h1>
      <div style="display: flex">
        ${render_floors()}
      </div>
    </div>
  `)
}

module.exports = dashboard;