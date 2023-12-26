const ComunicacionSerial = require("./serialcommunication.class");

const serial = new ComunicacionSerial("COM12");
serial.sendMessage("2:Hay un retraso en la Prensa 1. Prensa 4. Prensa 5:4:Hay un retraso en la Prensa 2. Prensa 6. Prensa 7. Prensa 9:3:Hay un retraso en la Prensa 3")
  .then((isSend) => {
    console.log("Se mando el mesaje via serial");
  })
  .catch((err) => {
    console.log("No se mando el mensaje via serial");
  })