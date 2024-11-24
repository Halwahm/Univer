const Math = {
    skip: (page) => {
        return parseInt( (page - 1) * process.env.TAKE_ITEM);
    }
}
module.exports = Math;