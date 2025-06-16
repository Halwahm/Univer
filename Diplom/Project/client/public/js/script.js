const ws = new WebSocket("wss://dreamcinema:9000");
const input = document.getElementById("input");
const send = document.getElementById("send");
let messages = document.getElementById("messages");
let status = document.getElementById("status");
let users = document.getElementById("users");
let allMessages = [];
let current = "";
let adminName = localStorage.getItem("login");

send.addEventListener("click", () => {
  if (input.value !== "")
    ws.send(
      JSON.stringify({
        action: "response",
        login: current,
        message: input.value,
        name: adminName,
      })
    );
  input.value = "";
});

ws.onopen = () => {
  console.log("open wss");
};

setTimeout(() => {
  ws.send(JSON.stringify({ action: "online", message: input.value }));
}, 500);

ws.onmessage = (response) => {
  let data = JSON.parse(response.data);
  let found = false;

  /* console.log(data)*/

  if (data.online !== undefined) return;
  else {
    if (allMessages.length === 0) {
      allMessages.push(data);

      build();
    } else {
      console.log("data: ", data);
      console.log("allMessages: ", allMessages);
      for (const message of allMessages) {
        if (message.data !== undefined)
          if (data.data[0].login === message.data[0].login) {
            message.data.push({
              login: data.data[0].name ? data.data[0].name : data.data[0].login,
              message: data.data[0].message[0],
            });
            console.log("message  ", data.data);
            found = true;
          }
      }

      if (found === false) {
        allMessages.push(data);
        build();
      }

      if (data.data[0].login === current) {
        loadMessage(current);
      } else {
        document.getElementById(data.data[0].login).style.color = "red";
      }
    }
    /*     console.log(allMessages)*/
  }
};

ws.onerror = (err) => {
  status.style.backgroundColor = "red";
  users.innerHTML = "";
  console.log(err);
};

const build = () => {
  users.innerHTML = "";
  for (let val of allMessages) {
    let button = document.createElement("button");
    button.appendChild(document.createTextNode(val.data[0].login));
    button.classList.add("users", "btn", "btn-outline-success");
    button.id = val.data[0].login;
    button.addEventListener("click", loadMessage, this.value);
    users.append(button);
  }
};

const loadMessage = (user) => {
  console.log("loadMessage : user.target: ", user.target);
  if (user.target) current = user.target.innerHTML;
  document.getElementById(current).style.color = "black";

  for (let val of allMessages) {
    if (val.data[0].login === current) {
      messages.innerHTML = "";
      val.data.forEach((obj) => {
        messages.innerHTML += `<span>${obj.login} : ${obj.message}</span><br>`;
      });
    }
  }
};
