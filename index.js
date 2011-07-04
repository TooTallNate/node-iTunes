require('autoreleasepool');
module.exports = require('./build/default/bindings.node');

var Application = module.exports.Application
  , Item = module.exports.Item
  , inspect = require('util').inspect

Application.prototype.inspect = function () {
  return inspect(Application.prototype.toString.call(this));
}
Item.prototype.inspect = function () {
  return inspect(Item.prototype.toString.call(this));
}
