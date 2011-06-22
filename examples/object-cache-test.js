var iTunes = require('../')
  , numCbExpected = 0
  , numCbGot = 0
  , tracks = []

// This is a little demonstration of how getting two of the same iTunesTrack
// instances via an API call (potentially from differenct sources) will return
// the same JS object. This is useful for comparison purposes in JS-land and
// helped implementing the mutex in C++ land.

iTunes.createConnection(function (err, conn) {
  if (err) throw err;
  conn.currentTrack(onTrack);
  numCbExpected++;
  conn.currentTrack(onTrack);
  numCbExpected++;
});

function onTrack (err, track) {
  if (err) throw err;
  if (!track) throw new Error('no track!');
  tracks.push(track);
  numCbGot++;
  if (numCbGot === numCbExpected) {
    done();
  }
}

function done () {
  var equals = tracks[0] == tracks[1]
    , strictEquals = tracks[0] === tracks[1]
  console.error("Equality: %s", equals)
  console.error("Strict Equality: %s", strictEquals)
}
