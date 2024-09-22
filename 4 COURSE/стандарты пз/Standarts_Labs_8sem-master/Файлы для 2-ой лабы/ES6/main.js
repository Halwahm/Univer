const NPC = require("./NPC");
const MeleeEnemy = require("./MeleeEnemy");
const settings = require("./settings");


let wolf1 = new MeleeEnemy(
    settings.HardWolf.name,
    settings.HardWolf.lvl,
);

let wolf2 = new MeleeEnemy(
    settings.SimpleWolf.name, 
    settings.SimpleWolf.lvl,
    settings.SimpleWolf.attackStrength,
    settings.SimpleWolf.attackSpeed
);

let NPCExample = NPC.create();

console.log( wolf1 );
console.log( wolf2 );
console.log( NPCExample );

console.log( wolf1.name );
console.log(  );

wolf1.walkForward();
wolf1.walkBack();
