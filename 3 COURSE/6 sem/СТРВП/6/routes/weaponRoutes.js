import { Router } from "express";
import * as weaponController from "../controllers/weaponController.js";

const router = Router();

router.get('/', (req, res, next) => {
    const { dps } = req.query;
    if (dps !== undefined) {
        return weaponController.getWeaponsByDps(req, res, next);
    } else {
        return weaponControllerController.getAllWeapons();
    }
});
router.get('/:id', weaponController.getWeaponsById);
router.post('/', weaponController.postNewWeapon);
router.put('/:id', weaponController.updateWeaponById);
router.delete('/:id', weaponController.deleteWeaponById);

export default router;
