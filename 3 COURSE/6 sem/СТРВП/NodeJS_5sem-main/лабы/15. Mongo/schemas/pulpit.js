const mongoose = require('mongoose');
let Schema = mongoose.Schema;

let pulpitSchema = new Schema({
    pulpit: {
        type: String
    },
    pulpit_name: {
        type: String
    },
    faculty: {
        type: String
    }
}, { collection: 'pulpit' });

module.exports = mongoose.model('pulpit', pulpitSchema);