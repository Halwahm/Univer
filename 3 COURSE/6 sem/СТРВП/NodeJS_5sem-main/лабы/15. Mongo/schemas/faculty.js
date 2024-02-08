const mongoose = require('mongoose');
let Schema = mongoose.Schema;

let facultySchema = new Schema({
    faculty: {
        type: String,
        required: true
    },
    faculty_name: {
        type: String,
        required: true
    }
}, { collection: 'faculty' });

module.exports = mongoose.model('faculty', facultySchema);