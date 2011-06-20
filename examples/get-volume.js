var iTunes = require('../');

console.time('createConnection');
iTunes.createConnection(onConnection);

function onConnection (err, itunes) {
  console.timeEnd('createConnection');
  if (err) throw err;

  console.time('getVolume');
  itunes.getVolume(onVolume);
}

function onVolume (err, v) {
  console.timeEnd('getVolume');
  if (err) throw err;

  console.log("Current Volume: %d", v);
}
