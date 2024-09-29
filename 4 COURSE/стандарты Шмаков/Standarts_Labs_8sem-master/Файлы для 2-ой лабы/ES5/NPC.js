function NPC(name, pos) {
  this._name = name || "NPC";
  this._pos = pos || 0;
  NPC.count++;
}

Object.defineProperty(NPC.prototype, "name", {
  get: function () {
    return this._name;
  },
  set: function (value) {
    this._name = value;
  },
  enumerable: true,
  configurable: true,
});

Object.defineProperty(NPC.prototype, "pos", {
  get: function () {
    return this._pos;
  },
  enumerable: true,
  configurable: true,
});

NPC.create = function () {
  return new NPC();
};

NPC.prototype.walkForward = function () {
  this._pos++;
};

NPC.prototype.walkBack = function () {
  this._pos--;
};

NPC.count = 0;

if (typeof module !== "undefined" && module.exports) {
  module.exports = NPC;
} else {
  throw new Error("Use Node.js!");
}
