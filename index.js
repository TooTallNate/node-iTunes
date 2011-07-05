require('autoreleasepool');
module.exports = require('./build/default/bindings.node');

var Application = module.exports.Application
  , Item = module.exports.Item
  , Artwork = module.exports.Artwork
  , inspect = require('util').inspect

// 'name' on Artwork instances is a no-no apparently...
Artwork.prototype.name = undefined;

Application.prototype.inspect = function () {
  return inspect(Application.prototype.toString.call(this));
}
Item.prototype.inspect = function () {
  return inspect(Item.prototype.toString.call(this));
}
