var iTunes = require('../')
  , speed  = Number(process.argv[2] || 50)
  , inc    = 1
  , i      = 0
  , conn   = null

iTunes.createConnection(function (err, c) {
  if (err) throw err;
  conn = c;
  conn.volume( initVolume );
});

function initVolume (err, v) {
  if (err) throw err;
  i = v;
  console.log('Toggling Volume at Speed: %d', speed);
  step();
}

function step () {
  if (i === 0 || i === 100) inc *= -1;
  conn.volume(i += inc, afterSet);
}

function afterSet (err, v) {
  if (err) throw err;
  setTimeout(step, speed);
}
