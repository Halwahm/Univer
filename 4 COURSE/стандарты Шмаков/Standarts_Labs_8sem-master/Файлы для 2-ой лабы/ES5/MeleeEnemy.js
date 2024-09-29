const NPC = require("./NPC.js");

function MeleeEnemy(name, pos, lvl, attackStrength, attackSpeed) {
  NPC.call(this, name, pos);
  this.lvl = lvl;
  this.attackStrength = attackStrength;
  this.attackSpeed = attackSpeed;
}

MeleeEnemy.prototype = Object.create(NPC.prototype);
MeleeEnemy.prototype.constructor = MeleeEnemy;

MeleeEnemy.prototype.walkForward = function () {
  NPC.prototype.walkForward.call(this);
  console.log("--> Argh!");
};

MeleeEnemy.prototype.walkBack = function () {
  NPC.prototype.walkBack.call(this);
  console.log("<--");
};

if (typeof module !== "undefined" && module.exports) {
  module.exports = MeleeEnemy;
} else {
  throw new Error("Use node.js!");
}
