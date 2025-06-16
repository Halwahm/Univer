const ws = new WebSocket("wss://dreamcinema:9000");
const input = document.getElementById("input");
const send = document.getElementById("send");
let messages = document.getElementById("messages");
let status = document.getElementById("status");

send.addEventListener("click", () => {
  if (input.value !== "")
    ws.send(JSON.stringify({ action: "message", message: input.value }));

  input.value = "";
});

ws.onopen = () => {
  console.log("open wss");
};

setTimeout(() => {
  ws.send(JSON.stringify({ action: "online" }));
}, 500);

ws.onmessage = (response) => {
  let data = JSON.parse(response.data);
  if (data.online === true) {
    status.style.backgroundColor = "#11ff00";
  } else if (data.online === false) {
    status.style.backgroundColor = "red";
  } else {
    data.data.forEach((message) => {
      if (message.online === true) {
        status.style.backgroundColor = "#11ff00";
      } else if (message.online === false) {
        status.style.backgroundColor = "red";
      }
      messages.innerHTML += `<span>${message.login} : ${message.message}</span><br>`;
    });
  }
};

ws.onerror = (err) => {
  status.style.backgroundColor = "red";
};
