var iTunes = require('../')
  , conn   = null

iTunes.createConnection(onConn);

function onConn (err, c) {
  if (err) throw err;
  conn = c;
  conn.selection( onSelection );
}

function onSelection (err, selection) {
  if (err) throw err;
  if (selection.length > 0) {
    var track = selection[0];
    track.artworks(onArtworks);
  } else {
    console.log('There are no tracks currently selected...');
  }
}

function onArtworks (err, artworks) {
  if (err) throw err;
  if (artworks.length > 0) {
    console.log(artworks);
  } else {
    console.log('The selected track does not have any album artwork...');
  }
}
