const nodemailer = require("nodemailer");

const transport = nodemailer.createTransport({
  service: "Gmail",
  auth: {
    user: "courseprphotohosting@gmail.com",
    pass: "12345678!q",
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
