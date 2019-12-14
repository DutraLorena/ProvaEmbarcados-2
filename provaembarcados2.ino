#define SetBit(RES, BIT)(RES |= (1 << BIT)) // Por BIT em nível alto
#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Por BIT em nível baixo


const int NTC = 10; // Define o pino que lera a saída do LM35
float temperatura; // Variável que armazenará a temperatura medida


void posicao_servo (float temperatura)
{
  int delay = ((temperatura * 1.8) * 1500) / 90; //usamos por base que 90 graus são 1500ms
  int movimentos = (20000 - delay)/delay; //calcula os movimentos
  
  SetBit(PORTD, PD6);  //pulso do servo
  delayMicroseconds(delay);
  ClrBit(PORTD, PD6);  //completa periodo do servo
  for (int i = 0; i < movimentos; i++) delayMicroseconds(delay);
}                     

void setup() {
  Serial.begin(9600);
  
  SetBit (DDRD, PD6); //Define o pino ~6 como de comunicação com motor servo SG90
}


void loop() {
  temperatura = (float(analogRead(NTC)) * 5 / (1023)) / 0.01;
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  posicao_servo(temperatura);
  delay(2000);
}
