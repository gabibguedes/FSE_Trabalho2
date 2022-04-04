const html = require('./html')

const dashboard = (title) => {
  return html(`
    <div>
      <h1>${title}</h1>
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