const express = require("express");
const router = express.Router();

const { PORT } = process.env

router.get("/", (req, res) => {
  res.send({
    success: true,
    message: `Central server is running on port ${PORT}`
  }).status(200);
});

module.exports = router;