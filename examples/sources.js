var iTunes = require('../')
  , conn   = null

iTunes.createConnection(onConn);

function onConn (err, c) {
  if (err) throw err;
  conn = c;
  conn.sources( onSources );
  conn.sources(1, onFirstSource);
}

function onSources (err, sources) {
  if (err) throw err;
  console.log(sources);
  sources.forEach(function (source) {
    source.kind(console.log);
  });
}

function onFirstSource (err, source) {
  if (err) throw err;
  console.log(source);
}
