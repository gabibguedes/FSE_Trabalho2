const express = require("express");
const router = express.Router();
const { write_on_socket } = require('./socket')

const dashboard = require('./pages/dashboard')

router.get("/status", (req, res) => {
  res.send({
    success: true,
    message: 'Central server is running'
  }).status(200);
});

router.get("/", (req, res) => {
  res.send(
    dashboard('Meu dashboard em "React"')
  ).status(200);
});

router.get('/button', (req, res) => {

  write_on_socket('Eu amo o Gabriel Davi')


  res.send({
    success: true,
    message: 'Central server is running'
  }).status(200);
})

module.exports = router;