var iTunes = require('../');

iTunes.createConnection(onConnection);

function onConnection (err, conn) {
  if (err) throw err;

  conn.running(function (err, running) {
    if (err) throw err;
    if (running) {
      console.log('iTunes is running.. Closing...');
      conn.quit(); // Fire and forget, async...
     } else {
      console.log('iTunes is not running...');
     }
  });
}
