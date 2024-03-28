import weaponService from '../services/weaponService.js';

export async function getAllWeapons(req, res) {
    try {
        const weapons = await weaponService.getAllWeapons();
        res.json(weapons);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
}

export async function getWeaponsById(req, res) {
    const { id } = req.params;

    try {
        const weapons = await weaponService.getWeaponsById(id);
        res.json(weapons);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
}

export async function getWeaponsByDps(req, res) {
    try {
        const { dps } = req.query;
        const match = dps.match(/(\d+)/);

        const num = match[0];
        const matchе = dps.match(/(gt|lt)(\d+)/);
        const dpsOperatore = matchе[1];

        const weapons = (dpsOperatore === 'gt') 
            ?
                await weaponService.getWeaponsByGreaterDps(num) 
            :
                await weaponService.getWeaponsByLessDps(num);

        res.json(weapons);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
}

export async function postNewWeapon(req, res) {
    try {
        const weaponBody = req.body;
        const newWeapon = await weaponService.postNewWeapon(weaponBody);
        res.status(201).json(newWeapon);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
}

export async function updateWeaponById(req, res) {
    try {
        const { id } = req.params;
        const weaponBody = req.body;
        
        const weapon = await weaponService.updateWeaponById(id, weaponBody);
        res.status(201).json(weapon);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
}

export async function deleteWeaponById(req, res) {
    try {
       const { id } = req.params;
        const weapon = await weaponService.deleteWeaponById(id);
        res.status(201).json(weapon);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
}
