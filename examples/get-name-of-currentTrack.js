var iTunes = require('../');

console.time('createConnection');
iTunes.createConnection(onConnection);

function onConnection (err, itunes) {
  console.timeEnd('createConnection');
  if (err) throw err;

  console.time('getCurrentTrack');
  itunes.getCurrentTrack(onTrack);
}

function onTrack (err, track) {
  console.timeEnd('getCurrentTrack');
  if (err) throw err;
  if (!track)
    return console.log('There is no track currently playing...');

  console.time('getName');
  track.getName(onName);
}

function onName (err, name) {
  console.timeEnd('getName');
  if (err) throw err;

  console.log("Current Track: %s", name);
}
