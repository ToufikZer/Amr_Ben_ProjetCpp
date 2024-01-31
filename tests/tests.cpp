#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>

#include "Inventory.hpp"
#include "TileMap.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "Obstacle.hpp"
#include "GameState.hpp"
#include "MainMenu.hpp"
#include "MapManager.hpp"
#include "Map.hpp"
#include "MiniJeu.hpp"
#include "Indoors.hpp"
#include "InGame_CarGameplay.hpp"
#include "Bagarre.hpp"
#include "FraudeGameplay.hpp"
#include "Explication.hpp"
#include "Item.hpp"
#include "Save.hpp"




/////////////////// enigme /////////////////////////////////

TEST_CASE("Enigme vérifierReponse retourne true si la réponse utilisateur est correcte") {
    sf::Font font;
    Enigme enigme("Quelle est la réponse ?", 42, font, 1);

    enigme.ajouterCaractere('4');
    enigme.ajouterCaractere('2');

    REQUIRE(enigme.verifierReponse() == true);
}

TEST_CASE("Enigme vérifierReponse retourne false si la réponse utilisateur est incorrecte") {
    sf::Font font; 
    Enigme enigme("Quelle est la réponse ?", 42, font, 2);

    enigme.ajouterCaractere('1');
    enigme.ajouterCaractere('0');

    REQUIRE(enigme.verifierReponse() == false);
}

TEST_CASE("Enigme vérifierReponse retourne false si la saisie utilisateur n'est pas un nombre") {
    sf::Font font;
    Enigme enigme("Quelle est la réponse ?", 42, font, 3);

    enigme.ajouterCaractere('a');
    enigme.ajouterCaractere('b');

    REQUIRE(enigme.verifierReponse() == false);
}

TEST_CASE("Enigme ajouterCaractere ne permet que les caractères ASCII") {
    sf::Font font; 
    Enigme enigme("Test", 123, font, 4);

    enigme.ajouterCaractere('A');
    enigme.ajouterCaractere(256); 

    REQUIRE(enigme.getId() == 4);
    REQUIRE(enigme.verifierReponse() == false); 
}

TEST_CASE("Enigme supprimerCaractere supprime le dernier caractère de la saisie utilisateur") {
    sf::Font font; 
    Enigme enigme("Test", 1, font, 5);

    enigme.ajouterCaractere('1');
    enigme.ajouterCaractere('2');

    enigme.supprimerCaractere();

    REQUIRE(enigme.verifierReponse() == true);
}


/////////////////// answer /////////////////////////////////

TEST_CASE("Le constructeur correctement l'instance") {
    Answer answer;

    REQUIRE(answer.getChoice().empty());
    REQUIRE(answer.getText().empty());
}


/////////////////// inventory /////////////////////////////////


TEST_CASE("Inventory addItem ajoute un objet à l'inventaire") {
   Inventory inventaire{Inventory()};    
    Item item("Sword", "A powerful weapon", 50, "knife.png");

    REQUIRE(inventaire.getItems().size() == 0);
    inventaire.addItem(item);
    REQUIRE(inventaire.getItems().size() == 1);
    REQUIRE(inventaire.getItems()[0].getName() == "Sword");
}

//////////////////// Save //////////////////////////////////////

TEST_CASE("Save création d'un objet Save avec des valeurs arbitraires") {
    Save save("GameState1", sf::Vector2f(10.0f, 20.0f), sf::Vector2u(1, 1), sf::Vector2u(100, 100), Inventory(), true, false);

    REQUIRE(save.getStateName() == "GameState1");
    REQUIRE(save.getPlayerPosition() == sf::Vector2f(10.0f, 20.0f));
    REQUIRE(save.getCurrentMap() == sf::Vector2u(1, 1));
    REQUIRE(save.getmapDimension() == sf::Vector2u(100, 100));
    REQUIRE(save.getGameStarted() == true);
    REQUIRE(save.getCombatWin() == false);
}

TEST_CASE("Save modification de l'attribut game_started") {
    Save save("GameState2", sf::Vector2f(5.0f, 10.0f), sf::Vector2u(2, 2), sf::Vector2u(150, 150), Inventory(), false, true);

    REQUIRE(save.getGameStarted() == false);

    save.setGameStarted(true);

    REQUIRE(save.getGameStarted() == true);
}