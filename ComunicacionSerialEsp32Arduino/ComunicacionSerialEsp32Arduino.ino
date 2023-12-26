#include "sms_constructor.h"
String Input = "";
char* numero1 = "8713659940";
void setup() {
  Serial.begin(9600);  // Establece la velocidad del puerto serial
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void ObtenerValores(String message_input, int indices) {
  message_input = message_input + ":";
  int size_array = indices / 2;
  String message_arr[size_array];
  int states_arr[size_array];
  char* message = const_cast<char*>(message_input.c_str());
  char* token = strtok(message, ":");
  int index = 0;
  int contadorState = 0;
  int contadorMessage = 0;
  while (token != NULL) {
    if (index == 2) {
      index = 0;
    }
    if (index == 0) {
      states_arr[contadorState] = atoi(token);
      contadorState++;
    }
    if (index == 1) {
      message_arr[contadorMessage] = token;
      contadorMessage++;
    }
    token = strtok(NULL, ":");
    index++;
  }
  for (int i = 0; i < size_array; i++) {
    int importancia = states_arr[i];
    String mensaje = message_arr[i];
    if (importancia == 1) {
      char* numeros[] = { numero1 };
      size_t size_numeros = sizeof(numeros) / sizeof(numeros[0]);  // 4 elements
      for (int i = 0; i < size_numeros; i++) {
        send_sms(numeros[i], mensaje + ". Sin produccion mas de 30 minutos", 0);
      }
    }
    if (importancia == 2) {
      char* numeros[] = { numero1 };
      size_t size_numeros = sizeof(numeros) / sizeof(numeros[0]);  // 4 elements
      for (int i = 0; i < size_numeros; i++) {
        send_sms(numeros[i], mensaje + ". Sin produccion mas de 1 hora", 0);
      }
    }
    if (importancia == 3) {
      char* numeros[] = { numero1 };
      size_t size_numeros = sizeof(numeros) / sizeof(numeros[0]);  // 4 elements
      for (int i = 0; i < size_numeros; i++) {
        send_sms(numeros[i], mensaje + ". Sin produccion mas de 2 horas", 0);
      }
    }
    if (importancia == 4) {
      char* numeros[] = { numero1 };
      size_t size_numeros = sizeof(numeros) / sizeof(numeros[0]);  // 4 elements
      for (int i = 0; i < size_numeros; i++) {
        send_sms(numeros[i], mensaje + ". Sin produccion mas de 3 horas", 0);
      }
    }
  }
  Serial.println("-------");
}

/**
*Funcion que valida las cadenas entrantes por serial
*/
void Validate_Input_Serial(String input) {
  char* str = (char*)input.c_str();
  Serial.println("Entrada de peticion: ");
  Serial.println(str);

  // Serial.println("Despues del primer corte");
  // Serial.println(message);
  String input_function = str;
  char delimiters[] = ":";
  char* token = strtok(str, delimiters);
  int iterator = 0;
  while (token != NULL) {

    iterator++;
    token = strtok(NULL, ":");
  }
  Serial.println("Si paso esta parte: ");
  Serial.println(input_function);
  Serial.println(iterator);

  ObtenerValores(input_function, iterator);
}

/**
*Funcion que recibe los caracteres por serial
*/
void loop() {
  if (Serial.available() > 0) {       // Verifica si hay datos disponibles
    char data = (char)Serial.read();  // Lee un byte de datos

    // Puedes realizar acciones con los datos recibidos, por ejemplo, imprimirlos
    Serial.print("Dato recibido: ");
    Serial.println(data);
    if (data == '$') {
      Validate_Input_Serial(Input);
      Input = "";
    } else {
      Input = Input + data;
    }
  }
}
