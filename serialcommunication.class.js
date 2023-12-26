const { SerialPort } = require('serialport');
class ComunicacionSerial {
    port;
    constructor(port, baudRate = 9600) {
        this.port = new SerialPort({ path: port, baudRate });
        this.open();
        this.recive();
        this.error();
    }


    /**
     * Funcion para abrir el puerto
     */
    open() {
        // Manejar eventos de apertura del puerto
        this.port.on('open', () => {
            console.log('Puerto abierto');
        });
    }

    /**
     * Funcion para escuchar la informacion entrante de la comunicacion serial
     */
    recive() {
        // Manejar eventos de datos recibidos
        this.port.on('data', (data) => {
            console.log(`Datos recibidos desde ESP32: ${data.toString()}`);
        });
    }

    /**
     * Funcion para recibir los errores de la conexion serial
     */
    error() {
        // Manejar eventos de error
        this.port.on('error', (err) => {
            console.error('Error en el puerto serie:', err.message);
        });
    }

    /**
     * Funcion para mandar mensaje
     * @param {string} message 
     */
    sendMessage(message) {
        return new Promise((resolve, reject) => {
            //Comprobar delimitador $
            const message_size = message.length;
            const delimitter_char = message[message_size-1];
            if(delimitter_char == "$"){
                this.port.write(message, (err) => {
                    if (err) {
                        reject(false);
                    }
                    resolve(true);
                    console.log("Mandando mensaje: ", message);
                });
            }else{
                console.log("Necesitas un delimitador '$' al final de la cadena de caracteres para mandar el mensaje");
              reject(false)
            }
        })
    }
}

module.exports = ComunicacionSerial;