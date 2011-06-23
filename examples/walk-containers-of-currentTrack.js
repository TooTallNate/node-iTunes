var iTunes = require('../')
  , currentItem = null
  , containerCount = 0

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
  currentItem = track;
  getContainer();
}

function getContainer () {
  console.time('container'+containerCount);
  console.log(currentItem);
  currentItem.container( onContainer );
}

function onContainer (err, container) {
  console.timeEnd('container'+containerCount);
  if (err) throw err;
  if (container) {
    containerCount++;
    currentItem = container;
    getContainer();
  } else {
    console.log("That's the last 'container'!");
  }
}
