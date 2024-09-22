class NPC {
    constructor(name = "NPC", pos = 0) {
        this._name = name;
        this._pos = pos;
        NPC.count++;
    }

    get name() {
        return this._name;
    }

    set name(value) {
        this._name = value;
    }

    get pos() {
        return this._pos;
    }

    static create() {
        return new NPC();
    }

    walkForward() {
        this._pos++;
    }

    walkBack() {
        this._pos++;
    }

}

NPC.count = 0;

if (module.exports) { 
    module.exports = NPC;
} else { 
    throw new Error("Use Node.js!");
}