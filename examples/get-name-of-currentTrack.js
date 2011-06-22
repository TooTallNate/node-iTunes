var iTunes = require('../');

console.time('createConnection');
iTunes.createConnection(onConnection);

function onConnection (err, itunes) {
  console.timeEnd('createConnection');
  if (err) throw err;

  console.time('currentTrack');
  itunes.currentTrack(onTrack);
}

function onTrack (err, track) {
  console.timeEnd('currentTrack');
  if (err) throw err;
  if (!track)
    return console.log('There is no track currently playing...');

  console.time('name');
  track.name(onName);
}

function onName (err, name) {
  console.timeEnd('name');
  if (err) throw err;

  console.log("Current Track: %s", name);
}
