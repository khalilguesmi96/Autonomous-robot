#include <Servo.h>

const int echoPin = 13;
const int triggerPin = 12;

int distanceAvant;
int distanceDroite;
int distanceGauche;
float intervalle;

Servo myservo; //Création de l'objet servo
const int delay_time = 250; //Temps accordé au servo pour la mesure de la distance de chaque côté

const int moteurGaucheA = 5;
const int moteurGaucheR = 6;
const int moteurDroitA = 11;
const int moteurDroitR = 10;

char valSerie;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(moteurGaucheA, OUTPUT);
  pinMode(moteurGaucheR, OUTPUT);
  pinMode(moteurDroitA, OUTPUT);
  pinMode(moteurDroitR, OUTPUT);
    // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(triggerPin, OUTPUT);
  myservo.attach(9); //Associe l'objet myservo à la pin 9 (PWM)
}


void avancer()
{
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}

void gauche()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}
void droite()
{
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);
}
void reculer()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, HIGH);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, HIGH);
}
void arreter()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, LOW);
}
void pivoterGauche()
{
  digitalWrite(moteurGaucheA, LOW);
  digitalWrite(moteurGaucheR, HIGH);
  digitalWrite(moteurDroitA, HIGH);
  digitalWrite(moteurDroitR, LOW);
}
void pivoterDroite()
{
  digitalWrite(moteurGaucheA, HIGH);
  digitalWrite(moteurGaucheR, LOW);
  digitalWrite(moteurDroitA, LOW);
  digitalWrite(moteurDroitR, HIGH);
}




void mesurerDistanceAvant()
{
  myservo.write(90);
  delay(delay_time);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
  intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore 
                                 //et la réception de l'écho en distance (cm)
  Serial.println("Distance avant:");
  Serial.println(intervalle);
  distanceAvant = intervalle; //Arrondissement de la distance
}

void mesurerDistanceGauche()
{
  myservo.write(180);
  delay(delay_time);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds( 2);
  digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
  delayMicroseconds( 10);
  digitalWrite(triggerPin, LOW);
  intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
  intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore 
                                 //et la réception de l'écho en distance (cm)
  Serial.println("Distance gauche:");
  Serial.println(intervalle);
  distanceGauche = intervalle;
}

void mesurerDistanceDroite()
{
  myservo.write(0);
  delay(delay_time);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds( 2);
  digitalWrite(triggerPin, HIGH); //Envoie d'une onde sonore
  delayMicroseconds( 10);
  digitalWrite(triggerPin, LOW);
  intervalle = pulseIn(echoPin, HIGH); //Réception de l'écho
  intervalle = intervalle/5.8/10; //Conversion de la différence de temps entre l'envoie de l'onde sonore et la réception de l'écho en distance (cm)
  Serial.println("Distance droite:");
  Serial.println(intervalle);
  distanceDroite = intervalle;
}

void modeUltrason()
{
  mesurerDistanceAvant();
  delay(delay_time);
  
  if(distanceAvant < 25) //Si la distance avant est de moins de 25cm
  {
    arreter();  
    mesurerDistanceGauche();
    delay(delay_time);
    mesurerDistanceDroite();
    delay(delay_time);
    
    if(distanceGauche < 15 && distanceDroite < 15) //Si la distance à gauche 
                                  //et la distance à droite sont de moins de 15cm
    {
    reculer();
    mesurerDistanceGauche();
    delay(delay_time);
    mesurerDistanceDroite();
    delay(delay_time);
      
    }
    else if(distanceGauche > distanceDroite) //Si la distance gauche
                                       //est plus grande que la distance droite
    {
      gauche();
    mesurerDistanceGauche();
    delay(delay_time);
    mesurerDistanceDroite();
    delay(delay_time);
    }
    else if(distanceGauche <= distanceDroite) //Si la distance gauche est plus petite 
                                                //ou égale à la distance droite
    {
       droite();
    mesurerDistanceGauche();
    delay(delay_time);
    mesurerDistanceDroite();
    delay(delay_time);
    }
  }
  else //Si la distance avant est de plus de 25cm
  {
   avancer();
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  modeUltrason();
}
