// Programm zum Umrechnen von Grad Celsius in Grad Fahrenheit
// Autor: Fabian Prestros
// Datum: 17.08.2020

#include <stdio.h>
#include <math.h>

struct array { double matrix[2][10000]; };

double einlesen(char koef[32])
{
	int chk;
	double zahl;

	do													// In einer Schleife einlesen, bis eine korrekte Zahl eingelesen wurde
	{
		printf("%s = ", koef);
		chk = scanf_s("%lf", &zahl);
		while (getchar() != '\n');						// Tastaturpuffer leeren.
		if (chk == 0)									// Fehlermeldung, wenn scanf_s meldet, dass keine Ganze Zahl eingegeben wurde
			printf("Bite geben Sie eine Ganze Zahl ein!\n");
	} while (chk == 0);									// Schleifendurchlauf, bis kein Fehler mehr vorliegt.

	return zahl;
}

struct array erzeugen(double min, double max, double schritt)
{
	struct array temp;
	double c, f;
	int i = 1;

	// Grad Celsius in Grad Fahrenheit umrechnen und in einem 2-dimensionalen Array abspeichern
	for (c = min; c <= max; c = c + schritt)
	{
		temp.matrix[0][i] = c;
		f = 1.8 * c + 32;
		temp.matrix[1][i] = f;
		i++;
	}
	temp.matrix[0][0] = i;								// Anzahl der Rechenergebnisse in das 1. Element des Arrays abspeichern
	return temp;
}

void ausgabe(struct array zahl)
{
	int i;
	
	// Rechenergebnisse aus Array an den Standardoutput ausgeben
	for (i = 1; i < zahl.matrix[0][0]; i++)
		printf("%.3lf \xF8 \bC\t%.3lf \xF8 \bF\n", zahl.matrix[0][i], zahl.matrix[1][i]);
}

int main(void)
{
	double min, max, schritt;
	struct array fahrenheit;

	do
	{
		// Wertebereich und Schrittweite der Berechnung vom Nutzer abfragen
		min = einlesen("Niedrigste Temperatur in Celsius");
		max = einlesen("H\x94 \bchste Temperatur in Celsius");
		schritt = einlesen("Schrittweite");

		// Eingabeprüfung
		if (max < min)
			printf("Kleinste Temperatur muss kleiner als die gr\x94\xe1te Temperatur sein.\n");
		if (min < -273.15)
			printf("Die niedrigste Temperatur muss gr\x94\xe1 \ber als die Absolute Temperatur von -273.15 \xF8 \bC sein!\n");
		if (trunc((max - min) / schritt + 2) > 10000)
			printf("Es k\x94nnen nur maximal 10000 Temperaturen umgerechnet werden.\n");
	} while ((max < min) || (min < -273.15) || (trunc((max - min) / schritt + 2) > 10000));
	
	fahrenheit = erzeugen(min, max, schritt);
	ausgabe(fahrenheit);
}