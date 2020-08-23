// Programm zum Umrechnen von Grad Celsius in Grad Fahrenheit und Ausgabe in eine HTML-Datei
// Autor: Fabian Prestros
// Datum: 23.08.2020

#include <stdio.h>
#include <math.h>

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

erzeugen(double min, double max, double schritt, double temp[2][10000])
{
	double c, f;
	int i = 1;

	// Grad Celsius in Grad Fahrenheit umrechnen und in einem 2-dimensionalen Array abspeichern
	for (c = min; c <= max; c = c + schritt)
	{
		temp[0][i] = c;
		f = 1.8 * c + 32;
		temp[1][i] = f;
		i++;
	}
	temp[0][0] = i;										// Anzahl der Rechenergebnisse in das 1. Element des Arrays abspeichern
}

void ausgabe(double zahl[2][10000])
{
	int i;

	// Rechenergebnisse aus Array an den Standardoutput ausgeben
	for (i = 1; i < zahl[0][0]; i++)
		printf("%.3lf \xF8 \bC\t%.3lf \xF8 \bF\n", zahl[0][i], zahl[1][i]);
}

void ausgabe_html(double zahl[2][10000])
{
	FILE* fp;											// Parameter "fp" gibt den Pfad der Datei auf der Festplatte an

	int i;

	fopen_s(&fp, "celsius2fahrenheit.html", "w");		// Öffnen der Datei "celsius2fahrenheit.html" zum Schreiben

	if (fp == NULL)
		printf("Datei konnte nicht ge\x94 \bffnet werden.\n");

	else
	{
		// Dateiheader der HTML-Datei schreiben
		fprintf(fp, "<html>\n");
		fprintf(fp, "\t<head>\n");
		fprintf(fp, "\t\t<title>Tabelle: Grad Celsius &harr; Grad Fahrenheit</title>\n");
		fprintf(fp, "\t</head>\n");
		fprintf(fp, "\t<body>\n");
		fprintf(fp, "\t\t<table border = 1>\n");

		// Rechenergebnisse aus Array in die HTML-Datei schreiben
		for (i = 1; i < zahl[0][0]; i++)
			fprintf(fp, "\t\t\t<tr><td>%.3lf &degC</td>\t<td>%.3lf &degF</td></tr>\n", zahl[0][i], zahl[1][i]);

		// HTML-Datei abschließen
		fprintf(fp, "\t\t</table>\n");
		fprintf(fp, "\t</body>\n");
		fprintf(fp, "</html>\n");

		printf("\nHTML-Datei wurde geschrieben.\n");	// Meldung, dass die HTML-Datei geschrieben wurde
	}
	
	fclose(fp);											// Schließen der erzeugten Datei
}

int main(void)
{
	double min, max, schritt;
	double fahrenheit[2][10000];

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



	erzeugen(min, max, schritt, fahrenheit);
	ausgabe(fahrenheit);
	ausgabe_html(fahrenheit);
}