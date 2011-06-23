var iTunes = require('../');

console.time('createConnection');
iTunes.createConnection(onConnection);

function onConnection (err, itunes) {
  console.timeEnd('createConnection');
  if (err) throw err;

  console.time('volume');
  if (process.argv[2]) {
    var val = Number( process.argv[2] );
    console.log('setting volume to: %d', val);
    itunes.volume(val, onVolume);
  } else {
    itunes.volume(onVolume);
  }
}

function onVolume (err, v) {
  console.timeEnd('volume');
  if (err) throw err;

  console.log("Current Volume: %d", v);
}
