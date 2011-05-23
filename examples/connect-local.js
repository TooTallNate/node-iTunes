var iTunes = require('../');

iTunes.createConnection(onConnection);

function onConnection(err, itunes) {
  if (err) throw err;

  console.log(itunes);
}
