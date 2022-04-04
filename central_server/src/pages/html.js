const html = (body) => {
  const { DASHBOARD_PORT } = process.env
  return `
    <html>
      <head>
        <meta http-equiv="refresh" content="1; URL=http://localhost:${DASHBOARD_PORT}/">
      </head>
      <body>
        ${body}
      </body>
    </html>
  `
}

module.exports = html;