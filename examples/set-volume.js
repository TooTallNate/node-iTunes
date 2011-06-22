var iTunes = require('../');

console.time('createConnection');
iTunes.createConnection(onConnection);

function onConnection (err, itunes) {
  console.timeEnd('createConnection');
  if (err) throw err;

  var val = Number( process.argv[2] || Math.floor(Math.random() * 100) );
  console.log('setting volume to: %d', val);

  console.time('volume');
  itunes.volume(val, onVolume);
}

function onVolume (err, v) {
  console.timeEnd('volume');
  if (err) throw err;

  console.log("Current Volume: %d", v);
}
