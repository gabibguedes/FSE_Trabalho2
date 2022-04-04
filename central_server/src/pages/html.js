const html = (body) => {
  return `
    <html>
      <head>
        <meta http-equiv="refresh" content="1; URL=http://localhost:3002/">
      </head>
      <body>
        ${body}
      </body>
    </html>
  `
}

module.exports = html;