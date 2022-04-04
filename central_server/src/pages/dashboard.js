const html = require('./html')
const floor = require('../components/floor')

const dashboard = (title) => {
  return html(`
    <div>
      <h1>${title}</h1>
      ${floor()}
      <button onclick="pressButton()">
        Botão
      </button>
    </div>

    <script>
      function pressButton(){
        fetch('http://localhost:3002/button')
      }
    </script>
  `)
}

module.exports = dashboard;