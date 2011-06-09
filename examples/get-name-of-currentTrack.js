var iTunes = require('../');

console.time('createConnection');
iTunes.createConnection(onConnection);

function onConnection (err, itunes) {
  console.timeEnd('createConnection');
  if (err) throw err;

  console.time('getCurrentTrack');
  var track = itunes.getCurrentTrackSync();
  console.timeEnd('getCurrentTrack');

  console.time('getName');
  track.getName(onName);
}

function onName (err, name) {
  console.timeEnd('getName');
  if (err) throw err;

  console.log("Current Track: %s", name);
}
