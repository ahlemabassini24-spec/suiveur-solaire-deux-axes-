#include <Servo.h>  // Bibliothèque pour contrôler les servomoteurs

// Déclaration des servomoteurs
Servo horizontal; // Servo horizontal (gauche-droite)
int servohori = 180;
int servohoriLimitHigh = 175;
int servohoriLimitLow = 5;

Servo vertical; // Servo vertical (haut-bas)
int servovert = 45;
int servovertLimitHigh = 100;
int servovertLimitLow = 1;

// Déclaration des photorésistances (LDR)
int ldrlt = A0; // LDR haut gauche
int ldrrt = A3; // LDR haut droit
int ldrld = A1; // LDR bas gauche
int ldrrd = A2; // LDR bas droit

void setup() {
  // Connexion des servomoteurs aux broches
  horizontal.attach(2);
  vertical.attach(13);

  // Position initiale
  horizontal.write(180);
  vertical.write(45);

  delay(2500); // Pause pour stabilisation
}

void loop() {
  // Lecture des valeurs des LDR
  int lt = analogRead(ldrlt); // Haut gauche
  int rt = analogRead(ldrrt); // Haut droit
  int ld = analogRead(ldrld); // Bas gauche
  int rd = analogRead(ldrrd); // Bas droit

  int dtime = 10;  // Délai entre ajustements
  int tol = 90;    // Tolérance pour éviter les petits mouvements inutiles

  // Calculs des moyennes
  int avt = (lt + rt) / 2; // Moyenne haut
  int avd = (ld + rd) / 2; // Moyenne bas
  int avl = (lt + ld) / 2; // Moyenne gauche
  int avr = (rt + rd) / 2; // Moyenne droite

  // Écarts verticaux et horizontaux
  int dvert = avt - avd;
  int dhoriz = avl - avr;

  // Correction verticale (vers la lumière)
  if (abs(dvert) > tol) {
    if (avt < avd) { // Inversion : plus de lumière en haut
      servovert = ++servovert;
      if (servovert > servovertLimitHigh) servovert = servovertLimitHigh;
    } else {
      servovert = --servovert;
      if (servovert < servovertLimitLow) servovert = servovertLimitLow;
    }
    vertical.write(servovert);
  }

  // Correction horizontale (vers la lumière)
  if (abs(dhoriz) > tol) {
    if (avl < avr) { // Inversion : plus de lumière à gauche
      servohori = --servohori;
      if (servohori < servohoriLimitLow) servohori = servohoriLimitLow;
    } else {
      servohori = ++servohori;
      if (servohori > servohoriLimitHigh) servohori = servohoriLimitHigh;
    }
    horizontal.write(servohori);
  }

  delay(dtime); // Pause avant prochaine lecture
}