const NPC = require("./NPC.js");

class MeleeEnemy extends NPC {

    constructor(name, pos, lvl, attackStrength, attackSpeed) {
        super(name, pos);
        this.lvl = lvl;
        this.attackStrength = attackStrength;
        this.attackSpeed = attackSpeed;
    }

    walkForward() {
        super.walkForward();
        console.log('--> Argh!');
    }

    walkBack() {
        super.walkBack();
        console.log('<--')
    }

}


if (module.exports) {
    module.exports = MeleeEnemy;
} else {
    throw new Exception("Use node.js!");
}