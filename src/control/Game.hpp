#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "../model/Platform.hpp"
#include <vector>

#include "PlayerControl.hpp"
#include "../view/Layer.hpp"

// Spiel-Klasse: Hauptklasse für Fenster, Eingabe, Update und Rendering
class Game
{
public:
    Game();       // Konstruktor: Fenster und Steuerungen initialisieren
    void start(); // Spielschleife starten

private:
    bool input();          // Eingaben verarbeiten, true bei Fenster-Schließung
    void update(float dt); // Spiellogik aktualisieren
    void draw();           // Szene zeichnen

    sf::RenderWindow window; // SFML-Fenster
    sf::View view;           // Kamerasicht
    Layer game_layer;        // Zeichnungsebene

    PlayerControl player_control;    // Steuerung der Spielfigur
    std::vector<Platform> platforms; // Liste der Plattformen
};

#endif