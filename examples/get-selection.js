var iTunes = require('../')
  , conn   = null
  , t1
  , t2

iTunes.createConnection(onConn);

function onConn (err, c) {
  if (err) throw err;
  conn = c;
  conn.selection( onSelection );
  conn.selection(0, onFirstSelection);
}

function onSelection (err, selection) {
  if (err) throw err;
  if (selection.length > 0) {
    console.log("%d Selected Tracks:", selection.length);
    t1 = selection[0];
    selection.forEach(function (track, i) {
      console.log('Track %d:', i);
      console.log('  ', track);
      console.log('  ', track.constructor.name);
    });
  } else {
    console.log('There are no tracks currently selected...');
  }
}

function onFirstSelection (err, track) {
  if (err) throw err;
  t2 = track;
  if (!track)
    console.log('There is no track currently selected...');
  console.log(track);
}

process.on('exit', function() {
  console.error("Referential Equality Test:", t1 === t2);
});
