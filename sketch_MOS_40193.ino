// Test avec un arduino du compsant CD40193BE qui est un compteur 4bit inc/dec

const int buttonPinUp = 2;  // Bouton connecté à la broche D2
const int buttonPinDown = 3;  // Bouton connecté à la broche D3
const int upPin = 4;      // Broche UP pour le CD40193BE
const int downPin = 5;      // Broche DOWN pour le CD40193BE
bool lastButtonStateUp = HIGH;
bool lastButtonStateDown = HIGH;
bool buttonPressedUp = false;
bool buttonPressedDown = false;
unsigned long lastDebounceTimeUp = 0;
unsigned long lastDebounceTimeDown = 0;
const long debounceDelay = 50;  // Temps de debounce en millisecondes

void setup() {
  Serial.begin(9600);        // Initialisation du moniteur série
  pinMode(buttonPinUp, INPUT);
  pinMode(buttonPinDown, INPUT);
  pinMode(upPin, OUTPUT);
  pinMode(downPin, OUTPUT);
  
  // Initialisation de la broche UP à LOW
  digitalWrite(upPin, LOW);
}

void loop() {
  // Lire l'état actuel du bouton
  int readingUp = digitalRead(buttonPinUp);
  int readingDown = digitalRead(buttonPinDown);

  if (readingUp == LOW) {
    if (!buttonPressedUp) {
      Serial.println("Bouton pressé - Incrémentation");

      // Envoyer une impulsion d'horloge au CD40193BE
      digitalWrite(downPin, HIGH);
      digitalWrite(upPin, HIGH);
      delay(10);  // Impulsion courte
      digitalWrite(upPin, LOW);
      buttonPressedUp = true;
    } else {
      buttonPressedUp = false; 
    }
  }

  if (readingDown == LOW) {
    if (!buttonPressedDown) {
      Serial.println("Bouton pressé - Décrémentation");

      // Envoyer une impulsion d'horloge au CD40193BE
      digitalWrite(upPin, HIGH);
      digitalWrite(downPin, HIGH);
      delay(10);  // Impulsion courte
      digitalWrite(downPin, LOW);
      buttonPressedDown = true;
    } else {
      buttonPressedDown = false; 
    }
  }

  // Sauvegarder l'état actuel du bouton
  lastButtonStateUp = readingUp;
  lastButtonStateDown = readingDown;

  delay(50);  // Petit délai pour éviter des lectures trop rapides
}
