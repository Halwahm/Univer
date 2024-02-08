const nodemailer = require("nodemailer");
const dotenv = require("dotenv");
dotenv.config();

const transport = nodemailer.createTransport({
  service: "Gmail",
  auth: {
    user: process.env.EMAIL_ADRESS,
    pass: process.env.EMAIL_PASSWORD,
  },
});

function send(mail) {
  const option = {
    from: "courseprphotohosting@gmail.com",
    to: "courseprphotohosting@gmail.com",
    subject: "Send function",
    text: mail,
  };

  transport.sendMail(option, (err, info) => {
    if (err) {
      console.log(err);
    } else {
      console.log(info);
    }
  });
}

module.exports = send;
