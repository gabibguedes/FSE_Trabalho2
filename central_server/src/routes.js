const express = require("express");
const router = express.Router();
const { write_on_socket } = require('./socket')
const Commands = require('./controllers/commands')

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

router.post('/gpio-update', Commands.change_gpio_value)
router.post('/alarm', Commands.change_alarm_value)

module.exports = router;