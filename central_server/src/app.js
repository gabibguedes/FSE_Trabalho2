const express = require('express')
const cors = require('cors')
const router = require('./routes')
const { initSocketServer } = require('./socket')

const { SOCKET_PORT, DASHBOARD_PORT } = process.env

const app = express()
app.use(cors())
app.use(express.json())
app.use(router)

app.listen(DASHBOARD_PORT, () =>
  console.log(`Dashboard is running on PORT ${DASHBOARD_PORT}`)
)

const server = initSocketServer()

server.listen(SOCKET_PORT, () =>
  console.log(`Socket is running on PORT ${SOCKET_PORT}`)
)

