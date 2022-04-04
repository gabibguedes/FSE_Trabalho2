const html = (body) => {
  const { CENTRAL_SERVER_IP, DASHBOARD_PORT } = process.env
  return `
    <html>
      <head>
        <meta http-equiv="refresh" content="1; URL=http://${CENTRAL_SERVER_IP}:${DASHBOARD_PORT}/">
        <link rel="preconnect" href="https://fonts.googleapis.com">
        <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
        <link href="https://fonts.googleapis.com/css2?family=Inter&display=swap" rel="stylesheet">
      </head>
      <body>
        ${body}
      </body>
      <style>
        body {
          font-family: 'Inter', sans-serif;
        }
      </style>
    </html>
  `
}

module.exports = html;