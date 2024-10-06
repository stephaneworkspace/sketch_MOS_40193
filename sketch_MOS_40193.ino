/*const int upPin = 3;  // Broche UP pour le CD40193BE (connectée à D3)
unsigned long previousMillis = 0;
const long interval = 1000;  // Intervalle d'une seconde (1000 ms)

void setup() {
  Serial.begin(9600);    // Initialisation du moniteur série
  pinMode(upPin, OUTPUT); // Broche UP comme sortie
  digitalWrite(upPin, LOW); // Initialiser à LOW

  Serial.println("Incrémentation toutes les secondes via Pin 3");
}

void loop() {
  unsigned long currentMillis = millis();

  // Si une seconde s'est écoulée
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Réinitialiser le temps

    // Envoyer une impulsion d'horloge à CLK UP du CD40193BE
    digitalWrite(upPin, HIGH);
    delay(10);  // Impulsion courte de 10ms
    digitalWrite(upPin, LOW);

    Serial.println("Incrémentation du CD40193BE");
  }
}
*/

const int buttonPin = 2;  // Bouton connecté à la broche D2
const int upPin = 3;      // Broche UP pour le CD40193BE (connectée à D3)
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const long debounceDelay = 50;  // Temps de debounce en millisecondes

void setup() {
  Serial.begin(9600);        // Initialisation du moniteur série
  pinMode(buttonPin, INPUT);  // Utilisation d'une résistance pull-up externe
  pinMode(upPin, OUTPUT);     // Broche UP comme sortie
  
  // Initialisation de la broche UP à LOW
  digitalWrite(upPin, LOW);
}

void loop() {
  // Lire l'état actuel du bouton
  int reading = digitalRead(buttonPin);

  // Vérifier si l'état du bouton a changé
  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // Mettre à jour l'heure du dernier changement
  }

  // Si l'état a été stable pendant longtemps (pas de rebonds)
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si le bouton est pressé (LOW)
    if (reading == LOW) {
      Serial.println("Bouton pressé - Incrémentation");

      // Envoyer une impulsion d'horloge au CD40193BE
      digitalWrite(upPin, HIGH);
      delay(10);  // Impulsion courte pour l'incrémentation
      digitalWrite(upPin, LOW);
    }
  }

  // Sauvegarder l'état actuel du bouton
  lastButtonState = reading;

  delay(50);  // Petit délai pour éviter des lectures trop rapides
}